// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash value
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //TODO: Search the list at that specific index and return the node if found
    bool found = false;
    node *current = table[index];

    while(current != nullptr)
    {
        if(current->key == key)
        {
            return current;
            found = true;
        }
        current = current->next;
    }
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list

        int x = hashFunction(key);

        node *current = table[x];
        node *empty = nullptr;

        if(current == nullptr)
        {
            node* nw = new node;
            nw->key = key;
            nw->next = nullptr;
            
            table[x] = nw;
        }
        else
        {
            while(current->next != nullptr)
            {
                current = current->next;
            }
            node* nw = new node;
            nw->key = key;
            nw->next = nullptr;
            
            current->next = nw;

        }
        return true;
    }
    else{
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }

    cout << table[hashFunction(15)]->key << endl;

}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";

        //TODO
        node * current = table[i];

        int x = 0;

        while(current != nullptr)
        {
            if(x==0)
            {
                cout << current->key;
            }
            else
            {
                cout << ", " << current->key; 
            }
            current = current->next;
            x++;
        }
        cout << endl;
    }

 }
