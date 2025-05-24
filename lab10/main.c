#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(arr, size) ({ \
	int i;\
    int max = arr[0]; \
    for (i = 1; i < size; i++) { \
        if (arr[i] > max) max = arr[i]; \
    } \
    max; \
})

#define ARIFM(arr, size) ({\
    long sum = 0;\
    int i;\
    for (i = 0; i < size; i++) sum += (arr)[i];\
    (double)sum / (size);\
})

int main() {
    char stroka[100];
    printf("Vvedite 4isla 4erez probel: ");
    fgets(stroka, sizeof(stroka), stdin);

    int numbers[100];
    int count = 0;

    char *razd = strtok(stroka, " ");
    while (razd != NULL) {
        numbers[count++] = atoi(razd);
        razd = strtok(NULL, " ");
    }

    if (count > 0) {
        int maximum = MAX(numbers, count);
        printf("max: %d\n", maximum);
    } else {
        printf("Chisla ne vvedeny.\n");
    }
    
   if (count > 0){
   	double arif = ARIFM(numbers,count);
   	printf("sred arifm: %.12f\n", arif);
   }
    
    
    

    return 0;
}
