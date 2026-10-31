#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == nullptr) {
        printf("Ошибка: не указан путь к файлу для проверки вложенности.\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        printf("Ошибка: не удалось открыть файл %s.\n", argv[1]);
        return 1;
    }

    int ch = 0;
    int line_num = 1;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            line_num++;
        }
    }

    fclose(fp);
    printf("Файл проверен. Всего строк: %d\n", line_num);
    return 0;
}