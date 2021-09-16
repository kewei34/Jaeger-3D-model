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

float upperLegRtAngle = 0, upperLegRt=0;
float lowerLegRtAngle = 0, lowerLegRt=0;
float wholeLegRtAngle = 0, wholeLegRt = 0;

void legRestore() {
	upperLegRtAngle = 0, upperLegRt = 0;
	lowerLegRtAngle = 0, lowerLegRt = 0;
	wholeLegRtAngle = 0, wholeLegRt = 0;
}

bool walk() {
	upperLegRt = 1;
	if (upperLegRtAngle < 10) {
		upperLegRtAngle += 0.5;
	}
	else if (upperLegRtAngle == 10) {
		lowerLegRt = 1;
		if (lowerLegRtAngle<20) {
			lowerLegRtAngle += 0.5;
		}
		else if (lowerLegRtAngle == 30) {
			return true;
		}
	}
	return false;
}

void leg() {
	
	glPushMatrix();
		glRotatef(wholeLegRtAngle, wholeLegRt, 0, 0);
			glPushMatrix();
				glTranslatef(0, 5.2, 0);
				glRotatef(-upperLegRtAngle, upperLegRt, 0, 0);
				glTranslatef(0, -5.2, 0);
				upperleg();
			

				glPushMatrix();
				glTranslatef(0, 4.2, 0);
				glRotatef(-lowerLegRtAngle, lowerLegRt, 0, 0);
				glRotatef(upperLegRtAngle*2, upperLegRt, 0, 0);
				glTranslatef(0, -4.2, 0);
				lowerleg();
				glPopMatrix();
			glPopMatrix();
		

	glPopMatrix();
}