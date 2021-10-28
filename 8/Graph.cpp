#include <iostream>
#include <queue>
#include <vector>
#include "Graph.hpp"
using namespace std;

void Graph::addVertex(string name)
{
    vertex *nv = new vertex;
    nv->name = name;
    vertices.push_back(nv);

}

void Graph::addEdge(string v1, string v2)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == v1)
        {
            for(int x = 0; x < vertices.size(); x++)
            {
                if(vertices[x]->name == v2 && i != x)
                {
                    adjVertex e0;
                    e0.v = vertices[x];
                    vertices[i]->adj.push_back(e0);

                    adjVertex e1;
                    e1.v = vertices[i];
                    vertices[x]->adj.push_back(e1);
                }
            }
        }
    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->adj.size() != 0)
        {
            cout << vertices[i]->name << " -->";
        }

        for(int x = 0; x < vertices[i]->adj.size(); x++)
        {
            cout << " " << vertices[i]->adj[x].v->name;
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string name)
{
    vertex *start;
    
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == name)
        {
            start = vertices[i];
        }
    }
    start->visited = true;

    queue<vertex*> myqueue;

    myqueue.push(start);

    vertex *n;

    cout << "Starting vertex (root): " << start->name << "-> ";


    while(!myqueue.empty())
    {
        n = myqueue.front();
        myqueue.pop();


        for(int i = 0; i < n->adj.size(); i++)
        {
            if(n->adj[i].v->visited == false)
            {
                n->adj[i].v->distance = n->distance +1;
                n->adj[i].v->visited = true;
                cout << n->adj[i].v->name <<"("<< n->adj[i].v->distance <<")"<< " ";
                myqueue.push(n->adj[i].v);
            }
        }
    }
}


vector<vertex*> helper(vertex *start)
{
    start->visited = true;
    queue<vertex*> myqueue;
    myqueue.push(start);
    vertex *n;

    vector<vertex*> back;
    back.push_back(start);

    while(!myqueue.empty())
    {
        n = myqueue.front();
        myqueue.pop();


        for(int i = 0; i < n->adj.size(); i++)
        {
            if(n->adj[i].v->visited == false)
            {
                n->adj[i].v->distance = n->distance +1;
                n->adj[i].v->visited = true;
                back.push_back(n->adj[i].v);
                myqueue.push(n->adj[i].v);
            }
        }
    }

    return back;
}


int Graph::getConnectedBuildings()
{
    vector<vertex*> first = vertices;
    vector<vertex*> second = vertices;
    int graphs = 0;

    while(second.size() != 0)
    {
        first = helper(second[0]);
        for(int i = 0; i < second.size(); i++)
        {
            for(int x = 0; x < first.size(); x++)
            {
                if(second[i]->name == first[x]->name)
                {
                    second.erase(second.begin() + i);
                }
            }
        }
        graphs++;
    }
    return graphs;
}