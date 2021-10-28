class HeapSort
{
    //standard declaration for heap
    int *heap;
    int capacity;
    int currentSize;
    void minHeapify(int index);
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    void swap(int &x, int &y);
public:
    HeapSort(int cap);
    void insert(int key);
    int pop();
    int peek();
    void printHeap();
};