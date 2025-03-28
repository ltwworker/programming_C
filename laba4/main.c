#include <stdio.h>
#include <math.h>

double perimeter(double a, double b, double c) {
    return a + b + c;
}

double ploshad(double a, double b, double c) {
    double p = perimeter(a, b, c) / 2; 
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
    double a, b, c;
    
    printf("Vvedite dlini storon:\n");
    
    while(1) {
        printf("storona a: ");
        scanf("%lf", &a);
        printf("storona b: ");
        scanf("%lf", &b);
        printf("storona c: ");
        scanf("%lf", &c);
        
        
        if(a > 0 && b > 0 && c > 0 &&
           a + b > c &&
           a + c > b &&
           b + c > a) {
            break;
        }
        printf("Oshibka! Eto ne dlini storon\n\n");
    }
    

    printf("\nRes:\n");
    printf("Perimeter: %.2f\n", perimeter(a, b, c));
    printf("Ploshad: %.2f\n", ploshad(a, b, c));
    
    return 0;
}

