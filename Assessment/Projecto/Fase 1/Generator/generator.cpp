#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>


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

	else cout << "Não foi possível abrir o ficheiro"; 
	 		
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

    double x, y, z;

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

        z = dimZ;
        for (int i = 0; i < div; i++) {
            x = -dimX;
            for (int j = 0; j < div; j++) {
                file << "" << x << " 0 " << (z - divZ) << "\n";
                file << "" << (x + divX) << " 0 " << z << "\n";
                file << "" << x << " 0 " << z << "\n";

                file << "" << x << " 0 " << (z - divZ) << "\n";
                file << "" << (x + divX) << " 0 " << (z - divZ) << "\n";
                file << "" << (x + divX) << " 0 " << z << "\n";

                x += divX;
            }
            z -= divZ;
        }

        y = height;
        z = -dimZ;
        for (int i = 0; i < div; i++) {
            x = -dimX;
            for (int j = 0; j < div; j++) {
                file << "" << (x + divX) << " " << y << " " << z << "\n";
                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << y << " " << (z + divZ) << "\n";

                file << "" << (x + divX) << " " << y << " " << z << "\n";
                file << "" << x << " " << y << " " << (z + divZ) << "\n";
                file << "" << (x + divX) << " " << y << " " << (z + divZ) << "\n";

                x += divX;
            }
            z += divZ;
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

        x = -dimX;
        z = -dimZ;
        for (int i = 0; i < div; i++) {
            y = height;
            for (int j = 0; j < div; j++) {
                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << (z + divZ) << "\n";

                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << (z + divZ) << "\n";
                file << "" << x << " " << y << " " << (z + divZ) << "\n";

                y -= divY;
            }
            z += divZ;
        }

        x = dimX;
        z = dimZ;
        for (int i = 0; i < div; i++) {
            y = height;
            for (int j = 0; j < div; j++) {
                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << (z - divZ) << "\n";

                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << (z - divZ) << "\n";
                file << "" << x << " " << y << " " << (z - divZ) << "\n";

                y -= divY;
            }
            z -= divZ;
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

        x = -dimX;
        z = dimZ;
        for (int i = 0; i < div; i++) {
            y = height;
            for (int j = 0; j < div; j++) {
                file << "" << x << " " << y << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << z << "\n";
                file << "" << (x + divX) << " " << y << " " << z << "\n";

                file << "" << x << " " << (y - divY) << " " << z << "\n";
                file << "" << (x + divX) << " " << (y - divY) << " " << z << "\n";
                file << "" << (x + divX) << " " << y << " " << z << "\n";

                y -= divY;
            }
            x += divX;
        }

        x = -dimX;
        z = -dimZ;
        for (int i = 0; i < div; i++) {
            y = height;
            for (int j = 0; j < div; j++) {
                file << "" << x << " " << y << " " << z << "\n";
                file << "" << (x + divX) << " " << y << " " << z << "\n";
                file << "" << (x + divX) << " " << (y - divY) << " " << z << "\n";

                file << "" << x << " " << y << " " << z << "\n";
                file << "" << (x + divX) << " " << (y - divY) << " " << z << "\n";
                file << "" << x << " " << (y - divY) << " " << z << "\n";

                y -= divY;
            }
            x += divX;
        }
       
    }

    file.close();
}


int main (int argc, char** argv){

	if(strcmp(argv[1],"plane")== 0)
		generatePlane(argv[2],argv[3]);

	if (strcmp(argv[1], "box") == 0) 
       // if (argc == 6)
            generateBox(argv[2], argv[3], argv[4],atoi(argv[5]),argv[6]);
      //  if (argc == 7)
        //    generateBox(argv[2], argv[3], argv[4], atoi(argv[5]), argv[6]);
	


	return 0;
}

