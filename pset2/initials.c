#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    string name_str = GetString();
    printf("%c", toupper(name_str[0]));
    
    for (int i = 1; i < strlen(name_str); i++)
    {
        if (name_str[i - 1] == ' ')
        {
            printf("%c", toupper(name_str[i]));
        }
    }
    
    printf("\n");
}
