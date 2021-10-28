int sumNodes(Node *node, int min, int max)
{
//TODO Base case
    if (node == NULL) return 0;

    if( node->data > max)
    {
        return( 0 + sumNodes(node->left) + sumNodes(node->right));
    }
    if(node->date < min)
    {
        return(0 + sumNodes(node->left) + sumNodes(node->right));
    }

    return(node->data + sumNodes(node->left) + sumNodes(node->right));
}

int sumRange(int min, int max)
{
    return sumNodes(root, min, max);
}


void breadthFirstTraverse(int name)
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

int DFTUtil(vertex *n, int dist)
{
    n->visited = true;
    
    for(int x = 0; x < n->adj.size(); x++)
    {
        if( !n->adj[x].v->visited)
        {
            return(DFTUtil(n->adj[x].v, dist + );
        }
    }
}

int depthFirstTraversal(string sourceVertex, int dist)
{
    vertex *vStart;

    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            vStart = vertices[i];
        }
    }

    DFTUtil(vStart, dist);
    
}

int countNodesWithDistance(int id, int dist)
{
    breadthFirstTraversal(id);

}