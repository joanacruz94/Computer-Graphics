#include "parser.h"
#include <string>
#include <vector>
#include "Group.h"
#include "Model.h"
#include "Vertex.h"
#include <tinyxml.h>
#include "tinystr.h"
using namespace std;

Vertex ParseAttributes(TiXmlElement *element)
{
    float x = 0, y = 0, z = 0;
    if (element->Attribute("X"))
        x = atof(element->Attribute("X"));
    if (element->Attribute("axisX"))
        x = atof(element->Attribute("axisX"));
    if (element->Attribute("Y"))
        y = atof(element->Attribute("Y"));
    if (element->Attribute("axisY"))
        y = atof(element->Attribute("axisY"));
    if (element->Attribute("Z"))
        z = atof(element->Attribute("Z"));
    if (element->Attribute("axisZ"))
        z = atof(element->Attribute("axisZ"));
    return Vertex(x, y, z);
}

Model ParseModel(TiXmlElement *modelElement)
{
    if (modelElement->Attribute("file"))
    {
        string filePath = modelElement->Attribute("file");
        return Model(filePath);
    }
    return Model();
}

Group ParseGroup(TiXmlElement *groupElement)
{
    Group group = Group();
    group.subGroups = vector<Group>();
    TiXmlElement *grandChildElement, *element3, *childElement;

    for (childElement = groupElement->FirstChildElement(); childElement; childElement = childElement->NextSiblingElement())
    {
        if (!strcmp(childElement->Value(), "models"))
        {
            for (grandChildElement = childElement->FirstChildElement("model"); grandChildElement; grandChildElement = grandChildElement->NextSiblingElement())
            {
                if (!strcmp(grandChildElement->Value(), "model"))
                {
                    group.models.push_back(ParseModel(grandChildElement));
                }
            }
        }

        else if (!strcmp(childElement->Value(), "rotate"))
        {
            group.rotation = ParseAttributes(childElement);
            group.rotationAngle = atof(childElement->Attribute("angle"));
        }
        else if (!strcmp(childElement->Value(), "translate"))
        {
            group.translation = ParseAttributes(childElement);
        }

        else if (!strcmp(childElement->Value(), "scale"))
        {
            group.scale = ParseAttributes(childElement);
        }

        else if (!strcmp(childElement->Value(), "group"))
        {
            group.subGroups.push_back(ParseGroup(childElement));
        }
    }
    return group;
}

vector<Group> ParseXMLFile(char *fileName)
{
    vector<Group> scene = vector<Group>();
    TiXmlDocument doc(fileName);
    TiXmlElement *groupElement;

    if (!doc.LoadFile())
    {
        cout << "Could not load XML file: " << fileName << "." << endl;
        return scene;
    }

    for (groupElement = doc.FirstChildElement("scene")->FirstChildElement(); groupElement; groupElement = groupElement->NextSiblingElement())
    {
        scene.push_back(ParseGroup(groupElement));
    }

    return scene;
}