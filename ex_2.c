/***********************
* Nir koren
* 316443902
* ass02
***********************/


#include <stdio.h>
#include <math.h>


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
* Function Name: hextodec
* Input: int long hexadecimal number
* Output: the number in decimal base
* Function Operation: using the definition of hexa number
******************/
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


/******************
* Function Name: dectobase
* Input: int base, int long decimal number
* Output: the number in the base specified
* Function Operation: deviation and % base
******************/
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


/******************
* Function Name: basetodec
* Input: int base, int long in the base number
* Output: the number in decimal base
* Function Operation: deviation and % 10
******************/
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


/******************
* Function Name: plus
* Input: int binary, int binary
* Output: the process of adding the two binary numbers
* Function Operation: regular adding binary numbers as seen in the class
******************/
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


/******************
* Function Name: shape
* Input: int n
* Output: a butterfly made of * covered by # with width 2n
* Function Operation: placing "#", "*" and " " with a certain logic to the line index
******************/
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
    if (n != 0) {
        printf("\n");
        for (int i = 1; i <= n - 1; i++) {
            for (int j = 1; j <= width; j++) {
                if (j == 1 || j == width || j == 2 + i || j == width - 1 - i) {
                    printf("#");
                    continue;
                }
                if ((j >= 2 && j < 2 + i) || (j > width - 1 - i && j < width)) {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
            printf("\n");
        }
        for (int i = 0; i < width; i++) {
            if (i == 0 || i == width - 1)
                printf("#");
            else
                printf("*");
        }
        printf("\n");
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 1; j <= width; j++) {
                if (j == 1 || j == width || j == 2 + i || j == width - 1 - i) {
                    printf("#");
                    continue;
                }
                if ((j >= 2 && j < 2 + i) || (j > width - 1 - i && j < width)) {
                    printf("*");
                    continue;
                }
                printf(" ");
            }
            printf("\n");
        }
    } else
        printf("\n");
    for (int i = 0; i < width; i++) {
        if (i <= 2 || width - i <= 3) {
            printf("#");
            continue;
        }
        printf(" ");
    }
    printf("\n");
}


/******************
* Function Name: cntbits
* Input: int number
* Output: the number of times that 1 appears in his binary presentation
* Function Operation:
******************/
void cntbits(){
    int long a, result = 0;
    printf("enter a number:\n");
    scanf("%ld", &a);
    while (1){
        if (a % 2 == 1)
            result += 1;
        a /= 2;
        if (a == 0)
            break;
    }
    printf("no of bits those are 1 in its binary representation: %ld\n", result);
}


int main(){
    int key = 0;
    while (1) {
        printf("Choose an option:\n"
               "\t1. hexaDecimal to Decimal\n"
               "\t2. Decimal to Base\n"
               "\t3. Base to Decimal\n"
               "\t4. PLUS\n"
               "\t5. Shape\n"
               "\t6. Count bits\n"
               "\t7. Exit\n");
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
            case 6:
                cntbits();
                break;
            case 7:
                return 0;
            default:
                printf("Wrong option!\n");
                empty_buffer();
                break;
        }
    }
}