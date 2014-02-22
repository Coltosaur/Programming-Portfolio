#include <iostream>
#include "Vertex.h"
using namespace std;

Vertex::Vertex(int ID) { 
        // give as follows as an example. nothing to do for this function
	inList.resize(0); 
	outList.resize(0);
	id = ID;
	pos = 0;
}

void Vertex::enInList(Edge inedge){
	// push_back
	inList.push_back(inedge);
}

void Vertex::enOutList(Edge outedge) {
	// similar to above
	outList.push_back(outedge);
}
void Vertex::printInEdge(){
	// print in edges for test purpose
	for (int i = 0; i < inList.size(); i++)
	{
            cout << "The inEdge weight: " << inList[i].getWeight() << endl;
        }
}
void Vertex::printOutEdge(){
	// print out edges for test purpose
	for (int i = 0; i < outList.size(); i++)
	{
            cout << "The outEdge weight: " << outList[i].getWeight() << endl;
        }
}

int Vertex::getID() {
	// return the identity of the vertex
	return id;
}

