#include <iostream>
#include <string>
#include <queue>
#include "hGraph.hpp"
using namespace std;


void Graph::addVertex(string name)
{
    if(name == "")
    {
        return;
    }
    else
    {
        vertex* newVertex = new vertex;
        newVertex->name = name;
        newVertex->visited = false;
        vertices.push_back(newVertex);
    }
}


vertex* getVertex(string name, vector<vertex*> vertices)
{
    for(int i = 0; i <= vertices.size(); i++)
    {
        if(vertices[i]->name == name)
        {
            return vertices[i];
        }        
    }
    return NULL;
}

void Graph::addEdge(string v1Name, string v2Name)
{
    if(v1Name != "" && v2Name != "")
    {
        vertex* vertex1 = getVertex(v1Name, vertices);
        vertex* vertex2 = getVertex(v2Name, vertices);
        adjVertex av1;
        adjVertex av2;
        av1.v = vertex1;
        av2.v = vertex2;
        vertex1->adj.push_back(av2);
        vertex2->adj.push_back(av1);
    }
}



void Graph::displayEdges()
{
    
    for(int i = 0; i < vertices.size(); i++)
    {
        vertex* vertex = vertices[i];
        cout << vertex->name << " -->";
        for(int j = 0; j < vertex->adj.size(); j++)
        {
            cout << " " << vertex->adj[j].v->name;
        }
        cout << endl;
    }
}


// void helpBreadth(vertex* current, int depth, bool isRoot = false)
// {
//     if(current->visited == true)
//     {
//         return;
//     }
    
//     current->visited = true;
//     if(!isRoot)
//     {
//         cout << current->name << "(" << depth << ") ";
//     }
    
// }


void Graph::breadthFirstTraverse(string sourceVertex)
{
    vertex* vStart = getVertex(sourceVertex, vertices);
    if(sourceVertex == "")
    {
        return;
    }
    else
    {
        cout << "Starting vertex (root): " << vStart->name << "->";
    }
    vStart->visited = true;
    vStart->distance = 0;
    queue<vertex*> queue;
    queue.push(vStart);
    while(!queue.empty())
    {
        vertex* current = queue.front();
        queue.pop();
        if(current != vStart)
        {
            cout << " " << current->name << "(" << current->distance << ")";
        }
        for(int i = 0; i < current->adj.size(); i++)
        {
            if(current->adj[i].v->visited != true)
            {
                current->adj[i].v->visited = true;
                current->adj[i].v->distance = current->distance + 1;
                queue.push(current->adj[i].v);
            }
        }
        current->visited = true;
    }
}


void helpConnectBuild(vertex* current)
{
    for(int i = 0; i < current->adj.size(); i++)
    {
        if(current->adj[i].v->visited != true)
        {
            current->adj[i].v->visited = true;
            helpConnectBuild(current->adj[i].v);
        }
    }
    current->visited = true;
}


int Graph::getConnectedBuildings()
{
    int components = 0;
    for(int i = 0; i < vertices.size(); i++)
    {
        vertex* current = vertices[i];
        if(current->visited == false)
        {
            components++;
            helpConnectBuild(current);
        }
    }
    return components;
}