/***********************
* Nir koren
* 316443902
* ass03
***********************/


#include <stdio.h>
#include <math.h>
#define SIZE 100


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


void lycherl(){

}


void longest(){

}



int main(){
//    int key;
//    printf("1: primes\n"
//           "2: goldbach\n"
//           "3: lychrel\n"
//           "4: max set\n");
//    scanf("%d", &key);
//    switch (key) {
//        case 1:
//            prime();
//            break;
//        case 2:
            gold();
//            break;
//        case 3:
//            lycherl();
//            break;
//        case 4:
//            longest;
//            break;
//        default:
//            printf("Wrong option!");
//    }
}