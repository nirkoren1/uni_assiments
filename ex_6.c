#include <stdio.h>
#include "sorting.h"
#include "person.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100


const char* INPUTFILE = "persons.txt";
const char* OUTPUTFILE = "sorted.txt";


int main() {
//    Person persons[MAX_LINES];
//    int numOfPersons = 0;
//    load(INPUTFILE, persons, &numOfPersons);
//    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
//    save(OUTPUTFILE, persons, numOfPersons);
    Person *p1 = (Person *) malloc(sizeof(Person) * 2);
    p1[0].weight = 15;
    p1[1].weight = 20;
    printf("%d", comparePersonByWeight(p1, 0, 0));
//    quicksort(l, 0, 7, swapPersons,)
    return 0;
}
