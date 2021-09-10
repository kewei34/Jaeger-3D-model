#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

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

void shpere(float radius) {

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

