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

int model, nVertices;

GLfloat cX, cY, cZ, cPosX=5.0, cPosY=5.0, cPosZ=5.0;
float xx=0.0f;
float yy=0.0f;
float zz=0.0f;
float degree=0.0f;

GLuint buffers[1];

vector<string> models;

// Entre os models que foram carregados com o fiheiro XML, seleciona um para ser desenhado

void changeModel(int direction){
	if(model<(models.size()-1)&&direction)
		model++;
	else 
	 if(model>0 && !direction)
	 	model--;
}

// Abre o ficheiro do modelo actual e passa-o para o Buffer 
void modelo2Buffer() {
	float n;
	vector<float> vertices;
	ifstream ficheiro;

	ficheiro.open(models[model], ifstream::in);

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

// Abre um ficheiro XML e guarda o nome de todos os models a serem carregados no vetor models
int parseXML(char* fileXML) {
	TiXmlDocument ficheiroXML(fileXML);

	if (!ficheiroXML.LoadFile()) 
			return 0;

	TiXmlElement* sceneElement = ficheiroXML.FirstChildElement("scene");
	TiXmlElement* modelElement = sceneElement->FirstChildElement("model");

	for (modelElement; modelElement != NULL; modelElement = modelElement->NextSiblingElement("model")) {
		models.push_back(modelElement->Attribute("file"));
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

/*
void changeColor(){
	int i;
	float r = 0.529f, g = 0.8078f, b = 0.98f;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < nVertices; i+=3) {
		glColor3f(r, g, b);
		r+=0.01;
		g+=0.01;			
	}
	glEnd(); 
}*/

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f,0.0f,0.0f,0.0f);


	// set the camera
	glLoadIdentity();
	gluLookAt(cPosZ,cPosY,cPosX, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// put the geometric transformations here
	glPushMatrix();
	glTranslatef(xx,yy,zz); // moves the object.
	glRotatef(degree,0.0f,1.0f,0.0f); // rotate the object (Vertical Axis)

	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	
	glColor3f(0.529f, 0.8078f, 0.98f);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, nVertices);

	glPopMatrix();
	// End of frame
	glutSwapBuffers();
	glFlush();
}

// Write function to process keyboard events
void keyboardAction(unsigned char key, int x,int y){

	switch(key){
	case 'w':
		yy+=1.f;
		break;
	case 's':
		yy-=1.f;
		break;
	case 'a':
		xx-=1.f;
		break;
	case 'd':
		xx+=1.f;
		break;
	case 'q':
		degree-=10.f;
		break;
	case 'e':
		degree+=10.f;
		break;
	case 'l':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'n':
		changeModel(0);
		modelo2Buffer();
		break;
	case 'm':
		changeModel(1);
		modelo2Buffer();
		break;
	case 'x':
		cY -= 0.1;
		normalizeCamCoords();
		break;
	case 'z':
		cY+= 0.1;
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

void showHelp(){
    cout << "-------------- HELP GUIDE -----------------" << endl;
    cout << "|                                         |" << endl;
    cout << "| -> Arrows to rotate the camera          |" << endl;
    cout << "| -> x, z to zoom in and zoom out         |" << endl;
    cout << "| -> p, f, l  PolygonModes                |" << endl;
    cout << "| -> n, m to change models                |" << endl;
	cout << "|                                         |" << endl;
    cout << "-------------------------------------------" << endl;
}

int main(int argc, char **argv) {
	char* config = "config.xml";
	cX = 0.0;
	cY = 3.0;
	cZ = -5.0;
	normalizeCamCoords();

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Computação Gráfica-Fase1");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(keyboardAction);
	glutSpecialFunc(processSpecialKeys);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, buffers);
	
// Parsing XML e adicionar os vertices dos models aos buffers
	if (!parseXML(argv[1])) return 1;
	modelo2Buffer();

	showHelp();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}

