#include <stdio.h>

int main(void) {
    int arr[3] = {1, 2, 3};
    arr[3] = 42;
    printf("Элемент: %d\n", arr[0]);
    return 0;
}