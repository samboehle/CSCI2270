struct Node
{
    int key;
    Node *next;
    Node *prev;
};


class LinkedList
{
    private:
        Node *head;
    public:
        void insert(int newKey);
        Node* searchList(int key);
        void printList();
}
