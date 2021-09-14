#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

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

GLuint robotTex,jointTex;

void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void joint(float boneLength,float boneWidth) {
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	cylinder(boneLength, boneWidth, boneWidth, 1.000, 0.871, 0.678);
	glPopMatrix();
}

void finger(float length) {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glPushMatrix();
	glScalef(0.06, length, 0.06);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void upperFingers(float length) {

	glPushMatrix();
	glTranslatef(0.13, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.28, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.43, 0, 0);
	finger(length);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.58, 0, 0);
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

	glPushMatrix();
	glTranslatef(0.08, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.23, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.38, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.53, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

}

void thumb(float length) {

	glPushMatrix();
	//rotate to put thumb outside
		glTranslatef(-0.1, 0.7, -0.1);
		glRotatef(-60, 0, 1, 1);
		glTranslatef(-0.12, -0.35, 0);
				glPushMatrix();
				glTranslatef(-0.05, 0.19, 0);
				joint(0.1, 0.06);
				glPopMatrix();
				//upper thumb
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
	
	glPushMatrix();	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glTranslatef(0.35,1.0,0);
	glScalef(0.35, 0.3, 0.15);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void foreArm() {

	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glTranslatef(0.1, 1.6, 0);
	glScalef(0.15, 0.3, 0.3);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 1.623, 0);
	glScalef(0.1, 0.32, 0.35);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.55, 1.6, 0);
	glScalef(0.18, 0.3, 0.3);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void upForeArm() {
	glPushMatrix();
	glTranslatef(0, 0.7, 0);
	foreArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.32, 1.95, 0);
	glScalef(0.35, 0.08, 0.2);
	cuboid(0.627, 0.322, 0.176);
	glPopMatrix();
}

void upperArm() {

	glPushMatrix();
	glTranslatef(0.34, 3.15, 0);
		glPushMatrix();
		glTranslatef(0, -0.4, 0);
		glRotatef(-90, 1, 0, 0);
		cylinder(0.8, 0.4, 0.4, 0.545, 0.271, 0.075);
		glPopMatrix();
	glScalef(0.3, 0.4, 0.3);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 2.7, 0);
	joint(0.6, 0.2);
	glPopMatrix();
}

void shoulder() {

}

void hand() {

	upperArm();
	upForeArm();
	foreArm();
	palm();
	allFingers();

}

void loadTex(){
	robotTex = LoadBMP("texture/metal.bmp");
	jointTex = LoadBMP("texture/joint.bmp");

}

void delTex() {
	DeleteObject(hBMP);
	glDeleteTextures(1, &robotTex);
	glDeleteTextures(1, &jointTex);
}
