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
#include "scene.h"
#include "bodyPart.h"
#include "interactive.h"

#define WINDOW_TITLE "OpenGL Window"

//draw curve line
GLfloat ctrlpoints[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

GLfloat ctrlpoints2[3][3] = {
	{ 6, 4, 0 },{ 4, -2, 0 },{ 0, 1.5, 0 }
};

// mouse movement
float lastX = 0.0f, lastY = 0.0f;
float xRotated = 0.0f, yRotated = 0.0f, zRotated = 0.0f;
float xPosition = 0.0f, yPosition = 0.0f, zPosition = 0.05f;
float zoomLevel = -7.0f;

//light
float x = 5.0f, y = 10.0f, z = 10.0f;
bool lightOn = 1, ambientOn = 1, diffuseOn = 1, specularOn = 1;

bool textureOn = 1,perspec = 1;
bool LArmUp = 0,LArmDown = 1, LArmnPalmUp = 0, LArmnPalmDown = 1;

bool liftLArm = 0, downLArm = 0, liftLArmnPalm = 0, downLArmnPalm = 0;
bool ballAtk = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		switch (wParam) {
		case MK_LBUTTON:
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			yRotated += xPos - lastX;
			xRotated += yPos - lastY;
			lastX = xPos;
			lastY = yPos;
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		lastX = GET_X_LPARAM(lParam);
		lastY = GET_Y_LPARAM(lParam);
		break;
	case WM_MOUSEWHEEL:
		zoomLevel += GET_WHEEL_DELTA_WPARAM(wParam) / 120.0f;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);

		else if(wParam == VK_SPACE) {
			xRotated = 0.0f; yRotated = 0.0f; zRotated = 0.0f;
			zoomLevel = -7.0f;
			restore();
		}
		else if (wParam == 'T') {
			if (textureOn) {
				glDisable(GL_TEXTURE_2D);
				textureOn = 0;
			}
			else{
				glEnable(GL_TEXTURE_2D);
				textureOn = 1;
			}
			
		}
		else if (wParam == '3') {
			if (lightOn) {
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				lightOn = 0;
			}
			else {
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				lightOn = 1;
			}
		}

		else if (wParam == 'P') {
			if (perspec) {
				perspec = 0;
			}
			else {
				perspec = 1;
			}
		}

		else if (wParam == '7') {
			if (LArmDown) {
				liftLArm = 1;
			}
			else {
				downLArm = 1;
			}
		}
		else if (wParam == '9') {
			if (LArmDown&& LArmnPalmDown) {
				liftLArmnPalm = 1;
			}
			else {
				downLArmnPalm = 1;
			}
		}
		else if (wParam == 'X') {
			if (LArmnPalmUp) {
				ballAtk = 0;
				moveLArmnPalmUp(1);
			}
		}
		break;
	case WM_KEYUP:
		if (wParam == 'X') {
			if (LArmnPalmUp) {
				ballAtk = 1;
			}
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

	
void display()
{
	/*glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);*/
	
	if (perspec) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(70.0, 1.0, 0.6, 21.0);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5.0 + zoomLevel, 5.0 - zoomLevel, -5.0 + zoomLevel, 5.0 - zoomLevel, -7.0 + zoomLevel, 3.0 - zoomLevel);
	}

	glEnable(GL_NORMALIZE);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	GLfloat light_ambient[] = { 1.0, 1.0 ,1.0, 1.0 };
	GLfloat light_close[] = { 0.0, 0.0 ,0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat light_position[] = { x,y,z, 0.0 };

	if (ambientOn) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	}
	else {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_close);
	}

	if (diffuseOn) {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_close);
	}

	if (specularOn) {
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	}
	else {
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_close);
	}


	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glClearColor(0.902, 0.902, 0.980, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, zoomLevel);
	//glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	glRotatef(xRotated, 1.0, 0.0, 0.0);
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();

	//movement
	if (liftLArm && LArmDown&& LArmnPalmDown) {
		LArmDown = moveLArmUp();
		if (!LArmDown) {
			LArmUp = 1;
			liftLArm = 0;
		}
	}

	if (downLArm && LArmUp && LArmnPalmDown) {
		LArmUp = moveLArmDown();
		if (!LArmUp) {
			LArmDown = 1;
			downLArm = 0;
		}
	}

	if (liftLArmnPalm && LArmDown && LArmnPalmDown) {
		LArmnPalmDown = moveLArmnPalmUp(0);
		if (!LArmnPalmDown) {
			liftLArmnPalm = 0;
			LArmnPalmDown = 0;
			LArmnPalmUp = 1;
		}
	}

	if (downLArmnPalm && LArmDown && LArmnPalmUp) {
		LArmnPalmUp = moveLArmnPalmDown();
		if (!LArmnPalmUp) {
			downLArmnPalm = 0;
			LArmnPalmDown = 1;
			LArmnPalmUp = 0;
		}
	}

	//attack
	if (ballAtk) {
		if (attackBall()) {
			ballAtk = 0;
		}
	}

	robot();
  
	
	
	glPopMatrix();
	glFlush();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_STENCIL_TEST);*/
	//glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glEnable(GL_TEXTURE_2D);

	loadTex();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}
	
	delTex();
	/*glDisable(GL_TEXTURE_2D);*/
	//DeleteObject(hBMP);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_STENCIL_TEST);
	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------