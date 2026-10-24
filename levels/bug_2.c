#include <stdio.h>

int main(void) {
    int age = 0;
    scanf("%d", age); // БАГ НА СТРОКЕ 5: забыт оператор взятия адреса & перед age
    printf("Ваш возраст: %d\n", age);
    return 0;
}