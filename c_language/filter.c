#include <stdio.h>
#include <stdlib.h>

int isEven(int n) {
    return n % 2 == 0;
}

int isOdd(int n) {
    return n % 2 == 1;
}

int filter(int* data, int size, int (*fp)(int), int* result, int result_size) {
    int i;
    int j = 0;
    for (i = 0; i < size; ++i) {
	if (fp(data[i])) { 
	    result[j++] = data[i];
	    if (j >= result_size) break;
	}
    }
    return j;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int result_even[5] = {};
    int result_odd[5] = {};
    
    printf("Original Array: ");
    for (i = 0; i < 10; ++i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    int evens = filter(numbers, sizeof(numbers) / sizeof(int), isEven, result_even, 5);
    int odds = filter(numbers, sizeof(numbers) / sizeof(int), isOdd, result_odd, 5);

    printf("Even Array: ");
    for (i = 0; i < evens; ++i) {
	printf("%d ", result_even[i]);
    }
    printf("\n");

    printf("Odd Array: ");
    for (i = 0; i < odds; ++i) {
	printf("%d ", result_odd[i]);
    }
    printf("\n");

    return 0;
}
