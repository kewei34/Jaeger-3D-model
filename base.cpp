#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>

void cuboid(float x, float y, float z, float r, float g, float b) {


	glShadeModel(GL_FLAT);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, y, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z);
	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, -y, -z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, -z);
	//up
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, y, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, -z);
	//down
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, -y, -z);
	//left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, y, z);
	//right
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y, -z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, -y, -z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, -y, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z);
	glEnd();
}

