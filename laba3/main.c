#include <stdio.h>

#define y 80

int main() {
    char str[y + 1];

    printf("Vvedite stroky: ");
    fgets(str, y + 1, stdin);
    

    int j;
    for (j = 0; str[j]; j++) {
        if (str[j] == 'a') str[j] = 'A';
        else if (str[j] == 'b') str[j] = 'B';
    }

    printf("%s\n", str);

    return 0;
}

