#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct wordRecord
{
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[])
    {
        ifstream myfile;
        myfile.open(ignoreWordFileName);

        string word;
        int i = 0;
        while (myfile >> word )
        {
            ignoreWords[i] = word;
            i++;
        }

        myfile.close();

        
    }

bool isIgnoreWord(string word, string ignoreWords[])
{
    for(int i = 0; i < 50; i++)
    {
        if(ignoreWords[i] == word)
        {
            return true;
        }
    }
    return false;
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length)
{
    int count = 0;

    for(int i = 0; i < length; i++)
    {
        count = count + distinctWords[i].count;
    }
    return count;
}

void sortArray(wordRecord distinctWords[], int length)
{
    
    wordRecord t;
    for(int i = 0; i < length - 1; i++)
    {
        for(int x = 0; x < length - i; x++)
        {
            if(distinctWords[x].count < distinctWords[x+1].count)
            {
                t = distinctWords[x];
                distinctWords[x] = distinctWords[x+1];
                distinctWords[x+1] = t;
            }
        }

    }
    
    /*wordRecord y[10000];
    int current;
    int place = 0;
    int start;
    int counter = 0;
    wordRecord temp;
    for(int i = 0; i < length; i++)
    {
        current = distinctWords[i].count;
        for(int x = 0; x < length; x++)
        {
            if(x == i)
            {
                continue;
            }
            if(current == distinctWords[x].count)
            {
                start = x;
                y[place] = distinctWords[x];
                place++;
            }
        }
        if(place == 0)
        {
            continue;
        }
        else
        {
            for(int z = 0; z < place -1; z++)
            {
                for(int k = 0; k < k -1 ; k++)
                {
                    if(y[k].word > y[k+1].word)
                    {
                        temp = y[k];
                        y[k] = y[k+1];
                        y[k+1] = temp;
                    }
                }
            }
            for(int x = start; x < start + current; x++)
            {
                distinctWords[x] = y[counter];
            }
            counter = 0;
            place = 0;
        
        }
        

        
    }*/
    
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords)
{
    float currentProb;
    float nextProb;
    int numCurrent;
    int numNext;

    float values[10];
    
    
    
    for(int i = N; i < N+10; i++)
    {
        currentProb = (float) distinctWords[i].count / totalNumWords;
        if(i == N+9)
        {
            cout << fixed << setprecision(5) << currentProb << " - " << distinctWords[i].word << endl;
        }
        else
        {
            nextProb = (float) distinctWords[i + 1].count / totalNumWords;

            if(currentProb == nextProb)
            {
                if(distinctWords[i].word < distinctWords[i+1].word)
                {
                    cout << fixed << setprecision(5) << currentProb << " - " << distinctWords[i].word << endl;
                }
                else
                {
                    cout << fixed << setprecision(5) << currentProb << " - " << distinctWords[i+1].word << endl;
                    distinctWords[i+1] = distinctWords[i];
                }
                
            }
            else
            {
                cout << fixed << setprecision(5) << currentProb << " - " << distinctWords[i].word << endl;
            }
            
        }
    }





}



int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt" << endl;
        return -1;
    }

    string ignorewords[50];
    getIgnoreWords(argv[3], ignorewords);


    ifstream myfile;
    myfile.open(argv[2]);
    if(myfile.fail())
    {
        cout << "Failed to open the file." << endl;
    }

    string word;
    int n = 100;
    wordRecord *a;
    a = new wordRecord[n];

    int doubled = 0;
    int current = 0;
    int place;
    int flag = 0;
    int numUnique = 0;


    while(myfile >> word)
    {
        if(current == n)
        {
            wordRecord *temp = new wordRecord[n*2];
            for(int i = 0; i < n; i++)
            {
                temp[i] = a[i];
            }
            n = 2*n;
            delete [] a;
            a = temp;
            doubled++;
        }
        if(isIgnoreWord(word, ignorewords) == false)
        {
            for(int i = 0; i < current; i++)
            {
                if(word == a[i].word)
                {
                    place = i;
                    flag = 1;
                }
            }
            if(flag == 1)
            {
                a[place].count++;
                flag = 0;
            }
            else
            {
            
                a[current].word = word;
                a[current].count = 1;
                current++;
                numUnique++;
            }
        }
    }

    sortArray(a, current);

    cout << "Array doubled: " << doubled << endl;
    cout << "Distinct non-common words: " << numUnique << endl;
    cout << "Total non-common words: " << getTotalNumberNonIgnoreWords(a, current) << endl;
    cout << "Probability of next 10 words from rank " << argv[1] << endl;
    cout << "---------------------------------------" << endl;
    printTenFromN(a, stoi(argv[1]), getTotalNumberNonIgnoreWords(a, current));

    return 0;
}