#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***********************
* Nir koren
* 316443902
* ass05
***********************/


typedef struct {
    char** translations;
    struct Word* next;
} Word;


typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;


void print_menu(){
    printf("Welcome to the dictionaries manager!\n"
           "Choose an option:\n"
           "1. Create a new dictionary.\n"
           "2. Add a word to a dictionary.\n"
           "3. Delete a word from a dictionary.\n"
           "4. Find a word in a dictionary.\n"
           "5. Delete a dictionary.\n"
           "6. Exit.\n");
}


/******************
* Function Name: empty_buffer
* Input: none
* Output: none
* Function Operation: cleans the buffer with scanf for error measures
******************/
void empty_buffer(){
    char c;
    while (1){
        scanf("%c", &c);
        if (c == '\n')
            return;
    }
}


/******************
* Function Name: string_to_tokens_lst
* Input: str, deliminator, size of the lst to update
* Output: ptr to the tokens lst
* Function Operation: cuts the str to tokens using the strtok func shown in class
******************/
char **string_to_tokens_lst(char str[], char delim[], int *size) {
    int i = -1;
    char *token = strtok(str, delim);
    char **out = (char **) malloc(sizeof(char *)), **t;
    if (out == NULL)
        printf("The creation of the string has failed!\n");
    while (token != NULL) {
        i += 1;
        if (size != NULL)
            *size += 1;
        t = out;
        out = (char **) realloc(out, sizeof(char *) * (i + 1));
        if (out == NULL)
            out = t;
        out[i] = (char *) malloc(sizeof(char) * strlen(token) + 1);
        if (out[i] == NULL)
            printf("The creation of the string has failed!\n");
        strcpy(out[i], token);
        token = strtok(NULL, delim);
    }
    return out;
}


char *scan_no_limit(){
    char c;
    int i = 1;
    char *str = (char *) malloc(sizeof(char) * i);
    if (str == NULL)
        printf("The creation of the dictionary has failed!\n");
    empty_buffer();
    while (1){
        scanf("%c", &c);
        if (c == '\n')
            break;
        i++;
        str = (char *) realloc(str, (sizeof(char) * i));
        if (str == NULL)
            printf("The creation of the dictionary has failed!\n");
        str[i - 2] = c;
    }
    str[i - 1] = '\0';
    return str;
}


int checkDecisions(int allDecisions[]){
    int cnt = 0, numOfDecisions = 5;
    for (int i = 0; i < numOfDecisions; i++) {
        if (allDecisions[i] == 1)
            cnt++;
    }
    if (cnt == numOfDecisions){
        for (int i = 0; i < numOfDecisions; ++i) {
            allDecisions[i] = 0;
        }
        return 1;
    }
    else
        return 0;
}


void create_dic(Dictionary *dictionary){
    int numOfLanguages = 0;
    char *languages;
    printf("Define a new dictionary:\n");
    languages = scan_no_limit();
    dictionary->languages = string_to_tokens_lst(languages, ",", &numOfLanguages);
    dictionary->numOfLanguages = numOfLanguages;
    dictionary->wordList = (Word *) malloc(sizeof(Word));
    dictionary->wordList->next = NULL;
    printf("The dictionary has been created successfully!\n");
    free(languages);
}


void print_all_dic(int numOfDictionaries, Dictionary *dictionaries){
    for (int i = 0; i < numOfDictionaries; i++) {
        printf("%d. ", i + 1);
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            printf("%s", dictionaries[i].languages[j]);
            if (j != dictionaries[i].numOfLanguages - 1)
                printf(",");
        }
        printf("\n");
    }
}


void create_new_word(Word *head){
    char *words;
    Word *iterator = head;
    while (iterator->next != NULL)
        iterator = iterator->next;
    words = scan_no_limit();
    iterator->translations = string_to_tokens_lst(words, ",", NULL);
    iterator->next = (Word *) malloc(sizeof(Word));
    if (iterator->next == NULL)
        printf("The addition of the word has failed!\n");
    else
        printf("The word has been added successfully!\n");
    free(words);
}


void add_word(int numOfDictionaries, Dictionary *dictionaries){
    int decision;
    printf("Choose a dictionary:\n");
    print_all_dic(numOfDictionaries, dictionaries);
    scanf("%d", &decision);
    decision -= 1;
    printf("Enter a word in ");
    for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
        printf("%s", dictionaries[decision].languages[i]);
        if (i != dictionaries[decision].numOfLanguages - 1)
            printf(",");
    }
    printf(":\n");
    create_new_word(dictionaries[decision].wordList);
}


Word *search_word(Word *head){
    Word *iterator = head;
    while (iterator->next != NULL or)
        iterator = iterator->next;
}


int main(){
    Dictionary *dictionaries;
    int numOfDictionaries = 0, decision, allDecisions[5] = {0};
    dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
    print_menu();
    while (1) {
        scanf("%d", &decision);
        if (decision == 1) {
            numOfDictionaries++;
            dictionaries = (Dictionary *) realloc(dictionaries, sizeof(Dictionary) * numOfDictionaries);
            if (dictionaries == NULL)
                printf("The creation of the dictionary has failed!\n");
            create_dic(&dictionaries[numOfDictionaries - 1]);
        } else if (1 < decision && decision < 6 && numOfDictionaries == 0){
            printf("This option is not available right now, try again:\n");
        } else if (decision == 2) {
            add_word(numOfDictionaries, dictionaries);
        }
//    else if (decision == 3)
//        del_word();
//        numOfDecisions++;
//    else if (decision == 4)
//        find_word();
//        numOfDecisions++;
//    else if (decision == 5)
//        del_dic();
//        numOfDecisions++;
        else if (decision == 6) {
            return 0;
        } else{
            printf("Wrong option, try again:");
            continue;
        }
        allDecisions[decision - 1] = 1;
        if (checkDecisions(allDecisions)){
            print_menu();
        }
    }
}