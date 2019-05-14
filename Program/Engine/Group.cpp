#include "Group.h"
#include "Model.h"
#include "Vertex.h"
#include <vector>
using namespace std;

Group::Group(void) {
}

Group::Group(Vertex rot, float rotAng, Vertex trans, Vertex scle, Vertex colr, vector<Model> modls, vector<Group> subs, vector<Vertex> orbitPoint, float timeTranslation, float timeRotation, string light, Vertex ligthPos, string fileTexture)
{
    rotation = rot;
    rotationAngle = rotAng;
    translation = trans;
    scale = scle;
    color = colr;
    models = modls;
    subGroups = subs;
    orbitPoints = orbitPoint;
    translationTime = timeTranslation;
    rotationTime = timeRotation;
    lightType = light;
    lightP = ligthPos;
    texture = fileTexture;
    
};

Group::~Group()
{
}


