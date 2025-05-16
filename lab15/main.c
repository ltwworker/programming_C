#include <stdio.h>

int main() {
    int N,i;
    printf("Vvedit num: ");
    scanf("%d", &N);

    int temp = N;
    int digits[10];
    int count = 0;

    while (temp > 0) {
        digits[count] = temp % 10;
        temp /= 10;
        count++;
    }

    for ( i = count - 1; i >= 0; i--) {
        printf("%d", digits[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");

    for ( i = 0; i < count; i++) {
        printf("%d", digits[i]);
        if (i < count - 1) printf(" ");
    }
    printf("\n");

    return 0;
}

