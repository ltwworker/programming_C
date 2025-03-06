#define SETBIT(b, k) ((0200 >> (k)) | (b))
#define CLRBIT(b, k) (~(0200 >> (k)) & (b))
#define TESTBIT(b, k) (((0200 >> (k)) & (b)) ? 1 : 0)
unsigned char nat[100000000];
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG
//#undef DEBUG

int main(int argc, char *argv[])
{  
    long N;
    printf("vvedite N:\n");
    scanf("%ld", &N);
  
    int i, j;

    for (i = 0; i < N / 8; i++)
        nat[i] = 0377; 
  
    #ifdef DEBUG
    nat[0] = 0; 
    nat[0] = SETBIT(nat[0], 4);
    nat[0] = SETBIT(nat[0], 5);
    printf("%x\n", nat[0]);
  
    for (i = 0; i < 8; i++)
        putchar(TESTBIT(nat[0], i) ? '1' : '0');
    putchar('\n');
    #endif

    nat[0] = CLRBIT(nat[0], 0);
    nat[0] = CLRBIT(nat[0], 1);

    long sqrtN = (long)sqrt(N);
    for (i = 2; i <= sqrtN; i++) {
        if (TESTBIT(nat[i / 8], i % 8)) {
            for (j = i * i; j <= N; j += i) {
                nat[j / 8] = CLRBIT(nat[j / 8], j % 8);
            }
        }
    }

    printf("Prostye chisla do %ld:\n", N);
    for (i = 2; i <= N; i++) {
        if (TESTBIT(nat[i / 8], i % 8)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
