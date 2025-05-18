#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
   char stroka[256];
   
   printf("Vvedite stroky: ");
   scanf("%[^\n]",stroka);
   
   double result = 0.0;
   char operator = '+';
   
   int i = 0;
   while(stroka[i] != '\0'){
   	if (stroka[i] == ' '){
   		i++;
   		continue;
	   }
	   
	   if (stroka[i] == '+' || stroka[i] == '-'){
	   	operator = stroka[i];
	   	i++;
	   	continue;
	   }
	   
	   char num_stroka[50];
	   int j = 0;
	   
	   if (stroka[i] == '-'){
	   	
	   	num_stroka[j++] = stroka[i++];
	   	
	   }
	   
	   while(isdigit(stroka[i]) || stroka[i] == '.'){
	   	num_stroka[j++] = stroka[i++];
	   }
	   num_stroka[j] = '\0';
	   
	   double num = atof(num_stroka);
	   
	   if (operator == '+'){
	   	result += num;
	   } else if (operator == '-'){
	   	result -= num;
	   	
	   }
   }
   
   	printf("Result: %lf", result);
    return 0;
}
