#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>


using namespace std;




/* Gerador de um plano:
	char* l : Corresponde ao tamanho, convertido posteriormente para um double.
	char* filename : Corresponde a figura geométrica a ser gerada.
*/


void generatePlane(char* l,char* fileName){
	 
	 double tamanho= atof(l);
	 ofstream ficheiro;
	 ficheiro.open(fileName,ios::app);

/* To check if a file stream was successful opening a file, you can do it by calling to member is_open. This member function returns a bool value of true in the case that indeed the stream object is associated with an open file, or false otherwise: */

	 	if(ficheiro.is_open()){

	 	/* Corresponde as coordenadas do primeiro triângulo definido a custa de 3 pontos */
        ficheiro << "" << (-tamanho/2) << " 0 " << (-tamanho/2) << "\n";
        ficheiro << "" << (-tamanho/2) << " 0 " << (tamanho/2) << "\n";
        ficheiro << "" << (tamanho/2) << " 0 " << (tamanho/2) << "\n";

	 	/* Corresponde as coordenadas do segundo triângulo definido a custa de 3 pontos */
        ficheiro << "" << (-tamanho/2) << " 0 " << (-tamanho/2) << "\n";
        ficheiro << "" << (tamanho/2) << " 0 " << (tamanho/2) << "\n";
		ficheiro << "" << (tamanho/2) << " 0 " << (-tamanho/2) << "\n";

		ficheiro.close();

	 	}

	 	else cout << "Não foi possível abrir o ficheiro"; 
	 		
}

/*
void generateBox(char* x,char* y,char* z,char* fileName){
	double comprimento=atof(x)/2;
	double altura=atof(y)/2;
	double largura=atof(z)/2;


	ofstream ficheiro;
	ficheiro.open(fileName,ios::app);


	if(ficheiro.is_open()){
		// Base
	ficheiro << comprimento << " " << -altura << " " << -largura << endl;
	ficheiro << comprimento << " " << -altura << " " << largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;

	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;
	ficheiro << comprimento << " " << -altura << " " << largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << largura << endl;

	// Topo
	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << comprimento << " " << altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << altura << " " << -largura << endl;

	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << altura << " " << largura << endl;

	// Frente
	ficheiro << -comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;

	ficheiro << -comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << largura << endl;

	// Trás
	ficheiro << comprimento << " " << altura << " " << -largura << endl;
	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << comprimento << " " << -altura << " " << -largura << endl;

	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << comprimento << " " << -altura << " " << largura << endl;
	ficheiro << comprimento << " " << -altura << " " << -largura << endl;

	// Lado Esquerdo
	ficheiro << -comprimento << " " << altura << " " << -largura << endl;
	ficheiro << comprimento << " " << altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;

	ficheiro << comprimento << " " << altura << " " << -largura << endl;
	ficheiro << comprimento << " " << -altura << " " << -largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << -largura << endl;

	// Lado Direito
	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << largura << endl;

	ficheiro << comprimento << " " << altura << " " << largura << endl;
	ficheiro << -comprimento << " " << -altura << " " << largura << endl;
	ficheiro << comprimento << " " << -altura << " " << largura << endl;

		ficheiro.close();
	}

	else cout << "Não foi possível abrir o ficheiro"; 

}
*/

void generateBox(char* a, char* b, char* c, int div, char* fileName)
{
    double length = atof(a);
    double height = atof(b);
    double width = atof(c);

    double x, y, z;

    double divX = length/div;
    double divY = height/div;
    double divZ = width/div;

    ofstream file;
    file.open(fileName, ios::app);

    if (file.is_open()) {

        // Base da caixa.
        z = width/2;
        for (int i = 0; i < div; i++) {
            x = -length/2;
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

        // Face traseira da caixa. (Esquerda)
        x = -length/2;
        z = -width/2;
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

        // Face esquerda da caixa.     (Frontal)
        x = -length/2;
        z = width/2;
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

        // Face direita da caixa.  (Traseira)
        x = -length/2;
        z = -width/2;
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

        // Face frontal da caixa.  (Direita)
        x = length/2;
        z = width/2;
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

        // Tampa superior da caixa.
        y = height;
        z = -width/2;
        for (int i = 0; i < div; i++) {
            x = -length/2;
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

