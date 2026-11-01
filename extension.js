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
    ensureBinariesCompiled();

    // Кнопка приветствия в верхней панели редактора
    const helloCmd = vscode.commands.registerCommand('cbuster.helloWorld', () => {
        vscode.window.showInformationMessage('Hello, World! Команда C-Buster приветствует вас!');
    });

    context.subscriptions.push(helloCmd);
}

function deactivate() {}

module.exports = { activate, deactivate };