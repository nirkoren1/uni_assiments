#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"


int compare_str(void* i, void* j) {
    char* s1 = (char*) i;
    char* s2 = (char*) j;
    return strcmp(s1, s2);
}


int compare_int(void* i, void* j) {
    int *i1 = (int *) i;
    int *i2 = (int *) j;
    return *i1 - *i2;
}


int compare_double(void* i, void* j) {
    double *i1 = (double *) i;
    double *i2 = (double *) j;
    return *i1 - *i2;
}


static void copy_str(void *p1, void *p2) {
    char* s1 = (char*) p1;
    char* s2 = (char*) p2;
    strcpy(s1, s2);
}


int comparePersonByWeight(void* arr, int i, int j) {
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_double(&p1->weight, &p2->weight);
}


int comparePersonByHeight(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_int(&p1->height, &p2->height);
}


int comparePersonByBMI(void* arr, int i, int j){

}


int comparePersonByFirstName(void* arr, int i, int j) {
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_str(p1->firstName, p2->firstName);
}


void load(const char* inputFile, Person persons[], int* numOfPersonsPtr){
    int i = 0;
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, MAX_STR_LEN, input)) {
        i += 1;
        persons = (Person *) realloc(persons, sizeof(Person) * i);


        fprintf(output, "%s", buffer);
    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
    }
}
}



//int compare_age(void *y1, void *m1, void *d1, void *y2, void *m2, void *d2){
//    int val = compare_int(y1, y2);
//    if (val != 0)
//        return val;
//    val = compare_int(m1, m2);
//    if (val != 0)
//        return val;
//    val = compare_int(d1, d2);
//    if (val != 0)
//        return val;
//    return val;
//}

int compare_bmi(void *p_h1, void *p_w1, void *p_h2, void *p_w2){

}





//void swapPersons(int arr[], int i, int j) {
//    int tmp = arr[i];
//    arr[i] = arr[j];
//    arr[j] = tmp;
//}
