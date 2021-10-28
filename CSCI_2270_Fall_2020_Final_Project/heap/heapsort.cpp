#include "heapsort.hpp"
#include <iostream>
using namespace std;

//define heap size
HeapSort::HeapSort(int cap)
{
    capacity = cap;
    currentSize = 0;
    heap = new int[capacity];
}


int HeapSort::parent(int index)
{
    return (index - 1)/2;
}
int HeapSort::leftChild(int index)
{
    return 2*index +1;
}
int HeapSort::rightChild(int index)
{
    return 2*index +2;
}

void HeapSort::swap(int &x, int &y)
{
    int temp = y;
    y = x;
    x = temp;
}

void HeapSort::insert(int value)
{
    if(currentSize < capacity)
    {
        heap[currentSize] = value;
        int i = currentSize;

        //tests to see if parent of inserted value is greater than
        while (i != 0 && heap[parent(i)] > heap[i])
        {
            //if so swap in order to make heap correct
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
        currentSize++;
        
    }
    else
    {
        cout << "full" << endl;
    }
    
}


int HeapSort::pop()
{
    if(currentSize <= 0)
    {
        return -1;
    }
    if(currentSize == 1)
    {
        currentSize--;
        return heap[0];
    }
    //this is the standard case where there is more than 1 element in which case a recurseive function is called to fix the heap
    int poppedVal = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    minHeapify(0);
    return poppedVal;
}

void HeapSort::minHeapify(int i)
{
    int left = leftChild(i);
    int right = rightChild(i);

    int smallest = i;

    //test to see if heap is correct
    if(left < currentSize && heap[left] < heap[i])
    {
        smallest = left;
    }
    if(right < currentSize && heap[right] < heap[smallest])
    {
        smallest = right;
    }

    //heap had been fixed
    if(smallest == i)
    {
        return;
    }
    //heap is not fully fixed so swap values and call funct again on index
    else
    {
        swap(heap[i], heap[smallest]);
        minHeapify(smallest);
    }
}

int HeapSort::peek()
{
    if(currentSize <= 0)
    {
        return -1;
    }
    else
    {
        return heap[0];
    }
}

void HeapSort::printHeap()
{
    int count = 0;
    for(int i = 0; i < capacity; i++)
    {
        cout << heap[i] << endl;
    }
}

