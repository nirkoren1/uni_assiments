#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int GCDRec(int large, int small, int iter){
    if (iter == 1)
        return 1;
    return
}

int GCD(int num1, int num2){
    return num1 > num2 ? GCDRec(num1, num2, num2) : GCDRec(num2, num1, num1);
}

int main()
{
    printf("%d", GCD(50, 10));
}

