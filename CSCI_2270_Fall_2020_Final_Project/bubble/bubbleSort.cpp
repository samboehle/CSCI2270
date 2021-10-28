#include "bubblesort.hpp"
#include <iostream>
using namespace std;


void BubbleSort::insert(int *tempArray, int sizeTemp, int *data)
{
    for(int i = 0; i < sizeTemp; i++)
    {
        tempArray[i] = data[i];
    }
}

void BubbleSort::print(int array[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << array[i] << endl;
    }
}

void BubbleSort::sort(int *array, int size)
{
    //loop to iterate over array
    for(int i= 0; i < size - 1; i++)
    {
        //loop that iterates over array to flip values
        for(int x = 0; x < size - i - 1; x++)
        {
            //tests to see if next 
            if(array[x] > array[x+1])
            {
                int switcher = array[x];
                array[x] = array[x+1];
                array[x+1]=switcher;
            }
        }
    }
}

