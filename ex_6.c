#include "sorting.h"
#include "person.h"
#define MAX_LINES 100
const char* INPUTFILE = "persons.txt";
const char* OUTPUTFILE = "sorted.txt";


int main() {
    Person persons[MAX_LINES];
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByWeight);
    save(OUTPUTFILE, persons, numOfPersons);
    return 0;
}
