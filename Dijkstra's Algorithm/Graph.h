#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "PQHeap.h"
//#include "PQArray.h"

using namespace std;


class Edge;
class Vertex;

class Graph{

private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;


public:
	Graph(string filename) {
		// This function is the most difficult one. Be carefull.
		// Using ifstream, e.g. ifstream ifs(filename.c_str()); 
		// make new vertices and edges, also fill out the information for them
		// the expected result will be: vertList contains all vertices and edgeList contains all edges. 
		// and the vertices and edges should contains information, e.g. weight, source/end vertex pointer for edge
		int source = 0, size = 0, end = 0, w = 0, next = 0;
		ifstream ifs;
		ifs.open(filename.c_str());
		if (ifs.is_open())
		{
                    ifs >> size;
                    for (int i = 0; i < size; i++)
                        vertList.push_back(new Vertex(i+1));
                    for (int i = 1; i < size; i++)
                    {
                        ifs >> source;
                        while (!ifs.eof())
                        {
                            ifs >> next;
                            if (next != -1)
                            {
                                end = next;
                                ifs >> next;
                                w = next;
                                Edge *e = new Edge(vertList[source-1], vertList[end-1], w);
                                cout << "Edge weight is: " << e->getWeight() << endl;
                                edgeList.push_back(e);
                                vertList[source-1]->enOutList(*e);
                                vertList[end-1]->enInList(*e);
                            }
                            else
                            {
                                ifs >> next;
                                source = next;
                            } 
                        }
                        ifs.close();
                    }         
                }
	} 

	void PrintGraph() // print out all the edges and associated vertices in the entire graph
	{
		cout<<"Graph is as follows: "<<endl;

                // print all edges and related vertices
		for(int i=0;i<edgeList.size();i++)
		{
			// print out weight of edge
                        // and source/end vertex id
                    cout << "Weight: " << edgeList[i]->getWeight();
                    cout << " Source: " << edgeList[i]->getsVertP()->getID();
                    cout << " End: " << edgeList[i]->geteVertP()->getID() << endl;
		}

                // print all vertices and related edges

		for(int i=0;i<vertList.size();i++)
		{
			// print out in edges and out edges with weight information
                    cout << "Vertex ID: " << vertList[i]->getID() << endl;
                    vertList[i]->printInEdge();
                    vertList[i]->printOutEdge();
		}
	}
        
        void addEdge()
        {
            int num_1 = 0, num_2 = 0, weit = 0;
            Vertex *ver_1, *ver_2;
            for (int i = 0; i < vertList.size(); i++)
            {
                cout << "Vertex ID's to choose from to add an edge from: " << endl;
                cout << vertList[i]->getID() << endl;
            }
            cout << "Enter the ID of the source vertex you wish to add an edge to: " << endl;
            cin >> num_1;
            cout << "Enter the ID of the end vertex you wish to add the edge to: " << endl;
            cin >> num_2;
            for (int i = 0; i < vertList.size(); i++)
            {
                if (vertList[i]->getID() == num_1)
                    ver_1 = vertList[i];
                if (vertList[i]->getID() == num_2)
                    ver_2 = vertList[i];
            }
            cout << "Now enter the weight of the edge to be added: " << endl;
            cin >> weit;
            Edge *e = new Edge(ver_1, ver_2, weit);
            edgeList.push_back(e);
            ver_1->enInList(*e);
            ver_2->enOutList(*e);
        }
        
        void addVertex()
        {
            int num = 0;
            cout << "Enter an integer representing the ID of the vertex you wish to add: " << endl;
            cin >> num;
            Vertex *v = new Vertex(num);
            vertList.push_back(v);
        }
        
        void Dijkstra_Algorithm();
};

void Graph::Dijkstra_Algorithm()
{
    int size=vertList.size();
    int d[size];
    int p[size];
    int *pos[size];
    
    for (int i = 0; i < size; i++)
    {
        d[i] = 999999;
        p[i] = -1;
        pos[i] = new int[1];
    }
    
    d[0] = 0;
    PQHeap<int> pq;
    int num_cmps = 0;
    int indiv_cmps = 0;
    
    for (int i = 0; i < size; i++)
    {
        pos[i] = pq.insertItem(d[i], i+1, num_cmps);
		cout << "Comparisons for insertion: " << num_cmps-indiv_cmps << endl;
		indiv_cmps = num_cmps;
    }

    while (!pq.isEmpty())
    {
        int vid = pq.minElement();
        pq.removeMin(num_cmps);
		cout << "Comparisons for removal: " << num_cmps-indiv_cmps << endl;
        for (int i = 0; i < vertList[vid-1]->getOutList().size(); i++)
        {
            Vertex *u = vertList[vid-1]->getOutList()[i].geteVertP();
            if (d[u->getID()-1] > (d[vid-1]+vertList[vid-1]->getOutList()[i].getWeight()))
            {
                d[u->getID()-1] = (d[vid-1]+vertList[vid-1]->getOutList()[i].getWeight());
                pq.updateKey(pos[u->getID()-1], d[u->getID()-1], num_cmps);
				cout << "Comparisons for updating: " << num_cmps-indiv_cmps << endl;
                p[u->getID()-1] = vid;
            }
        }
		indiv_cmps = num_cmps;
    }
    
    for (int i = 0; i < size; i++)
    {
        int temp = i;
        int parent = p[i];
        cout << "From Source Vertex 1 to Vertex " << i+1 << endl;
        if (d[i] == 999999)
            cout << "Vertex cannot be reached from the source.";
        else
            cout << "d[" << i+1 << "]: " << d[i];
        if (p[i] == -1)
            cout << " Vertex has no parent." << endl;
        else
        {
            cout << " P[" << i+1 << "]: " << p[i];
			if (p[i] == 1)
				cout << endl;
            while (parent != 1 || parent != -1) //follows the yellow brick road back to the source
            {
                i = parent;
                parent = p[i-1];
                if (parent == -1)
                    break;
                cout << " P[" << i << "]: " << parent;
				if (parent == 1)
					cout << endl;
            }
            i = temp;
        }
    }
}

#endif

