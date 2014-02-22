#include "Edge.h"

Edge::Edge(){}
Edge::Edge(Vertex* svert, Vertex* evert, int weit){
	sVertP = svert;
	eVertP = evert;
	weight = weit;
// constructor
}	
int Edge::getWeight() {
// return weight of edge 
	return weight;
}
Vertex* Edge::getsVertP() {
	// return source vertex pointer
	return sVertP;
}
Vertex* Edge::geteVertP() {
	// return end vertex pointer
	return eVertP;
}

