/***********************
* Nir koren
* 316443902
* ass03
***********************/


#include <stdio.h>
#include <math.h>
#define SIZE 100
#define LIMIT 30



int is_prime(int num){
    for (int i = 2; i < num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}


void prime(){
    for (int i = 2; i < SIZE; i++) {
        if (is_prime(i))
            printf("%d ", i);
    }
    printf("\n");
}


void gold(){
    int prime_arr[SIZE] = {0};
    for (int j = 0; j < SIZE; j++) {
        for (int i = 2; i < SIZE; i++) {
            if (is_prime(i))
                prime_arr[i] = i;
        }
    }
    for (int k = 4; k < SIZE; k += 2) {
        for (int i = 0; i < SIZE; i++) {
            if (prime_arr[i] != 0) {
                for (int j = 0; j < SIZE; j++) {
                    if (prime_arr[j] + prime_arr[i] == k)
                        printf("%d = %d + %d\n", k, i, j);
                }
            }
        }
    }
}


int inverse_num(int num){
    int output = 0;
    while (1){
        output += (num % 10) ;
        num /= 10;
        if (num == 0)
            return output;
        output *= 10;
    }
}


int is_poly(int num){
    if (num == inverse_num(num))
        return 1;
    return 0;
}


void lycherl(){
    for (int i = 1; i < LIMIT ; i++) {
        printf("%d", i);
        int result = i, rev;
        while (!is_poly(result)){
            rev = inverse_num(result);
            printf(":%d+%d=%d", result, rev, result + rev);
            result += rev;
        }
        printf("\n");
    }
}


int get_longest_ser(int lst[], int i, int pre_big){
    int bigger_than = 0;
    if (i == 0)
        return 0;
    for (int j = i; j >= 0; j--) {
        if (lst[i] > lst[j])
            bigger_than += 1;
    }
    if (bigger_than < pre_big)
        return 1 + get_longest_ser(lst, i - 1, bigger_than);
    return get_longest_ser(lst, i - 1, bigger_than);
}


void longest(){
    int lst_len, max, lst[SIZE];
    printf("Enter the number of elements\n");
    scanf("%d", &lst_len);
    for (int i = 0; i < lst_len; i++) {
        scanf("%d", &lst[i]);
    }
    max = get_longest_ser(lst, lst_len - 1, lst_len);
    printf("%d", max);
}


int main(){
    int key;
    printf("1: primes\n"
           "2: goldbach\n"
           "3: lychrel\n"
           "4: max set\n");
    scanf("%d", &key);
    switch (key) {
        case 1:
            prime();
            break;
        case 2:
            gold();
            break;
        case 3:
            lycherl();
            break;
        case 4:
            longest();
            break;
        default:
            printf("Wrong option!");
    }
}