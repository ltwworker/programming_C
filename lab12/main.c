#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT 100

const char *week_days[] = {"Voskresene", "Ponedelnik", "Vtornik", "Sreda", "Chetverg", "Pyatnica", "Subbota"};
const char *week_days_short[] = {"Vs", "Pn", "Vt", "Sr", "Ct", "Pt", "Sb"};
const char *months[] = {
    "Yanvar", "Fevral", "Mart", "Aprel", "Mai", "Iyun",
    "Iyul", "Avgust", "Sentyabr", "Oktyabr", "Noyabr", "Dekabr"
};

int is_leap_year(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int days_in_month(int year, int month) {
    static const int days_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2) {
        return days_month[1] + is_leap_year(year);
    }
    return days_month[month - 1];
}

int day_of_week(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + 13*(month + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7;
    return d;
}

int i, d, month;
void print_month_calendar(int year, int month) {
    printf("\n    %s %d\n", months[month - 1], year);
    for (i = 0; i < 7; i++) {
        printf("%s ", week_days_short[i]);
    }
    printf("\n");

    int first_day = day_of_week(year, month, 1);
    int days = days_in_month(year, month);

    for (i = 0; i < first_day; i++) {
        printf("   ");
    }

    for (d = 1; d <= days; d++) {
        printf("%2d ", d);
        if ((first_day + d) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void print_year_calendar(int year) {
    printf("\nKalendar na %d god\n", year);
    for (month = 1; month <= 12; month++) {
        print_month_calendar(year, month);
        printf("\n");
    }
}

void print_day_of_week(int year, int month, int day) {
    int w = day_of_week(year, month, day);
    printf("Data: %04d.%02d.%02d - %s\n", year, month, day, week_days[w]);
}

int main() {
    char input[MAX_INPUT];

    printf("Vvedite datu (gggg.mm.dd, gggg.mm, gggg, now): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Oshibka vvoda\n");
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "now") == 0) {
        time_t t = time(NULL);
        struct tm *tm_now = localtime(&t);
        int year = tm_now->tm_year + 1900;
        int month = tm_now->tm_mon + 1;
        int day = tm_now->tm_mday;
        print_day_of_week(year, month, day);
        return 0;
    }

    int year = 0, month = 0, day = 0;
    int scanned = 0;

    scanned = sscanf(input, "%d.%d.%d", &year, &month, &day);
    if (scanned == 3) {
        if (year < 1 || month < 1 || month > 12 || day < 1 || day > days_in_month(year, month)) {
            printf("Nevernaya data\n");
            return 1;
        }
        print_day_of_week(year, month, day);
        return 0;
    }

    scanned = sscanf(input, "%d.%d", &year, &month);
    if (scanned == 2) {
        if (year < 1 || month < 1 || month > 12) {
            printf("Neverny mesyac ili god\n");
            return 1;
        }
        print_month_calendar(year, month);
        return 0;
    }

    scanned = sscanf(input, "%d", &year);
    if (scanned == 1) {
        if (year < 1) {
            printf("Neverny god\n");
            return 1;
        }
        print_year_calendar(year);
        return 0;
    }

    printf("Neverny format vvoda\n");
    return 1;
}

