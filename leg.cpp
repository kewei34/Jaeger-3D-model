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
bool moveFront = 0, moveR = 0, moveL = 0;

void legRestore() {
	upperLLegRtAngle = 0, upperLLegRt = 0, upperRLegRtAngle = 0, upperRLegRt = 0;
	lowerLLegRtAngle = 0, lowerLLegRt = 0, lowerRLegRtAngle = 0, lowerRLegRt = 0;
	wholeLLegRtAngle = 0, wholeLLegRt = 0, wholeRLegRtAngle = 0, wholeRLegRt = 0;
	moveFront = 0, moveR = 0, moveL = 0;
}



bool walkLeft() {
	if (!moveL && !moveR || moveL) {
		upperLLegRt = 1;
		if (upperLLegRtAngle < 20) {
			upperLLegRtAngle += 0.5;
		}
		else if (upperLLegRtAngle >= 20) {
			lowerLLegRt = 1;
			wholeLLegRt = 1;
			if (wholeLLegRtAngle < 20) {
				wholeLLegRtAngle += 0.5;
			}
			if (wholeLLegRtAngle == 20) {
				moveFront = 1;
				moveL = 0;
				moveR = 1;
				return true;
			}
		}
	}
	return false;
}

bool walkRight() {
	if (moveR) {
		upperRLegRt = 1;
		if (upperRLegRtAngle < 20) {
			upperRLegRtAngle += 0.5;
		}
		else if (upperRLegRtAngle >= 20) {
			lowerRLegRt = 1;
			wholeRLegRt = 1;
			if (wholeRLegRtAngle < 20) {
				wholeRLegRtAngle += 0.5;
			}
			if (wholeRLegRtAngle == 20) {
				moveFront = 1;
				moveL = 1;
				moveR = 0;
				return true;
			}
		}
	}
	return false;
}

bool walk() {

	if (moveL) {
		return walkLeft();
	}
	else if (moveR) {
		return walkRight();
	}
	else {
		return walkLeft();
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

void moveLLowerLegUp() {
	lowerLLegRt = 1;
	if (lowerLLegRtAngle < 60) {		
		lowerLLegRtAngle += 1.0;		
	}

}

void moveRLowerLegUp() {
	lowerRLegRt = 1;
	if (lowerRLegRtAngle < 60) {
		lowerRLegRtAngle += 1.0;
	}

}

void moveLLowerLegDown() {
	
	if (lowerLLegRtAngle> 0) {
		lowerLLegRtAngle -= 1.0;
	}if (lowerLLegRtAngle == 0) {
		lowerLLegRt = 0;
	}

}

void moveRLowerLegDown() {

	if (lowerRLegRtAngle > 0) {
		lowerRLegRtAngle -= 1.0;
	}if (lowerRLegRtAngle == 0) {
		lowerRLegRt = 0;
	}

}


bool walk2() {
	if (!moveL) {
		if (wholeLLegRtAngle > 0) {
			wholeLLegRtAngle -= 0.5;
			upperLLegRtAngle -= 0.5;
			if (wholeLLegRtAngle <= 0) {
				return true;
			}
		}
	}
	else if (!moveR) {
		if (wholeRLegRtAngle > 0) {
			wholeRLegRtAngle -= 0.5;
			upperRLegRtAngle -= 0.5;
			if (wholeRLegRtAngle <= 0) {
				return true;
			}
		}
		
	}
	return false;
}

bool moveLegBack() {

		return walk2();
}



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
				glTranslatef(0, 3.1, -0.3);
				glRotatef(-lowerLLegRtAngle, lowerLLegRt, 0, 0);
				glRotatef(upperLLegRtAngle*2, upperLLegRt, 0, 0);
				glTranslatef(0, -3.1, 0.3);
				lowerleg();
				glPopMatrix();
			glPopMatrix();
		

	glPopMatrix();
}

void rLeg() {

	glPushMatrix();
		glTranslatef(0, 5.2, 0);
		glRotatef(-wholeRLegRtAngle, wholeRLegRt, 0, 0);
		glTranslatef(0, -5.2, 0);
		glPushMatrix();
			glTranslatef(0, 5.2, 0);
			glRotatef(-upperRLegRtAngle, upperRLegRt, 0, 0);
			glTranslatef(0, -5.2, 0);
			upperleg();

				glPushMatrix();
					glTranslatef(0, 3.1, -0.3);
					glRotatef(-lowerRLegRtAngle, lowerRLegRt, 0, 0);
					glRotatef(upperRLegRtAngle * 2, upperRLegRt, 0, 0);
					glTranslatef(0, -3.1, 0.3);
					lowerleg();
				glPopMatrix();
		glPopMatrix();


	glPopMatrix();
}