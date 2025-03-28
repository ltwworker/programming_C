#include <stdio.h>
#include <stdlib.h>

double** summa(double **m1, double **m2, int N) {
    double **result;
    int i, j;

    result = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        result[i] = (double*)malloc(N * sizeof(double));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}

double** vichitanie(double **m1, double **m2, int N) {
    double **result;
    int i, j;

    result = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        result[i] = (double*)malloc(N * sizeof(double));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return result;
}

double** ymozhenie(double **m1, double **m2, int N) {
    double **result;
    int i, j;

    result = (double**)malloc(N * sizeof(double*));
    for (i = 0; i < N; i++) {
        result[i] = (double*)malloc(N * sizeof(double));
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = m1[i][j] * m2[i][j];
        }
    }

    return result;
}

int main() {
    double **m1, **m2, **result;
    int N, i, j;
    char operation;
    char choice;
    
    do {

	    printf("Vvedite razmer matricy N: ");
	    scanf("%d", &N);
	
	    m1 = (double**)malloc(N * sizeof(double*));
	    for (i = 0; i < N; i++) {
	        m1[i] = (double*)malloc(N * sizeof(double));
	    }
	
	    m2 = (double**)malloc(N * sizeof(double*));
	    for (i = 0; i < N; i++) {
	        m2[i] = (double*)malloc(N * sizeof(double));
	    }
	
	    printf("\nVvedite elementy matricy m1:\n");
	    for (i = 0; i < N; i++) {
	        for (j = 0; j < N; j++) {
	            printf("m1[%d][%d]: ", i, j);
	            scanf("%lf", &m1[i][j]);
	        }
	    }
	
	    printf("\nVvedite elementy matricy m2:\n");
	    for (i = 0; i < N; i++) {
	        for (j = 0; j < N; j++) {
	            printf("m2[%d][%d]: ", i, j);
	            scanf("%lf", &m2[i][j]);
	        }
	    }
	
	    printf("\nVvedite znak operacii (+, -, *): ");
	    scanf(" %c", &operation);  
	
	    if (operation == '+') {
	        result = summa(m1, m2, N);
	    } else if (operation == '-') {
	        result = vichitanie(m1, m2, N);
	    } else if (operation == '*') {
	        result = ymozhenie(m1, m2, N);
	    } else {
	        printf("Nedopustimaya operaciya\n");
	        result = NULL;
	    }
	
	
	    if (result != NULL) {
	        printf("\nResultat:\n");
	        for (i = 0; i < N; i++) {
	            for (j = 0; j < N; j++) {
	                printf("%lf ", result[i][j]);
	            }
	            printf("\n");
	        }
	    }
	
	    for (i = 0; i < N; i++) {
	        free(m1[i]);
	        free(m2[i]);
	        if (result != NULL) {
	            free(result[i]);
	        }
	    }
	    free(m1);
	    free(m2);
	    if (result != NULL) {
	        free(result);
	        
	    }
	    printf("\nHotite prodolzhit? (y/n)?:\n");
	    scanf(" %c",&choice);
	    printf("\n");
    
	} while (choice == 'y' || choice == 'Y');
	
	printf("\nPoka\n");
    return 0;
}

