#include "Group.h"
#include "Model.h"
#include "Vertex.h"
#include <vector>
using namespace std;

Group::Group(void) {
}

Group::Group(Vertex rot, float rotAng, Vertex trans, Vertex scle, vector<Model> modls, vector<Group> subs)
{
    rotation = rot;
    rotationAngle = rotAng;
    translation = trans;
    scale = scle;
    models = modls;
    subGroups = subs;
};

Group::~Group()
{
}
