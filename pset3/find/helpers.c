/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int bot = 0;
    int top = n - 1;
    int mid = (bot + top) / 2;
    while (top - bot >= 0)
    {
        if (values[mid] == value)
        { return true; }
        else if (values[mid] > value)
        { 
            top = mid - 1; 
            mid = (bot + top) / 2;
        }
        else
        { 
            bot = mid + 1;
            mid = (bot + top) / 2;
        }    
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) bubble sorting algorithm
    bool isSorted = false;
    if (isSorted == false)
    {
        int k = 1;
        for (int j = 0; j < n - 1; j++)
        {
            for (int i = 0; i < n - k; i++)
            {
                int count = 0;
                if (values[i] > values[i + 1])
                {
                    int temp = values[i];
                    values[i] = values[i + 1];
                    values[i + 1] = temp;
                    count++;
                }
                if (count == 0)
                { isSorted = true; }
            }
            k++;
        } 
    }
}
