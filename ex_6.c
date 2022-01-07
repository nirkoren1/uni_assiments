#include <stdio.h>
#include "sorting.h"
#include "person.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100


const char* INPUTFILE = "C:\\Users\\Nirkoren\\CLionProjects\\uni_assiments\\persons.txt";
const char* OUTPUTFILE = "sorted.txt";


int main() {
    Person persons[MAX_LINES];
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
//    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
//    save(OUTPUTFILE, persons, numOfPersons);
    printf("%f", persons[0].weight);
//    quicksort(l, 0, 7, swapPersons,)
    return 0;
}
