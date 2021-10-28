/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of Building structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network between the building *previous and the building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    // if we are passed an empty list, just create a new head node, and return

    if (head == NULL)
    {
        cout << "adding: " << buildingName << " (HEAD)" << endl;
        head = new CUBuilding;
        head->name = buildingName;
        head->numberMessages = 0;
        head->totalRoom = numOfroom;

        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        cout << "adding: " <<buildingName<< " (HEAD)" << endl;
        CUBuilding *c = new CUBuilding;
        c->name = buildingName;
        c->numberMessages = 0;
        c->next = head;
        c->totalRoom = numOfroom;

        head = c;
    }else{
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
        CUBuilding *newBuilding = new CUBuilding;
        newBuilding->name = buildingName;
        newBuilding->numberMessages = 0;
        newBuilding->next = previous->next;
        newBuilding->totalRoom = numOfroom;

        previous->next = newBuilding;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    int num_buildings = 6;
    string buildings[] = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int rooms[] = {2,10,6,5,4,9};
    head = NULL;
    CUBuilding* prev = NULL;
    for(int i = 0; i < num_buildings; i++)
    {
        addBuildingInfo(prev, buildings[i],rooms[i]);
        prev = searchForBuilding(buildings[i]);
    }
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // Search until the head is NULL, or we find the building
    CUBuilding* ptr = head;
    while (ptr != NULL && ptr->name != buildingName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    CUBuilding* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr != NULL)
        {
            cout << ptr->name << "(" << ptr->totalRoom << ")" <<" -> ";
            ptr = ptr->next;
        }
        //cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
  }

/*
 * Purpose: delete the building in the network with the specified name.
 * @param buildingName name of the building to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName)
{
    if(head->name == buildingName)
    {
        CUBuilding *temp = head;

        head = head->next;

        delete temp;
    }
    else
    {
       CUBuilding *ptr = head;


       while(ptr->next != NULL)
       {
           if(ptr->name == buildingName)
           {
               break;
           }
           ptr = ptr->next;
       }
       if(ptr->name != buildingName)
       {
           cout << "Building does not exist." << endl;
           return;
       }

       CUBuilding *crawler = head;

       while(crawler->next != ptr)
       {
           crawler = crawler->next;
       }


       crawler->next = ptr->next;
       delete ptr;


    }

}

/*
* Purpose: Creates a loop from last node to the building specified.
* @param buildingName name of the building to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName)
{
    CUBuilding *last = head;
    CUBuilding *ptr;

    ptr = searchForBuilding(buildingName);

    while(last->next != NULL)
    {
        last = last->next;
    }
    
    if(ptr == NULL)
    {
        return last;
    }

    last->next = ptr;

    return last;




}

/*
 * Purpose: deletes all buildings in the network starting at the head building.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    CUBuilding *crawler;

    if(head == NULL)
    {
        return;
    }
    while(head != nullptr)
    {
        cout << "deleting: " << head->name << endl;
        crawler = head->next;
        delete head;
        head = crawler;
    }
    cout << "Deleted network" << endl;
}

/*
 * Purpose: to detect loop in the linkedlist
 * @return: true if loop is detected.
 */
bool CUBuildingNetwork::detectLoop()
{
    if(head == NULL)
    {
        return false;
    }

    CUBuilding *fast = head->next;
    CUBuilding *slow = head;

    while(fast != NULL && fast->next != NULL && slow != NULL)
    {
        if(fast == slow)
        {
            return true;
        }

        fast = fast->next->next;
        slow = slow->next;
    }

    return false;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 * @param: start index, end index
 * @return: none
 */
void CUBuildingNetwork:: readjustNetwork(int start_index, int end_index)
{
    
    if(head == NULL)
    {
        cout << "Linked List is Empty" << endl;
        return;
    }

    CUBuilding *ptr = head;
    int length = 0;

    while(ptr->next != NULL)
    {
        ptr = ptr->next;
        length++;
    }
    
    if(end_index > length || end_index < 0)
    {
        cout << "Invalid end index" << endl;
        return;
    }

    if(start_index > length || start_index < 0)
    {
        cout << "Invalid start index" << endl;
        return;
    }

    if(start_index > end_index)
    {
        cout << "Invalid indices" << endl;
        return;
    }

    CUBuilding *prev = head;
    CUBuilding *start = head->next;
    CUBuilding *end = head;
    CUBuilding *back = head;

    while(back->next != NULL)
    {
        back = back->next;
    }
    
    if(start_index == 0)
    {
        for(int i = 0; i < end_index; i++)
        {
            end = end->next;
        }
        start = head;
        head = end->next;
        back->next = start;
        end->next = NULL;

    }
    else if (start_index == end_index)
    {
        for(int i = 0; i < start_index -1; i++)
        {
            prev = prev->next;
            start = start->next;
        }
        for(int i = 0; i < end_index; i++)
        {
            end = end->next;
        }

        prev->next = start->next;
        back->next = start;
        start->next = NULL;
    }
    else
    {
        for(int i = 0; i < start_index -1; i++)
        {
            prev = prev->next;
            start = start->next;
        }
        for(int i = 0; i < end_index; i++)
        {
            end = end->next;
        }

        prev->next = end->next;

        back->next = start;
        end->next = NULL;
    }



}