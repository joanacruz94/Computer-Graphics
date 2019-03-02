#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tinyxml.h>
#include "tinystr.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <ctype.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int pmode, modeloActual, nVertices;
GLfloat cX, cY, cZ, cPosX, cPosY, cPosZ;
GLuint buffers[1];
vector<string> modelos;

// Entre os modelos que foram carregados com o fiheiro XML, seleciona um para ser desenhado
void alterarModelo(int direcao) {
	if (modeloActual < (modelos.size()-1) && direcao) {
		modeloActual++;
	}
	else if (modeloActual > 0 && !direcao) {
		modeloActual--;
	}
}

// Abre o ficheiro do modelo actual e passa-o para o Buffer 
void modelo2Buffer() {
	float n;
	vector<float> vertices;
	ifstream ficheiro;

	ficheiro.open(modelos[modeloActual], ifstream::in);

	for (ficheiro; ficheiro >> n;) {
		vertices.push_back(n);
	}

	ficheiro.close();

	nVertices = vertices.size() / 3;

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	vertices.clear();
}

// Abre um ficheiro XML e guarda o nome de todos os modelos a serem carregados no vetor modelos
int parseXML(char* fileXML) {
	TiXmlDocument ficheiroXML(fileXML);

	if (!ficheiroXML.LoadFile()) return 0;
	TiXmlElement* sceneElement = ficheiroXML.FirstChildElement("scene");
	TiXmlElement* modelElement = sceneElement->FirstChildElement("model");

	for (modelElement; modelElement != NULL; modelElement = modelElement->NextSiblingElement("model")) {
		modelos.push_back(modelElement->Attribute("file"));
	}

	return 1;
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void normalizeCamCoords() {
	cPosX = (cY * 4) * cos(cZ) * sin(cX);
	cPosY = (cY * 4) * sin(cZ);
	cPosZ = (cY * 4) * cos(cZ) * cos(cX);
}

void drawAxe(){
	
//draw coordinate system
	glLineWidth(2.5);
	glBegin(GL_LINES);
	//Eixo do X.
	glVertex3f(-3.0,0.0f,0.0f);
	glVertex3f(3.0,0.0f,0.0f);
	glColor3f(1.0,0.0f,0.0f);
	glEnd();

	glBegin(GL_LINES);
	//Eixo do Y.
	glVertex3f(0.0f,-3.0,0.0f);
	glVertex3f(0.0f,3.0,0.0f);
	glColor3f(.0,1.0f,0.0f);
	glEnd();

	glBegin(GL_LINES);
	//Eixo do Z.
	glVertex3f(0.0f,0.0f,-3.0f);
	glVertex3f(0.0f,0.0f,3.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glEnd();

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	/*
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	*/
	glLoadIdentity();
	gluLookAt(cPosZ,cPosY,cPosX, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	

	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	switch (pmode) {
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	default:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}

	glColor3f(1.0f, 0.2f, 0.3f);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, nVertices);


	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'q':
		alterarModelo(0);
		modelo2Buffer();
		break;
	case 'w':
		alterarModelo(1);
		modelo2Buffer();
		break;
	case 'a':
		pmode = 1;
		break;
	case 's':
		pmode = 2;
		break;
	case 'd':
		pmode = 3;
		break;
	case 'x':
		cY -= 0.1;
		normalizeCamCoords();
		break;
	case 'z':
		cY += 0.1;
		normalizeCamCoords();
		break;
	default:
		break;
	}
	glutPostRedisplay();
	
}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT:
		cX -= 0.1;
		normalizeCamCoords();
		break;
	case GLUT_KEY_RIGHT:
		cX += 0.1;
		normalizeCamCoords();
		break;
	case GLUT_KEY_UP:
		cZ += 0.1;
		normalizeCamCoords();
		break;
	case GLUT_KEY_DOWN:
		cZ -= 0.1;
		normalizeCamCoords();
		break;
	default:
		break;
	}
	glutPostRedisplay();

}


int main(int argc, char **argv) {
	char* config = "config.xml";
	cX = 0.0;
	cY = 3.0;
	cZ = -5.0;
	pmode = 1;
	normalizeCamCoords();

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Computação Gráfica");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, buffers);
	
// Parsing XML e adicionar os vertices dos modelos aos buffers
	if (!parseXML(argv[1])) return 1;
	modelo2Buffer();

	cout << "Teclas :" << endl;
	cout << "Setas para rodar a camera" << endl;
	cout << "x,z para fazer zoom in e zoom out com a camera" << endl;
	cout << "a,s,d para trocar entre PolygonModes" << endl;
	cout << "q,w para trocar entre modelos carregados" << endl;
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
