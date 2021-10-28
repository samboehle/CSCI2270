#include "Graph.hpp"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

using namespace std;

void Graph::createEdge(string v1, string v2, int num)
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;
                    av.weight = num;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.weight = num;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);

                }
            }
        }
    }

}

void Graph::insertVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == n)
        {
            found = true;
        }
    }
    if(found == false)
    {
        vertex * v = new vertex;
        v->name = n;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    // cout<<"here"<<vertices.size()<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name << " "<<vertices[i]->adj[j].weight<<endl;
        }
        cout<<endl;
    }
}



void Graph::traverseWithDijkstra(string start)
{
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == start)
        {
            vStart = vertices[i];
        }
    }

    vStart->visited = true;
    vStart->distance = 0;

    vector<vertex*> solvedList;

    solvedList.push_back(vStart);

    bool allSolved = false;

    while(!allSolved)
    {
        int minDist = INT_MAX;

        vertex* solvedV = nullptr;
        allSolved = true;

        for(int i = 0; i < solvedList.size(); i++)
        {
            vertex* s = solvedList[i];

            for(int j = 0; j < s->adj.size(); j++)
            {
                if(!s->adj[j].v->visited)
                {
                    int dist = s->distance + s->adj[j].weight;

                    if(minDist > dist)
                    {
                        solvedV = s->adj[j].v;
                        s->adj[j].v->pred = s;
                        minDist = dist;
                    }
                    allSolved = false;
                }
            }
        }

        if(!allSolved)
        {
            solvedV->distance = minDist;
            solvedV->visited = true;
            solvedList.push_back(solvedV);
        }
    }

}

void DFTUtil(vertex *n)
{
    n->visited = true;
    cout << n->name << " -> ";

    for(int x = 0; x < n->adj.size(); x++)
    {
        if( !n->adj[x].v->visited)
        {
            DFTUtil(n->adj[x].v);
        }
    }
}

void Graph::depthFirstTraversal(string sourceVertex)
{
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            vStart = vertices[i];
        }
    }

    DFTUtil(vStart);
    
    cout << "DONE";
    


}

int findShortestPath(vertex *src, vertex *dest){

    // Need to find the source vertex since we only have it's key 'src'
    // A pointer for source vertex
    vertex *vStart = src;

    vStart->visited = true;

    // Use the queue to keep track of visited vertices
    queue<vertex*> q;

    // Enqueue the source vertex
    q.push(vStart);

    vertex *n;

    // standard BFS
    while(!q.empty()){

        n = q.front();
        q.pop();

        // go to all the adjacent vertices of n
        for( int x = 0; x < n->adj.size(); x++ )
        {
            // If a adjacent has not been visited, then mark it visited and enqueue it
            // Update the distance of the adjacent vertices along the way
            // Stop when you reach the destination vertex and return the needful

            if(n->adj[x].v->visited == false)
            {
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance +1;
                q.push(n->adj[x].v);
                n->adj[x].v->pred = n;
                if(n->adj[x].v->name  == dest->name)
                {
                    return n->adj[x].v->distance;
                }
            }
        }

    }

    return -1;

}

void Graph::minDistPath(string source, string destination)
{
    vertex *vStart;
    vertex *vEnd;

    traverseWithDijkstra(source);
    
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == source)
        {
            vStart = vertices[i];
        }
        if(vertices[i]->name == destination)
        {
            vEnd = vertices[i];
        }
    }

    vertex *temp = vEnd;


    int distance = vEnd->distance;
    vector<vertex*> result;
    while(temp != vStart)
    {
        result.insert(result.begin(), temp);
        temp = temp->pred;
    }
    result.insert(result.begin(), vStart);

    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i]->name << " -> ";
        if(i == 0)
        {
            continue;
        }
        //distance = distance + result[i]->distance;

    }

    cout << "DONE " << "[" << distance << "]" << endl;
}
