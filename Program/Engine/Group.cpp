#include "Group.h"
#include "Model.h"
#include "Vertex.h"
#include <vector>
using namespace std;

Group::Group(void) {
}

Group::Group(Vertex rot, float rotAng, Vertex trans, Vertex scle, Vertex colr, vector<Model> modls, vector<Group> subs)
{
    rotation = rot;
    rotationAngle = rotAng;
    translation = trans;
    scale = scle;
    color = colr;
    models = modls;
    subGroups = subs;
};

Group::~Group()
{
}


