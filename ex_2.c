/***********************
* Nir koren
* 316443902
* ass02
***********************/


#include <stdio.h>
#include <math.h>

int init(){
    int key;
    while (1){
        printf("Choose an option:\n"
               "        1. hexadecimal to Decimal\n"
               "        2. Decimal to Base\n"
               "        3. Base to Decimal\n"
               "        4. PLUS\n"
               "        5. Shape\n"
               "        6. Count bits\n"
               "        7. Exit\n");
        scanf("%d", &key);
        if (key <= 7)
            return key;
        printf("Wrong option!\n");

    }
}


void hextodec(){
    char hexnum;
    printf("Enter a reversed number in base 16:\n");
    while (1){
        scanf("%c", &hexnum);
        if (hexnum == 'e') {
            printf("%c", hexnum);
            return;
        }
    }

}

int main(){
    int key;

    key = init();
    switch (key) {
        case 1:
            hextodec();
            break;
//        case 2:
//            dectobase();
//            break;
//        case 3:
//            basetodec();
//            break;
//        case 4:
//            plus();
//            break;
//        case 5:
//            shape();
//            break;
//        case 6:
//            cntbits();
//            break;
        default:
            return 0;
    }
}