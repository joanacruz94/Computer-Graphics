#include "Vertex.h"
#include <string>
#include <vector>
#ifndef MODEL_H
#define MODEL_H
using namespace std;

class Model{
public:
	string fileName;
	string fileTexture;
	vector<Vertex> vertexes;
	Model();
	Model(string path, string texture);	
	~Model();
};

#endif
