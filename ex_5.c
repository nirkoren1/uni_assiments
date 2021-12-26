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


int print_all_dic(int numOfDictionaries, Dictionary *dictionaries){
    if (numOfDictionaries == 0)
        return 1;
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
    return 0;
}


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


void del_word(int numOfDictionaries, Dictionary *dictionaries){
    Word *word_to_del, *head, *prev_word, *next_word;
    int decision = 0;
    char *word;
    char delete_decision;
    print_all_dic(numOfDictionaries, dictionaries);
    scanf("%d", &decision);
    decision -= 1;
    head = dictionaries[decision].wordList;
    printf("Enter a word in %s:\n", dictionaries[decision].languages[0]);
    word = scan_no_limit();
    prev_word = search_word(head, word, 1);
    free(word);
    printf("Are you sure? (y/n)\n");
    scanf("%c", &delete_decision);
    empty_buffer();
    if (delete_decision != 'y') {
        printf("The deletion of the word has been canceled.\n");
        return;
    }
    if (prev_word == NULL){
        printf("The deletion of the word has failed!\n");
        return;
    }
    word_to_del = prev_word->next;
    if (word_to_del == NULL)
        next_word = NULL;
    else
        next_word = word_to_del->next;
    if (word_to_del == NULL){
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(prev_word->translations[i]);
        }
        free(prev_word->translations);
        prev_word->translations = NULL;
    } else if (next_word == NULL && prev_word == head){
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(prev_word->translations[i]);
        }
        free(prev_word->translations);
        head->next = word_to_del;
        free(prev_word);
    } else if (next_word == NULL){
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(word_to_del->translations[i]);
        }
        free(word_to_del->translations);
        free(word_to_del);
        prev_word->next = NULL;
    } else {
        for (int i = 0; i < dictionaries[decision].numOfLanguages; i++) {
            free(word_to_del->translations[i]);
        }
        free(word_to_del->translations);
        prev_word->next = next_word;
        free(word_to_del);
    }
    printf("The word has been deleted successfully!\n");
}


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
    // need to check!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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


void destroy_linked_lst(Word *head, int numOfLang){
    if (head == NULL)
        return;
    destroy_linked_lst(head->next, numOfLang);
    if (head->translations != NULL)
        for (int i = 0; i < numOfLang; i++) {
            free(head->translations[i]);
        }
    free(head);
}


void del_dic(int *numOfDictionaries, Dictionary *dictionaries){
    int decision;
    char del_decision;
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
    destroy_linked_lst(dictionaries[decision].wordList, dictionaries[decision].numOfLanguages);
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


void free_all(Dictionary *dictionaries, int numOfDictionaries){
    if (numOfDictionaries == 0)
        return;
    for (int i = 0; i < numOfDictionaries; i++) {
        destroy_linked_lst(dictionaries[i].wordList, dictionaries[i].numOfLanguages);
        for (int j = 0; j < dictionaries[j].numOfLanguages; j++) {
            free(dictionaries[j].languages[j]);
        }
        free(dictionaries[i].languages);
    }
    free(dictionaries);
}


int main(){
    Dictionary *dictionaries;
    int numOfDictionaries = 0, decision, allDecisions[5] = {0};
    dictionaries = (Dictionary *) malloc(sizeof(Dictionary));
    print_menu();
    while (1) {
        scanf("%d", &decision);
        if (decision == 1) {
            dictionaries = (Dictionary *) realloc(dictionaries, sizeof(Dictionary) * (numOfDictionaries + 1));
            if (dictionaries == NULL){
                printf("The creation of the dictionary has failed!\n");
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
            return 0;
        } else {
            printf("Wrong option, try again:");
        }
        print_menu();
    }
}