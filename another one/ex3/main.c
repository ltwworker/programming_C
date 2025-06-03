#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Макрос для проверки установленного бита
#define ISBIT(n, x) (((01 << (n)) & (x)) ? 1 : 0)
// Максимальное количество глифов
#define MAX_GLYPHS 4000
// Порог схожести глифов
#define SIMILARITY_THRESHOLD 0.1

// Структура для хранения информации об изображении глифа
typedef struct img {
    int w;              // Ширина
    int h;              // Высота
    int dx;             // Смещение по горизонтали
    int count;          // Количество черных пикселей
    int id;             // Идентификатор
    int bytes;          // Количество байт данных
    double density;     // Плотность черных пикселей
    int diam;           // Диаметр
    int perim;          // Периметр
    int conn;           // Связность
    unsigned char *data; // Данные изображения
} IMG;

// Прототипы функций
int popcnt8(unsigned char i);
IMG *init_img(int id, int w, int h);
IMG *load_img(int id, char *File);
int ISPIX(IMG *glyph, int i, int j);
void calculate_stats(IMG *glyph);
void print_glyph_info(IMG *glyph);
double compare_glyphs(IMG *g1, IMG *g2);
void find_similar_glyphs(IMG **glyphs, int count);

// Глобальный массив глифов и счетчик
IMG *G[MAX_GLYPHS];
int N = 0;

int main(int argc, char *argv[]) {
    // Проверка аргументов командной строки
    if (argc < 2) {
        printf("Usage: %s <glyph_file1> <glyph_file2> ...\n", argv[0]);
        return 1;
    }

    N = argc - 1;
    if (N > MAX_GLYPHS) {
        printf("Too many glyphs. Maximum is %d\n", MAX_GLYPHS);
        return 1;
    }

    // Загрузка глифов из файлов
    for (int i = 1; i < argc; i++) {
        if (i-1 >= MAX_GLYPHS) break;
        G[i-1] = load_img(i-1, argv[i]);
        if (G[i-1] == NULL) {
            printf("Error loading file: %s\n", argv[i]);
            continue;
        }
        printf("Loaded %s\n", argv[i]);
        
        // Подсчет черных пикселей
        int c = 0;
        unsigned char *s = G[i-1]->data;
        int len = G[i-1]->bytes;

        for (int j = 0; j < len; j++) {
            c += popcnt8(s[j]);
        }

        G[i-1]->count = c;
        calculate_stats(G[i-1]);
    }

    // Вывод информации о глифах
    for (int i = 0; i < N; i++) {
        if (G[i] != NULL) {
            print_glyph_info(G[i]);
        }
    }

    // Поиск похожих глифов
    find_similar_glyphs(G, N);

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        if (G[i] != NULL) {
            free(G[i]->data);
            free(G[i]);
        }
    }

    return 0;
}

// Функция подсчета количества установленных битов в байте
int popcnt8(unsigned char i) {
    return __builtin_popcount(i);
}

// Функция инициализации структуры изображения
IMG *init_img(int id, int w, int h) {
    IMG *t = (IMG *)malloc(sizeof(IMG));
    if (!t) return NULL;
    
    t->w = w;
    t->h = h;
    t->dx = 0;
    t->count = 0;
    t->id = id;
    t->bytes = ((w + 7) / 8) * h;
    t->data = (unsigned char *)calloc(t->bytes, 1);
    if (!t->data) {
        free(t);
        return NULL;
    }
    return t;
}

// Функция загрузки изображения из файла
IMG *load_img(int id, char *File) {
    FILE *F = fopen(File, "rb");
    if (!F) {
        perror("File opening error");
        return NULL;
    }

    IMG *I = (IMG *)malloc(sizeof(IMG));
    if (!I) {
        fclose(F);
        return NULL;
    }

    // Чтение заголовка файла
    if (fread(&(I->w), sizeof(int), 1, F) != 1 ||
        fread(&(I->h), sizeof(int), 1, F) != 1 ||
        fread(&(I->dx), sizeof(int), 1, F) != 1 ||
        fread(&(I->count), sizeof(int), 1, F) != 1 ||
        fread(&(I->id), sizeof(int), 1, F) != 1 ||
        fread(&(I->bytes), sizeof(int), 1, F) != 1) {
        free(I);
        fclose(F);
        return NULL;
    }

    // Выделение памяти под данные изображения
    I->data = (unsigned char *)malloc(I->bytes);
    if (!I->data) {
        free(I);
        fclose(F);
        return NULL;
    }

    // Чтение данных изображения
    if (fread(I->data, 1, I->bytes, F) != I->bytes) {
        free(I->data);
        free(I);
        fclose(F);
        return NULL;
    }

    fclose(F);
    return I;
}

// Функция проверки пикселя на черноту
int ISPIX(IMG *glyph, int i, int j) {
    if (i < 0 || j < 0 || i >= glyph->w || j >= glyph->h) {
        return 0;
    }
    int bytes_per_row = (glyph->w + 7) / 8;
    int byte_pos = j * bytes_per_row + i / 8;
    return ISBIT(7 - (i % 8), glyph->data[byte_pos]);
}

// Функция вычисления статистик глифа
void calculate_stats(IMG *glyph) {
    if (glyph->w == 0 || glyph->h == 0) {
        glyph->density = 0.0;
        glyph->perim = 0;
        glyph->diam = 1; 
        glyph->conn = 0;
        return;
    }

    // Вычисление плотности
    glyph->density = (double)glyph->count / (glyph->w * glyph->h);
    
    int perimeter = 0;
    int *x_coords = NULL;
    int *y_coords = NULL;
    int black_pixels = 0;
    
    if (glyph->count > 0) {
        x_coords = malloc(glyph->count * sizeof(int));
        y_coords = malloc(glyph->count * sizeof(int));
    }

    // Вычисление периметра и сбор координат черных пикселей
    for (int i = 0; i < glyph->w; i++) {
        for (int j = 0; j < glyph->h; j++) {
            if (ISPIX(glyph, i, j)) {
                if (black_pixels < glyph->count) {
                    x_coords[black_pixels] = i;
                    y_coords[black_pixels] = j;
                }
                black_pixels++;

                // Проверка соседей для определения граничного пикселя
                int neighbors = 0;
                neighbors += ISPIX(glyph, i-1, j);
                neighbors += ISPIX(glyph, i+1, j);
                neighbors += ISPIX(glyph, i, j-1);
                neighbors += ISPIX(glyph, i, j+1);
                if (neighbors < 4) perimeter++;
            }
        }
    }
    glyph->perim = perimeter;
    
    // Вычисление диаметра (максимальное расстояние между пикселями)
    int max_dist = 0;
    if (black_pixels > 0) {
        for (int i = 0; i < black_pixels; i++) {
            for (int j = i+1; j < black_pixels; j++) {
                int dist = abs(x_coords[i] - x_coords[j]) + abs(y_coords[i] - y_coords[j]);
                if (dist > max_dist) {
                    max_dist = dist;
                }
            }
        }
        glyph->diam = max_dist + 1; 
    } else {
        glyph->diam = 1; 
    }
    
    // Освобождение памяти
    if (x_coords) free(x_coords);
    if (y_coords) free(y_coords);
    
    // Упрощенное определение связности (всегда 1 в этой реализации)
    glyph->conn = 1;
}

// Функция вывода информации о глифе
void print_glyph_info(IMG *glyph) {
    printf("Glyph ID: %d\n", glyph->id);
    printf("Dimensions: %d x %d\n", glyph->w, glyph->h);
    printf("Black pixels: %d\n", glyph->count);
    printf("Density: %.2f\n", glyph->density);
    printf("Perimeter: %d\n", glyph->perim);
    printf("Diameter: %d\n", glyph->diam);
    printf("Connectivity: %d\n", glyph->conn);
    printf("\n");
}

// Функция сравнения двух глифов
double compare_glyphs(IMG *g1, IMG *g2) {
    if (g1 == NULL || g2 == NULL) return 1.0;
    if (g1->w != g2->w || g1->h != g2->h) {
        return 1.0;
    }
    
    int diff = 0;
    int total_pixels = g1->w * g1->h;
    if (total_pixels == 0) return 0.0;
    
    // Построчное сравнение пикселей
    for (int i = 0; i < g1->w; i++) {
        for (int j = 0; j < g1->h; j++) {
            if (ISPIX(g1, i, j) != ISPIX(g2, i, j)) {
                diff++;
            }
        }
    }
    
    // Возврат коэффициента различия
    return (double)diff / total_pixels;
}

// Функция поиска похожих глифов
void find_similar_glyphs(IMG **glyphs, int count) {
    printf("\nSearching for similar glyphs...\n");
    
    int similar_pairs = 0;
    
    // Попарное сравнение всех глифов
    for (int i = 0; i < count; i++) {
        if (glyphs[i] == NULL) continue;
        for (int j = i + 1; j < count; j++) {
            if (glyphs[j] == NULL) continue;
            if (glyphs[i]->w != glyphs[j]->w || glyphs[i]->h != glyphs[j]->h) {
                continue;
            }
            
            double similarity = compare_glyphs(glyphs[i], glyphs[j]);
            if (similarity <= SIMILARITY_THRESHOLD) {
                similar_pairs++;
                
                printf("Glyphs %d and %d are similar (difference %.2f%%)\n", 
                       glyphs[i]->id, glyphs[j]->id, similarity * 100);
                
            }
        }
    }
    
    printf("Found similar glyph pairs: %d\n", similar_pairs);
}
