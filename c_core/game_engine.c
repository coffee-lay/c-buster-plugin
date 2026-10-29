#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Функция чтения текущих очков
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

// Функция сохранения новых очков игрока
void save_score(int score) {
    FILE *fp = fopen("score.txt", "w");
    if (fp != nullptr) {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}

// Определение ранга
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

    bool is_status_mode = (strcmp(argv[1], "status") == 0);
    if (is_status_mode) {
        int score = read_score();
        printf("Очки: %d | Ранг: %s\n", score, get_rank(score));
        return 0;
    }

    bool is_check_mode = (strcmp(argv[1], "check_bug") == 0);
    if (is_check_mode) {
        if (argc < 3 || argv[2] == nullptr) {
            printf("Ошибка: не передан номер строки для проверки.\n");
            return 1;
        }

        int clicked_line = atoi(argv[2]);
        bool is_hit = (clicked_line == 5);

        if (is_hit) {
            int new_score = read_score() + 10;
            save_score(new_score);
            printf("БАГ ОБЕЗВРЕЖЕН на строке 5! (+10 очков) | Всего очков: %d | Достижение: %s\n",
                   new_score, get_rank(new_score));
        } else {
            printf("Мимо! На строке %d багов нет. Внимательнее изучите условия if, scanf и границы массивов!\n",
                   clicked_line);
        }
        return 0;
    }

    printf("Неизвестная команда игрового движка.\n");
    return 1;
}
