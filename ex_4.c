/***********************
* Nir koren
* 316443902
* ass04
***********************/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define WORDSSIZE 15
#define SIZEPERWORD 20


char **string_to_tokens_lst(char str[], char delim[], int *size){
    int i = -1;
    char *token = strtok(str, delim);
    char **out = (char **) malloc(sizeof (char *));
    token = strtok(NULL, delim);
    while (token != NULL) {
        i += 1;
        *size += 1;
        out = (char **) realloc(out, sizeof (char *) * (i + 1));
        out[i] = (char *) malloc(sizeof(char) * strlen(token) + 1);
        strcpy(out[i], token);
        token = strtok(NULL, delim);
    }
    return out;
}


void swap(char** ptr1, char** ptr2)
{
    char * temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}


void lexicografic_sort(char **tokens, int size){
    int i = 1;
    while (i){
        i = 0;
        for (int j = 0; j < size - 1; j++) {
            if (strcmp(tokens[j], tokens[j + 1]) > 0){
                swap(&tokens[j], &tokens[j + 1]);
                i = 1;
            }
        }
    }
}


char *init(){
    char words[WORDSSIZE * SIZEPERWORD] = {"\0"}, **token_ptr;
    int size = 0;
    printf("Enter your words:\n");
    fgets(words, WORDSSIZE * SIZEPERWORD, stdin);
    words[strlen(words) - 1] = '\0';
    token_ptr = string_to_tokens_lst(words, ":,", &size);
    lexicografic_sort(token_ptr, size);
    for (int j = 0; j < size; j++) {
        printf("%s\n", token_ptr[j]);
    }
}


int main(){
    init();
//    hang_man();
}
