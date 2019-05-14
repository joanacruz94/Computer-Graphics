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
	Vertex color;
	vector<Model> models;
	vector<Group> subGroups;
	vector<Vertex> orbitPoints;
	float translationTime;
	float rotationTime;
	string lightType;
	Vertex lightP;
	string texture;
	Group(void);
	Group(Vertex rot, float rotAng, Vertex trans, Vertex scle, Vertex colr, vector<Model> modls, vector<Group> subs, vector<Vertex> orbitPoint, float timeTranslation, float timeRotation, string light, Vertex ligthPos, string fileTexture);
	~Group();
};


#endif
