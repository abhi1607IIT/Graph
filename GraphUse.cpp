#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	Graph g;
	char a[] = "Delhi";
	char b[] = "Noida";
	char c[] = "Faridabad";
	char d[] = "Gurgaon";
	g.addVertex(a);
	g.addVertex(b);
	g.addVertex(c);
	g.addVertex(d);
	g.print();
	cout << g.hasVertex("Delhi") << endl;

	g.addEdge(a, b);
  g.addEdge(a, d);
	g.addEdge(c, d);
	g.print();
	vector<vector<char*>*>* cc = g.connectedComponents();
	for (int i = 0; i < cc->size(); i++) {
		vector<char*>* c = cc->at(i);
		for (int j = 0; j < c->size(); j++) {
			cout << c->at(j) << " ";
		}
		cout << endl;
	}
	cout << "Path" << endl;
	cout << g.hasPath(a, d) << endl;
	cout << g.numVertices() << endl;
	cout << g.numEdges() << endl;
	cout << g.hasEdge(b, d) << endl;
	cout << g.hasEdge(a, d) << endl;
	g.removeEdge(a, d);
	cout << g.hasEdge(a, d) << endl;
	cout << g.numEdges() << endl;
	g.removeVertex(a);
	g.print();
}

