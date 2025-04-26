#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 64
#define DATA_FILENAME "people.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int yearOfBirth;
    char gender;
    float height;
} Person;

int mainSortField;
int secondarySortField;

int loadPersonsFromFile(Person **personsArray, int *numPersons) {
    FILE *file = fopen(DATA_FILENAME, "r");
    if (!file) {
        printf("Ne udalos otkryt fayl %s\n", DATA_FILENAME);
        return 0;
    }

    *personsArray = NULL;
    *numPersons = 0;

    Person tempPerson;

    while (fscanf(file, "%s %d %c %f", tempPerson.name, &tempPerson.yearOfBirth, &tempPerson.gender, &tempPerson.height) == 4) {
        (*numPersons)++;
        *personsArray = (Person *)realloc(*personsArray, (*numPersons) * sizeof(Person));
        if (*personsArray == NULL) {
            printf("Oshibka vydeleniya pamyati\n");
            fclose(file);
            return 0;
        }
        (*personsArray)[*numPersons - 1] = tempPerson;
    }

    fclose(file);
    return 1;
}

int compareByYear(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;
    return p1->yearOfBirth - p2->yearOfBirth;
}

int compareByName(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;
    return strcmp(p1->name, p2->name);
}

int compareByGender(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;
    return p1->gender - p2->gender;
}

int compareByHeight(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;
    if (p1->height < p2->height) return -1;
    if (p1->height > p2->height) return 1;
    return 0;
}

int multiFieldComparator(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;
    int result = 0;

    switch (mainSortField) {
        case 1: result = compareByYear(p1, p2); break;
        case 2: result = compareByName(p1, p2); break;
        case 3: result = compareByGender(p1, p2); break;
        case 4: result = compareByHeight(p1, p2); break;
        default: result = 0; break;
    }

    if (result == 0 && secondarySortField != 0) {
        switch (secondarySortField) {
            case 1: result = compareByYear(p1, p2); break;
            case 2: result = compareByName(p1, p2); break;
            case 3: result = compareByGender(p1, p2); break;
            case 4: result = compareByHeight(p1, p2); break;
            default: result = 0; break;
        }
    }

    return result;
}
int i;

void printPersonsList(Person *personsArray, int numPersons) {
    printf("Otsortirovannyi spisok:\n");
    for (i = 0; i < numPersons; i++) {
        printf("FIO: %s, God rozhdeniya: %d, Pol: %c, Rost(m): %.2f\n",
               personsArray[i].name, personsArray[i].yearOfBirth, personsArray[i].gender, personsArray[i].height);
    }
}

int main() {
    Person *persons = NULL;
    int totalPersons = 0;

    if (!loadPersonsFromFile(&persons, &totalPersons)) {
        return 1;
    }

    if (totalPersons == 0) {
        printf("Fayl pust ili ne soderzhit dannykh.\n");
        return 0;
    }

    printf("Vyberite osnovnoe pole dlya sortirovki:\n");
    printf("1. God rozhdeniya\n");
    printf("2. FIO\n");
    printf("3. Pol\n");
    printf("4. Rost\n");
    printf("Vvedite nomer polya: ");
    scanf("%d", &mainSortField);

    

    if (secondarySortField == 0) {
        switch (mainSortField) {
            case 1: qsort(persons, totalPersons, sizeof(Person), compareByYear); break;
            case 2: qsort(persons, totalPersons, sizeof(Person), compareByName); break;
            case 3: qsort(persons, totalPersons, sizeof(Person), compareByGender); break;
            case 4: qsort(persons, totalPersons, sizeof(Person), compareByHeight); break;
            default:
                printf("Nedopustimyi vybor polya.\n");
                free(persons);
                return 1;
        }
    } else {
        qsort(persons, totalPersons, sizeof(Person), multiFieldComparator);
    }

    printf("\nRezultat sortirovki:\n");
    printPersonsList(persons, totalPersons);

    free(persons);
    return 0;
}

