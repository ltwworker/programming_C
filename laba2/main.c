#include <stdio.h>

int main() {	
	int x,y;
	printf("vvedite razmer X x X: \n" );
	scanf("%d", &x);

    double m[x][x];
    double sum1 = 0, sum2 = 0;

    char i, j, k;

	
    printf("Vvedite dannye %dx%d:\n",x);
    for (i = 0; i < x; i++) {
        for (j = 0; j < x; j++) {
            scanf("%lf", &m[i][j]);
        }
    }

    for (i = 0; i < x; i++) {
        sum1 += m[i][i];
    }

    for (i = 0; i < x; i++) {
        sum2 += m[i][x - 1 - i];
    }

    printf("Sum diagonal osnovi: %.2lf\n", sum1);
    printf("Sum diagona ne osnovnoi: %.2lf\n", sum2);
	
	printf("vvedite razmer y x y: \n" );
	scanf("%d", &y);
    int m2[y][y];
    double res[y][y];
		
    printf("Vvedite dannye 2x2:\n");
    for (i = 0; i < y; i++) {
        for (j = 0; j < y; j++) {
            scanf("%d", &m2[i][j]);
        }
    }

    for (i = 0; i < y; i++) {
        for (j = 0; j < y; j++) {
            for (k = 0; k < y; k++) {
                res[i][j] += m2[i][k] * m2[k][j];
            }
        }
    }

    printf("2x2:\n");
    for (i = 0; i < y; i++) {
        for (j = 0; j < y; j++) {
            printf("%.2lf ", res[i][j]);
        }
    }
    return 0;
}
