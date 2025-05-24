#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(arr, size) ({ \
    int max_val = arr[0]; \
    for (int i = 1; i < size; i++) { \
        if (arr[i] > max_val) max_val = arr[i]; \
    } \
    max_val; \
})

int main() {
    char stroka[100];
    printf("Vvedite 4isla 4erez probel: ");
    fgets(stroka, sizeof(stroka), stdin);
    stroka[strcspn(stroka, "\n")] = '\0';

    int numbers[100];
    int count = 0;

    char *razd = strtok(stroka, " ");
    while (razd != NULL && count < 100) {
        numbers[count++] = atoi(razd);
        razd = strtok(NULL, " ");
    }

    if (count > 0) {
        int maximum = MAX(numbers, count);
        printf("max: %d\n", maximum);
    } else {
        printf("Chisla ne vvedeny.\n");
    }

    return 0;
}
