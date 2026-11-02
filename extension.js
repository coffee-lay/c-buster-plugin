const vscode = require('vscode');
const path = require('path');
const fs = require('fs');
const { execFile, execSync } = require('child_process');

// Проверка и компиляция 4 сишных модулей при запуске плагина
function ensureBinariesCompiled() {
    const isWin = process.platform === 'win32';
    const ext = isWin ? '.exe' : '';
    const tools = ['analyzer', 'detector', 'game_engine', 'quiz_bank'];

    for (const tool of tools) {
        const srcPath = path.join(__dirname, 'c_core', `${tool}.c`);
        const binPath = path.join(__dirname, 'c_core', `${tool}${ext}`);

        if (fs.existsSync(srcPath) && !fs.existsSync(binPath)) {
            try {
                const staticFlag = isWin ? '-static' : '';
                execSync(`clang -std=c23 ${staticFlag} "${srcPath}" -o "${binPath}"`, { cwd: __dirname });
            } catch (err) {
                try {
                    execSync(`clang -std=c23 "${srcPath}" -o "${binPath}"`, { cwd: __dirname });
                } catch (innerErr) {
                    console.error(`Ошибка компиляции ${tool}:`, innerErr);
                }
            }
        }
    }
}

// Вызов скомпилированного бинарника и чтение его вывода из stdout
function runCoreTool(toolName, args, callback) {
    const isWin = process.platform === 'win32';
    const ext = isWin ? '.exe' : '';
    const binPath = path.join(__dirname, 'c_core', `${toolName}${ext}`);

    execFile(binPath, args, { cwd: __dirname, encoding: 'utf8' }, (error, stdout) => {
        if (error && !stdout) {
            vscode.window.showErrorMessage(`Ошибка запуска модуля ${toolName}: проверьте компиляцию через clang.`);
            return;
        }
        callback((stdout || '').trim());
    });
}

function activate(context) {
    // 1. Компилируем модули при старте плагина
    ensureBinariesCompiled();

    // 2. Создаем элемент в статус-баре: Таймер Кодера + Ранг игрока
    const statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Left, 100);
    statusBarItem.command = 'cbuster.resetTimer';
    statusBarItem.tooltip = 'C-Buster: Нажмите, чтобы сбросить Таймер Кодера';
    context.subscriptions.push(statusBarItem);

    let secondsElapsed = 0;
    let currentRankStatus = 'Очки: 0 | Ранг: Стажёр SimpleIT';

    // Запрос актуальных очков и ранга из движка game_engine
    function refreshRankStatus() {
        runCoreTool('game_engine', ['status'], (output) => {
            if (output) {
                currentRankStatus = output;
            }
        });
    }

    refreshRankStatus();
    statusBarItem.show();

    // Секундный таймер работы в IDE
    const timerInterval = setInterval(() => {
        secondsElapsed++;
        const mins = String(Math.floor(secondsElapsed / 60)).padStart(2, '0');
        const secs = String(secondsElapsed % 60).padStart(2, '0');
        statusBarItem.text = `$(clock) Время кода: ${mins}:${secs} | $(trophy) ${currentRankStatus}`;
    }, 1000);

    context.subscriptions.push({ dispose: () => clearInterval(timerInterval) });

    // Сброс таймера по клику на статус-бар
    const resetTimerCmd = vscode.commands.registerCommand('cbuster.resetTimer', () => {
        secondsElapsed = 0;
        vscode.window.showInformationMessage('C-Buster: Таймер Кодера сброшен! Не забывайте делать перерыв.');
    });

    // 3. Кнопка приветствия в верхней панели Toolbar
    const helloCmd = vscode.commands.registerCommand('cbuster.helloWorld', () => {
        vscode.window.showInformationMessage('Hello, World! Команда C-Buster приветствует вас!');
    });

    // 4. Кнопка выбора и открытия учебного уровня с багом
    const startGameCmd = vscode.commands.registerCommand('cbuster.startGame', async () => {
        const levels = [
            { label: 'Уровень 1: Ловушка в условии if (bug_1.c)', file: 'bug_1.c' },
            { label: 'Уровень 2: Потерянный адрес в scanf (bug_2.c)', file: 'bug_2.c' },
            { label: 'Уровень 3: Выход за границу массива (bug_3.c)', file: 'bug_3.c' }
        ];
        const picked = await vscode.window.showQuickPick(levels, {
            placeHolder: 'Выберите учебный уровень игры «Найди баг в C»:'
        });
        if (picked) {
            const levelPath = path.join(__dirname, 'levels', picked.file);
            const doc = await vscode.workspace.openTextDocument(levelPath);
            await vscode.window.showTextDocument(doc);
            vscode.window.showInformationMessage('Найдите строку с ошибкой, кликните по ней правой кнопкой мыши и выберите «C-Buster: Тут баг!»');
        }
    });

    // 5. Пункт контекстного меню №1: Проверка выбранной строки на баг
    const checkBugCmd = vscode.commands.registerCommand('cbuster.checkBug', () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        const clickedLine = editor.selection.active.line + 1;
        const filePath = editor.document.fileName;

        runCoreTool('game_engine', ['check_bug', String(clickedLine), filePath], (output) => {
            if (output.includes('ОБЕЗВРЕЖЕН')) {
                vscode.window.showInformationMessage(output);
            } else {
                vscode.window.showWarningMessage(output);
            }
            refreshRankStatus();
        });
    });

    // 6. Пункт контекстного меню №2: Подсчет строк и памяти
    const analyzeCmd = vscode.commands.registerCommand('cbuster.analyzeFile', () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        const filePath = editor.document.fileName;
        runCoreTool('analyzer', [filePath], (output) => {
            vscode.window.showInformationMessage(output);
        });
    });

    // 7. Пункт контекстного меню №3: Детектор Спагетти-кода
    const detectorCmd = vscode.commands.registerCommand('cbuster.detectSpaghetti', () => {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        const filePath = editor.document.fileName;
        runCoreTool('detector', [filePath], (output) => {
            if (output.includes('Осторожно')) {
                vscode.window.showWarningMessage(output);
            } else {
                vscode.window.showInformationMessage(output);
            }
        });
    });

    // 8. Пункт контекстного меню №4: Викторина и Шутка дня
    const quizCmd = vscode.commands.registerCommand('cbuster.quizAndJoke', async () => {
        const modePick = await vscode.window.showQuickPick(
            [
                { label: '1) Получить профильную шутку от коллеги', mode: 'joke' },
                { label: '2) Пройти вопрос викторины по C23 и Git (+10 очков)', mode: 'ask' }
            ],
            { placeHolder: 'C-Buster: Выберите режим отдыха и проверки знаний' }
        );
        if (!modePick) {
            return;
        }

        const randomId = String(Math.floor(Math.random() * 5) + 1);

        if (modePick.mode === 'joke') {
            runCoreTool('quiz_bank', ['joke', randomId], (output) => {
                vscode.window.showInformationMessage(output);
            });
        } else {
            runCoreTool('quiz_bank', ['ask', randomId], async (output) => {
                const parts = output.split('|').map(s => s.trim());
                if (parts.length < 5) {
                    vscode.window.showInformationMessage(output);
                    return;
                }
                const question = parts[0];
                const options = [parts[1], parts[2], parts[3]];
                const correctIndex = parseInt(parts[4], 10) - 1;

                const answer = await vscode.window.showQuickPick(options, {
                    placeHolder: question
                });
                if (!answer) {
                    return;
                }
                if (options.indexOf(answer) === correctIndex) {
                    runCoreTool('game_engine', ['check_bug', '5', 'quiz_bonus'], () => {
                        refreshRankStatus();
                        vscode.window.showInformationMessage('ВЕРНО! Вы получаете +10 очков к рангу.');
                    });
                } else {
                    vscode.window.showWarningMessage(`Неверно! Правильный ответ: ${options[correctIndex]}`);
                }
            });
        }
    });

    context.subscriptions.push(
        resetTimerCmd,
        helloCmd,
        startGameCmd,
        checkBugCmd,
        analyzeCmd,
        detectorCmd,
        quizCmd
    );
}

function deactivate() {}

module.exports = { activate, deactivate };
