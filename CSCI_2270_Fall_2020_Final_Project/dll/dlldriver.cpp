#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "dll.hpp"
using namespace std;

//split input file
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


//function provides a random value in order to search array
int random(int lower, int upper) 
{
    return (rand() % (upper - lower + 1)) + lower; 
} 


int main()
{
    LinkedList myList;
    
    int testData[10000];
    float insert[100];
    float search[100];

    //read in file
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

    using namespace std:: chrono;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double> execTime;

    int ranNum[100];

    for(int i = 0; i < 100; i++)
    {
        //insert values
        start = high_resolution_clock::now();
        for(int x = i*100; x < i*100 + 100; x++)
        {
            myList.insert(testData[x]);
        }
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        insert[i] = execTime.count() / 100;

        for(int x = 0; x < 100; x++)
        {
            ranNum[x] = random(0, 99 + 100*i);
        }

        //search list for values
        start = high_resolution_clock::now();
        for(int i = 0; i < 100; i++)
        {
            myList.searchList(testData[ranNum[i]]);
        }
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        search[i] = execTime.count() / 100;

    }

    fstream output;

    output.open("dll_output.csv");

    output << "Insert" << ", " << "Search" << endl;
    for(int i =0; i < 100; i++)
    {
        output << insert[i] << ", "<< search[i] << endl;
    }

    

   return 0;

}