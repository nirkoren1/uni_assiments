
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


int compare_age(void *y1, void *m1, void *d1, void *y2, void *m2, void *d2){
    int val = compare_int(y1, y2);
    if (val != 0)
        return val;
    val = compare_int(m1, m2);
    if (val != 0)
        return val;
    val = compare_int(d1, d2);
    if (val != 0)
        return val;
    return val;
}

int compare_bmi(void *p_h1, void *p_w1, void *p_h2, void *p_w2){

}