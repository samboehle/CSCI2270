#include "bubblesort.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

//standard function used to split up the input file
int split(string main, char splitter, string array[], int size)
{
    main += splitter;
    char current;
    int place = 0;


    for(int i = 0; i < main.length(); i++)
    {
        
        if(main[i] != splitter)
        {
            array[place] += main[i];
        }
        else if(main[i] == splitter)
        {
            place++;
        }
    }

    return place;

}

int main()
{
    BubbleSort mySort;
    
    int testData[10000];
    float sort[100];

    ifstream myfile;
    myfile.open("dataSetA.csv");
    if(myfile.fail())
    {
        cout << "Failed to open the file." << endl;
    }

    //this code reads the file using getline and the split function
    string line;
    string current[10000];
    int size = 0;
    getline(myfile,line);
    split(line, ',', current, 10000);
    //convert string to int
    for(int i = 0; i < 10000; i++)
    {
        testData[i] = stoi(current[i]);
    }

    myfile.close();

    using namespace std::chrono;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> execTime;

    int ranNum[100];

    for(int i = 0; i < 100; i++)
    {
        //size calculates how much data should be taken to be sorted
        int size = 100 +(100*i);
        int tempArary[size];

        mySort.insert(tempArary, size, testData);

        start = high_resolution_clock::now();
            mySort.sort(tempArary, size);
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        sort[i] = execTime.count();
    }
    fstream output;

    output.open("bubble_output.csv");

    output << "sort" << endl;
    for(int i =0; i < 100; i++)
    {
        output << sort[i] << endl;
    }

   return 0;

}