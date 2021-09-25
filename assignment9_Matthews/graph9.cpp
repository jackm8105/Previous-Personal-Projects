#include "graph9.hpp"
#include <vector>
#include <queue>
#include <limits.h>
#include <iostream>

using namespace std;

void Graph::createEdge(string v1, string v2, int num)
{
  vertex* vertex1;
  vertex* vertex2;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == v1)
    {
      vertex1 = vertices[i]; 
    }
    if(vertices[i]->name == v2)
    {
      vertex2 = vertices[i];
    }
  }
  adjVertex av;
  av.v = vertex2;
  av.weight = num;
  vertex1->adj.push_back(av);
  //another vertex for edge in other direction
  adjVertex av2;
  av2.v = vertex1;
  av2.weight = num;
  vertex2->adj.push_back(av2);
}

void Graph::insertVertex(string n){

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

vertex* helpBeShort(vector<vertex*> vertices)
{
  if(vertices.empty())
  {
    return NULL;
  }
  vertex* minSoFar = NULL;
  for(int v = 0; v < vertices.size(); v++)
  {
    if(vertices[v]->visited == false)
    {
      if(minSoFar == NULL || vertices[v]->distance < minSoFar->distance)
      {
        minSoFar = vertices[v];
      }
    }
  }
  return minSoFar;
}

void Graph::traverseWithDijkstra(string start)
{
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == start)
    {
      vertices[i]->distance = 0;
    }
    else
    {
      vertices[i]->distance = INT_MAX;
    }
  }
  for(int count = 0; count < vertices.size() - 1; count++)
  {
    vertex* shortDist = helpBeShort(vertices);
    shortDist->visited = true;
    for(int j = 0; j < shortDist->adj.size(); j++)
    {
      adjVertex neighbor = shortDist->adj[j];
      if(shortDist->distance + neighbor.weight < neighbor.v->distance && shortDist->distance != INT_MAX)
      {
        neighbor.v->distance = shortDist->distance + neighbor.weight;
      }
    }
  }
}


void helpDepth(vertex* n)
{
  if(n->visited == true)
  {
      return;
  }
  n->visited = true;
  cout << n->name << " -> ";
  for(int x = 0; x < n->adj.size(); x++)
  {
    helpDepth(n->adj[x].v);
  }
}

void Graph::depthFirstTraversal(string sourceVertex)
{
  vertex* vertex1;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == sourceVertex)
    {
      vertex1 = vertices[i]; 
    }
  }
  helpDepth(vertex1);
  cout << "DONE";
}

void Graph::minDistPath(string startName, string endName)
{
  vertex* start;
  vertex* end;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == startName)
    {
      start = vertices[i]; 
    }
    if(vertices[i]->name == endName)
    {
      end = vertices[i];
    }
  }
  traverseWithDijkstra(startName);
  vertex* current = end;
  vector<vertex*> shortestPath;
  shortestPath.push_back(end);
  while(current != start)
  {
    vertex* closestSmall = current->adj[0].v;
    for(int v = 1; v < current->adj.size(); v++)
    {
      if(current->adj[v].v->distance < closestSmall->distance)
      {
        closestSmall = current->adj[v].v;
      }
    }
    shortestPath.push_back(closestSmall);
    current = closestSmall;
  }
  for(int k = shortestPath.size() - 1; k >= 0; k--)
  {
    cout << shortestPath[k]->name << " -> ";
  }
  cout << "DONE [" << end->distance << "]" << endl;
}


void Graph::minDistPath(string startName, string endName)
{
  vertex* start;
  vertex* end;
  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices[i]->name == startName)
    {
      start = vertices[i]; 
    }
    if(vertices[i]->name == endName)
    {
      end = vertices[i];
    }
  }
  traverseWithDijkstra(startName);
  vertex* current = end;
  vector<vertex*> shortestPath;
  shortestPath.push_back(end);
  while(current != start)
  {
    shortestPath.push_back(current->pred);
    current = current->pred;
  }
  for(int k = shortestPath.size() - 1; k >= 0; k--)
  {
    cout << shortestPath[k]->name << " -> ";
  }
  cout << "DONE [" << end->distance << "]" << endl;
}