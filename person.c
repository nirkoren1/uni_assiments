//
// Created by Nirkoren on 05/01/2022.
//



#include <string.h>

int compare_int(void *p1, void *p2){
    int* i1 = (int*) p1;
    int* i2 = (int*) p2;
    return *i1 - *i2;
}


int compare_str(void *p1, void *p2) {
    char* s1 = (char*) p1;
    char* s2 = (char*) p2;
    return strcmp(s1,s2);
}


int compare_bmi(void *y1, void *m1, void *d1, void *y2, void *m2, void *d2){

}

