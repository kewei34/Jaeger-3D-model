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

void thumb(float length) {

	glPushMatrix();
	//rotate to put thumb outside
		glTranslatef(-0.1, 0.7, 0);
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

void lThumb() {
	glPushMatrix();
	//rotate to put thumb outside
	glTranslatef(-0.1, 0.7, 0);
	glRotatef(60, 0, 1, 1);
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
	
	glPushMatrix();
	glTranslatef(1.0, 0.05, 0.55);
	glTranslatef(0, 4.2, 0);
	glRotatef(15, 0, 0, 1);
	glTranslatef(-1.0, -0.05, -0.55);
	glTranslatef(0, -4.0, 0);
	//up
	glPushMatrix();
	glTranslatef(0,4.0, 0);
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
	glPushMatrix();
	glTranslatef(-0.5, 0, 0.1);
	joint(1, 0.15);
	glPopMatrix();
}
void rightsidelegpad() {
	//right side leg design
	glPushMatrix();
	glTranslatef(0.4, 2.2, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.6, 0.16, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 1, -0.3);
	glRotatef(270, 1, 0, 0);
	cylinder(0.6, 0.1, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();
}

void leftsidelegpad() {
	//left side leg design
	glPushMatrix();
	glTranslatef(-0.4, 1, -0.3);
	glRotatef(270, 1, 0, 0);
	cylinder(0.6, 0.1, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 2.2, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.6, 0.16, 0.37, 0.502, 0.000, 0.0);
	glPopMatrix();
}
void lowerfirstpartleg() {
	//lower first part leg
	glPushMatrix();
	glTranslatef(0, 1.6, -0.3);
	glScalef(0.4, 0.6, 0.4);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowersecondpartleg() {
	//lower second part leg
	glPushMatrix();
	glTranslatef(0, 0.5, -0.3);
	glScalef(0.40, 0.4, 0.40);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowerleg() {
	rightsidelegpad();
	lowerfirstpartleg();
	leftsidelegpad();
	//joint between lowerfirstpartleg and lowersecondpartleg
	glPushMatrix();
	glTranslatef(0, 1.1, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(0.3, 0.35, 0.35, 0.804, 0.522, 0.247);
	glPopMatrix();
	lowersecondpartleg();
	//shoe part
	shoejointfront();
	glPushMatrix();
	glScalef(0.450, 0.5, 0.80);
	shoe();
	glPopMatrix();
}

void legjointbehind() {
	glPushMatrix();
	glTranslatef(-0.5, 2.3, -0.7);
	joint(1, 0.2);
	glPopMatrix();
}

void legjointfront() {
	glPushMatrix();
	glTranslatef(-0.45, 2.3, -0.35);
	joint(0.9, 0.2);
	glPopMatrix();
}

void upperlegfirstpart() {
	glPushMatrix();
	glScalef(1.6,1.4,1.0);
	glTranslatef(0, 2.7, -0.25);
	glRotatef(90, 1, 0, 0);
	cylinder(1, 0.45, 0.45, 0.502, 0.000, 0.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 3.1, -0.25);
	glScalef(0.45, 0.7, 0.45);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void upperleg() {
	upperlegfirstpart();
	//ankle
  
	//add ankle code here

	//legjointbehind();
	legjointfront();
	//joint between lowerfirstpartleg and uppersecondpartleg
	//glPushMatrix();
	//glTranslatef(0, 2.4, -0.3);
	//glRotatef(90, 1, 0, 0);
	//cylinder(0.3, 0.35, 0.35, 0.502, 0.000, 0.0);
	//glPopMatrix();
}

void leg() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, shoeTex);
	
	upperleg();
	lowerleg();	
}

void rightHand() {
	shoulder();
	upperArm();
	glTranslatef(0.28, 0, 0);
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glTranslatef(-0.28, 0, 0);
	upForeArm();
	foreArm();
	palm();
	thumb(0.2);
	allFingers();
	glPopMatrix();
}

void leftHand() {
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	glRotatef(180, 0, 1, 0);
	shoulder();
	glPopMatrix();
	glPushMatrix();
	glRotatef(-30, 0, 1, 0);
	glTranslatef(-0.28, 0, 0);
	upperArm();
	upForeArm();
	foreArm();
	palm();
	allFingers();
	glPushMatrix();
	glTranslatef(1.0, 0.1, -0.2);
	lThumb();
	glPopMatrix();
	glPopMatrix();

}


void body() {

	glPushMatrix();
	glTranslatef(0.28, 4.0, 0);
	glRotatef(90, 1, 0, 0);
	cylinder(3.0, 1.5, 1.0, 0.627, 0.322, 0.176);
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
