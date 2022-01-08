#include "sorting.h"
#include "person.h"
#define MAX_LINES 100
const char* INPUTFILE = "C:\\Users\\Nirkoren\\CLionProjects\\uni_assiments\\persons.txt";
const char* OUTPUTFILE = "C:\\Users\\Nirkoren\\CLionProjects\\uni_assiments\\sorted.txt";


int main() {
    Person persons[MAX_LINES];
    int numOfPersons = 0;
    load(INPUTFILE, persons, &numOfPersons);
    quicksort(persons, 0, numOfPersons, swapPersons, comparePersonByFirstName);
    save(OUTPUTFILE, persons, numOfPersons);
    return 0;
}
