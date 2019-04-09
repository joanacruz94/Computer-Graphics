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
#include "Group.h"
#include "Model.h"
#include "Vertex.h"
#include "parser.h"
using namespace std;

/*
 * alpha - ângulo com o eixo dos xx e a camera; varia de 0 a 2pi
 * beta - ângulo com o eixo dos yy e a camera; varia de 0 a pi
 * radius - raio com a posição da camera
 * alpha, beta e radius - estas variáveis vão definir constantemente a posição para onde a camera está a apontar
 * cPosX - posição no eixo dos xx da camera
 * cPosY - posição no eixo dos yy da camera
 * cPosZ - posição no eixo dos zz da camera
 */

GLfloat alpha, radius, beta, cPosX = 0.0, cPosY = 0.0, cPosZ = 0.0;
float xx = 0.0f;
float yy = 0.0f;
float zz = 0.0f;
float degree = 0.0f;
int nBuffer,counterBuff;
vector<Group> scene;
GLuint * buffers;

//constrói a matriz
void buildRotMatrix(float *x, float *y, float *z, float *m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

//efetua o produto escalar
void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

//comprimento de um vetor
float length(float *v) {

	float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return res;

}

//normaliza um vetor
void normalize(float *a) {
	float l = sqrt(length(a));
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}


void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

	// catmull-rom matrix
	float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
					{ 1.0f, -2.5f,  2.0f, -0.5f },
					{ -0.5f,  0.0f,  0.5f,  0.0f },
					{ 0.0f,  1.0f,  0.0f,  0.0f } };

	// reset res and deriv
	pos[0] = 0.0; pos[1] = 0.0; pos[2] = 0.0;
	deriv[0] = 0.0; deriv[1] = 0.0; deriv[2] = 0.0;
	
	// Compute A = M * P
    float Px[4] = {p0[0], p1[0], p2[0], p3[0]};
    float Py[4] = {p0[1], p1[1], p2[1], p3[1]};
    float Pz[4] = {p0[2], p1[2], p2[2], p3[2]};

	float A[3][4];
    multMatrixVector(*m, Px, A[1]);
    multMatrixVector(*m, Py, A[2]);
    multMatrixVector(*m, Pz, A[3]);

	// Compute point res = T * A
	// compute deriv = T' * A
	float T[4] = { pow(t,3), pow(t,2), t, 1 };
    float Td[4] = { 3*pow(t,2), 2*pow(t,1), 1, 0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pos[i] += T[j] * A[i][j];
			deriv[i] += Td[j] * A[i][j];
		}
	}
}

/*
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;	
	indices[1] = (indices[0]+1)%POINT_COUNT;
	indices[2] = (indices[1]+1)%POINT_COUNT; 
	indices[3] = (indices[2]+1)%POINT_COUNT;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}*/

void renderCatmullRomCurve() {
	// draw curve using line segments with GL_LINE_LOOP
    float res[3];
    float deriv[3];

    glBegin(GL_LINE_LOOP);
    for (float gt = 0.0; gt < 1; gt += 0.2) {
        getGlobalCatmullRomPoint(gt, res, deriv);
        glVertex3f(res[0], res[1], res[2]);
    }
    glEnd();
}

int countGroups()
{
	int nGroups;
	for (int i = 0; i < scene.size(); i++)
	{
		nGroups++;
		Group g = scene[i];
		for(int j = 0; j < g.subGroups.size(); j++)
		{
			nGroups++;
		}		
	}
	return nGroups;
}

int groupVertexSize(Group g){
	int res = 0;
	vector<Model> models = g.models;
	for(int i = 0; i < models.size(); i++){
		res += models[i].vertexes.size();
	}
	return res*3;
}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void normalizeCamCoords()
{
	cPosX = radius * cos(beta) * sin(alpha);
	cPosY = radius * sin(beta);
	cPosZ = radius * cos(beta) * cos(alpha);
}

void drawScene(vector<Group>groups) 
{	
	int size = 0;
	for (int i = 0; i < groups.size(); i++) {
		Group group = groups[i];
		glPushMatrix();
		glRotatef(group.rotationAngle, group.rotation.x, group.rotation.y, group.rotation.z);
		glTranslatef(group.translation.x, group.translation.y, group.translation.z);
		if(group.scale.x || group.scale.y || group.scale.z)
			glScalef(group.scale.x, group.scale.y, group.scale.z);
		glColor3f(group.color.x, group.color.y, group.color.z);
		if (group.models.size() > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, buffers[counterBuff++]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			size = groupVertexSize(group);
			glDrawArrays(GL_TRIANGLES, 0, size);
		}
		drawScene(group.subGroups);
		glPopMatrix();
	}
}

void renderScene(void)
{
	counterBuff = 0;

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	//Eixos conforme os desenhados no gerador(yy na vertical, xx na horizontal, zz na diagonal)
	gluLookAt(cPosX, cPosY, cPosZ,
			  0.0, 0.0, 0.0,
			  0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glTranslatef(xx,yy,zz); // moves the object.
	glRotatef(degree,0.0f,1.0f,0.0f); // rotate the object (Vertical Axis)
	drawScene(scene);
	glPopMatrix();
	
	// End of frame
	glutSwapBuffers();
	glFlush();
}

// Write function to process keyboard events
void keyboardAction(unsigned char key, int x, int y)
{

	switch (key)
	{
	//Translações nos eixos xx, yy e zz
	case 'w':
		yy += 10.f;
		break;
	case 's':
		yy -= 10.f;
		break;
	case 'a':
		xx -= 10.f;
		break;
	case 'd':
		xx += 10.f;
		break;
	case '4':
		zz -= 10.f;
		break;
	case '5':
		zz += 10.f;
		break;
	//Rotação no eixo vertical
	case 'q':
		degree -= 10.f;
		break;
	case 'e':
		degree += 10.f;
		break;
	//Diferentes modos de apresentar os polígonos: cor preenchida, linhas com a representação dos triângulos, ou por pontos
	case 'l':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'p':
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	//Fazer zoom in(diminui o raio da camera) e zoom out(aumenta o raio da camera)
	case 'x':
		radius -= 2.0;
		normalizeCamCoords();
		break;
	case 'z':
		radius += 2.0;
		normalizeCamCoords();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy)
{
	//Rotações aumentando e diminuindo os ângulos alpha e beta da camera
	switch (key)
	{
	//Rotações no eixo do xx
	case GLUT_KEY_LEFT:
		alpha -= 0.1;
		normalizeCamCoords();
		break;
	case GLUT_KEY_RIGHT:
		alpha += 0.1;
		normalizeCamCoords();
		break;
	//Rotações no eixo dos yy
	case GLUT_KEY_UP:
		beta += 0.1;
		normalizeCamCoords();
		break;
	case GLUT_KEY_DOWN:
		beta -= 0.1;
		normalizeCamCoords();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void showHelp()
{
	cout << "-------------- HELP GUIDE -----------------" << endl;
	cout << "|                                         |" << endl;
	cout << "| -> Arrows to rotate the camera          |" << endl;
	cout << "| -> x, z to zoom in and zoom out         |" << endl;
	cout << "| -> p, f, l  PolygonModes                |" << endl;
	cout << "|                                         |" << endl;
	cout << "-------------------------------------------" << endl;
}

void fillBuffers(vector<Group> groups)
{
	for (int i = 0; i < groups.size(); i++) {
		Group g = groups[i];
		if (g.models.size() > 0) {
			vector<Vertex> points;
			for(int w = 0; w < g.models.size(); w++){
				vector<Vertex> pointsPrimitive = g.models[w].vertexes;
				points.insert(points.end(),pointsPrimitive.begin(), pointsPrimitive.end());			
			}
			float * vertices;
			vertices = (float*)malloc(sizeof(float)*points.size() * 3);
			for (int j = 0; j < points.size(); j++) {
				vertices[3 * j] = points[j].x;
				vertices[3 * j + 1] = points[j].y;
				vertices[3 * j + 2] = points[j].z;
			}
			glBindBuffer(GL_ARRAY_BUFFER, buffers[nBuffer++]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 3, vertices, GL_STATIC_DRAW);
			free(vertices);
		}
		fillBuffers(g.subGroups);
	}
}

int main(int argc, char **argv)
{
	scene = ParseXMLFile(argv[1]);

	alpha = 0.0;
	radius = 100.0;
	beta = 0.0;
	normalizeCamCoords();

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Computação Gráfica");

	// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(keyboardAction);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	nBuffer = 0;
	counterBuff = 0;
	int groupsNumber = countGroups();
	buffers = (GLuint*)malloc(sizeof(GLuint)*groupsNumber);
	glGenBuffers(groupsNumber, buffers);

	fillBuffers(scene);
	glEnableClientState(GL_VERTEX_ARRAY);

	showHelp();

	// enter GLUT's main radiuscle
	glutMainLoop();

	return 1;
}
