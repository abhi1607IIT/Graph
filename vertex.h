#ifndef VERTEX_H
#define VERTEX_H
#include "edge.h"
#include <iostream>
#include <vector>
using namespace std;

class vertex {
	vector<edge*> edges;
	public:
	char* name;
	vertex(char* name) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}

	int edgeCount() {
		return edges.size();
	}

	bool isAdjacent(vertex * v) {
		int i;
		for (i = 0; i < edges.size(); i++) {
			if (edges[i]->v1 == v || edges[i]->v2 == v) {
				return true;
			}
		}
		return false;
	}

	void addEdge(edge* e) {
		edges.push_back(e);
	}

	void removeEdgeWith(vertex * v) {
		int i;
		for (i = 0; i < edges.size(); i++) {
			if (edges[i]->v1 == v || edges[i]->v2 == v) {
				break;
			}
		}
		edges.erase(edges.begin() + i);
	}

	void print() {
		cout << name << ":";
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i]->v1 == this) {
				cout << edges[i]->v2->name << ",";
			} else {
				cout << edges[i]->v1->name << ",";
			}
		}
		cout << endl;
	}

	vector<vertex*>* getAdjacentVertices() {
		vector<vertex*>* adjacent = new vector<vertex*>();
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i]->v1 == this) {
				adjacent->push_back(edges[i]->v2);
			} else {
				adjacent->push_back(edges[i]->v1);
			}
		}
		return adjacent;
	}


};
#endif
