#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc < 3 || argv[1] == nullptr || argv[2] == nullptr) {
        printf("Ошибка: укажите режим (joke или ask) и номер от 1 до 5.\n");
        return 1;
    }

    int id = atoi(argv[2]);
    bool is_joke_mode = (strcmp(argv[1], "joke") == 0);
    bool is_ask_mode = (strcmp(argv[1], "ask") == 0);

    if (is_joke_mode) {
        switch (id) {
            case 1:
                printf("Шутка дня: Программист на C не боится темноты — он боится только разыменования nullptr!\n");
                break;
            case 2:
                printf("Шутка дня: git push --force в пятницу вечером заменяет три чашки крепкого кофе!\n");
                break;
            case 3:
                printf("Шутка дня: Настоящий программист на C всегда говорит free() после каждого malloc()!\n");
                break;
            case 4:
                printf("Шутка дня: В C23 добавили nullptr, но выход за границы массива все еще стреляет прямо в ногу!\n");
                break;
            default:
                printf("Шутка дня: Хороший комментарий в коде — как алиби на код-ревью!\n");
                break;
        }
        return 0;
    }

    if (is_ask_mode) {
        switch (id) {
            case 1:
                printf("Какое ключевое слово для нулевого указателя ввели в стандарте C23? | 1) nil | 2) nullptr | 3) none | 2\n");
                break;
            case 2:
                printf("Какая функция в языке C освобождает динамически выделенную память? | 1) delete() | 2) clear() | 3) free() | 3\n");
                break;
            case 3:
                printf("Какая команда Git создает новую ветку и сразу переключается на нее? | 1) git checkout -b | 2) git init | 3) git status | 1\n");
                break;
            case 4:
                printf("Что произойдет при записи в if (x = 5) вместо if (x == 5) в языке C? | 1) Ошибка компиляции | 2) Присваивание 5 и всегда истина | 3) Выход из программы | 2\n");
                break;
            default:
                printf("Какой символ нужен перед целочисленной переменной в функции scanf? | 1) Символ & (амперсанд) | 2) Символ * (звездочка) | 3) Символ # (решетка) | 1\n");
                break;
        }
        return 0;
    }

    printf("Неизвестная команда модуля викторины.\n");
    return 1;
}