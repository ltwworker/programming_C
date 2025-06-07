#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int vector_size, i;
	
	printf("Vvedite razmer vektora N: ");
	scanf("%d", &vector_size);
	
	if (vector_size <= 0) { 
		printf("Erorr N.\n");
		return 1; 
	}
	
	FILE* file = fopen("input.txt", "w"); 
	if (file == NULL) { 
		printf("Error file.\n");
		return 1;
	}
	
	srand(time(NULL));
	
	
	for (i = 0; i < vector_size; ++i) { 
		int random_number = rand() % 100; 
		fprintf(file, "%d ", random_number); 
	}
	
	fclose(file); 
	return 0; 

	
}
