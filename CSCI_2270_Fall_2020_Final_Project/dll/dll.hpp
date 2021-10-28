//standard Linked list class
struct Node{
      int key;
      Node *next;
      Node *prev;
};

class LinkedList
{
  private:
    Node *head;
  public:
    LinkedList();
    void insert(int newKey);
    Node* searchList(int key);
    void printList();
};