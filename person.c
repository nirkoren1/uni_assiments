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
    copy_double(&persons[index].weight, strToDouble(tokens[6]));
    for (int i = 0; i < size; i++) {
        free(tokens[i]);
    }
    free(tokens);
}


static char *int_to_str(int num, char out[]){
    int size = 0, j;
    char c[2];
    c[1] = '\0';
    strcpy(out, "");
    j = num;
    while (j != 0){
        j /= 10;
        size += 1;
    }
    for (int i = size - 1; i > -1; i--) {
        j = ((int) (num * pow(10, -i)) % 10);
        c[0] = '0' + j;
        strcat(out, c);
    }
    return out;
}


static char *double_to_str(double num, char out[]){
    int size = 0;
    double j;
    char c[2];
    num += 2 * 10e-15;
    c[1] = '\0';
    strcpy(out, "");
    j = num;
    while (j > 1){
        j /= 10;
        size += 1;
    }
    for (int i = size - 1; i > - 3; i--) {
        if (i == - 1)
            strcat(out, ".");
        j = ((int) (num * pow(10, -i)) % 10);
        c[0] = '0' + j;
        strcat(out, c);
    }
    return out;
}


static void person_id(Person person, char out[]){
    char c[MAX_STR_LEN] = "";
    strcpy(out, "");
    strcat(out, person.firstName);
    strcat(out, DELIM);
    strcat(out, person.lastName);
    strcat(out, DELIM);
    strcat(out, int_to_str(person.dateOfBirth.day, c));
    strcat(out, DELIM);
    strcat(out, int_to_str(person.dateOfBirth.month, c));
    strcat(out, DELIM);
    strcat(out, int_to_str(person.dateOfBirth.year, c));
    strcat(out, DELIM);
    strcat(out, int_to_str(person.height, c));
    strcat(out, DELIM);
    strcat(out, double_to_str(person.weight, c));
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
    double c, bmi1, bmi2;
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    bmi1 = p1->weight / (p1->height * p1->height);
    bmi2 = p2->weight / (p2->height * p2->height);
    c = compare_double(&bmi1, &bmi2);
    if (c > 0)
        return 1;
    if (c < 0)
        return -1;
    return 0;
}


int comparePersonByFirstName(void* arr, int i, int j) {
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_str(p1->firstName, p2->firstName);
}


int comparePersonByLastName(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_str(p1->lastName, p2->lastName);
}


int comparePersonByDate(void* arr, int i, int j){
    int result;
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    result = compare_int(&p1->dateOfBirth.year, &p2->dateOfBirth.year);
    if (result != 0)
        return result;
    result = compare_int(&p1->dateOfBirth.month, &p2->dateOfBirth.month);
    if (result != 0)
        return result;
    result = compare_int(&p1->dateOfBirth.day, &p2->dateOfBirth.day);
    return result;
}


void swapPersons(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    Person tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
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
        paste_person(persons, i, buffer);
        *numOfPersonsPtr += 1;
    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}


void save(const char* outputFile, Person persons[], int numOfPersons){
    FILE* output = fopen(outputFile, "w");
    if (!output) {
        printf("Error with file: %s\n", outputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    for (int i = 0; i < numOfPersons; i++) {
        person_id(persons[i], buffer);
        fprintf(output, "%s\n", buffer);
    }
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
    }
}

