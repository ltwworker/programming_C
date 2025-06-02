#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VVOD 100

struct tm poluchit_tm_datu(int god, int mesyats, int den) {
    struct tm data = {0};
    data.tm_year = god - 1900;
    data.tm_mon = mesyats - 1;
    data.tm_mday = den;
    mktime(&data);
    return data;
}

void pechatat_den_nedeli(int god, int mesyats, int den) {
    struct tm data = poluchit_tm_datu(god, mesyats, den);
    char buf[20];
    strftime(buf, sizeof(buf), "%A", &data);
    printf("%s", buf);
}

void pechatat_korotkiy_den(int den_nedeli) {
    const char* dni[] = {"Vs", "Pn", "Vt", "Sr", "Cht", "Pt", "Sb"};
    printf("%s", dni[den_nedeli]);
}

void pechatat_mesyats(int god, int mesyats) {
    struct tm pervoe = poluchit_tm_datu(god, mesyats, 1);
    int dney_v_mesyatse = poluchit_tm_datu(god, mesyats + 1, 0).tm_mday;
    
    printf("\n    %d-%02d\n", god, mesyats);
    
    for (int i = 0; i < 7; i++) {
        pechatat_korotkiy_den(i);
        printf(" ");
    }
    printf("\n");
    
    for (int i = 0; i < pervoe.tm_wday; i++) {
        printf("    ");
    }
    
    for (int den = 1; den <= dney_v_mesyatse; den++) {
        printf("%2d  ", den);
        if ((pervoe.tm_wday + den) % 7 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    setlocale(LC_TIME, "ru_RU.UTF-8");
    
    char vvod[MAX_VVOD];
    printf("Vvedite datu (gggg.mm.dd, gggg.mm, gggg ili 'now'): ");
    fgets(vvod, MAX_VVOD, stdin);
    vvod[strcspn(vvod, "\n")] = 0;
    
    if (strcmp(vvod, "now") == 0) {
        time_t seychas = time(NULL);
        struct tm* tm_seychas = localtime(&seychas);
        printf("Segodnya: ");
        pechatat_den_nedeli(tm_seychas->tm_year + 1900, tm_seychas->tm_mon + 1, tm_seychas->tm_mday);
        printf("\n");
        return 0;
    }
    
    int god, mesyats = 1, den = 1;
    if (sscanf(vvod, "%d.%d.%d", &god, &mesyats, &den) == 3) {
        printf("Den nedeli: ");
        pechatat_den_nedeli(god, mesyats, den);
        printf("\n");
    } 
    else if (sscanf(vvod, "%d.%d", &god, &mesyats) == 2) {
        pechatat_mesyats(god, mesyats);
    } 
    else if (sscanf(vvod, "%d", &god) == 1) {
        for (mesyats = 1; mesyats <= 12; mesyats++) {
            pechatat_mesyats(god, mesyats);
        }
    } 
    else {
        printf("Neverny format vvoda\n");
    }
    
    return 0;
}
