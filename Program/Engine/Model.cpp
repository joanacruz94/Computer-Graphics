#include "Model.h";
#include <fstream>;
using namespace std;

Model::Model() {}

Model::Model(string path, string texture)
{
    ifstream file;

    file.open(path, ifstream::in);
    while (file)
    {
        float x, y, z;
        file >> x;
        file >> y;
        file >> z;
        vertexes.push_back(Vertex(x, y, z));
    }
    file.close();
    fileTexture = texture;
    
};

Model::~Model()
{
}