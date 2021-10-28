/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
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
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) 
{
    if(previous == NULL && head == NULL)
    {
        CUBuilding * new_node = new CUBuilding;

        new_node->name = buildingName;
        new_node->totalRoom = numOfroom;

        new_node->next = NULL;
        head = new_node;
        
        cout << "adding: " << buildingName << " (HEAD)" << endl;
    }
    else if (previous == NULL)
    {
        CUBuilding * new_node = new CUBuilding;

        new_node->name = buildingName;
        new_node->totalRoom = numOfroom;

        new_node->next = head;
        head = new_node;
        cout << "adding: " << buildingName << " (HEAD)" << endl;
    }
    else if(previous->next == NULL)
    {
        
        CUBuilding * new_node = new CUBuilding;

        new_node->name = buildingName;
        new_node->totalRoom = numOfroom;

        previous->next = new_node;
        new_node->next = NULL;

        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    }
    else
    {
        
        CUBuilding * new_node = new CUBuilding;

        new_node->name = buildingName;
        new_node->totalRoom = numOfroom;

        CUBuilding * ptrN = previous->next;
        previous->next = new_node;
        new_node->next = ptrN;
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;

    }
    
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */

void CUBuildingNetwork::loadDefaultSetup()
{
    addBuildingInfo(NULL, "FLMG", 2);
    addBuildingInfo(head, "DLC", 10);
    addBuildingInfo(head->next, "ECOT", 6);
    addBuildingInfo(head->next->next, "CASE", 5);
    addBuildingInfo(head->next->next->next, "AERO", 4);
    addBuildingInfo(head->next->next->next->next, "RGNT", 9);
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    CUBuilding *node = head;
    while(node != NULL)
    {
        if(node->name == buildingName)
        {
            return node;
        }
        node = node->next;
    }
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    if(head == NULL)
    {
        cout << "Empty list" << endl;
        return;
    }

    CUBuilding *node = head;
    int flag = 0;
    while(node != NULL)
    {
        if(node->name == receiver)
        {
            flag = 1;
        }
        node = node->next;
    }

    if(flag == 0)
    {
        cout << "Building not found" << endl;
        return;
    }

    node = head;
    while(node != NULL)
    {
        node->message = "available room at " + node->name + " is " + to_string(node->totalRoom);
        node->numberMessages = node->numberMessages + 1;
        cout << node->name << " [# messages received: " << node->numberMessages << "] received: " << node->message << endl;
        if(node->name == receiver)
        {
            return;
        }
        node = node->next;
    }

}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork()
{
    if(head == NULL)
    {
        cout << "== CURRENT PATH ==" << endl;
        cout << "nothing in path" << endl;
        cout << "===" << endl;
        return;
    }
    
    cout << "== CURRENT PATH ==" << endl;
    
    CUBuilding *node = head;
    while (node != NULL)
    {
        cout << node->name << "(" << node->totalRoom << ")"; 

        if(node != NULL)
        {
            cout << " -> ";
        }
        node = node->next;
    }

    cout << "NULL" << endl << "===" << endl;
    

}
