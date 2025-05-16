#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char input[256];
    printf("Vvedite virazhenie: ");
    fgets(input, sizeof(input), stdin);

    double result = 0.0;
    int sign = 1;
    int i = 0;

    while (input[i] == ' ') i++;

    if (input[i] == '-') {
        sign = -1;
        i++;
    } else if (input[i] == '+') {
        sign = 1;
        i++;
    }

    while (input[i] != '\0' && input[i] != '\n') {
        while (input[i] == ' ') i++;

        double num = 0.0;
        int has_dot = 0;
        double frac = 0.1;
        int has_digit = 0;

        while ((isdigit(input[i]) || input[i] == '.') && input[i] != '\0') {
            if (input[i] == '.') {
                has_dot = 1;
                i++;
                continue;
            }
            has_digit = 1;
            if (!has_dot) {
                num = num * 10 + (input[i] - '0');
            } else {
                num = num + (input[i] - '0') * frac;
                frac /= 10;
            }
            i++;
        }

        result += sign * num;

        while (input[i] == ' ') i++;

        if (input[i] == '+') {
            sign = 1;
            i++;
        } else if (input[i] == '-') {
            sign = -1;
            i++;
        } else if (input[i] == '\0' || input[i] == '\n') {
            break;
        }
    }

    printf("Result: %.2lf\n", result);
    return 0;
}

