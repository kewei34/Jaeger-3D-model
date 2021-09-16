#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#include "base.h"
#include "bodyPart.h"

float upperLLegRtAngle = 0, upperLLegRt=0, upperRLegRtAngle = 0, upperRLegRt = 0;
float lowerLLegRtAngle = 0, lowerLLegRt=0, lowerRLegRtAngle = 0, lowerRLegRt = 0;
float wholeLLegRtAngle = 0, wholeLLegRt = 0, wholeRLegRtAngle = 0, wholeRLegRt = 0;
bool moveFront = 0, legBack = 1;

void legRestore() {
	upperLLegRtAngle = 0, upperLLegRt = 0;
	lowerLLegRtAngle = 0, lowerLLegRt = 0;
	wholeLLegRtAngle = 0, wholeLLegRt = 0;
	moveFront = 0;
}

void walk() {
	upperLLegRt = 1;
	if (upperLLegRtAngle < 20) {
		upperLLegRtAngle += 0.5;
	}
	else if (upperLLegRtAngle == 20) {
		lowerLLegRt = 1;
		wholeLLegRt = 1;
		if (lowerLLegRtAngle<40) {
			lowerLLegRtAngle += 0.5;
		}
		if (wholeLLegRtAngle <20) {
			wholeLLegRtAngle += 0.5;
		}
		else if (lowerLLegRtAngle >= 40) {
			moveFront = 1;
			legBack = 0;
		}
	}
}

bool moveRobotFront() {
	if (moveFront) {
		moveFront = 0;
		return 1;
	}
	else {
		return 0;
	}
}


void walk2() {
	if (upperLLegRtAngle>  0) {
		upperLLegRtAngle -= 0.5;
	}
	if (lowerLLegRtAngle > 0) {
		lowerLLegRtAngle -= 1.0;
	}
	if (wholeLLegRtAngle > 0) {
		wholeLLegRtAngle -= 0.5;
	}
	
}

void moveLegBack() {
	if (legBack) {
	}
	else {
		walk2();
	}
}

//void move


void leg() {
	
	glPushMatrix();
		glTranslatef(0, 5.2, 0);
		glRotatef(-wholeLLegRtAngle, wholeLLegRt, 0, 0);
		glTranslatef(0, -5.2, 0);
			glPushMatrix();
				glTranslatef(0, 5.2, 0);
				glRotatef(-upperLLegRtAngle, upperLLegRt, 0, 0);
				glTranslatef(0, -5.2, 0);
				upperleg();
			

				glPushMatrix();
				glTranslatef(0, 4.2, 0);
				glRotatef(-lowerLLegRtAngle, lowerLLegRt, 0, 0);
				glRotatef(upperLLegRtAngle*2, upperLLegRt, 0, 0);
				glTranslatef(0, -4.2, 0);
				lowerleg();
				glPopMatrix();
			glPopMatrix();
		

	glPopMatrix();
}

void rLeg() {

	glPushMatrix();
	glRotatef(wholeRLegRtAngle, wholeRLegRt, 0, 0);
	glPushMatrix();
	glTranslatef(0, 5.2, 0);
	glRotatef(-upperRLegRtAngle, upperRLegRt, 0, 0);
	glTranslatef(0, -5.2, 0);
	upperleg();


	glPushMatrix();
	glTranslatef(0, 4.2, 0);
	glRotatef(-lowerRLegRtAngle, lowerRLegRt, 0, 0);
	glRotatef(upperRLegRtAngle * 2, upperRLegRt, 0, 0);
	glTranslatef(0, -4.2, 0);
	lowerleg();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();
}