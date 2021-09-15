#include <Windows.h>
#include <Windowsx.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLUT.h>

#include "interactive.h"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")


//bool moveLforeArmUp() {
//
//	lForeArmRt = 1;	
//	if (lForeArmRtAngle < 30) {
//		lForeArmRtAngle += 0.1;
//	}
//	else if (lForeArmRtAngle == 30) {
//		return false;
//	}
//	return true;
//}
//
//bool moveForeArmDown() {
//	if (lForeArmRtAngle > 0) {
//		lForeArmRtAngle -= 0.1;
//	}
//	else if (lForeArmRtAngle == 0) {
//		lForeArmRt = 0;
//		return false;
//	}
//	return true;
//}
