#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        long k = atoi(argv[1]);
    
        string sentence = GetString();
    
        for (int i = 0; i < strlen(sentence); i++)
        {
            int pos = (int) sentence[i];
            if (pos >= 65 && pos < 65 + 26)
            {
                int pos_new = (pos - 65 + k) % 26 + 65;
                printf("%c", (char) pos_new);
            }
            else if (pos >= 97 && pos < 97 + 26)
            {
                int pos_new = (pos - 97 + k) % 26 + 97;
                printf("%c", (char) pos_new);
            }
            else
            { printf("%c", sentence[i]); }
        }
        printf("\n");
        return 0;
    }
    else
    { return 1; }
}
