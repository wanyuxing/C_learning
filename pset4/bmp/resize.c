/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Programmed by Henry Wan
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n <= 0)
    {
        printf("Pls input a n as positive integer\n");
        return 2;
    }

    // remember filenames and scale of picture
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_n;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_n = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_n;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_n = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine new and original parameters
    int padding_org =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new =  (4 - (bi.biWidth * n * sizeof(RGBTRIPLE)) % 4) % 4;
    bi_n.biWidth = bi.biWidth * n;
    bi_n.biHeight = bi.biHeight * n;
    
    // write outfile's BITMAPFILEHEADER
    bf_n.bfSize = bf.bfSize + sizeof(bi_n.biWidth + padding_new) * bi_n.biHeight - sizeof(bi.biWidth + padding_org) * bi.biHeight;
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    bi_n.biSizeImage = sizeof(n * bi.biWidth + padding_new) * n * abs(bi.biHeight);
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int m = 0; m < n; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int c = 0; c < n; c++)  
                {   
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // move the inptr pointer back to the origin of the line
            fseek(inptr, -sizeof(RGBTRIPLE) * bi.biWidth, SEEK_CUR);

            // then add it back
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip to the next line
        fseek(inptr, sizeof(RGBTRIPLE) * bi.biWidth + padding_org, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
