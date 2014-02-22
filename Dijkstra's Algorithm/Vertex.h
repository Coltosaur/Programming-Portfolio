#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
#include "Edge.h"
//#ifndef EDGE_H
//#define 
//#endif
using namespace std;

class Edge;

class Vertex {

private:

    vector<Edge> inList; // source vertex
    vector<Edge> outList; // end vertex 
    
    int id;	// the identity of the vertex in the file of graph
    int pos;	// the index of this vertex in the binary heap or the index of this vertex in the unsorted array

public:

	Vertex(int ID);
	void enInList(Edge inedge);	// push inedge into in edge list
	void enOutList(Edge outedge);   // push outedge into out edge list
	void printInEdge();             // print in edges
	void printOutEdge();            // print out edges
	int getID();	// return the identity of the vertex
        vector<Edge> getOutList()
        {
            return outList;
        }
        vector<Edge> getInList()
        {
            return inList;
        }
};

#endif
