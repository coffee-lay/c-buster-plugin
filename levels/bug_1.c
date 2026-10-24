#include <stdio.h>

int main(void) {
    int x = 0;
    if (x = 10) { // БАГ НА СТРОКЕ 5: присваивание = вместо сравнения ==
        printf("Значение x равно десяти!\n");
    }
    return 0;
}