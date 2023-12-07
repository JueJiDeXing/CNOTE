#include <stdio.h>

void printArray(const int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(arr + i * cols + j));
        }
        printf("\n");
    }
}

int main() {
    int arr[3][4] = {{1, 2,  3,  4},
                     {5, 6,  7,  8},
                     {9, 10, 11, 12}};
    printArray((int *) arr, 3, 4);
    return 0;
}

