/*    N.B. do not allocate memory,
   instead: return a string literal  */

const char *bmi (int weight, double height)
{
    int bmi = weight/(height*height);
    if (bmi <= 18.5) return "Underweight";
    if (bmi <= 20.0) return "Normal";
    if (bmi <= 30.0) return "Overweight";
    return "Obese";
}

#include <stdio.h>
int main(){
    printf("%s\n", bmi(90, 1.8));
}