#include <stdio.h>

int main() {
    double m[3][3];
    double sum1 = 0, sum2 = 0;
    int m2[2][2];
    double res[2][2];
    char i, j, k;

    printf("Vvedite dannye 3x3:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%lf", &m[i][j]);
        }
    }

    for (i = 0; i < 3; i++) {
        sum1 += m[i][i];
    }

    for (i = 0; i < 3; i++) {
        sum2 += m[i][2 - i];
    }

    printf("Sum diagonal osnovi: %.2lf\n", sum1);
    printf("Sum diagona ne osnovnoi: %.2lf\n", sum2);

    printf("Vvedite dannye 2x2:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                res[i][j] += m2[i][k] * m2[k][j];
            }
        }
    }

    printf("2x2:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            printf("%.2lf ", res[i][j]);
        }
    }
    return 0;
}

