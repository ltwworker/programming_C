#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* ������� 1
	�������� ������������ ���������� a, b � � � ������ �� ��������. �����������, ��� a, b, c ���� ������������ ����������� ��������� ������� �� ������� �������� �� ������ �1, �2.
	������� ��������� ����� �������� �������������, ��� ������� ����� ����� ������������.
	����������. ��� ���������� ������� ����������� ������� ���������� ����-������� ����� (���������� � �������), � ��� �� ����� ������ �� �������.
	���������� � ������� - ���������� ������������ ����	 math.h � ������-���� ������� pow, ������ ���������� �������� ������ ���� ���������� ��������, � ������ - �������, ��� ������ double.
	����� ������ - ������������ ���� stdio.h, ������� printf, ������ ���������� �������� ��������� ������, � ����������� - ����������, �������� ������� ������-���� �������.
	�������� ����� ��������� � � ���������� ���������� ��\���?
*/
int main(int argc, char *argv[]) {
	double a,b,c;
	double x1,x2,d;
	char choice;
	
	do{				
		printf("Vvedite a:\n");
		scanf("%lf", &a);
		printf("Vvedite b:\n");
		scanf("%lf", &b);
		printf("Vvedite c:\n");
		scanf("%lf", &c);
		
		
		d = pow(b,2) - 4*a*c;
		printf("d = %1f \n",d);
		
		if (d>0){
			x1 = -b + sqrt(d)/(2*a);
			x2 = -b - sqrt(d)/(2*a);
		
			printf("x1 = %1f \n", x1);
			printf("x2 = %2f \n", x2);
		}
		
		if (d==0){
			x1 = -b + sqrt(d)/(2*a);
			printf("x1 = %1f \n", x1);
		}
		
		if (d<0) printf("Korney net! \n");
	
		printf("Hotite prodolzit? (y/n): ");
		scanf(" %c", &choice);
		
	}while (choice == 'y' || choice == 'Y');

    printf("Vsego dobrogo!\n");
    return 0;
}
