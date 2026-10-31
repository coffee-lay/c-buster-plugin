#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == nullptr) {
        printf("Ошибка: не указан путь к файлу для анализа.\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        printf("Ошибка: не удалось открыть файл %s.\n", argv[1]);
        return 1;
    }

    int total_lines = 0;
    int empty_lines = 0;
    int comment_lines = 0;
    int code_lines = 0;
    char line[1024];

    while (fgets(line, sizeof(line), fp) != nullptr) {
        total_lines++;

        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') {
            i++;
        }

        bool is_empty = (line[i] == '\n' || line[i] == '\r' || line[i] == '\0');
        if (is_empty) {
            empty_lines++;
            continue;
        }

        bool is_comment = (
            (line[i] == '/' && line[i + 1] == '/') ||
            (line[i] == '/' && line[i + 1] == '*') ||
            (line[i] == '*')
        );

        if (is_comment) {
            comment_lines++;
        } else {
            code_lines++;
        }
    }

    fclose(fp);
    printf("Код: %d стр. | Комментарии: %d стр. | Пустые: %d стр.\n", code_lines, comment_lines, empty_lines);
    return 0;
}
