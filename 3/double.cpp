#include <iostream>
#include <string>
using namespace std;


bool ​append​(string* &str_arr​, string ​s​, int &numEntries​, int​ &arraySize​)
{
    bool doubled = false;
    if(numEntries​ == arraySize​)
    {
        string *temp = new string[2*arraySize​];

        for(int i = 0; i < arraySize​; i++)
        {
            temp[i] = str_arr​[i];
        }

        delete [] str_arr​;

        str_arr​ = temp;
        arraySize​ = arraySize​ * 2;
        doubled = true;
    }

    str_arr[numEntries​] = s;

    numEntries​++;

    return doubled;




}