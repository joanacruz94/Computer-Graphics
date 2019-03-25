#include "Vertex.h"
#include <string>
#include <vector>
#ifndef MODEL_H
#define MODEL_H
using namespace std;

class Model{
public:
	string fileName;
	vector<Vertex> vertexes;
	Model();
	Model(string path);
	~Model();
};

#endif
