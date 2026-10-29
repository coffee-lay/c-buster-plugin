#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 

//Function of game score
int read_score(void) {
    FILE *fp = fopen("score.txt", "r");
    // Используем ключевое слово nullptr из стандарта C23
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

//Function of saving game score
void save_score(int score) {
    FILE *fp = fopen("score.txt", "w");
    if (fp != nullptr) {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argv[1] == nullptr) {
        printf("Ошибка: укажите режим работы (check_bug или status).\n");
        return 1;
    }

    int current_score = read_score();
    printf("Текущие очки игрока: %d\n", current_score);
    return 0;
}
