#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#include "base.h"
#include "interactive.h"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;


GLuint LoadBMP(const char* fileName) {

	glColor3f(1.0f, 1.0f, 1.0f);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
}

void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void joint(float boneLength,float boneWidth) {
	GLuint robotTex = LoadBMP("texture/stone.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	cylinder(boneLength, boneWidth, boneWidth, 1, 1, 1);
	glPopMatrix();
	DeleteObject(hBMP);
	glDeleteTextures(1, &robotTex);
}

void finger(float length) {
	GLuint robotTex = LoadBMP("texture/metal.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glPushMatrix();
	glScalef(0.06, length, 0.06);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
	DeleteObject(hBMP);
	glDeleteTextures(1, &robotTex);
}

void upperFingers(float length) {

	glPushMatrix();
	glTranslatef(0.15, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.45, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, 0, 0);
	finger(length);
	glPopMatrix();
}

void lowerFingers() {

	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	upperFingers(0.2);
	glPopMatrix();
}

void fingerJoint() {
	
	/*glPushMatrix();
	glTranslatef(-0.05, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(0.1, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.25, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

}

void thumb(float length) {

	glPushMatrix();
	//rotate to put thumb outside
		glTranslatef(-0.18, 0.8, 0);
		glRotatef(-50, 0, 0, 1);
		glTranslatef(0, -0.35, 0);
				glPushMatrix();
				glTranslatef(-0.05, 0.19, 0);
				joint(0.1, 0.06);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0, 0.16, 0);
				glRotatef(30, 1, 0, 0);
				glTranslatef(0, -0.16, 0);
				finger(0.16);
				glPopMatrix();
		//lower thumb
		glPushMatrix();
		glTranslatef(0, 0.38, 0);
			glPushMatrix();
			glTranslatef(-0.05, 0.19, 0);
			joint(0.1, 0.06);
			glPopMatrix();

			finger(0.16);
		glPopMatrix();

	glPopMatrix();

}

void allFingers() {
	
	thumb(0.2);

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.15, 0);
	upperFingers(0.15);
	glPopMatrix();

	//middle
	
	fingerJoint();
	//with palm
	glPushMatrix();
	glTranslatef(0, 0.45, 0);
	fingerJoint();
	glPopMatrix();

	lowerFingers();
}

void palm() {
	
	allFingers();
	glPushMatrix();	
	
	glTranslatef(0.35,1.0,0);
	glScalef(0.35, 0.3, 0.1);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
	
}

void leg() {
	GLuint shoeTex = LoadBMP("texture/metal.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, shoeTex);
	
	glPushMatrix();
	glTranslatef(0.4, 1, -0.3);
	glRotatef(270, 1, 0, 0);
	cylinder(0.6, 0.25, 0.37, 1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.4, 2.2, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.6, 0.25, 0.37, 1, 1, 1);
	glPopMatrix();
	
	//side leg
	glPushMatrix();
	glTranslatef(-0.4, 1, -0.3);
	glRotatef(270, 1, 0, 0);

	cylinder(0.6, 0.25, 0.37, 1, 1, 1);
	glPopMatrix();
	//side leg
	glPushMatrix();
	glTranslatef(-0.4, 2.2, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.6, 0.25, 0.37, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.6, -0.3);
	glScalef(0.4, 0.6, 0.4);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

	glPushMatrix();
	//glScalef(0.7, 0.5, 0.7);
	glTranslatef(0, 1.1, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.3,0.35,0.35,1,1,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.5, -0.3);
	glScalef(0.40, 0.4, 0.40);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

	/*glPushMatrix();
	glTranslatef(0, 0.5, -0.3);
	glScalef(0.35, 0.5, 0.4);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();*/


	glPushMatrix();
	glScalef(0.450, 0.5, 0.80);
	shoe();
	glPopMatrix();

	DeleteObject(hBMP);
	glDeleteTextures(1, &shoeTex);
}