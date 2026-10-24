#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        return 1;
    }

    int total_lines = 0;
    int empty_lines = 0;
    int comment_lines = 0;
    int code_lines = 0;
    int malloc_count = 0;
    int free_count = 0;

    char line[1024];

    while (fgets(line, sizeof(line), fp) != nullptr) {
        total_lines++;
        bool is_empty = true;
        int i = 0;

        while (line[i] != '\0') {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\r' && line[i] != '\n') {
                is_empty = false;
                break;
            }
            i++;
        }

        if (is_empty) {
            empty_lines++;
        } else if ((line[i] == '/' && line[i + 1] == '/') ||
                   (line[i] == '/' && line[i + 1] == '*') ||
                   (line[i] == '*')) {
            comment_lines++;
        } else {
            code_lines++;
            if (strstr(line, "malloc(") != nullptr) {
                malloc_count++;
            }
            if (strstr(line, "free(") != nullptr) {
                free_count++;
            }
        }
    }

    fclose(fp);

    if (malloc_count == free_count) {
        printf("Анализ файла: Код: %d стр. | Комментарии: %d стр. | Пустые: %d стр. | Память (malloc/free): %d/%d [Статус: ОК, утечек нет]\n",
               code_lines, comment_lines, empty_lines, malloc_count, free_count);
    } else {
        printf("Анализ файла: Код: %d стр. | Комментарии: %d стр. | Пустые: %d стр. | Память (malloc/free): %d/%d [ВНИМАНИЕ: Возможна утечка памяти!]\n",
               code_lines, comment_lines, empty_lines, malloc_count, free_count);
    }

    return 0;
}