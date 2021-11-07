/***********************
* Nir koren
* 316443902
* ass01
***********************/


#include <stdio.h>
#include <math.h>


/******************
* Function Name: hello
* Input: None
* Output: printing "hello \/\/orld %d\n"
* Function Operation: using the printf function and double // %% \\
******************/
void hello(){
    printf("\"hello \\/\\/orld %%d\\n\"\n");
}


/******************
* Function Name: distance
* Input: two points (x1, y1), (x2, y2)
* Output: the distance between the points
* Function Operation: using the distance formula (pitagorian triangle) sqrt((x1 - x2)^2 + (y1 - y2)^2)
******************/
void distance(){
    double x1, x2, y1, y2, dist;
    printf("Enter x1:\n");
    scanf("%lf", &x1);
    printf("Enter y1:\n");
    scanf("%lf", &y1);
    printf("Enter x2:\n");
    scanf("%lf", &x2);
    printf("Enter y2:\n");
    scanf("%lf", &y2);
    dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    printf("The distance between the points is: %.4lf\n", dist);
}


/******************
* Function Name: conversions
* Input: distance in nano meters
* Output: the same distance in  mm, cm, dm, m, km and nn with 5 numbers before the decimal point and 4 after
* Function Operation: using the formulas mm = nm / 1e6, cm = mm / 10, dm = cm / 10, m = dm / 10, km = m / 1000
******************/
void conversions(){
    int nm;
    double km, m, dm, cm, mm;
    printf("Please enter nm:\n");
    scanf("%d", &nm);
    mm = nm / 1e6;
    cm = mm / 10;
    dm = cm / 10;
    m = dm / 10;
    km = m / 1000;
    printf("%010.4lf km\n", km);
    printf("%010.4lf m\n", m);
    printf("%010.4lf dm\n", dm);
    printf("%010.4lf cm\n", cm);
    printf("%010.4lf mm\n", mm);
    printf("%010d nm\n", nm);
}


/******************
* Function Name: baking
* Input: baking time of the cake, the time it was put in the oven
* Output: the time when you should get it out of the oven
* Function Operation: adding the time together using modulo and with the remainder
******************/
void baking(){
    int add_h, add_m, add_s, start_h, start_m, start_s, final_h, final_m, final_s;
    printf("Please enter the baking time: [hh:mm:ss]\n");
    scanf("%d:%d:%d", &add_h, &add_m, &add_s);
    printf("When did you put the cake into the oven? [hh:mm:ss]\n");
    scanf("%d:%d:%d", &start_h, &start_m, &start_s);
    final_s = (start_s + add_s);
    final_m = (start_m + add_m + final_s / 60);
    final_h = (start_h + add_h + final_m / 60) % 24;
    printf("The cake will be ready at %02d:%02d:%02d o'clock.\n", final_h, final_m % 60, final_s % 60);
}

int main() {
    hello();
    distance();
    conversions();
    baking();
    return 0;
}
