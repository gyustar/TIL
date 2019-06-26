#include <stdio.h>
#include <stdlib.h>

int isEven(int n) {
    return n % 2 == 0;
}

int isOdd(int n) {
    return n % 2 == 1;
}

int* filter(int* data, int size, int (*fp)(int)) {
    int* result = (int*) malloc(sizeof(int) * size);
    int i;
    int j = 0;
    for (i = 0; i < size; ++i) {
	if (fp(data[i])) { 
	    result[j++] = data[i];
	}
    }
    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    
    printf("Original Array: ");
    for (i = 0; i < 10; ++i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    int* evens = filter(numbers, sizeof(numbers) / sizeof(int), isEven);
    int* odds = filter(numbers, sizeof(numbers) / sizeof(int), isOdd);

    printf("Even Array: ");
    for (i = 0; i < 5; ++i) {
	printf("%d ", evens[i]);
    }
    printf("\n");

    printf("Odd Array: ");
    for (i = 0; i < 5; ++i) {
	printf("%d ", odds[i]);
    }
    printf("\n");

    free(evens);
    free(odds);
    return 0;
}
