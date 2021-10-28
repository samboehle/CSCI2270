#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
};

//provided hashtable class with change to make the table based on nodes
class HashTable
{
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array of nodes
    node **table;
    int numOfcolision =0;
public:
    HashTable(int bsize);  // Constructor

    // inserts a key into hash table
    void insert(int key);
    void resetCollisions();

    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getNumOfCollision();

    int search(int key);
};


#endif