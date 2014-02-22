#include <string>
#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    string str("graph_2.txt");
    Graph graph(str);
   // graph.PrintGraph();
    graph.Dijkstra_Algorithm();
    return 0; 
}
