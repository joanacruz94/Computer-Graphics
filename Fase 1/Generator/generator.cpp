#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define PI       3.14159265358979323846   // pi

using namespace std;




/* Gerador de um plano:
 * @param l : Corresponde ao tamanho, convertido posteriormente para um double.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todos as coordenadas de todos os pontos de um plano.
 */


void generatePlane(char* l, char* fileName){
	 
	 double lenght = atof(l);
     double dim = lenght/2;
	 ofstream file;
	 file.open(fileName,ios::app);

/* To check if a file stream was successful opening a file, you can do it by calling to member is_open. This member function returns a bool value of true in the case that indeed the stream object is associated with an open file, or false otherwise: */

	if(file.is_open()){

	 	/* Corresponde as coordenadas do primeiro triângulo definido a custa de 3 pontos */
        file << "" << (-dim) << " 0 " << (-dim) << "\n";
        file << "" << (-dim) << " 0 " << (dim) << "\n";
        file << "" << (dim) << " 0 " << (dim) << "\n";

	 	/* Corresponde as coordenadas do segundo triângulo definido a custa de 3 pontos */
        file << "" << (-dim) << " 0 " << (-dim) << "\n";
        file << "" << (dim) << " 0 " << (dim) << "\n";
		file << "" << (dim) << " 0 " << (-dim) << "\n";

		file.close();

	 	}

	else cout << "Impossível escrever sobre ficheiro"; 
	 		
}


/* Gerador de uma caixa:
 * @param a : Corresponde ao comprimento da caixa, convertido posteriormente para um double.
 * @param b : Corresponde à altura da caixa, convertido posteriormente para um double.
 * @param c : Corresponde à largura da caixa, convertido posteriormente para um double.
 * @param div : Corresponde ao número de divisões da caixa.
 * @param filename : Corresponde a figura geométrica a ser gerada.
 * Método que cálcula todos as coordenadas de todos os pontos de uma caixa.
 */
void generateBox(char* a, char* b, char* c, int div, char* fileName)
{
    double length = atof(a); // Comprimento da caixa - dimensão da caixa no eixo dos xx
    double height = atof(b); // Altura da caixa - dimensão da caixa no eixo dos yy
    double width = atof(c);  // Largura da caixa - dimensão da caixa no eixo dos zz

    double x, y, z, i, j;

    double divX = length/div; // Dimensão de uma divisão da caixa no eixo dos xx
    double divY = height/div; // Dimensão de uma divisão da caixa no eixo dos xx
    double divZ = width/div; // Dimensão de uma divisão da caixa no eixo dos xx

    double dimX = length/2; // Coordenada x do centro da caixa
    double dimY = height/2; // Coordenada y do centro da caixa
    double dimZ = width/2;  // Coordenada z do centro da caixa

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

        file << "" << dimX << " " << dimY << " " << (-dimZ) << "\n";
        file << "" << (-dimX) << " " << dimY << " " << (-dimZ) << "\n";
        file << "" << (-dimX) << " " << dimY << " " << dimZ << "\n";

        file << "" << dimX << " " << dimY << " " << (-dimZ) << "\n";
        file << "" << (-dimX) << " " << dimY << " " << dimZ << "\n";
        file << "" << dimX << " " << dimY << " " << dimZ << "\n";

        file << "" << dimX << " " << (-dimY) << " " << (-dimZ) << "\n";
        file << "" << (-dimX) << " " << (-dimY)  << " " << dimZ << "\n";
        file << "" << (-dimX) << " " << (-dimY)  << " " << (-dimZ) << "\n";

        file << "" << dimX << " " << (-dimY)  << " " << (-dimZ) << "\n";
        file << "" << dimX << " " << (-dimY)  << " " << dimZ << "\n";
        file << "" << (-dimX) << " " << (-dimY)  << " " << dimZ << "\n";


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

    	//for (float i = x; i < dimX; i += divX) {
			//for (float j = y; j < dimY; j += divY){

                file << "" << (-dimX) << " " << (-dimY) << " " << dimZ << "\n";
                file << "" << dimX << " " << dimY << " " << dimZ << "\n";
                file << "" << (-dimX) << " " << (dimY) << " " << dimZ << "\n";

                file << "" << (-dimX) << " " << (-dimY) << " " << dimZ << "\n";
                file << "" << (dimX) << " " << (-dimY) << " " << (dimZ) << "\n";
                file << "" << (dimX) << " " << dimY << " " << dimZ << "\n";

                file << "" << (-dimX) << " " << (-dimY) << " " << (-dimZ) << "\n";
                file << "" << (-dimX) << " " << dimY << " " << (-dimZ) << "\n";
                file << "" << (dimX) << " " << (dimY) << " " << (-dimZ) << "\n";

                file << "" << (-dimX) << " " << (-dimY) << " " << (-dimZ) << "\n";
                file << "" << (dimX) << " " << (dimY) << " " << (-dimZ) << "\n";
                file << "" << dimX << " " << (-dimY) << " " << (-dimZ) << "\n";

            //}
        //}


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

        file << "" << dimX << " " << (-dimY) << " " << dimZ << "\n";
        file << "" << dimX << " " << dimY << " " << (-dimZ) << "\n";
        file << "" << dimX << " " << dimY << " " << dimZ << "\n";

        file << "" << dimX << " " << (-dimY) << " " << dimZ << "\n";
        file << "" << dimX << " " << (-dimY) << " " << (-dimZ) << "\n";
        file << "" << dimX << " " << dimY << " " << (-dimZ) << "\n";

        file << "" << (-dimX) << " " << (-dimY) << " " << dimZ << "\n";
        file << "" << (-dimX) << " " << dimY << " " << dimZ << "\n";
        file << "" << (-dimX) << " " << dimY << " " << (-dimZ) << "\n";

        file << "" << (-dimX) << " " << (-dimY) << " " << dimZ << "\n";
        file << "" << (-dimX) << " " << dimY << " " << (-dimZ) << "\n";
        file << "" << (-dimX) << " " << (-dimY) << " " << (-dimZ) << "\n";

        file.close();

    }

    else cout << "Não foi possível abrir o ficheiro"; 

}

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

	else cout << "Impossível escrever sobre ficheiro"; 
	 		
}

void generateCone(char* r,char* h,int slices,int stacks,char* fileName){
    
    double altura=atof(h);
    double raio=atof(r);
    double x,y,z,aux,incAlfa,incHeight,oldRadius,newRadius,alfa;
    incAlfa=(2*M_PI)/slices;
    incHeight=altura/stacks;
    oldRadius=raio;
    aux=raio/altura;

    ofstream file;
    file.open(fileName, ios::app);
    // Check if file open
    if (file.is_open()) {

        
        // Base
        for (int i = 0; i < slices; i++) {
            alfa = i * incAlfa;
            x = raio * sin(alfa);
            y = 0;
            z = raio * cos(alfa);

            file << 0 << " " << y << " " << 0 << endl;
            file << raio * sin(alfa + incAlfa) << " " << y << " " << raio * cos(alfa + incAlfa) << endl;
            file << x << " " << y << " " << z << endl;
        }

        // Cone
        for (int i = 0; i < stacks; i++) {
            y = i * incHeight;
            // New radius
            newRadius = aux * (altura - ((i+1) * incHeight));
            for (int j = 0; j < slices; j++) {
                alfa = j * incAlfa;

                x = oldRadius * sin(alfa);
                z = oldRadius * cos(alfa);

                // First Triangle
                file << x << " " << y << " " << z << endl;
                file << oldRadius * sin(alfa + incAlfa) << " " << y << " " << oldRadius * cos(alfa + incAlfa) << endl;
                file << newRadius * sin(alfa + incAlfa) << " " << y + incHeight << " " << newRadius * cos(alfa + incAlfa) << endl;

                // Second Triangle
                file << x << " " << y << " " << z << endl;
                file << newRadius * sin(alfa + incAlfa) << " " << y + incHeight << " " << newRadius * cos(alfa + incAlfa) << endl;
                file << newRadius * sin(alfa) << " " << y + incHeight << " " << newRadius * cos(alfa) << endl;
            }

            oldRadius = newRadius;
        }

        // Close File
        file.close();
    }
    else
        cout << "Impossível escrever sobre ficheiro " ;
}
int main (int argc, char** argv){

	if(strcmp(argv[1],"plane")== 0)
		generatePlane(argv[2],argv[3]);

	if (strcmp(argv[1], "box") == 0) 
        generateBox(argv[2], argv[3], argv[4],atoi(argv[5]),argv[6]);

    if (strcmp(argv[1], "sphere") == 0) 
        generateSphere(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);

    if(strcmp(argv[1],"cone")==0)
        generateCone(argv[2], argv[3], atoi(argv[4]),atoi(argv[5]),argv[6]);  


	return 0;
}

