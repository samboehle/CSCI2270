#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int addToArrayAsc(float sortedArray[], int numElements, float newValue)
{
    int insert;

    if(numElements == 0)
    {
        sortedArray[0] = newValue;
    }
    else
    {
    
    
        for(int i = 0; i < numElements; i++)
        {
            if(newValue < sortedArray[i])
            {
                insert = i;
                break;
            }
            if(i == numElements -1)
            {
                insert = i + 1;
            }
        }

        for(int i = numElements -1; i >= insert; i--)
        {
            sortedArray[i + 1] = sortedArray[i]; 
        }

        sortedArray[insert] = newValue;
    }


    return numElements + 1;
}

int main(int argc, char *argv[])
{
    ifstream myfile;

    myfile.open(argv[1]);

    if(myfile.fail())
    {
        cout << "Failed to open the file." << endl;
    }

    string line;
    float sorted[100];
    int size = 0;



    while(getline(myfile, line))
    {
        addToArrayAsc(sorted, size, stof(line));
        size++;

        for(int i= 0; i < size; i++)
        {
            if(i != 0)
            {
                cout << ",";
            }
            cout << sorted[i];
        }
        cout << endl;
    } 
    return 0;

}