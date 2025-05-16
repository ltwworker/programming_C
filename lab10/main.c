#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
int i;
#define MAX_IN_ARRAY(arr, n, max) \
    do { \
        max = arr[0]; \
        for (i = 1; i < n; i++) { \
            if (arr[i] > max) { \
                max = arr[i]; \
            } \
        } \
    } while(0)

int main() {
    char input[256];
    printf("Vvedite 4isla 4erez probel: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    int numbers[100];
    int count = 0;

    char *token = strtok(input, " ");
    while (token != NULL && count < 100) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    if (count == 0) {
        printf("Error\n");
        return 1;
    }

    int max_value;
    MAX_IN_ARRAY(numbers, count, max_value);

    printf("Max number: %d\n", max_value);

    return 0;
}

