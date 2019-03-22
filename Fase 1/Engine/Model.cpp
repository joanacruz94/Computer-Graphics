#include "Model.h";
#include <fstream>;
using namespace std;

Model::Model() {}

Model::Model(string path)
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
};

Model::~Model()
{
}