#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include <math.h>


/******************
* Function Name: compare_str
* Input: void* str1, void* str2
* Output: int 1 if str1 > str2, -1 if str1 < str2, 0 if equal (lexicographic order)
* Function Operation: using the strcmp func
******************/
static int compare_str(void* i, void* j) {
    char* s1 = (char*) i;
    char* s2 = (char*) j;
    return strcmp(s1, s2);
}


/******************
* Function Name: compare_int
* Input: void* num1, void* num2
* Output: int greater than 0 if num1 > num2, less than 0 if num1 < num2, 0 if equal
* Function Operation: subtracts between the two numbers
******************/
static int compare_int(void* i, void* j) {
    int *i1 = (int *) i;
    int *i2 = (int *) j;
    return *i1 - *i2;
}


/******************
* Function Name: compare_double
* Input: void* num1, void* num2
* Output: double greater than 0 if num1 > num2, less than 0 if num1 < num2, 0 if equal
* Function Operation: subtract between the two numbers
******************/
static double compare_double(void* i, void* j) {
    double *i1 = (double *) i;
    double *i2 = (double *) j;
    return *i1 - *i2;
}


/******************
* Function Name: string_to_tokens_lst
* Input: str, deliminator, size of the lst to update
* Output: ptr to the tokens lst
* Function Operation: cuts the str to tokens using the strtok func shown in class
******************/
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


/******************
* Function Name: strToDouble
* Input: str
* Output: double
* Function Operation: creating a new double number from the string provided
******************/
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


/******************
* Function Name: strToInt
* Input: str
* Output: int
* Function Operation: creating a new int number from the string provided
******************/
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


/******************
* Function Name: copy_str
* Input: str ptr of destination, str ptr of origin (generic input)
* Output: None
* Function Operation: using the strcpy func
******************/
static void copy_str(void *p1, void *p2) {
    char* s1 = (char*) p1;
    char* s2 = (char*) p2;
    strcpy(s1, s2);
}


/******************
* Function Name: copy_int
* Input: int ptr of destination, int ptr of origin (generic input)
* Output: None
* Function Operation: regular assignment
******************/
static void copy_int(void *p1, int val) {
    int* s1 = (int*) p1;
    *s1 = val;
}


/******************
* Function Name: copy_double
* Input: double ptr of destination, double ptr of origin (generic input)
* Output: None
* Function Operation: regular assignment
******************/
static void copy_double(void *p1, double val) {
    double *s1 = (double *) p1;
    *s1 = val;
}


/******************
* Function Name: convert_n_to_0
* Input: str
* Output: None
* Function Operation: replacing '\n' with '\0'
******************/
static void convert_n_to_0(char str[]){
    int i = 0;
    char c = str[i];
    while (c != '\n') {
        i += 1;
        c = str[i];
    }
    str[i] = '\0';
}


/******************
* Function Name: paste_person
* Input: Persons lst, int index, str person_str
* Output: None
* Function Operation: pasting the data of a given line representing a person
******************/
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


/******************
* Function Name: int_to_str
* Input: int num, str out
* Output: str out
* Function Operation: creating a new str of the num and puts it in out
******************/
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


/******************
* Function Name: double_to_str
* Input: double num, str out
* Output: str out
* Function Operation: creating a new str of the num and puts it in out
******************/
static char *double_to_str(double num, char out[]){
    int size = 0;
    double j;
    char c[2];
    // compensation of the loss of data when passing the num to the func
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


/******************
* Function Name: person_id
* Input: Persons person, str person_str
* Output: None
* Function Operation: creating a new line representing the person data and puts it in person_str
******************/
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


/******************
* Function Name: comparePersonByWeight
* Input: ptr arr, int person1, int person2
* Output: int result of compare_double(person1_weight, person2_weight)
* Function Operation: compare the weight of the two using compare_double
******************/
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


/******************
* Function Name: comparePersonByHeight
* Input: ptr arr, int person1, int person2
* Output: int result of compare_int(person1_height, person2_height)
* Function Operation: compare the height of the two using compare_int
******************/
int comparePersonByHeight(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_int(&p1->height, &p2->height);
}


/******************
* Function Name: comparePersonByBMI
* Input: ptr arr, int person1, int person2
* Output: int result of compare_double(person1_bmi, person2_bmi)
* Function Operation: calculating the bmi of the two and compare the bmi using compare_double
******************/
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


/******************
* Function Name: comparePersonByFirstName
* Input: ptr arr, int person1, int person2
* Output: int result of compare_str(person1_firstName, person2_firstName)
* Function Operation: compare the firstName of the two using compare_str
******************/
int comparePersonByFirstName(void* arr, int i, int j) {
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_str(p1->firstName, p2->firstName);
}


/******************
* Function Name: comparePersonByLastName
* Input: ptr arr, int person1, int person2
* Output: int result of compare_str(person1_lastName, person2_lastName)
* Function Operation: compare the lastName of the two using compare_str
******************/
int comparePersonByLastName(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    return compare_str(p1->lastName, p2->lastName);
}


/******************
* Function Name: comparePersonByHeight
* Input: ptr arr, int person1, int person2
* Output: int result of compare_int(person1_year/month/day, person2_year/month/day)
* Function Operation: compare the year/month/day of the two using compare_int
******************/
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


/******************
* Function Name: swapPersons
* Input: ptr arr, int person1, int person2
* Output: None
* Function Operation: swap the two objects in arr with assigment
******************/
void swapPersons(void* arr, int i, int j){
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    Person tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


/******************
* Function Name: load
* Input: char[] input_file, Person ptr persons arr, int ptr num_of_persons
* Output: None
* Function Operation: reading the input_file and using paste_person to load data into persons arr
******************/
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


/******************
* Function Name: save
* Input: char[] output_file, Person ptr persons arr, int num_of_persons
* Output: None
* Function Operation: using person_id to turn the data to line strings and outputs them to output_file
******************/
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

