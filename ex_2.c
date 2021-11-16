/***********************
* Nir koren
* 316443902
* ass02
***********************/


#include <stdio.h>
#include <math.h>


void empty_buffer(){
    char c;
    while (1){
        scanf("%c", &c);
        if (c == '\n')
            return;
    }
}


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
            empty_buffer();
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
    if (decnum < 0) {
        printf("Error!\n");
        return;
    }
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
    int long basecnum, result = 0;
    printf("Enter base and a number:\n");
    scanf("%d %ld", &base, &basecnum);
    if (basecnum < 0){
        printf("Error!\n");
        return;
    }
    while (1){
        if (basecnum == 0)
            break;
        result += (basecnum % 10) * pow(base, cnt);
        basecnum /= 10;
        cnt++;
    }
    printf("%ld\n", result);
}


void plus(){
    int long n1, n2, max, min, result = 0, tmp_carry = 0, carry = 0, tmp_sum, last_round = 0;
    int cnt = 0;
    printf("Enter 2 binary numbers:\n");
    scanf("%ld %ld", &n1, &n2);
    max = n1 > n2 ? n1 : n2;
    min = n1 > n2 ? n2 : n1;
    if (n1 < 0 || n2 < 0){
        printf("Error!\n");
        empty_buffer();
        return;
    }
    while (1){
        if (n1 % 10 > 1 || n2 % 10 > 1){
            printf("Error!\n");
            empty_buffer();
            return;
        }
        if (n1 == 0 && n2 == 0)
            last_round = 1;
        carry += tmp_carry * pow(10, cnt);
        tmp_sum = (n1 % 10) + (n2 % 10) + tmp_carry;
        tmp_carry = tmp_sum / 2;
        result += (tmp_sum % 2) * pow(10, cnt);
        n1 /= 10;
        n2 /= 10;
        cnt++;
        if (last_round)
            break;
    }
    printf("%0*d\n%0*d\n+\n%0*d\n", cnt, carry, cnt, max, cnt, min);
    for (int i = 0; i < cnt; ++i) {
        printf("-");
    }
    printf("\n%d\n", result);
    empty_buffer();
}


void shape(){
    int n, width;
    printf("Enter a number:\n");
    scanf("%d", &n);
    width = 2 * n + 2;
    for (int i = 0; i < width; i++) {
        if (i <= 2 || width - i <= 3) {
            printf("#");
            continue;
        }
        printf(" ");
    }
    printf("\n");

}


int main(){
    int key = 0;
    while (1) {
        printf("Choose an option:\n"
               "        1. hexadecimal to Decimal\n"
               "        2. Decimal to Base\n"
               "        3. Base to Decimal\n"
               "        4. PLUS\n"
               "        5. Shape\n"
               "        6. Count bits\n"
               "        7. Exit\n");
        scanf("%d", &key);
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
            case 4:
                plus();
                break;
            case 5:
                shape();
                break;
//            case 6:
//                cntbits();
//                break;
            case 7:
                return 0;
            default:
                printf("Wrong option!\n");
                empty_buffer();
                break;
        }
    }
}