#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include <math.h>


static int compare_str(void* i, void* j) {
    char* s1 = (char*) i;
    char* s2 = (char*) j;
    return strcmp(s1, s2);
}


static int compare_int(void* i, void* j) {
    int *i1 = (int *) i;
    int *i2 = (int *) j;
    return *i1 - *i2;
}


static double compare_double(void* i, void* j) {
    double *i1 = (double *) i;
    double *i2 = (double *) j;
    return *i1 - *i2;
}


static char **string_to_tokens_lst(char *str, char delim[], int *size) {
    int i = -1;
    char *token = strtok(str, delim);
    char **out = (char **) malloc(sizeof (char *));
    while (token != NULL) {
        i += 1;
        if (size != NULL)
            *size += 1;
        out = (char **) realloc(out, sizeof (char *) * (i + 1));
        out[i] = (char *) malloc(sizeof(char) * strlen(token) + 1);
        strcpy(out[i], token);
        token = strtok(NULL, delim);
    }
    return out;
}


static double strToDouble(const char *str){
    int i = 0, is_float = 0, size = 0;
    double out_d = 0;
    char c = str[i];
    while (c != '\0') {
        if (c == '.')
            is_float = 1;
        if (!is_float)
            size += 1;
        i += 1;
        c = str[i];
    }
    i = 0;
    c = str[i];
    while (c != '\0') {
        if (c != '.'){
            out_d += (c - '0') * pow(10, size - 1);
            size -= 1;
        }
        i += 1;
        c = str[i];
    }
    return out_d;
}


static int strToInt(const char *str){
    int i = 0, size = 0;
    int out_i = 0;
    char c = str[i];
    while (c != '\0') {
        size += 1;
        i += 1;
        c = str[i];
    }
    i = 0;
    c = str[i];
    while (c != '\0') {
        out_i += (c - '0') * pow(10, size - 1);
        size -= 1;
        i += 1;
        c = str[i];
    }
    return out_i;
}


static void copy_str(void *p1, void *p2) {
    char* s1 = (char*) p1;
    char* s2 = (char*) p2;
    strcpy(s1, s2);
}


static void copy_int(void *p1, int val) {
    int* s1 = (int*) p1;
    *s1 = val;
}


static void copy_double(void *p1, double val) {
    double *s1 = (double *) p1;
    *s1 = val;
}


static void convert_n_to_0(char str[]){
    int i = 0;
    char c = str[i];
    while (c != '\n') {
        i += 1;
        c = str[i];
    }
    str[i] = '\0';
}


static void paste_person(Person persons[], int index, char *person_str){
    int size = 0;
    char **tokens = string_to_tokens_lst(person_str, DELIM, &size);
    copy_str(persons[index].firstName, tokens[0]);
    copy_str(persons[index].lastName, tokens[1]);
    copy_int(&persons[index].dateOfBirth.day, strToInt(tokens[2]));
    copy_int(&persons[index].dateOfBirth.month, strToInt(tokens[3]));
    copy_int(&persons[index].dateOfBirth.year, strToInt(tokens[4]));
    copy_int(&persons[index].height, strToInt(tokens[5]));
    copy_int(&persons[index].weight, strToDouble(tokens[6]));
    for (int i = 0; i < size; i++) {
        free(tokens[i]);
    }
    free(tokens);
}


int comparePersonByWeight(void* arr, int i, int j) {
    double c;
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    c = compare_double(&p1->weight, &p2->weight);
    if (c > 0)
        return 1;
    if (c < 0)
        return -1;
    return 0;
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
    int i = -1;
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, MAX_STR_LEN, input)) {
        i += 1;
        convert_n_to_0(buffer);
        printf("%s\n", buffer);
        paste_person(persons, i, buffer);
        *numOfPersonsPtr += 1;
    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
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
