#include <stdio.h>

void forward(int n){
	if (n < 10){
		printf("%d\n",n);
	}else{
		forward(n / 10);
		printf("%d\n", n % 10);
	}
}

void bacward(int n){
	if (n < 10){
		printf("%d\n",n);
	}else{
		printf("%d\n", n % 10);
		bacward(n / 10);
	}
}




int main(){
	int n;
	printf("Vvedite 4islo: ");
	scanf("%d", &n);
	
	forward(n);
	printf("\n");
	
	bacward(n);
	printf("\n");
	
	return 0;
}
