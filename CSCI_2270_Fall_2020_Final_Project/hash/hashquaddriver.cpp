#include <iostream>
#include <fstream>
#include <chrono>
#include "hashquad.hpp"

using namespace std;

//function to split input file
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

//random fucntion to aid in search
int random(int lower, int upper) 
{
    return (rand() % (upper - lower + 1)) + lower; 
}


int main()
{
    HashTable myTable(40009);
    
    int testData[10000];
    float insert[100];
    float search[100];
    int collisionsInsert[100];
    int collisionsSearch[100];

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
        myTable.resetCollisions();
        //insert values into table
        start = high_resolution_clock::now();
        for(int x = i*100; x < i*100 + 100; x++)
        {
            myTable.insert(testData[x]);
        }
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        insert[i] = execTime.count() / 100;
        //record and then reset collisions
        collisionsInsert[i] = myTable.getNumOfCollision();
        myTable.resetCollisions();
        for(int x = 0; x < 100; x++)
        {
            ranNum[x] = random(0, 99 + 100*i);
        }

        //search table for random values in testData array

        start = high_resolution_clock::now();
        for(int x = 0; x < 100; x++)
        {
            myTable.search(testData[ranNum[x]]);
        }
        end = high_resolution_clock::now();
        execTime = duration_cast<nanoseconds>(end - start);
        search[i] = execTime.count() / 100;

        //record collisions
        collisionsSearch[i] = myTable.getNumOfCollision();
    }
    fstream output;

    output.open("hash_output.csvs");

    output << "Insert" << ", " << "Search" << ", " << "Insert Collisions" << ", " << "Search Collisions" << endl;
    for(int i =0; i < 100; i++)
    {
        output << insert[i] << ", "<< search[i] << ", "<< collisionsInsert[i] << ", "<< collisionsSearch[i] << endl;
    }
}  