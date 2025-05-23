#include <stdio.h>

int main(){
	int num;
	printf("Vvedite 4islo: ");
	scanf("%d",&num);
	
	
	int tsifri[30];
	int count = 0;
	
	if (num == 0){
		tsifri[count++] = 0;
	
	} else{
		while (num > 0){
			tsifri[count++] = num % 10;
			num /= 10;
		}
	}
	
	int i;
	
	for(i = count - 1; i>=0; i--){
		printf("%d",tsifri[i]);
		if (i != 0) printf(" ");
	}
	printf(" => ");
	
	for(i = 0; i < count; i++ ){
		printf("%d", tsifri[i]);
		if (i != count - 1) printf(" ");
	}
	
	return 0;
}
