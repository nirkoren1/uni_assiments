/***********************
* Nir koren
* 316443902
* ass04
***********************/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define WORDSSIZE 16
#define SIZEPERWORD 21


/******************
* Function Name: string_to_tokens_lst
* Input: str, deliminator, size of the lst to update
* Output: ptr to the tokens lst
* Function Operation: cuts the str to tokens using the strtok func shown in class
******************/
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


/******************
* Function Name: swap
* Input: **ptr1, **ptr2
* Output: none
* Function Operation: swap the val of the pointers (addresses of the words)
******************/
void swap(char** ptr1, char** ptr2)
{
    char * temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}


/******************
* Function Name: lexicogragic_sort
* Input: words list, size of the list
* Output: none
* Function Operation: using strcmp and swap func to sort the list in lexicografic order
******************/
void lexicografic_sort(char **tokens, int *size){
    int i = 1;
    while (i){
        i = 0;
        for (int j = 1; j < *size - 1; j++) {
            if (strcmp(tokens[j], tokens[j + 1]) > 0){
                swap(&tokens[j], &tokens[j + 1]);
                i = 1;
            }
        }
    }
}


/******************
* Function Name: init
* Input: size (of the malloc ptr for free later)
* Output: pointer to char list
* Function Operation: takes a clue and words, sorting them in lexicografic order and return the words
******************/
char **init(int *size){
    char words[WORDSSIZE * SIZEPERWORD] = {"\0"}, **token_ptr;
    printf("Enter your words:\n");
    fgets(words, WORDSSIZE * SIZEPERWORD, stdin);
    words[strlen(words) - 1] = '\0';
    token_ptr = string_to_tokens_lst(words, ":,", size);
    lexicografic_sort(token_ptr, size);
    printf("choose an option:\n");
    for (int j = 1; j < *size; j++) {
        printf("%d: %s\n",j, token_ptr[j]);
    }

    return token_ptr;
}


/******************
* Function Name: empty_buffer
* Input: none
* Output: none
* Function Operation: cleans the buffer with scanf for error measures
******************/
int is_over(const char *str1, const char *str2){
    int i = 0, j = 0, match = 0, sum_match = 0;
    while (str1[i] != '\0'){
        if (str1[i] == ' '){
            i++;
            sum_match++;
            continue;
        }
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


/******************
* Function Name: print_man
* Input: bad score
* Output: prints the hanged man
* Function Operation: prints the hanged man according to the bad score
******************/
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


/******************
* Function Name: print_used_chars
* Input: guessed chars
* Output: prints the guessed words
* Function Operation: prints the guessed words by order: *, *, *, *
******************/
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
* Function Name: is_char_in_chars
* Input: char, char list
* Output: int (bool) 1 if char in chars else 0
* Function Operation: iterating the chars and chek if char equal
******************/
int is_char_in_chars(char current_char, const char *chars){
    int i = 0, out = 0;
    while (chars[i] != '\0'){
        if (chars[i] == current_char) {
            out = 1;
            break;
        }
        i++;
    }
    return out;
}


/******************
* Function Name: print_word
* Input: the word, guessed chars
* Output: prints the target word
* Function Operation: prints the word in format:   _**___   if * in guessed chars
******************/
void print_word(char *the_word, char *guessedChars){
    int i = 0;
    while (the_word[i] != '\0'){
        if (the_word[i] == ' ') {
            printf(" ");
        }else if (is_char_in_chars(the_word[i], guessedChars)) {
            printf("%c", the_word[i]);
        }else {
            printf("_");
        }
        i++;
    }
    printf("\n");
}


/******************
* Function Name: hang_man
* Input: clue, the word
* Output: none
* Function Operation: contains the logic of the hang man game
******************/
void hang_man(char *clue, char *the_word){
    int bad_score = 0, clue_used = 0, size = 1;
    char *guessedChars = (char *) calloc(1, sizeof(char)), current_char;
    while (!is_over(the_word, guessedChars) && bad_score < 5){
        print_man(bad_score);
        print_word(the_word, guessedChars);
        if (!clue_used)
            printf("do you want a clue? press -> *\n");
        printf("The letters that you already tried:");
        print_used_chars(guessedChars);
        printf("please choose a letter:\n");
        scanf("%c", &current_char);
        empty_buffer();
        if (current_char == '*' && !clue_used){
            printf("the clue is: %s.\n", clue);
            clue_used = 1;
            continue;
        } else if (current_char == '*'){
            continue;
        } else if (is_char_in_chars(current_char, guessedChars)){
            printf("You've already tried that letter.\n");
            continue;
        } else {
            size++;
            guessedChars = (char *) realloc(guessedChars, (size) * sizeof(char));
            guessedChars[size - 2] = current_char;
            guessedChars[size - 1] = '\0';
        }
        if (!is_char_in_chars(current_char, the_word))
            bad_score++;
    }
    print_man(bad_score);
    if (bad_score == 5){
        printf("The word is %s, GAME OVER!", the_word);
    } else {
        printf("The word is %s, good job!", the_word);
    }
    free(guessedChars);
}



int main(){
    char **token_ptr, *clue, *the_word;
    int chosen, size = 0;
    token_ptr = init(&size);
    scanf("%d", &chosen);
    empty_buffer();
    clue = token_ptr[0];
    the_word = token_ptr[chosen];
    hang_man(clue, the_word);
    // free all heap
    for (int i = 0; i < size; i++) {
        free(token_ptr[i]);
    }
    free(token_ptr);
}
