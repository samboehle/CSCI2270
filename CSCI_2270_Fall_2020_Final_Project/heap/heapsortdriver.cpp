#include "heapsort.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

//split input file up
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
    int testData[10000];
    float sort[100];
    //read in file contents
    ifstream myfile;
    myfile.open("dataSetA.csv");
    if(myfile.fail())
    {
        cout << "Failed to open the file." << endl;
    }

    string line;
    string current[10000];
    int size = 0;
    getline(myfile,line);
    split(line, ',', current, 10000);

    for(int i = 0; i < 10000; i++)
    {
        testData[i] = stoi(current[i]);
    }

    myfile.close();

    using namespace std::chrono;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> execTime;

    for(int i = 0; i < 100; i++)
    {
        int size = 100 +(100*i);
        int tempArary[size];
        HeapSort myHeap(size);

        for(int x = 0; x < size; x++)
        {
            tempArary[x] = testData[x];
        }
        //time insert b/c inserting is part of the sorting function of the heap
        start = high_resolution_clock::now();
        for(int x =0; x < size; x++)
        {
            myHeap.insert(tempArary[x]);
        }
        //popping out the top node of the heap in order to get sorted array
        for(int x =0; x < size; x++)
        {
            tempArary[x] = myHeap.pop();
        }
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        sort[i] = execTime.count();
    }
    fstream output;

    output.open("heap_output.csv");

    output << "Sort" << endl;
    for(int i =0; i < 100; i++)
    {
        output << sort[i] << endl;
    }

   return 0;

}