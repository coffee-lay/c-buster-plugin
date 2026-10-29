#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Игровой движок и система достижений C-Buster (Стандарт C23, LLVM Clang)

// Функция чтения текущих очков игрока из файла score.txt
int read_score(void) {
    FILE *fp = fopen("score.txt", "r");
    if (fp == nullptr) {
        return 0;
    }
    int score = 0;
    if (fscanf(fp, "%d", &score) != 1) {
        score = 0;
    }
    fclose(fp);
    return score;
}

// Функция сохранения новых очков игрока в файл score.txt
void save_score(int score) {
    FILE *fp = fopen("score.txt", "w");
    if (fp != nullptr) {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}

// Определение игрового ранга (бейджа достижений) по очкам
const char* get_rank(int score) {
    if (score >= 40) {
        return "Божество Указателей";
    } else if (score >= 20) {
        return "Охотник за багами";
    }
    return "Стажёр SimpleIT";
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == nullptr) {
        printf("Ошибка: укажите режим работы (check_bug или status).\n");
        return 1;
    }

    // Режим вывода текущего счета и ранга для статус-бара VS Code
    bool is_status_mode = (strcmp(argv[1], "status") == 0);
    if (is_status_mode) {
        int score = read_score();
        printf("Очки: %d | Ранг: %s\n", score, get_rank(score));
        return 0;
    }

    return 0;
}
