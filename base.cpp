#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define PI 3.14159265359

void cuboid(float r, float g, float b) {

	glShadeModel(GL_FLAT);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//up
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//down
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
}

void unfilledPyramid() {
	//front
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1, 0, 1);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(1, 1, 0);
	glVertex3f(0, 1.0f, 0);
	glEnd();

	//back
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(1, 1, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0, 1.0f, 0);
	glEnd();

	//left
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1, 1, 0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(0, 1.0f, 0);
	glEnd();

	//right
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(1, 1, 0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(0, 1.0f, 0);
	glEnd();

	//down
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1, 1, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd();
}

void cylinder(float height, float topR, float bottomR, float r, float g, float b) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(r, g, b);
	gluQuadricTexture(cylinder, true);
	gluQuadricDrawStyle(cylinder, GL_TRIANGLE_FAN);
	gluCylinder(cylinder, topR, bottomR, height, 10, 10);
	gluDeleteQuadric(cylinder);
}

void sphere(float radius) {

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, true);
	gluQuadricDrawStyle(sphere, GL_TRIANGLE_FAN);
	gluSphere(sphere, radius, 30, 10);
	gluDeleteQuadric(sphere);
}

void pyramid(float s,float h) {

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-s, 0.0, -s);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-s, 0.0, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0, s);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(s, 0.0, -s);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-s, 0.0, -s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-s, 0.0, s);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-s, 0.0, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0, s);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(s, 0.0, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0, -s);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(s, 0.0, -s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-s, 0.0, -s);
	glEnd();
}

void arc(float x, float y, float z, float radiusX, float radiusY, float startAngle, float endAngle, float width, float color1, float color2, float color3) {

	glShadeModel(GL_FLAT);
	glColor3f(color1, color2, color3);

	float startR = startAngle * PI / 180.0f;
	float endR = endAngle * PI / 180.0f;

	glLineWidth(width);
	glBegin(GL_LINE_STRIP);

	for (float angle = startR; angle <= endR; angle += (PI / 1000)) {
		float x2 = radiusX * cos(angle) + x;
		float y2 = radiusY * sin(angle) + y;

		glVertex3f(x2, y2, z);
	}
	glEnd();
}

void spikeHammer() {
	glutSolidIcosahedron();
}

void disk() {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricTexture(disk, true);
	gluQuadricDrawStyle(disk, GL_TRIANGLE_FAN);
	gluDisk(disk, 1, 2, 100, 50);
	gluDeleteQuadric(disk);
}