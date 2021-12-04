/***********************
* Nir koren
* 316443902
* ass04
***********************/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


char *string_to_tokens_lst(char str[], char delim[]){
    int i = -1;
    char out[15][20];
    char *token = strtok(str, delim);
    while (token != NULL) {
        i += 1;
        strcpy(out[i], token);
        token = strtok(NULL, delim);
    }
    for (int j = 0; j < i + 1; j++) {
        printf("%s\n", out[j]);
    }
}

char *init(){
    int size_names = 15, size_per_name = 20;
    char names[15 * 20];
    printf("Enter your words:\n");
    scanf("%s", names);
    string_to_tokens_lst("name:Avi cohen,Moshe,Dana!", ":,");
}


int main(){
//    init();
    string_to_tokens_lst("name:Avi cohen,Moshe,Dana!", ":,");
//    hang_man();
}
