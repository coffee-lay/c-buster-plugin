#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Проверяем, передан ли путь к файлу в аргументах командной строки
    if (argc < 2) {
        printf("Ошибка: не указан путь к файлу для анализа!\n");
        return 1;
    }

    // Открываем файл для чтения и проверяем указатель через nullptr (стандарт C23)
    FILE *fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        printf("Ошибка: не удалось открыть файл %s\n", argv[1]);
        return 1;
    }

    // Закрываем файл и завершаем программу
    fclose(fp);
    return 0;
}