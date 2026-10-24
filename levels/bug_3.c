#include <stdio.h>

int main(void) {
    int arr[3] = {1, 2, 3};
    arr[3] = 42; // БАГ НА СТРОКЕ 5: выход за границу массива (индексы только от 0 до 2)
    printf("Элемент: %d\n", arr[0]);
    return 0;
}