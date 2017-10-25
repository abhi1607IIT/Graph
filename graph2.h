#include "vertex.h"
#include <iostream>
#include "edge.h"
#include <vector>
#include <unordered_set>
using namespace std;

class Graph {
	vector<vertex*> vertices;

	vertex* findVertex(char* name) {
		for (int i = 0; i < vertices.size(); i++) {
			if (strcmp(vertices[i]->name, name) == 0) {
				return vertices[i];
			}
		}
		return NULL;
	}

	public:
	int numVertices() {
		return vertices.size();
	}

	int numEdges() {
		int count = 0;
		for (int i = 0; i < vertices.size(); i++) {
			count += vertices[i]->edgeCount();
		}
		return count/2;
	}

	void addVertex(char* name) {
		vertex* v = findVertex(name);
		if (v != NULL) {
			return;
		}
		v = new vertex(name);
		vertices.push_back(v);
	}

	void removeVertex(char* name) {
		/*int i = 0;
		for (; i < vertices.size(); i++) {
			if (strcmp(vertices[i]->name, name) == 0) {
				break;
			}
		}
		if (i == vertices.size()) {
			return;
		}
		vertices.erase(vertices.begin() + i);
		*/
		vertex* v = findVertex(name);
		if (v == NULL) {
			return;
		}
		vector<vertex*>* adjacent = v->getAdjacentVertices();
		for(int i = 0; i < adjacent->size(); i++) {
			adjacent->at(i)->removeEdgeWith(v);
		}
		vertices.erase(find(vertices.begin(), vertices.end(), v));
	}

	bool hasVertex(char* name) {
		if (findVertex(name) != NULL) {
			return true;
		} else {
			return false;
		}
	}

	void addEdge(char* name1, char* name2, int distance) {
		vertex* v1 = findVertex(name1);
		vertex* v2 = findVertex(name2);
		if (v1 == NULL || v2 == NULL) {
			return;
		}
		if (v1->isAdjacent(v2)) {
			return;
		}
		edge* e = new edge(v1, v2, distance);
		v1->addEdge(e);
		v2->addEdge(e);
	}
	
	void removeEdge(char* name1, char* name2) {
		vertex* v1 = findVertex(name1);
		vertex* v2 = findVertex(name2);
		if (v1 == NULL || v2 == NULL) {
			return;
		}
		if (!v1->isAdjacent(v2)) {
			return;
		}
		v1->removeEdgeWith(v2);
		v2->removeEdgeWith(v1);
	}

	bool hasEdge(char* name1, char* name2) {
		vertex* v1 = findVertex(name1);
		vertex* v2 = findVertex(name2);
		if (v1 == NULL || v2 == NULL) {
			return false;
		}
		return v1->isAdjacent(v2);
	}
	
	void print() {
		cout << "Printing Graph" << endl;
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i]->print();
		}
		cout << "Printing done" << endl;
	}

	private:
	bool hasPath(vertex* v1, vertex* v2, unordered_set<vertex*>& visited) {
		if (v1->isAdjacent(v2)) {
			return true;
		}
		visited.insert(v1);
		vector<vertex*>* adjacent = v1->getAdjacentVertices();
		for (int i = 0;i < adjacent->size(); i++) {
			if (visited.count(adjacent->at(i)) != 0) {
				continue;
			}
			if (hasPath(adjacent->at(i), v2, visited)) {
				return true;
			}
		}
		return false;
	}

	void startAWalk(vertex* start, 
			unordered_set<vertex*>& visited) {
		visited.insert(start);
		vector<vertex*>* adjacent = start->getAdjacentVertices();
		for (int i = 0; i < adjacent->size(); i++) {
			if (visited.count(adjacent->at(i)) == 0) {
				startAWalk(adjacent->at(i), visited);
			}
		}
	}

	public:

	vector<vector<char*>*>* connectedComponents() {
		vector<vector<char*>*>* out = new vector<vector<char*>*>();
		if (vertices.size() == 0) {
			return out;
		}
		unordered_set<vertex*> visited;
		for (int i = 0; i < vertices.size(); i++) {
			if (visited.count(vertices[i]) == 0) {
				unordered_set<vertex*> visitedSmall;
				startAWalk(vertices[i], visitedSmall);
				vector<char*>* aCC = new vector<char*>();
				unordered_set<vertex*>::iterator it = 
					visitedSmall.begin();
				while (it != visitedSmall.end()) {
					char* nameCopy = new char[strlen((*it)->name) + 1];
					strcpy(nameCopy, (*it)->name);
					aCC->push_back(nameCopy);
					visited.insert(*it);
					it++;
				}
				out->push_back(aCC);
			}
		}
		return out;
	}

	bool isConnected() {
		if (vertices.size() == 0) {
			return true;
		}
		unordered_set<vertex*> visited;
		startAWalk(vertices[0], visited);
		if (visited.size() == vertices.size()) {
			return true;
		} else {
			return false;
		}
	}

	bool hasPath(char* name1, char* name2) {
		vertex* v1 = findVertex(name1);
		vertex* v2 = findVertex(name2);
		if (v1 == NULL || v2 == NULL) {
			return false;
		}
		unordered_set<vertex*> visited;
		return hasPath(v1, v2, visited);
	}


};
