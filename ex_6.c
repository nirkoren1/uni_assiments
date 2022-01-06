#include <stdio.h>
#include "sorting.h"
#include "person.h"
#include <string.h>

#define MAX_LINES 100


const char* INPUTFILE = "persons.txt";
const char* OUTPUTFILE = "sorted.txt";


int main() {
//    Person persons[MAX_LINES];
//    int numOfPersons = 0;
//    load(INPUTFILE, persons, &numOfPersons);
//    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
//    save(OUTPUTFILE, persons, numOfPersons);
    char l[2][4] = {"acs", "aca"};
    printf("%d", comparePersonByFirstName(l, 0, 1));
//    quicksort(l, 0, 7, swapPersons,)
    return 0;
}
