1
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    // Открываем файл для чтения даты
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }

    int day, month, year;
    fscanf(file, "%d.%d.%d", &day, &month, &year);
    fclose(file);

    // Получаем текущую дату
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    
    // Устанавливаем целевую дату
    struct tm target = {0};
    target.tm_year = year - 1900;
    target.tm_mon = month - 1;
    target.tm_mday = day;
    time_t target_time = mktime(&target);

    // Вычисляем разницу в секундах и переводим в дни
    double diff = difftime(target_time, now) / (60 * 60 * 24);
    int days = (int)diff;

    if (days > 0) {
        printf("Days until %02d.%02d.%d: %d\n", day, month, year, days);
    } else {
        printf("The date %02d.%02d.%d has already passed\n", day, month, year);
    }

    return 0;
}


2.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int m;
    printf("Enter matrix size (m): ");
    scanf("%d", &m);

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Создание матрицы m x m
    int matrix[m][m];
    
    // Заполнение матрицы случайными числами 0-9
    printf("Generated matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

3.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int size = 3; // Размер матрицы
    int attempts = 0;
    int found = 0;
    
    while (!found) {
        attempts++;
        
        // Создаем первую матрицу и считаем сумму
        int mat1[size][size], sum1 = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                mat1[i][j] = rand() % 10;
                sum1 += mat1[i][j];
            }
        }
        
        // Создаем вторую матрицу и считаем сумму
        int mat2[size][size], sum2 = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                mat2[i][j] = rand() % 10;
                sum2 += mat2[i][j];
            }
        }
        
        // Проверяем совпадение сумм
        if (sum1 == sum2) {
            found = 1;
            FILE *out = fopen("output.txt", "w");
            
            // Записываем первую матрицу
            fprintf(out, "Matrix 1 (sum = %d):\n", sum1);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    fprintf(out, "%d ", mat1[i][j]);
                }
                fprintf(out, "\n");
            }
            
            // Записываем вторую матрицу
            fprintf(out, "\nMatrix 2 (sum = %d):\n", sum2);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    fprintf(out, "%d ", mat2[i][j]);
                }
                fprintf(out, "\n");
            }
            
            fclose(out);
            printf("Found matrices with equal sum (%d) after %d attempts\n", sum1, attempts);
        }
    }
    
    return 0;
}

4.
#include <stdio.h>
#include <time.h>

void long_running_operation() {
    // Имитация долгой операции
    for (int i = 0; i < 100000000; i++);
}

int main() {
    clock_t start = clock();
    
    // Выполняем операции, время которых хотим замерить
    long_running_operation();
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Program execution time: %.3f seconds\n", time_taken);
    
    return 0;
}
