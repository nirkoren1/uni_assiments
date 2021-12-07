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
        for (int j = 1; j < size - 1; j++) {
            if (strcmp(tokens[j], tokens[j + 1]) > 0){
                swap(&tokens[j], &tokens[j + 1]);
                i = 1;
            }
        }
    }
}


char **init(){
    char words[WORDSSIZE * SIZEPERWORD] = {"\0"}, **token_ptr;
    int size = 0;
    printf("Enter your words:\n");
    fgets(words, WORDSSIZE * SIZEPERWORD, stdin);
    words[strlen(words) - 1] = '\0';
    token_ptr = string_to_tokens_lst(words, ":,", &size);
    lexicografic_sort(token_ptr, size);
    printf("choose an option:\n");
    for (int j = 1; j < size; j++) {
        printf("%d: %s\n",j, token_ptr[j]);
    }

    return token_ptr;
}


int is_over(char *str1, char *str2){
    int i = 0, j = 0, match = 0, sum_match = 0;
    while (str1[i] != '\0'){
        while (str2[j] != '\0'){
            if (str1[i] == str2[j]){
                match = 1;
                break;
            }
            j++;
        }
        j = 0;
        if (match)
            sum_match++;
        match = 0;
        i++;
    }
    if (sum_match == i)
        return 1;
    return 0;
}


void print_man(int bad_score){
    if (bad_score == 0)
        printf(" _________________\n"
                       "|                |\n"
                       "|                |\n"
                       "|                |\n"
                       "|                |\n"
                       "|                |\n"
                       "|________________|\n");
    else if (bad_score == 1)
        printf(" _________________\n"
                       "|                |\n"
                       "|  **            |\n"
                       "|  **            |\n"
                       "|                |\n"
                       "|                |\n"
                       "|________________|\n");
    else if (bad_score == 2)
        printf(" _________________\n"
                       "|                |\n"
                       "|  **        **  |\n"
                       "|  **        **  |\n"
                       "|                |\n"
                       "|                |\n"
                       "|________________|\n");
    else if (bad_score == 3)
        printf(" _________________\n"
                       "|  --            |\n"
                       "|  **        **  |\n"
                       "|  **        **  |\n"
                       "|                |\n"
                       "|                |\n"
                       "|________________|\n");
    else if (bad_score == 4)
        printf(" _________________\n"
                       "|  --        --  |\n"
                       "|  **        **  |\n"
                       "|  **        **  |\n"
                       "|                |\n"
                       "|                |\n"
                       "|________________|\n");
    else
        printf(" _________________\n"
                       "|  --        --  |\n"
                       "|  **        **  |\n"
                       "|  **        **  |\n"
                       "|                |\n"
                       "| \\/\\/\\/\\/\\/\\/\\  |\n"
                       "|________________|\n");
}


void print_used_chars(char *chars){
    int i = 0;
    while (chars[i] != '\0'){
        if (i == 0)
            printf(" %c", chars[i]);
        else
            printf(", %c", chars[i]);
        i++;
    }
    printf("\n");
}


void empty_buffer(){
    char c;
    while (1){
        scanf("%c", &c);
        if (c == '\n')
            return;
    }
}


void hang_man(char *clue, char *the_word){
    int bad_score = 0, clue_used = 0;
    char *guessedChars = (char *) malloc(sizeof(char)), current_char;
    guessedChars[0] = '\0';
    while (is_over(the_word, guessedChars)){
        print_man(bad_score);
        if (!clue_used)
            printf("do you want a clue? press -> *\n");
        printf("The letters that you already tried:");
        print_used_chars(guessedChars);
        printf("please choose a letter:\n");
        scanf("%c", &current_char);
        empty_buffer();
    }
}


int main(){
    char **token_ptr, *clue, *the_word;
    int chosen;
    token_ptr = init();
    scanf("%d", &chosen);
    clue = token_ptr[0];
    the_word = token_ptr[chosen];
    printf("%s", clue);
    hang_man(clue, the_word);
}
