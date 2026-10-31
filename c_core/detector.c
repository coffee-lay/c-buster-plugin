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
    int current_depth = 0;
    int max_depth = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            line_num++;
        } else if (ch == '{') {
            current_depth++;
            if (current_depth > max_depth) {
                max_depth = current_depth;
            }
        } else if (ch == '}') {
            current_depth--;
            if (current_depth < 0) {
                current_depth = 0;
            }
        }
    }

    fclose(fp);
    printf("Максимальная глубина вложенности: %d\n", max_depth);
    return 0;
}
