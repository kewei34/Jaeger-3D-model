#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#include "base.h"
#include "hand.h"
#include "interactive.h"
#include "bodyPart.h"

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

GLuint robotTex, jointTex, shoeTex;

void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void joint(float boneLength,float boneWidth) {
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	cylinder(boneLength, boneWidth, boneWidth, 0.804, 0.522, 0.247);
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

void palm() {

	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glTranslatef(0.35, 1.0, 0);
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

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
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

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glPushMatrix();
	glTranslatef(1.0, 0.05, 0.55);
	glTranslatef(0, 4.2, 0);
	glRotatef(15, 0, 0, 1);
	glTranslatef(-1.0, -0.05, -0.55);
	glTranslatef(0, -4.0, 0);
	//up
	glPushMatrix();
	glTranslatef(0, 4.0, 0);
	glScalef(0.8, 0.05, 0.55);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();
	//left
	glPushMatrix();
	glTranslatef(0, 3.7, 0.5);
	glScalef(0.8, 0.3, 0.05);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslatef(0, 3.7, -0.5);
	glScalef(0.8, 0.3, 0.05);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex);
	glPushMatrix();
	glTranslatef(0.2, 3.7, 0);
	sphere(0.25);
	glPopMatrix();

	glPopMatrix();
}

void shoejointfront() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);

	glPushMatrix();
	glTranslatef(-0.5, 0, 0.1);
	joint(1, 0.15);
	glPopMatrix();
}
void rightsidelegpad() {
	//right side leg design
	glPushMatrix();
	glTranslatef(0.35, 3.1, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.9, 0.16, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.35, 1.3, -0.3);
	glRotatef(270, 1, 0, 0);
	cylinder(0.9, 0.1, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();
}

void leftsidelegpad() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	//left side leg design
	glPushMatrix();
	glTranslatef(-0.35, 3.1, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.9, 0.16, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.35, 1.3, -0.3);
	glRotatef(270, 1, 0, 0);
	cylinder(0.9, 0.1, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();


}
void lowerfirstpartleg() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	//lower first part leg
	glPushMatrix();
	glTranslatef(0, 2.2, -0.3);
	glScalef(0.35, 0.9, 0.4);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowersecondpartleg() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	//lower second part leg
	glPushMatrix();
	glTranslatef(0, 0.6, -0.3);
	glScalef(0.35, 0.55, 0.40);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowerleg() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	rightsidelegpad();
	lowerfirstpartleg();
	leftsidelegpad();
	//joint between lowerfirstpartleg and lowersecondpartleg
	glPushMatrix();
	glTranslatef(-0.35, 1.25, -0.35);
	joint(0.7, 0.2);
	glPopMatrix();
	//glPushMatrix();
	//glTranslatef(0, 1.1, -0.3);
	//glRotatef(90, 1, 0, 0);
	//cylinder(0.3, 0.35, 0.35, 0.804, 0.522, 0.247);
	//glPopMatrix();
	lowersecondpartleg();
	//shoe part
	shoejointfront();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);

	glPushMatrix();
	glScalef(0.450, 0.5, 0.80);
	shoe();
	glPopMatrix();
}

void legjointmiddle() {
	glPushMatrix();
	glTranslatef(-0.45, 3.2, -0.35);
	joint(0.9, 0.2);
	glPopMatrix();
}

void upperlegfirstpart() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glPushMatrix();
	glScalef(1.4,1.4,1.0);
	glTranslatef(0,3.58, -0.25);
	glRotatef(90, 1, 0, 0);
	cylinder(1.3, 0.45, 0.45, 0.502, 0.000, 0.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 4.1, -0.25);
	glScalef(0.30, 0.9, 0.45);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void upperleg() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	upperlegfirstpart();
	//ankle
  
	//add ankle code here

	legjointmiddle();

}

void leg() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	
	upperleg();
	lowerleg();	
}



void leftmuscle() {
	//left muscle
	glPushMatrix();
	glTranslatef(-0.01, 2.34, 0.85);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-120,1, 0, 0);
	glRotatef(-40,0,0,1);
	glScalef(0.4, 0.8, 0.15);
	shoe();
	glPopMatrix();

}

void rightmuscle() {
	//right muscle
	glPushMatrix();
	glTranslatef(0.55, 2.3, 0.85);
	glRotatef(-270, 0, 1, 0);
	glRotatef(-475, 1, 0, 0);
	glRotatef(-320, 0, 0, 1);
	glScalef(0.4, 0.8, 0.15);
	shoe();
	glPopMatrix();

}

void bodymuscle() {
	//top muscle
	glPushMatrix();
	glTranslatef(0, 0, 0.2);
	leftmuscle();
	rightmuscle();
	glPopMatrix();
	//middle muscle
	glPushMatrix();
	glTranslatef(0, -0.45,0.1);
	leftmuscle();
	rightmuscle();
	glPopMatrix();
	//bottom muscle
	glPushMatrix();
	glTranslatef(0, -0.9, 0);
	leftmuscle();
	rightmuscle();
	glPopMatrix();
}


void body() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex);
	glPushMatrix();
	glTranslatef(0.28, 4.0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 0.8, 1);
	cylinder(3.0, 1.7, 1.2, 0.627, 0.322, 0.176);
	glPopMatrix();
}

void lowerBody() {
	glPushMatrix();
	glTranslatef(0.28, 0.5, 0);
	glScalef(1.5, 0.75, 1);
	irregularCuboid(0.627, 0.322, 0.176);
	glPopMatrix();
}

void wholeBody() {
	//lowerBody();
	body();
	bodymuscle();
}

void head() {
	glPushMatrix();
	glTranslatef(0.28,5.5,0);
	glRotatef(10, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(1,0.8,0.8);
	sphere(1.2);
	glPopMatrix();
	//left anthenna
	glPushMatrix();
	glTranslatef(-0.65, 6.2, -0.4);
	glRotatef(-30, 1, 0, 0);
	glScalef(0.1, 0.8, 0.1);
	shoe();
	glPopMatrix();
	//right anthenna
	glPushMatrix();
	glTranslatef(1.2, 6.2, -0.4);
	glRotatef(-30, 1, 0, 0);
	glScalef(0.1, 0.8, 0.1);
	shoe();
	glPopMatrix();

	//ear
	glPushMatrix();
	{
		glTranslatef(-0.72, 5.5, 0);
		joint(2, 0.3);
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-0.72, 5.5, 0);
		joint(2, 0.2);
	}
	glPopMatrix();
	//eye
	glPushMatrix();
	glTranslatef(0.3, 5.5, 0.742);
	glScalef(0.50, 0.3, 0.45);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

}

void robot() {
	head();
	wholeBody();

	//hand
	glPushMatrix();
	glTranslatef(-2, 0, 0.1);
	leftHand();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.14, 0, 0.1);
	rightHand();
	glPopMatrix();

	//Lleg
	glPushMatrix();
	glTranslatef(-0.72, -4, 0);
		glPushMatrix();
		glTranslatef(0, 5, 0);
		glRotatef(-30, 1, 0, 0);
		glTranslatef(0, -5, 0);
		leg();
		glPopMatrix();
	glPopMatrix();
	//Rleg
	glPushMatrix();
	glTranslatef(1.28, -4, 0);
	leg();
	glPopMatrix();
}

void loadTex() {
	robotTex = LoadBMP("texture/metal.bmp");
	jointTex = LoadBMP("texture/joint.bmp");
	shoeTex = LoadBMP("texture/metal.bmp");

}

void delTex() {
	DeleteObject(hBMP);
	glDeleteTextures(1, &robotTex);
	glDeleteTextures(1, &jointTex);
	glDeleteTextures(1, &shoeTex);
}
