/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * Programmed by Henry Wan
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define SIZE 512

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // ensure proper input
    if (argc != 1)
    { 
        printf("Usage: ./recover.\n");
        return 1;
    }
    
    FILE* inptr = fopen("card.raw", "r");
    
    // ensure card.raw is in the same file
    if (inptr == NULL)
    {
        printf("Could not open card.raw.\n");
        return 2;
    }
    
    // count the number of images fread reads successfully
    int count = 0;
    
    BYTE data[SIZE];
    char title[7];
    bool hit = false;
    FILE* img;
    
    while ((fread(data, sizeof(BYTE), SIZE, inptr) == SIZE))
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff/home/jharvard/Desktop/home/jharvard/Desktop
        && (data[3] == 0xe0 || data[3] == 0xe1))
        {
            count++;
            if (hit == true)
            { fclose(img); }
            sprintf(title, "%d.jpg", count);
            img = fopen(title, "a");
            hit = true;
        }
        if (hit == true)
        { fwrite(data, sizeof(BYTE), SIZE, img); }
    }
    
    // close infile
    fclose(inptr);
    
    return 0; 
}
