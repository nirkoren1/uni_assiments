#include <string.h>
#include <stdio.h>
#include "person.h"


int compare_str(void* arr, int i, int j) {
    char* s1 = (char*) arr + sizeof(char *) * i;
    char* s2 = (char*) arr + sizeof(char *) * j;
    return strcmp(s1, s2);
}


int compare_int(void* arr, int i, int j) {
    int *i1 = (int *) arr + i;
    int *i2 = (int *) arr + j;
    return *i1 - *i2;
}


int compare_double(void* i, void* j) {
    double *i1 = (double *) i;
    double *i2 = (double *) j;
    return *i1 - *i2;
}


int comparePersonByWeight(void* arr, int i, int j) {
    Person *p1 = (Person *) arr + i;
    Person *p2 = (Person *) arr + j;
    double w1 = p1->weight;
    double w2 = p2->weight;
    return compare_double(&p1->weight, &p2->weight);
}


int comparePersonByFirstName(void* arr, int i, int j) {
    return compare_str(arr, i, j);
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
