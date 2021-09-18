#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "GLUT32.lib")

#define PI 3.14159265359

void disk(float,float);

float normalize(float *v) {
	float length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

	for (int i = 0; i < 3; i++) {
		v[i] = v[i] / length;
	}

	return v[0];
}

float *cross_product(float *a, float *b) {
	float result[] = { a[1] * b[2] - a[2] * b[1],
		-(a[0] * b[2] - a[2] * b[0]),a[0] * b[1] - a[1] * b[0] };

	normalize(result);
	return result;
}

float *calculate_normal(float *a, float *b, float *c) {
	float x[] = { b[0] - a[0],b[1] - a[1],b[2] - a[2] };
	float y[] = { c[0] - a[0],c[1] - a[1],c[2] - a[2] };

	float* result = cross_product(x, y);

	return result;	
}

void circle(float x, float y, float radiusX, float radiusY, float color1, float color2, float color3)
{
	glShadeModel(GL_FLAT);
	glColor3f(color1, color2, color3);

	glBegin(GL_TRIANGLE_FAN);
	for (int angle = 0; angle < 360; angle++) {
		float x2 = radiusX * cos(angle) + x;
		float y2 = radiusY * sin(angle) + y;

		glVertex2f(x2, y2);
	}
	glEnd();

}

void circleLine(float x, float y, float radiusX, float radiusY, float color1, float color2, float color3)
{
	glShadeModel(GL_FLAT);
	glColor3f(color1, color2, color3);

	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (int angle = 0; angle < 360; angle++) {
		float x2 = radiusX * cos(angle) + x;
		float y2 = radiusY * sin(angle) + y;

		glVertex2f(x2, y2);
	}
	glEnd();

}

void cuboid(float r, float g, float b) {

	float f1[] = { -1.0, 1.0, 1.0 };
	float f2[] = { -1.0, -1.0, 1.0 };
	float f3[] = { 1.0, -1.0, 1.0 };
	float f4[] = { 1.0, 1.0, 1.0 };
	float b1[] = { -1.0, 1.0, -1.0 };
	float b2[] = { -1.0, -1.0, -1.0 };
	float b3[] = { 1.0, -1.0, -1.0 };
	float b4[] = { 1.0, 1.0, -1.0};

	glShadeModel(GL_FLAT);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	//front
	glNormal3fv(calculate_normal(f1,f2,f3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	//back
	glNormal3fv(calculate_normal(b1, b2, b3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//up
	glNormal3fv(calculate_normal(b1, f1, f4));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	//down
	glNormal3fv(calculate_normal(b2, f2, f3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	//left
	glNormal3fv(calculate_normal(b1, b2, f2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	//right
	glNormal3fv(calculate_normal(b4, b3, f3));
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

void cylinder(float height, float topR, float bottomR, float r, float g, float b) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(r, g, b);
	gluQuadricTexture(cylinder, true);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricDrawStyle(cylinder, GL_TRIANGLE_FAN);
	gluCylinder(cylinder, topR, bottomR, height, 20, 20);
	gluDeleteQuadric(cylinder);

	disk(0, topR);
	glPushMatrix();
	glTranslatef(0,0 , height);
	disk(0, bottomR);
	glPopMatrix();
}

void unfilledCylinder(float height, float topR, float bottomR, float r, float g, float b) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(r, g, b);
	gluQuadricTexture(cylinder, true);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricDrawStyle(cylinder, GL_TRIANGLE_FAN);
	gluCylinder(cylinder, topR, bottomR, height, 20, 20);
	gluDeleteQuadric(cylinder);
}

void sphere(float radius) {

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricTexture(sphere, true);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glColor3f(0.824, 0.412, 0.118);
	gluQuadricNormals(sphere,GL_TRUE);
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
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-s, 0.0, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0, s);
	glEnd();

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0, h, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(s, 0.0, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0, -s);
	glEnd();

	glBegin(GL_TRIANGLES);
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

void disk(float innerR,float outerR) {
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	gluQuadricTexture(disk, true);
	gluQuadricDrawStyle(disk, GL_TRIANGLE_FAN);
	gluDisk(disk, innerR, outerR, 50, 50);
	gluDeleteQuadric(disk);
}

void shoe() {	
	float f1[] = { -1.0f, 0.0f, 1.0f };
	float f2[] = { -1.1f, -0.5f, 1.0f };
	float f3[] = { -1.0f, -1.0f, 1.0f };
	float f4[] = { 1.0f, -1.0f, 1.0f };
	float f5[] = { 1.1f, -0.5f, 1.0f };
	float f6[] = { 1.0f, 0.0f, 1.0f };
	float b1[] = { -1.2f, 0.5f, -1.0f };
	float b2[] = { -1.28f, 0.2f, -1.0f };
	float b3[] = { -1.4f, -1.0f, -1.0f };
	float b4[] = { 1.4f, -1.0f, -1.0f };
	float b5[] = { 1.28f, 0.2f, -1.0f };
	float b6[] = { 1.2f, 0.5f, -1.0f };

	glColor3f(0.502, 0.000, 0.0);
	glBegin(GL_POLYGON);
	//front
	glNormal3fv(calculate_normal(f1, f2, f3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);  //t1
	glVertex3f(-1.1f, -0.5f, 1.0f);   //t2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);  //t3
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);    //t4
	glVertex3f(1.1f, -0.5f, 1.0f);    //5
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);     //t6
	glEnd();
	glBegin(GL_POLYGON);
	//back
	glNormal3fv(calculate_normal(b1, b2, b3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.2f, 0.5f, -1.0f);  //b1
	glVertex3f(-1.28f, 0.2f, -1.0f);  //b2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.4f, -1.0f, -1.0f); //b3
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.4f, -1.0f, -1.0f);   //b4
	glVertex3f(1.28f, 0.2f, -1.0f);   //b5
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.2f, 0.5f, -1.0f);  //b6
	glEnd();
	glBegin(GL_POLYGON);
	////up
	glNormal3fv(calculate_normal(f1, f6, b6));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.2f, 0.5f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.2f, 0.5f, -1.0f);
	glEnd();
	glBegin(GL_POLYGON);
	//down
	glNormal3fv(calculate_normal(f3, f4, b4));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.4f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.4f, -1.0f, -1.0f);
	glEnd();
	glBegin(GL_POLYGON);
	//left
	glNormal3fv(calculate_normal(f1, f2, f3));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);  //t1
	glVertex3f(-1.1f, -0.5f, 1.0f);   //t2
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);  //t3
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.4f, -1.0f, -1.0f); //b3	
	glVertex3f(-1.28f, 0.2f, -1.0f);  //b2
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.1f, 0.5f, -1.0f);  //b1	
	glEnd();
	glBegin(GL_POLYGON);
	//right
	glNormal3fv(calculate_normal(f4, f5, f6));

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);    //t4
	glVertex3f(1.1f, -0.5f, 1.0f);    //5
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);     //t6
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.1f, 0.5f, -1.0f);  //b6
	glVertex3f(1.28f, 0.2f, -1.0f);   //b5
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.4f, -1.0f, -1.0f);   //b4
	glEnd();
}

void irregularCuboid(float r,float g,float b) {
	glShadeModel(GL_FLAT);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.8f, 1.0f, 0.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.8f, 1.0f, -0.8f);
	//up
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.8f, 1.0f, 0.8f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.8f, 1.0f, -0.8f);
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
	glVertex3f(-0.8f, 1.0f, -0.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.8f, 1.0f, 0.8f);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.8f, 1.0f, -0.8f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.8f, 1.0f, 0.8f);
	glEnd();

}