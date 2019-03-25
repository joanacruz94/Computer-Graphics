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

Vertex ParseColor(TiXmlElement *element)
{
    float r = 0, g = 0, b = 0;
   
    if (element->Attribute("R"))
        r = atof(element->Attribute("R"));
    if (element->Attribute("G"))
        g = atof(element->Attribute("G"));
    if (element->Attribute("B"))
        b = atof(element->Attribute("B"));

    return Vertex(r, g, b);
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
    TiXmlElement *grandChildElement, *childElement;
    group.rotation.x = 0;
    group.rotation.y = 0;
    group.rotation.z = 0;
    group.rotationAngle = 0;
    group.translation.x = 0;
    group.translation.y = 0;
    group.translation.z = 0;
    group.scale.x = 0;
    group.scale.y = 0;
    group.scale.z = 0;
    group.color.x = 0;
    group.color.y = 0;
    group.color.z = 0;
    bool translate = false, rotate = false, scale = false;

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
        else if (!strcmp(childElement->Value(), "color"))
        {
            group.color = ParseColor(childElement);
        }
        else if (!strcmp(childElement->Value(), "rotate") && !rotate)
        {
            group.rotation = ParseAttributes(childElement);
            group.rotationAngle = atof(childElement->Attribute("angle"));
            rotate = true;
        }
        else if (!strcmp(childElement->Value(), "translate") && !translate)
        {
            group.translation = ParseAttributes(childElement);
            translate = true;
        }
        else if (!strcmp(childElement->Value(), "scale") && !scale)
        {
            group.scale = ParseAttributes(childElement);
            scale = true;
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