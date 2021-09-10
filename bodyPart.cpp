#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "base.h"

void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void joint(float boneLength,float boneWidth) {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	cylinder(boneLength, boneWidth, boneWidth, 1, 1, 1);
	glPopMatrix();
}

void finger(float length) {

	glPushMatrix();
	glScalef(0.06, length, 0.06);
	cuboid(0.545, 0.271, 0.075);
	glPopMatrix();
}

void upperFingers(float length) {

	finger(length);

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
	glPushMatrix();
	glTranslatef(-0.05, 0.22, 0);
	joint(0.1, 0.06);
	glPopMatrix();

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

void allFingers() {

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.15, 0);
	upperFingers(0.15);
	glPopMatrix();

	fingerJoint();

	lowerFingers();
}

void hand() {

}
