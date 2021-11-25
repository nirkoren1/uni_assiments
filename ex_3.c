/***********************
* Nir koren
* 316443902
* ass03
***********************/


#include <stdio.h>
#include <math.h>


void prime(){

}


void gold(){

}


void lycherl(){

}


void longest(){

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
            longest;
            break;
        default:
            printf("Wrong option!");
    }
}