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
#include "leg.h"
#include "interactive.h"
#include "bodyPart.h"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

int robotTexNum = 1;
int jointTexNum = 1;

GLuint robotTex[10];
GLuint jointTex[10];
GLuint skyT[2];
GLuint landT[2];
GLuint goldTex, ebTex,skyTex,skyTex2,landTex2,landTex;

int rt = 0;

float headAngle = 0, headRtX = 0, headRtY = 0;
int skyNum = 0, landNum = 0;

void goldRT() {
	rt++;
}

void restoreHead() {
	headAngle = 0;
}

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

void changeBg() {
	if (skyNum == 0) {
		skyNum = 1;
		landNum = 1;
	}
	else if (skyNum == 1) {
		skyNum = 0;
		landNum = 0;
	}
}

void bg() {

	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, skyT[skyNum]);
	if (skyNum == 0) {
		glColor3f(0.529, 0.808, 0.980);
	}
	else if (skyNum == 1) {
		glColor3f(0.098, 0.098, 0.439);
	}
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();
}

void land() {

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glTranslatef(0, -1.35,0);
	glRotatef(1, 1, 0, 0);
	glTranslatef(0, -2, 0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, landT[landNum]);
	if (skyNum == 0) {
		cuboid(0.196, 0.804, 0.196);
	}
	else if (skyNum == 1) {
	cuboid(0.000, 0.392, 0.000);
	}
	glPopMatrix();
}


void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void joint(float boneLength,float boneWidth) {
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	cylinder(boneLength, boneWidth, boneWidth, 0.804, 0.522, 0.247);
	glPopMatrix();
}

void finger(float length) {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	glTranslatef(0.35, 1.0, 0);
	glScalef(0.35, 0.3, 0.15);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void foreArm() {

	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, goldTex);
	glPushMatrix();
	glTranslatef(0.2, 3.7, 0);
	sphere(0.25);
	glPopMatrix();

	glPopMatrix();
}

void shoejointfront() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);

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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	//lower first part leg
	glPushMatrix();
	glTranslatef(0, 2.2, -0.3);
	glScalef(0.35, 0.9, 0.4);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowersecondpartleg() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	//lower second part leg
	glPushMatrix();
	glTranslatef(0, 0.6, -0.3);
	glScalef(0.35, 0.55, 0.40);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void lowerleg() {

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);

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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
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
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	upperlegfirstpart();
	//ankle
  
	//add ankle code here

	legjointmiddle();

}

void swordhandle() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	//swordhandle
	glPushMatrix();
	glTranslatef(-4, 1.85, -0.3);
	glScalef(0.15, 0.1, 0.05);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

	//swordhandledesign
	glPushMatrix();
	glScalef(1, 1, 0.4);
	glTranslatef(-4, 1.95, -0.75);
	glRotatef(90, 1, 0, 0);
	cylinder(0.6, 0.25, 0.25, 0.804, 0.522, 0.247);
	glPopMatrix();
	//sworduppersupport 
	glPushMatrix();
	glTranslatef(-4, 1.5, -0.3);
	glScalef(0.6, 0.1, 0.1);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
	//swordslowersupport
	glPushMatrix();
	glTranslatef(-4, 1.3, -0.3);
	glScalef(0.3, 0.1, 0.1);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void swordbody() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, goldTex);
	//sword body
	glPushMatrix();
	glTranslatef(-4, 0.6, -0.3);
	glScalef(0.2, 1.2, 0.05);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
	//swordtip
	glPushMatrix();
	glTranslatef(-4, -0.6, -0.3);
	glRotatef(180, 1, 0, 0);
	glScalef(0.2, 0.9, 0.05);
	pyramid(1, 1);
	glPopMatrix();
}


void leftmuscle() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	//left muscle
	glPushMatrix();
	glTranslatef(-0.01, 2.34, 0.85);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-120,1, 0, 0);
	glRotatef(-40,0,0,1);
	glScalef(0.4, 0.8, 0.15);
	glColor3f(0.502, 0.000, 0.0);
	shoe();
	glPopMatrix();

}

void rightmuscle() {
	//right muscle
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	glPushMatrix();
	glTranslatef(0.55, 2.3, 0.85);
	glRotatef(-270, 0, 1, 0);
	glRotatef(-475, 1, 0, 0);
	glRotatef(-320, 0, 0, 1);
	glScalef(0.4, 0.8, 0.15);
	shoe();
	glPopMatrix();

}
void upperchest() {
	//upper left chest
	glPushMatrix();
	glTranslatef(-0.58, 4, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(85, 0, 1, 0);
	//glRotatef(40, 1, 0, 0);
	glScalef(0.1, 1.3, 0.85);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();

	//upper right chest
	glPushMatrix();
	glTranslatef(1.15, 4, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(95, 0, 1, 0);
	//glRotatef(40, 1, 0, 0);
	glScalef(0.1, 1.3, 0.85);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();
}

void chest() {
	//left chest
	glPushMatrix();
	glTranslatef(-0.5, 3.35, 1.25);
	glRotatef(90, 0, 1, 0);
	glRotatef(110, 1, 0, 0);
	glScalef(0.1, 0.6, 0.4);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();
	//right chest
	glPushMatrix();
	glTranslatef(1, 3.3, 1.25);
	glRotatef(270, 0, 1, 0);
	glRotatef(465, 1, 0, 0);
	glScalef(0.1, 0.6, 0.4);
	cuboid(0.502, 0.000, 0.0);
	glPopMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	glPushMatrix();
	glTranslatef(0.28, 3.1, 1.3);
	cylinder(0.1, 0.4,0.4,1,1,1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, ebTex);
	glRotatef(rt, 0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	sphere(0.25);
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

void bone() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	//bone
	glPushMatrix();
	glTranslatef(0.2, 3.7, -1.3);
	glRotatef(354, 1, 0, 0);
	glScalef(0.4, 0.1, 0.1);
	cuboid(0.804, 0.522, 0.247);
	glPopMatrix();
}

void backbone() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	//backbone
	glPushMatrix();
	glTranslatef(0.2, 2.65, -1.15);
	glRotatef(354,1,0,0);
	glScalef(0.1,1.185,0.1);
	cuboid(0.804, 0.522, 0.247);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0, 0.08);
	bone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.4, 0.15);
	bone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.2);
	bone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -1.2, 0.25);
	bone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -1.6, 0.3);
	bone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -2.0, 0.35);
	bone();
	glPopMatrix();

}

void body() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	glPushMatrix();
	glTranslatef(0.28, 4.0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 0.8, 1);
	cylinder(3.0, 1.7, 1.2, 0.627, 0.322, 0.176);
	glPopMatrix();
	upperchest();
	chest();
	backbone();
}

void lowerBody() {
	glPushMatrix();
	glTranslatef(0.28, 0.5, 0);
	glScalef(1.5, 0.75, 1);
	irregularCuboid(0.627, 0.322, 0.176);
	glPopMatrix();
}

void wholeBody() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	body();
	bodymuscle();
	glPushMatrix();
	glTranslatef(4,4.8,-1.3);
	glRotatef(350,1,0,0);
	glRotatef(30, 0, 0, 1);

	sword();
	glPopMatrix();
	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	glScalef(1.3,0.6,1.1);
	glTranslatef(0.20, 2.0, 0);
	sphere(1);
	glPopMatrix();
}

void head() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, robotTex[robotTexNum]);
	glPushMatrix();
	glTranslatef(0.28,5.0,0);
	glRotatef(10, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glScalef(1,0.8,0.8);
	sphere(1.2);
	glPopMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, goldTex);
	//left anthenna
	glPushMatrix();
	glTranslatef(-0.65, 5.7, -0.4);
	glRotatef(-30, 1, 0, 0);
	glScalef(0.1, 0.8, 0.1);
	glColor3f(0.502, 0.000, 0.0);
	shoe();
	glPopMatrix();
	//right anthenna
	glPushMatrix();
	glTranslatef(1.2, 5.7, -0.4);
	glRotatef(-30, 1, 0, 0);
	glScalef(0.1, 0.8, 0.1);
	glColor3f(0.502, 0.000, 0.0);
	shoe();
	glPopMatrix();

	//ear
	glPushMatrix();
	{
		glTranslatef(-0.72, 5.0, 0);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
			glPushMatrix();
			glRotatef(90, 0, 0, 1);
			glRotatef(90, 1, 0, 0);
			unfilledCylinder(2, 0.3, 0.3, 0.502, 0.000, 0.0);
			glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	{
		
		glTranslatef(-0.72, 5.0, 0);
		joint(2, 0.2);
		glColor3f(0.502, 0.000, 0.0);
	}
	glPopMatrix();
	//eye
	glPushMatrix();
	glTranslatef(0.3, 5.0, 0.742);
		glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, goldTex);
		glTranslatef(-0.2,0, 0.46);
		circle(0, 0, 0.1, 0.15, 1, 1, 1);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
		circleLine(0, 0, 0.05, 0.05, 0, 0, 0);
		glPopMatrix();
		glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, goldTex);
		glTranslatef(0.2, 0, 0.46);
		circle(0, 0, 0.1, 0.15, 1, 1, 1);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
		circleLine(0, 0, 0.05, 0.05, 0, 0, 0);
		
		glPopMatrix();
	glScalef(0.50, 0.3, 0.45);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();

}


void spikehammertop() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, goldTex);
	
	//ball
	glPushMatrix();
	glTranslatef(0, 0.6, -0.3);
	sphere(0.4);
	glPopMatrix();
	//spike
	glPushMatrix();
	glTranslatef(0, 0.6, -0.3);
	pyramid(0.4,0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.6, -0.3);
	glRotatef(180,1,0,0);
	pyramid(0.4, 0.5);
	glPopMatrix();
}
void spikehammerhandle() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	glPushMatrix();
	glTranslatef(0, 2.1, -0.3);
	glScalef(0.15, 0.1, 0.15);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
	glPushMatrix();
	//glScalef(1, 1, 0.4);
	glTranslatef(0, 2, -0.3);
	glRotatef(90, 1, 0, 0);
	cylinder(1.4, 0.1, 0.1, 1, 1, 1);
	glPopMatrix();
}

void energyBall() {
	glColor3f(1.000, 0.855, 0.725);
	glutSolidIcosahedron();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, jointTex[jointTexNum]);
	glPushMatrix();
	glScalef(1.35, 1.35, 1.35);
	glColor3f(1.000, 0.627, 0.478);
	glutWireIcosahedron();
	glPopMatrix();
}

void turnLeft() {
	headRtY = 1;
	if (headAngle <= 50) {
		headAngle += 2.0;
	}
}

void turnRight() {
	headRtY = 1;
	if (headAngle >= -50) {
		headAngle -= 2.0;
	}
}

void robot() {
	
		glPushMatrix();
			glTranslatef(0, 5.0, 0);
			//glRotatef(headAngle, headRtX, 0, 0);
			glRotatef(headAngle, 0, headRtY, 0);
			glTranslatef(0, -5.0, 0);
			head();
		glPopMatrix();

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
			//glRotatef(-30, 1, 0, 0);
			glTranslatef(0, -5, 0);
			leg();
			glPopMatrix();
		glPopMatrix();
		
		//Rleg
		glPushMatrix();
		glTranslatef(1.28, -4, 0);
		rLeg();
		glPopMatrix();
		
}

void changeMTex() {
	
	if (robotTexNum < 3) {
		robotTexNum++;
	}
	else if(robotTexNum >=3){
		robotTexNum = 1;
	}
}

void changeFTex() {
	if (robotTexNum <= 3|| robotTexNum>5) {
		robotTexNum = 4;
	}
	else if (robotTexNum > 3&& robotTexNum <5) {
		robotTexNum++;
	}
	else if (robotTexNum == 5) {
		robotTexNum = 4;
	}
}

void changeATex() {
	if (robotTexNum <= 5) {
		robotTexNum = 6;
	}
	else if (robotTexNum > 5 && robotTexNum < 7) {
		robotTexNum++;
	}
	else if (robotTexNum == 7) {
		robotTexNum = 6;
	}
}

void changeJTex() {
	if (jointTexNum < 3) {
		jointTexNum++;
	}
	else if (jointTexNum >= 3) {
		jointTexNum = 1;
	}
}

void loadTex() {
	GLuint metalTex = LoadBMP("texture/metal.bmp");
	GLuint pinkMtTex = LoadBMP("texture/pinkMetal.bmp");
	GLuint redMtTex = LoadBMP("texture/redMetal.bmp");

	GLuint redFlameTex = LoadBMP("texture/flame.bmp");
	GLuint blueFlameTex = LoadBMP("texture/blueFlame.bmp");

	GLuint armyTex = LoadBMP("texture/army.bmp");
	GLuint blueArmyTex = LoadBMP("texture/blueArmy.bmp");

	GLuint silverTex = LoadBMP("texture/silver.bmp");
	GLuint blackTex = LoadBMP("texture/joint.bmp");
	GLuint purpleTex = LoadBMP("texture/purple.bmp");

	goldTex = LoadBMP("texture/gold.bmp");
	ebTex = LoadBMP("texture/geb.bmp");
	skyTex = LoadBMP("texture/sky.bmp");
	skyTex2 = LoadBMP("texture/sky2.bmp");
	landTex = LoadBMP("texture/land.bmp");
	landTex2 = LoadBMP("texture/land2.bmp");

	skyT[0] = skyTex;
	skyT[1] = skyTex2;

	landT[0] = landTex;
	landT[1] = landTex2;

	robotTex[1] = metalTex;
	robotTex[2] = pinkMtTex;
	robotTex[3] = redMtTex;
	robotTex[4] = redFlameTex;
	robotTex[5] = blueFlameTex;
	robotTex[6] = armyTex;
	robotTex[7] = blueArmyTex;

	jointTex[1] = blackTex;
	jointTex[2] =  silverTex;
	jointTex[3] = purpleTex;


}

void delTex() {
	DeleteObject(hBMP);
	for (int i = 1; i <= 10; i++) {
		glDeleteTextures(1, &robotTex[i]);
		glDeleteTextures(1, &jointTex[i]);
	}

	for (int i = 0; i <= 1; i++) {
		glDeleteTextures(1, &skyT[i]);
		glDeleteTextures(1, &landT[i]);
	}
	glDeleteTextures(1, &goldTex);
	glDeleteTextures(1, &ebTex);
	
	
}


