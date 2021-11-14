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
    int decnum = 0, cnt = -1, pow16 = 1;
    printf("Enter a reversed number in base 16:\n");
    scanf("%c", &hexnum);
    while (1){
        scanf("%c", &hexnum);
        if (hexnum == '\n')
            break;
        if (hexnum <= ' ')
            continue;
        cnt++;
        pow16 = pow(16, cnt);
        if (hexnum >= '0' && hexnum <= '9')
            decnum += (hexnum - '0') * pow16;
        else if (hexnum >= 'a' && hexnum <= 'f')
            decnum += (hexnum - 'a' + 10) * pow16;
        else if (hexnum >= 'A' && hexnum <= 'F')
            decnum += (hexnum - 'A' + 10) * pow16;
        else{
            printf("Error!\n");
            decnum = 0;
            while (1){
                scanf("%c", &hexnum);
                if (hexnum == '\n')
                    break;
            }
            break;
        }
    }
    if (decnum == 0)
        return;
    printf("%d\n", decnum);
}


void dectobase(){
    int base, cnt = 0;
    int long decnum, result = 0;
    printf("Enter base and a number:\n");
    scanf("%d %ld", &base, &decnum);
    while (1){
        if (decnum == 0)
            break;
        result += (decnum % base) * pow(10, cnt);
        decnum /= base;
        cnt++;
    }
    printf("%ld\n", result);
}


void basetodec(){
    int base, cnt = 0;
    int long decnum, result = 0;
    printf("Enter base and a number:\n");
    scanf("%d %ld", &base, &decnum);
    while (1){

    }
}


int main(){
    int key;
    while (1) {
        key = init();
        switch (key) {
            case 1:
                hextodec();
                break;
            case 2:
                dectobase();
                break;
            case 3:
                basetodec();
                break;
//            case 4:
//                plus();
//                break;
//            case 5:
//                shape();
//                break;
//            case 6:
//                cntbits();
//                break;
            default:
                return 0;
        }
    }
}