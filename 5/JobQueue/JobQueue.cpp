#include "JobQueue.hpp"
#include <iostream>
using namespace std;

JobQueue::JobQueue()
{
    queueFront = 0;
    queueEnd = 0;
    counter = 0;
}

bool JobQueue::isEmpty()
{
    if(counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    } 
}

bool JobQueue::isFull()
{
    if(counter == SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void JobQueue::enqueue(std::string job)
{
    if(!isFull())
    {
        counter++;
        queue[queueEnd] = job;
        queueEnd = (queueEnd + 1)%SIZE;
    }
    else
    {
        cout << "Queue full, cannot add new job" << endl;
    }
}

void JobQueue::dequeue()
{
    if(!isEmpty())
    {
        counter --;
        queueFront = (queueFront + 1)%SIZE;
    }
    else
    {
        cout << "Queue empty, cannot dequeue a job" << endl;
    }
}

int JobQueue::queueSize()
{
    return counter;
}

std::string JobQueue::peek()
{
    if(isEmpty() == true)
    {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    else
    {
        return queue[queueFront];
    }
    
}