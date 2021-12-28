#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***********************
* Nir koren
* 316443902
* ass05
***********************/


typedef struct Word {
    char** translations;
    struct Word* next;
} Word;


typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;


/******************
* Function Name: print_menu
* Input: none
* Output: none
* Function Operation: prints the menu
******************/
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
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


/******************
* Function Name: string_to_tokens_lst
* Input: str, deliminator, size of the lst to update
* Output: ptr to the tokens lst
* Function Operation: cuts the str to tokens using the strtok func shown in class
******************/
char **string_to_tokens_lst(char *str, char delim[], int *size) {
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
* Function Name: scan_no_limit
* Input: none
* Output: char[]
* Function Operation: scans unlimited amount of digits and returns a string
******************/
char *scan_no_limit(){
    char c;
    int i = 1;
    char *str = (char *) malloc(sizeof(char) * i);
    empty_buffer();
    if (str == NULL){
        printf("Error!");
        return str;
    }
    while (1){
        scanf("%c", &c);
        if (c == '\n')
            break;
        i++;
        str = (char *) realloc(str, (sizeof(char) * i));
        if (str == NULL){
            printf("Error!");
            return str;
        }
        str[i - 2] = c;
    }
    str[i - 1] = '\0';
    return str;
}


/******************
* Function Name: create_dic
* Input: ptr of dictionaries arr, ptr of num of dictionaries
* Output: none
* Function Operation: create new dictionary and puts it in the end of dic arr and later adds 1 to num of dic
******************/
void create_dic(Dictionary *dictionaries, int *numOfDictionaries){
    int numOfLanguages = 0;
    char *languages;
    Dictionary *current_dic;
    *numOfDictionaries += 1;
    current_dic = &dictionaries[*numOfDictionaries - 1];
    printf("Define a new dictionary:\n");
    languages = scan_no_limit();
    current_dic->languages = string_to_tokens_lst(languages, ",", &numOfLanguages);
    current_dic->numOfLanguages = numOfLanguages;
    current_dic->wordList = (Word *) malloc(sizeof(Word));
    current_dic->wordList->translations = NULL;
    current_dic->wordList->next = NULL;
    printf("The dictionary has been created successfully!\n");
    free(languages);
}


/******************
* Function Name: print_all_dic
* Input: ptr of dictionaries arr, ptr of num of dictionaries
* Output: none
* Function Operation: prints all dic by order
******************/
void print_all_dic(int numOfDictionaries, Dictionary *dictionaries){
    if (numOfDictionaries == 0)
        return;
    printf("Choose a dictionary:\n");
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


/******************
* Function Name: create_new_word
* Input: ptr of the head (Word type)
* Output: none
* Function Operation: iterates to the end of the linked list and add a new scanned word
******************/
void create_new_word(Word *head){
    char *words;
    Word *iterator = head;
    while (iterator->next != NULL) {
        iterator = iterator->next;
    }
    words = scan_no_limit();
    if (iterator == head && iterator->translations == NULL){
        iterator->translations = string_to_tokens_lst(words, ",", NULL);
    } else{
        iterator->next = (Word *) malloc(sizeof(Word));
        if (iterator->next == NULL) {
            printf("The addition of the word has failed!\n");
            return;
        }
        iterator->next->translations = string_to_tokens_lst(words, ",", NULL);
        iterator->next->next = NULL;
    }
    free(words);
    printf("The word has been added successfully!\n");
}


/******************
* Function Name: add_word
* Input: ptr of dictionaries arr, ptr of num of dictionaries
* Output: none
* Function Operation: choosing the dic where the new word would ne added then uses create_new_word to add it
******************/
void add_word(int numOfDictionaries, Dictionary *dictionaries){
    int decision;
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


/******************
* Function Name: search_word
* Input: ptr of the head of the linkes list, char word that is searched, bool if return prev object
* Output: ptr of the desired word or the prev one
* Function Operation: iterates the linked list and using strcmp to find the desired location, then return it
******************/
Word *search_word(Word *head, char word[], int return_prev){
    Word *iterator = head, *prev = head;
    while (iterator != NULL){
        if (iterator->translations == NULL)
            return NULL;
        if (strcmp(iterator->translations[0], word) == 0) {
            if (!return_prev)
                return iterator;
            return prev;
        }
        prev = iterator;
        iterator = iterator->next;
    }
    return NULL;
}


/******************
* Function Name: del_word
* Input: ptr of dictionaries arr, int num of dictionaries
* Output: none
* Function Operation: uses search_word to find the prev object to del than delete it and connect the linked list properlu
******************/
void del_word(int numOfDictionaries, Dictionary *dictionaries){
    Word *second, *head, *first, *third;
    int decision = 0;
    char *word;
    char delete_decision;
    print_all_dic(numOfDictionaries, dictionaries);
    scanf("%d", &decision);
    decision -= 1;
    head = dictionaries[decision].wordList;
    printf("Enter a word in %s:\n", dictionaries[decision].languages[0]);
    word = scan_no_limit();
    first = search_word(head, word, 1);
    printf("Are you sure? (y/n)\n");
    scanf("%c", &delete_decision);
    empty_buffer();
    if (delete_decision != 'y') {
        printf("The deletion of the word has been canceled.\n");
        free(word);
        return;
    }
    if (first == NULL){
        printf("The deletion of the word has failed!\n");
        free(word);
        return;
    }
    second = first->next;
    if (second == NULL)
        third = NULL;
    else
        third = second->next;
    if (first == head && strcmp(word, first->translations[0]) == 0 && second != NULL){
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(first->translations[i]);
        }
        free(first->translations);
        dictionaries[decision].wordList = second;
    } else if (first == head && strcmp(word, first->translations[0]) == 0){
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(first->translations[i]);
        }
        free(first->translations);
        first->translations = NULL;
    } else if (second != NULL) {
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(second->translations[i]);
        }
        free(second->translations);
        first->next = third;
        free(second);
    }
    printf("The word has been deleted successfully!\n");
    free(word);
}


/******************
* Function Name: find_word
* Input: ptr of dictionaries arr, int num of dictionaries
* Output: none
* Function Operation: uses search_word to find the object needed and prints the his translations
******************/
void find_word(int numOfDictionaries, Dictionary *dictionaries){
    int decision;
    char *word;
    Word *head, *word_to_search;
    print_all_dic(numOfDictionaries, dictionaries);
    scanf("%d", &decision);
    decision -= 1;
    head = dictionaries[decision].wordList;
    printf("Enter a word in %s:\n", dictionaries[decision].languages[0]);
    word = scan_no_limit();
    if (word == NULL){
        printf("The search has failed successfully!\n"); // XD
        return;
    }
    word_to_search = search_word(head, word, 0);
    if (word_to_search == NULL){
        printf("There are no translations for \"%s\" in this dictionary.\n", word);
        free(word);
        return;
    }
    free(word);
    printf("The translations are:\n");
    for (int i = 1; i < dictionaries[decision].numOfLanguages; i++) {
        printf("%s: %s", dictionaries[decision].languages[i], word_to_search->translations[i]);
        if (i != dictionaries[decision].numOfLanguages - 1)
            printf(", ");
    }
    printf("\n");
}


/******************
* Function Name: destroy_linked_lst
* Input: ptr (Word) of head of the linked list, int num of languages
* Output: none
* Function Operation: recursivly go to all objects of the linked list and frees the translations and themselves
******************/
void destroy_linked_lst(Word *head, int numOfLang){
    if (head == NULL)
        return;
    destroy_linked_lst(head->next, numOfLang);
    if (head->translations != NULL) {
        for (int i = 0; i < numOfLang; i++) {
            free(head->translations[i]);
        }
        free(head->translations);
    }
    free(head);
}


/******************
* Function Name: del_dic
* Input: ptr of dictionaries arr, ptr num of dictionaries
* Output: none
* Function Operation: choose which dic to del and uses destroy_linked_list then decreasing num of dic
******************/
void del_dic(int *numOfDictionaries, Dictionary *dictionaries){
    int decision;
    char del_decision;
    Word *head;
    print_all_dic(*numOfDictionaries, dictionaries);
    scanf("%d", &decision);
    if (decision > *numOfDictionaries){
        printf("The deletion of the dictionary has failed!\n");
        return;
    }
    decision -= 1;
    printf("Are you sure? (y/n)\n");
    empty_buffer();
    scanf("%c", &del_decision);
    empty_buffer();
    if (del_decision != 'y'){
        printf("The deletion of the dictionary has been canceled.\n");
        return;
    }
    head = dictionaries[decision].wordList;
    destroy_linked_lst(head, dictionaries[decision].numOfLanguages);
    for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
        free(dictionaries[decision].languages[i]);
    }
    free(dictionaries[decision].languages);
    *numOfDictionaries -= 1;
    if (*numOfDictionaries == 0){
        printf("The dictionary has been deleted successfully!\n");
        return;
    }
    for (int i = decision; i < *numOfDictionaries - decision; i++) {
        dictionaries[i] = dictionaries[i + 1];
    }
    dictionaries = (Dictionary *) realloc(dictionaries, *numOfDictionaries * sizeof(Dictionary));
    printf("The dictionary has been deleted successfully!\n");
}


/******************
* Function Name: free_all
* Input: ptr of dictionaries arr, int num of dictionaries
* Output: none
* Function Operation: iterates all the dic and del all the data in them
******************/
void free_all(Dictionary *dictionaries, int numOfDictionaries){
    if (numOfDictionaries == 0)
        return;
    for (int i = 0; i < numOfDictionaries; i++) {
        destroy_linked_lst(dictionaries[i].wordList, dictionaries[i].numOfLanguages);
        for (int j = 0; j < dictionaries[i].numOfLanguages; j++) {
            free(dictionaries[i].languages[j]);
        }
        free(dictionaries[i].languages);
    }
    free(dictionaries);
}


int main(){
    Dictionary *dictionaries;
    int numOfDictionaries = 0, decision;
    dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
    print_menu();
    while (1) {
        scanf("%d", &decision);
        if (decision == 1) {
            // increasing the memory of dictionaries arr
            dictionaries = (Dictionary *) realloc(dictionaries, sizeof(Dictionary) * (numOfDictionaries + 1));
            if (dictionaries == NULL){
                printf("The creation of the dictionary has failed!\n");
                continue;
            }
            create_dic(dictionaries, &numOfDictionaries);
        } else if (1 < decision && decision < 6 && numOfDictionaries == 0) {
            printf("This option is not available right now, try again:\n");
            continue;
        } else if (decision == 2) {
            add_word(numOfDictionaries, dictionaries);
        } else if (decision == 3) {
            del_word(numOfDictionaries, dictionaries);
        } else if (decision == 4) {
            find_word(numOfDictionaries, dictionaries);
        } else if (decision == 5) {
            del_dic(&numOfDictionaries, dictionaries);
        } else if (decision == 6) {
            free_all(dictionaries, numOfDictionaries);
            printf("Bye!\n");
            return 0;
        } else {
            printf("Wrong option, try again:");
        }
        print_menu();
    }
}