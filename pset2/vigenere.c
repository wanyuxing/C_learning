#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int key_len = strlen(key);
        int key_pos = 0;
        string sentence = GetString();
    
        for (int i = 0; i < strlen(sentence); i++)
        {
            int pos = (int) sentence[i];
            if (pos >= 65 && pos < 65 + 26)
            {
                int pos_new = (pos - 65 - 97 + (int) tolower(key[key_pos])) % 26 + 65;
                printf("%c", (char) pos_new);
                key_pos = (key_pos + 1) % key_len;
            }
            else if (pos >= 97 && pos < 97 + 26)
            {     
                int pos_new = (pos - 97 - 97 + (int) tolower(key[key_pos])) % 26 + 97;
                printf("%c", (char) pos_new);
                key_pos = (key_pos + 1) % key_len;
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
