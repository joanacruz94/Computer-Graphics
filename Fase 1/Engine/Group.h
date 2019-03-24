#include "Vertex.h"
#include "Model.h"
#ifndef GROUP_H
#define GROUP_H
using namespace std;

class Group{
public:
	Vertex rotation;
	float rotationAngle;
	Vertex translation;
	Vertex scale;
	vector<Model> models;
	vector<Group> subGroups;
	Group(void);
	Group(Vertex rot, float rotAng, Vertex trans, Vertex scle, vector<Model> modls, vector<Group> subs);
	~Group();
};

#endif
