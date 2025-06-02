#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_INPUT 100

const char *months[] = {
    "Yanvar", "Fevral", "Mart", "Aprel", "Mai", "Iyun",
    "Iyul", "Avgust", "Sentyabr", "Oktyabr", "Noyabr", "Dekabr"
};

int is_leap_year(int year) {
    struct tm date = {0};
    date.tm_year = year - 1900;
    date.tm_mon = 1;
    date.tm_mday = 29;

    time_t t = mktime(&date);
    if (t == -1) {
        return 0;
    }

    return (date.tm_mday == 29);
}

int i,d,month;

int days_in_month(int year, int month) {
    static const int days_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2) {
        return days_month[1] + is_leap_year(year);
    }
    return days_month[month - 1];
}


int get_weekday_index(int year, int month, int day) {
    struct tm date = {0};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    if (mktime(&date) == -1) {
        return -1;
    }

    int wday = date.tm_wday;
   
    wday = (wday + 6) % 7;
    return wday;
}


void print_weekdays_header() {
    char buffer[20];
    struct tm tm_day = {0};
    tm_day.tm_year = 125; 
    tm_day.tm_mon = 0;     
    tm_day.tm_mday = 1;   

    for (i = 0; i < 7; i++) {
        tm_day.tm_mday = 1 + i;
        mktime(&tm_day);

        if (strftime(buffer, sizeof(buffer), "%A", &tm_day) == 0) {
            printf("error \n");
            return;
        }
        printf("%-10s ", buffer);
    }
    printf("\n");
}

void print_month_calendar(int year, int month) {
    printf("\n    %s %d\n", months[month - 1], year);

    print_weekdays_header();

    int first_day = get_weekday_index(year, month, 1);
    int days = days_in_month(year, month);

    
    for (i = 0; i < first_day; i++) {
        printf("           ");
    }

    for (d = 1; d <= days; d++) {
        printf("%-11d", d);
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
    struct tm date = {0};
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    if (mktime(&date) == -1) {
        printf("Nevernaya data\n");
        return;
    }

    char buffer[20];
    if (strftime(buffer, sizeof(buffer), "%A", &date) == 0) {
        printf("Oshibka polucheniya dnya nedeli\n");
        return;
    }

    printf("Data: %04d.%02d.%02d - %s\n", year, month, day, buffer);
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
