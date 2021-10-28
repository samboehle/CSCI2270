#include "dll.hpp"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}


void LinkedList::insert(int newKey)
{
    //LL is empty
    if(head == nullptr)
    {
        head = new Node;
        head->key = newKey;
        head->next = NULL;
        head->prev = NULL;
    }
    //insert at end of LL
    else
    {
        Node *current = head;

        while(current->next != nullptr)
        {
            current = current->next;
        }

        Node *nn = new Node;
        nn->key = newKey;
        current->next = nn;
        nn->next = NULL;
        nn->prev = current;
    }

}

Node* LinkedList::searchList(int key)
{
    //Loop through list to find right key
    Node* ptr = head;
    while (ptr != nullptr && ptr->key != key)
    {
        ptr = ptr->next;
    }
    return ptr;
}

void LinkedList::printList(){
    Node* temp = head;

    while(temp->next != nullptr)
    {
        cout<< temp->key <<" -> ";
        temp = temp->next;
    }

    cout<<temp->key<<endl;
}

