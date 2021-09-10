#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "base.h"

void bone(float boneLength) {

	cylinder(boneLength, 0.2, 0.2, 1, 1, 1);
}

void finger(float length) {

	glScalef(0.3, length, 0.3);
	cuboid(1, 1, 1);
}

void upperFingers() {

	finger(0.35);

	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	finger(0.35);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	finger(0.35);
	glPopMatrix();
}

