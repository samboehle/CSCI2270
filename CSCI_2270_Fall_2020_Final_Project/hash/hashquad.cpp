#include "hashquad.hpp"
#include <math.h>
#include <iostream>
#include <cmath>

using namespace std;

//define hashtable of size of nodes
HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    this->table = new node*[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        table[i] = new node;
        table[i]->key = -1;
    }
}

unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}


int HashTable::search(int key)
{
    int i = hashFunction(key);
    int x = 1;
    //find key in hashtable
    while(table[i]->key != key || table[i]->key == -1)
    {
        numOfcolision++;
        //in this case the index has been made larger than the array so it loops around
        if(i + x*x > tableSize-1)
        {
            i = (i + x*x) -(tableSize);
        }
        //quadraticly increasy index
        else
        {
            i += x*x;
        }
        x++;
    }
    return table[i]->key;
}

void HashTable::printTable()
{
    for(int i = 0; i < tableSize; i++)
    {
        cout << table[i]->key << "|";
    }
    cout << endl;
}

int HashTable::getNumOfCollision()
{
    return numOfcolision;
}

void HashTable::resetCollisions()
{
    numOfcolision = 0;
}

void HashTable::insert(int key)
{
    int i = hashFunction(key);
    int x = 1;
    node* nn = new node;
    nn->key = key;
    //whil current index is full keep looping
    while(table[i]->key != -1)
    {
        numOfcolision++;
        //index is larger than array
        if(i + x*x > tableSize-1)
        {
            i = (i + (x*x)-(tableSize));
        }
        //increase index quadraticly
        else
        {
            i += x*x;
        }
        x++;
    }

    table[i] = nn;
}