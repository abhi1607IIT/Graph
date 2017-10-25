#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

class vertex;

class edge {
	public:
	vertex* v1;
	vertex* v2;
	int distance;
	edge (vertex* v1, vertex* v2, int distance) {
		this->v1 = v1;
		this->v2 = v2;
		this->distance = distance;
	}
};
#endif
