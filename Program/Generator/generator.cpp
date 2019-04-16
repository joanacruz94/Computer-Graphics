#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI       3.14159265358979323846   // pi

using namespace std;


/* Gerador de um plano:
 * @param lenght : Corresponde ao tamanho do plano.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todas as coordenadas dos triângulos de um plano.
 */
void generatePlane(double lenght, char* fileName){
    
    double dim = lenght/2;
    ofstream file;
    file.open(fileName,ios::app);
    
    /* To check if a file stream was successful opening a file, you can do it by calling to member is_open. This member function returns a bool value of true in the case that indeed the stream object is associated with an open file, or false otherwise: */
    
    if(file.is_open()){
        
        /* Corresponde as coordenadas do primeiro triângulo definido a custa de 3 pontos */
        file << "" << (-dim) << " 0 " << (dim) << "\n";
        file << "" << (dim) << " 0 " << (-dim) << "\n";
        file << "" << (-dim) << " 0 " << (-dim) << "\n";
        
        /* Corresponde as coordenadas do segundo triângulo definido a custa de 3 pontos */
        file << "" << (-dim) << " 0 " << (dim) << "\n";
        file << "" << (dim) << " 0 " << (dim) << "\n";
        file << "" << (dim) << " 0 " << (-dim) << "\n";
        
        file.close();
        
    }
}



/* Gerador de uma caixa:
 * @param length : Corresponde ao comprimento da caixa, dimensão da caixa no eixo dos xx.
 * @param height : Corresponde à altura da caixa, dimensão da caixa no eixo dos yy.
 * @param width : Corresponde à largura da caixa, dimensão da caixa no eixo dos zz.
 * @param div : Corresponde ao número de divisões da caixa.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todas as coordenadas dos triângulos de uma caixa.
 */
void generateBox(double length, double height, double width, int div, char* fileName){
    
    double divX = length/div; // Dimensão de uma divisão da caixa no eixo dos xx
    double divY = height/div; // Dimensão de uma divisão da caixa no eixo dos xx
    double divZ = width/div; // Dimensão de uma divisão da caixa no eixo dos xx
    
    double dimX = length/2; // Coordenada x do centro da caixa
    double dimY = height/2; // Coordenada y do centro da caixa
    double dimZ = width/2;  // Coordenada z do centro da caixa
    
    double x, y, z;
    int i,j;
    
    
    ofstream file;
    file.open(fileName, ios::app);
    
    if (file.is_open()) {
        
        /*
         * Faces XZ.
         * Base da caixa.
         * Tampa superior da caixa.
         *   v1------v3
         *  /       /
         * v2------v4
         *
         *   v5------v6
         *  /       /
         * v7------v8
         */
        
        for (i = 0; i < div; i++) {
            x = i*divX;
            for (j = 0; j < div; j++){
                z = j*divZ;
                file << "" << (x-dimX+divX) << " " << dimY << " " << (z-dimZ) << "\n";
                file << "" << (x-dimX) << " " << dimY << " " << (z-dimZ) << "\n";
                file << "" << (x-dimX) << " " << dimY << " " << (z-dimZ+divZ) << "\n";
                
                file << "" << (x-dimX+divX) << " " << dimY << " " << (z-dimZ) << "\n";
                file << "" << (x-dimX) << " " << dimY << " " << (z-dimZ+divZ) << "\n";
                file << "" << (x-dimX+divX) << " " << dimY << " " << (z-dimZ+divZ)  << "\n";
                
                file << "" << (x-dimX+divX) << " " << (-dimY) << " " << (z-dimZ) << "\n";
                file << "" << (x-dimX) << " " << (-dimY)  << " " << (z-dimZ+divZ)  << "\n";
                file << "" << (x-dimX) << " " << (-dimY)  << " " << (z-dimZ) << "\n";
                
                file << "" << (x-dimX+divX) << " " << (-dimY)  << " " << (z-dimZ) << "\n";
                file << "" << (x-dimX+divX) << " " << (-dimY)  << " " << (z-dimZ+divZ) << "\n";
                file << "" << (x-dimX) << " " << (-dimY)  << " " << (z-dimZ+divZ) << "\n";
                
            }
        }
        
        /*
         * Faces XY.
         * Face traseira da caixa.
         * Face frontal da caixa.
         *
         *   v8----- v6
         *   |       |
         * v4------v3|
         * | |     | |
         * | |v5---|-|v7
         * |       |
         * v1------v2
         */
        
        for (i = 0; i < div; i++) {
            x = i*divX;
            for (j = 0; j < div; j++){
                y = j*divY;
                file << "" << (x-dimX) << " " << (y-dimY) << " " << dimZ << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY+divY) << " " << dimZ << "\n";
                file << "" << (x-dimX) << " " << (y-dimY+divY) << " " << dimZ << "\n";
                
                file << "" << (x-dimX) << " " << (y-dimY) << " " << dimZ << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY) << " " << (dimZ) << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY+divY) << " " << dimZ << "\n";
                
                file << "" << (x-dimX) << " " << (y-dimY) << " " << (-dimZ) << "\n";
                file << "" << (x-dimX) << " " << (y-dimY+divY) << " " << (-dimZ) << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY+divY) << " " << (-dimZ) << "\n";
                
                file << "" << (x-dimX) << " " << (y-dimY) << " " << (-dimZ) << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY+divY) << " " << (-dimZ) << "\n";
                file << "" << (x-dimX+divX) << " " << (y-dimY) << " " << (-dimZ) << "\n";
                
            }
        }
        
        /*
         * Faces YZ.
         * Face esquerda da caixa.
         * Face direita da caixa.
         *   v7      v2
         *  /|      /|
         * v6|     v3|
         * | |     | |
         * | |v5   |v1
         * |/      |/
         * v8      v4
         */
        
        for (i = 0; i < div; i++) {
            y = i*divY;
            for (j = 0; j < div; j++){
                z = j*divZ;
                file << "" << dimX << " " << (y-dimY) << " " << (z-dimZ+divZ) << "\n";
                file << "" << dimX << " " << (y-dimY+divY) << " " << (z-dimZ) << "\n";
                file << "" << dimX << " " << (y-dimY+divY) << " " << (z-dimZ+divZ) << "\n";
                
                file << "" << dimX << " " << (y-dimY) << " " << (z-dimZ+divZ) << "\n";
                file << "" << dimX << " " << (y-dimY) << " " << (z-dimZ) << "\n";
                file << "" << dimX << " " << (y-dimY+divY) << " " << (z-dimZ) << "\n";
                
                file << "" << (-dimX) << " " << (y-dimY) << " " << (z-dimZ+divZ) << "\n";
                file << "" << (-dimX) << " " << (y-dimY+divY) << " " << (z-dimZ+divZ) << "\n";
                file << "" << (-dimX) << " " << (y-dimY+divY) << " " << (z-dimZ) << "\n";
                
                file << "" << (-dimX) << " " << (y-dimY) << " " << (z-dimZ+divZ) << "\n";
                file << "" << (-dimX) << " " << (y-dimY+divY) << " " << (z-dimZ) << "\n";
                file << "" << (-dimX) << " " << (y-dimY) << " " << (z-dimZ) << "\n";
            }
        }
        
        file.close();
        
    }
}

/* Gerador de uma esfera:
 * @param radius : Corresponde ao raio da esfera.
 * @param slices : Corresponde ao número de divisões na vertical ao longo da esfera.
 * @param stacks : Corresponde ao número de divisões na horizontal ao longo da esfera.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todas as coordenadas dos triângulos de uma esfera.
 */
void generateSphere(double radius, int slices, int stacks, char* fileName){
    double deltaBeta = PI / stacks;
    double deltaAlpha = 2 * PI / slices;
    double angleBeta, angleAlpha;
    double aX, aY, aZ, bX, bY, bZ, cX, cY, cZ, dX, dY, dZ;
    ofstream file;
    file.open(fileName,ios::app);
    
    
    if(file.is_open()){
        for (int i = 0; i < stacks; i++) {
            angleBeta = i*deltaBeta;
            for (int j = 0; j < slices; j++) {
                angleAlpha = j*deltaAlpha;
                aX = radius*sin(angleBeta)*sin(angleAlpha);
                aY = radius*cos(angleBeta);
                aZ = radius*sin(angleBeta)*cos(angleAlpha);
                
                bX = radius*sin(angleBeta)*sin(angleAlpha + deltaAlpha);
                bY = radius*cos(angleBeta);
                bZ = radius*sin(angleBeta)*cos(angleAlpha + deltaAlpha);
                
                cX = radius*sin(angleBeta + deltaBeta)*sin(angleAlpha + deltaAlpha);
                cY = radius*cos(angleBeta + deltaBeta);
                cZ = radius*sin(angleBeta + deltaBeta)*cos(angleAlpha + deltaAlpha);
                
                dX = radius*sin(angleBeta + deltaBeta)*sin(angleAlpha);
                dY = radius*cos(angleBeta + deltaBeta);
                dZ = radius*sin(angleBeta + deltaBeta)*cos(angleAlpha);
                
                file << "" << aX << " " << aY << " " << aZ << "\n";
                file << "" << bX << " " << bY << " " << bZ << "\n";
                file << "" << cX << " " << cY << " " << cZ << "\n";
                
                file << "" << aX << " " << aY << " " << aZ << "\n";
                file << "" << cX << " " << cY << " " << cZ << "\n";
                file << "" << dX << " " << dY << " " << dZ << "\n";
            }
        }
        
        file.close();
        
    }
}

/* Gerador de um cone:
 * @param radius : Corresponde ao raio do cone.
 * @param height : Corresponde à altura do cone.
 * @param slices : Corresponde ao número de divisões na vertical ao longo do cone.
 * @param stacks : Corresponde ao número de divisões na horizontal ao longo do cone.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todas as coordenadas dos triângulos de um cone.
 */
void generateCone(double radius, double height, int slices, int stacks, char* fileName){
    
    double x,y,z,aux,incAlfa,incHeight,oldRadius,newRadius,alfa;
    incAlfa = (2*M_PI)/slices;
    incHeight = height/stacks;
    oldRadius = radius;
    aux = radius/height;
    
    ofstream file;
    file.open(fileName, ios::app);
    
    if (file.is_open()) {
        //Base
        
        for (int i = 0; i < slices; i++) {
            alfa = i * incAlfa;
            x = radius * sin(alfa);
            y = 0;
            z = radius * cos(alfa);
            
            file << x << " " << y << " " << z << endl;
            file << 0 << " " << y << " " << 0 << endl;
            file << radius * sin(alfa + incAlfa) << " " << y << " " << radius * cos(alfa + incAlfa) << endl;
        }
        
        //Superfície Lateral
        for (int i = 0; i < stacks; i++) {
            y = i * incHeight;
            //Novo raio
            newRadius = aux * (height - ((i+1) * incHeight));
            for (int j = 0; j < slices; j++) {
                alfa = j * incAlfa;
                
                x = oldRadius * sin(alfa);
                z = oldRadius * cos(alfa);
                
                //Primeiro Triângulo
                file << x << " " << y << " " << z << endl;
                file << oldRadius * sin(alfa + incAlfa) << " " << y << " " << oldRadius * cos(alfa + incAlfa) << endl;
                file << newRadius * sin(alfa + incAlfa) << " " << y + incHeight << " " << newRadius * cos(alfa + incAlfa) << endl;
                
                //Segundo Triângulo
                file << x << " " << y << " " << z << endl;
                file << newRadius * sin(alfa + incAlfa) << " " << y + incHeight << " " << newRadius * cos(alfa + incAlfa) << endl;
                file << newRadius * sin(alfa) << " " << y + incHeight << " " << newRadius * cos(alfa) << endl;
            }
            
            oldRadius = newRadius;
        }
        
        file.close();
    }
}

float getBezierPoint(float u, float v, int coord, float ** vertices, int * indices) {
    float pointValue = 0;
    
    float bu[4][1] = { { powf(1 - u, 3) },{ 3 * u * powf(1 - u, 2) },{ 3 * powf(u, 2) * (1 - u) },{ powf(u, 3) } };
    float bv[4][1] = { { powf(1 - v, 3) },{ 3 * v * powf(1 - v, 2) },{ 3 * powf(v, 2) * (1 - v) },{ powf(v, 3) } };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pointValue += vertices[indices[j + 4 * i]][coord] * bu[i][0] * bv[j][0];
        }
    }
    return pointValue;
}



void generatePatch(int points, float ** controlPoints, int patches, int ** indices, float tessel, char * fileName) {
    float ponto[3];
    float v, u;
    float tesselation = 1.0 / tessel;
    ofstream file;
    file.open(fileName, ios::app);
    
    if(file.is_open()){
        for (int patch = 0; patch < patches; patch++) {
            int * indicesPatch = indices[patch];
            for (v = 0; v < 1; v += tesselation) {
                for (u = 0; u < 1; u += tesselation) {
                    ponto[0] = getBezierPoint(u, v, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u, v, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u, v, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                    ponto[0] = getBezierPoint(u + tesselation, v, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u + tesselation, v, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u + tesselation, v, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                    ponto[0] = getBezierPoint(u, v + tesselation, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u, v + tesselation, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u, v + tesselation, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                    ponto[0] = getBezierPoint(u, v + tesselation, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u, v + tesselation, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u, v + tesselation, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                    ponto[0] = getBezierPoint(u + tesselation, v, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u + tesselation, v, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u + tesselation, v, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                    ponto[0] = getBezierPoint(u + tesselation, v + tesselation, 0, controlPoints, indicesPatch);
                    ponto[1] = getBezierPoint(u + tesselation, v + tesselation, 1, controlPoints, indicesPatch);
                    ponto[2] = getBezierPoint(u + tesselation, v + tesselation, 2, controlPoints, indicesPatch);
                    file << ponto[0] << " " << ponto[1] << " " << ponto[2] << endl;
                }
            }
        }
        file.close();
    }
        
}

void patches(string fileIn, float tesselLvl, char * fileName) {
    string line;
    string indice[16];
    ifstream infile;
    int i, j, patches, points, **indices;
    float **controlPoints;
    infile.open(fileIn);
    
    getline(infile, line);
    patches = stoi(line);
    indices = (int **)malloc(sizeof(int*)*patches);
    for (i = 0; i < patches; i++) {
        indices[i] = (int *)malloc(sizeof(int) * 16);
    }
    
    for (i = 0; i < patches; i++) {
        getline(infile, line);
        std::istringstream ss(line);
        std::string token;
        j = 0;
        while (std::getline(ss, token, ',')) {
            indices[i][j] = stoi(token);
            j++;
        }
    }
    getline(infile, line);
    points = stoi(line);
    controlPoints = (float **)malloc(sizeof(float*)*points);
    for (i = 0; i < points; i++) {
        controlPoints[i] = (float *)malloc(sizeof(float) * 3);
    }
    for (i = 0; i < points; i++) {
        getline(infile, line);
        std::istringstream ss(line);
        std::string token;
        j = 0;
        while (std::getline(ss, token, ',')) {
            controlPoints[i][j] = stof(token);
            j++;
        }
    }
    generatePatch(points, controlPoints, patches, indices, tesselLvl, fileName);
}

void showHelp(){
    cout << "-------------------------------- Help Guide ---------------------------------------" << endl;
    cout << "|                                                                                 |" << endl;
    cout << "| How to use:                                                                     |" << endl;
    cout << "|  -> ./generator (figure) (dimensions) (file)                                    |" << endl;
    cout << "|                                                                                 |" << endl;
    cout << "| Supported figures:                                                              |" << endl;
    cout << "|  -> plane:                                                                      |" << endl;
    cout << "|     Syntax: generator plane <size> <fileName>                                   |" << endl;
    cout << "|  -> box:                                                                        |" << endl;
    cout << "|     Syntax: generator box <xSize> <ySize> <zSize> <divisions> <fileName>        |" << endl;
    cout << "|  -> sphere:                                                                     |" << endl;
    cout << "|     Syntax: generator sphere <radius> <slices> <stacks> <fileName>              |" << endl;
    cout << "|  -> cone:                                                                       |" << endl;
    cout << "|     Syntax: generator cone <bottomRadius> <height> <slices> <stacks> <fileName> |" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
}

int main(int argc, char** argv){
    
    if(argc < 2){
        cout << "Need arguments!" << endl;
        return -1;
    }
    
    else if(strcmp(argv[1],"plane")== 0){
        if (argc != 4) {
            cout << "Error! Syntax: generator plane <size> <fileName>" << endl;
            return -1;
        }
        generatePlane(atof(argv[2]), argv[3]);
    }
    
    else if (strcmp(argv[1], "box") == 0){
        if (argc != 7) {
            cout << "Error! Syntax: generator box <xSize> <ySize> <zSize> <divisions> <fileName>" << endl;
            return -1;
        }
        generateBox(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]),argv[6]);
    }
    
    else if (strcmp(argv[1], "sphere") == 0){
        if (argc != 6) {
            cout << "Error! Syntax: generator sphere <radius> <slices> <stacks> <fileName>" << endl;
            return -1;
        }
        generateSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
    }
    
    else if(strcmp(argv[1],"cone") == 0){
        if (argc != 7) {
            cout << "Error! Syntax: generator cone <bottomRadius> <height> <slices> <stacks> <fileName>" << endl;
            return -1;
        }
        generateCone(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    }
    
    else if(strcmp(argv[1], "help") == 0){
        showHelp();
        return 0;
    }
    
    else if (strcmp(argv[1], "patch") == 0) {
        if (argc != 5) {
            printf("sintaxe: gerador patch <patchFile> <tesselation> <fileName>\n");
            return -1;
        }
        patches(argv[2], stof(argv[3]), argv[4]);
    }
    
    else{
        cout << "Don't recognize that input. Need help? Try './generator help!" << endl;
        return -1;
    }
    
    return 0;
}
