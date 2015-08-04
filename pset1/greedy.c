#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    float change = 0;
    int quarter_n = 0;
    int dime_n = 0;
    int nickel_n = 0;
    
    do
    {
    printf("How much is the change?: ");
    change = GetFloat();
    } while (change <= 0);
    
    int dollar = round(change - 0.5);
    int cents = round((change - dollar) * 100);
    
    while (cents >= 25)
    {
        cents -= 25;
        quarter_n++;
    }
    
    while (cents >= 10)
    {
        cents -= 10;
        dime_n++;
    }
    
    while (cents >= 5)
    {
        cents -= 5;
        nickel_n++;
    }
    
    printf("%d\n", dollar + quarter_n + dime_n + nickel_n + cents);
}
