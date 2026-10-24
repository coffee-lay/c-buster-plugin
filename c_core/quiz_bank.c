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

    return 0;
}