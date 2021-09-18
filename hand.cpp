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


float lArmRtAngle = 0, lArmRt = 0, rArmRtAngle = 0, rArmRt = 0;
float lPalmRtAngle = 0, lPalmRt = 0,rPalmRtAngle = 0, rPalmRt = 0;
float lForeArmRtAngle = 0, lForeArmRtX = 0, lForeArmRtY = 0, lWaveAngle = 0, lArmWaveAngle = 0, lArmWave = 0;
float rForeArmRtAngle = 0, rForeArmRtX = 0, rForeArmRtY = 0, rWaveAngle = 0, rArmWaveAngle = 0, rArmWave = 0;
float fingerLRtAngle = 0, fingerLRt = 0, fingerRRtAngle = 0, fingerRRt = 0;

float lPalmWpAngle = 0, lPalmWp = 0, rPalmWpAngle = 0, rPalmWp = 0 ,takeSword = 0, takeSH = 0;
float ebZoomR = 0, ebRtR = 0, ebZoomL = 0, ebRtL = 0, ballAtk = 0;
bool ebR = 0, ebL = 0, readyL=0,readyR=0;
bool right = 0, left = 0, rightR = 0, leftR = 0;

void restore() {
	lArmRtAngle = 0, lArmRt = 0, rArmRtAngle = 0, rArmRt = 0;
	lPalmRtAngle = 0, lPalmRt = 0, rPalmRtAngle = 0, rPalmRt = 0;
	lForeArmRtAngle = 0, lForeArmRtX = 0, lForeArmRtY = 0, lWaveAngle = 0, lArmWaveAngle = 0, lArmWave = 0;
	rForeArmRtAngle = 0, rForeArmRtX = 0, rForeArmRtY = 0, rWaveAngle = 0, rArmWaveAngle = 0, rArmWave = 0;
	fingerLRtAngle = 0, fingerLRt = 0, fingerRRtAngle = 0, fingerRRt = 0;

	lPalmWpAngle = 0, lPalmWp = 0, rPalmWpAngle = 0, rPalmWp = 0, takeSword = 0, takeSH = 0;
	ebZoomR = 0, ebRtR = 0, ebZoomL = 0, ebRtL = 0, ballAtk = 0;
	ebR = 0, ebL = 0, readyL = 0, readyR = 0;
	right = 0, left = 0, rightR = 0, leftR = 0;
}

bool moveLArmUp() {

	lArmRt = 1;
	if (lArmRtAngle < 90) {
		lArmRtAngle += 1.0;
	}
	else if (lArmRtAngle == 90) {
		return 0;
	}
	return 1;
}

bool moveRArmUp() {

	rArmRt = 1;
	if (rArmRtAngle < 90) {
		rArmRtAngle += 1.0;
	}
	else if (rArmRtAngle == 90) {
		return 0;
	}
	return 1;
}

bool moveLArmDown() {
	lArmRt = 1;
	if (lArmRtAngle > 0) {
		lArmRtAngle -= 1.0;
	}
	else if (lArmRtAngle == 0) {
		lArmRt = 0;
		return 0;
	}
	return 1;
}

bool moveRArmDown() {
	rArmRt = 1;
	if (rArmRtAngle > 0) {
		rArmRtAngle -= 1.0;
	}
	else if (rArmRtAngle == 0) {
		rArmRt = 0;
		return 0;
	}
	return 1;
}

bool moveLArmnPalmUp(bool attack) {
	lArmRt = 1;
	lPalmRt = 1;
	if (lArmRtAngle < 90) {
		lArmRtAngle += 1.0;
		lPalmRtAngle = lArmRtAngle;
	}
	else if (lArmRtAngle == 90) {
		if (attack) {
			ebL = 1;
			ebRtL += 30;
			ballAtk = 0;
			if (ebZoomL < 0.4) {
				ebZoomL += 0.02;
			}
		}
		return 0;
	}
	return 1;
}

bool moveLArmnPalmDown() {
	lArmRt = 1;
	lPalmRt = 1;
	if (lArmRtAngle > 0) {
		lArmRtAngle -= 1.0;
		lPalmRtAngle = lArmRtAngle;
	}
	else if (lArmRtAngle == 0) {
		lArmRt = 0;
		lPalmRt = 0;
		return 0;
	}
	return 1;
}

bool moveRArmnPalmUp(bool attack) {
	rArmRt = 1;
	rPalmRt = 1;
	if (rArmRtAngle < 90) {
		rArmRtAngle += 1.0;
		rPalmRtAngle = rArmRtAngle;
	}
	else if (rArmRtAngle == 90) {
		if (attack) {
			ebR = 1;
			ebRtR += 30;
			ballAtk = 0;
			if (ebZoomR < 0.4) {
				ebZoomR += 0.02;
			}
		}
		return 0;
	}
	return 1;
}

bool moveRArmnPalmDown() {
	rArmRt = 1;
	rPalmRt = 1;
	if (rArmRtAngle > 0) {
		rArmRtAngle -= 1.0;
		rPalmRtAngle = rArmRtAngle;
	}
	else if (rArmRtAngle == 0) {
		rArmRt = 0;
		rPalmRt = 0;
		return 0;
	}
	return 1;
}

bool moveLForeArmnArmUp(float angle) {
	lForeArmRtX = 1;
	lArmWave = 1;

	if (lForeArmRtAngle < angle) {
		lForeArmRtAngle += 1.0;
		lArmWaveAngle = lForeArmRtAngle;
	}
	else if (lForeArmRtAngle >= angle) {
		return true;
	}
	return false;
}

void moveLForeArmnArmDown() {

	if (lForeArmRtAngle >0) {
		lForeArmRtAngle -= 1.0;
		lArmWaveAngle = lForeArmRtAngle;
	}
	else if (lForeArmRtAngle == 0) {
		lForeArmRtX = 0;
		lArmWave = 0;
	}
}

bool moveRForeArmnArmUp(float angle) {
	rForeArmRtX = 1;
	rArmWave = 1;

	if (rForeArmRtAngle < angle) {
		rForeArmRtAngle += 1.0;
		rArmWaveAngle = rForeArmRtAngle;
	}
	else if (rForeArmRtAngle >= angle) {
		return true;
	}
	return false;
}

void moveRForeArmnArmDown() {

	if (rForeArmRtAngle > 0) {
		rForeArmRtAngle -= 1.0;
		rArmWaveAngle = rForeArmRtAngle;
	}
	else if (rForeArmRtAngle == 0) {
		rForeArmRtX = 0;
		rArmWave = 0;
	}
}

void wave() {
	if (moveLForeArmnArmUp(90)) {
		lForeArmRtY = 1;
		if (left || !left && !right) {
			lWaveAngle += 1.0;
			if (lWaveAngle >= 20) {
				right = 1;
				left = 0;
			}
		}
		if (right) {
			lWaveAngle -= 1.0;
			if (lWaveAngle <= -20) {
				left = 1;
				right = 0;
			}
		}
	}
}

void waveLHandDown() {
	lWaveAngle = 0;
	lForeArmRtY = 0;
	moveLForeArmnArmDown();
	
}

void waveR() {
	if (moveRForeArmnArmUp(90)) {
		rForeArmRtY = 1;
		if (leftR || !leftR && !rightR) {
			rWaveAngle += 1.0;
			if (rWaveAngle >= 20) {
				rightR = 1;
				leftR = 0;
			}
		}
		if (rightR) {
			rWaveAngle -= 1.0;
			if (rWaveAngle <= -20) {
				leftR = 1;
				rightR = 0;
			}
		}
	}
}

void waveRHandDown() {
	rWaveAngle = 0;
	moveRForeArmnArmDown();

}

void LtakeSword() {
		lPalmWp = 1;
		fingerLRt = 1;
		if (lPalmWpAngle < 90) {
			lPalmWpAngle += 1.0;
			fingerLRtAngle += 0.5;
			moveLForeArmnArmUp(50);
			if (lPalmWpAngle >= 90) {
				takeSword = 1;
			}
			moveLForeArmnArmUp(50);
		}
}

void downSword() {
	takeSword = 0;
	if (lPalmWpAngle > 0) {
		lPalmWpAngle -= 1.0;
		fingerLRtAngle -= 0.5;
		moveLForeArmnArmDown();
		if (lPalmWpAngle == 0) {
			fingerLRt = 0;
			lPalmWp = 0;
		}
	}
	
	
}

void RtakeSH() {

	rPalmWp = 1;
	fingerRRt = 1;
	if (rPalmWpAngle < 90) {
		rPalmWpAngle += 1.0;
		fingerRRtAngle += 0.5;
		moveRForeArmnArmUp(50);
		if (rPalmWpAngle >= 90) {
			takeSH = 1;
		}
		moveRForeArmnArmUp(50);
	}
}

void downSH() {
	takeSH = 0;
	if (rPalmWpAngle > 0) {
		rPalmWpAngle -= 1.0;
		fingerRRtAngle -= 0.5;
		moveRForeArmnArmDown();
		if (rPalmWpAngle == 0) {
			fingerRRt = 0;
		}
	}


}

bool attackBall() {
	if (ballAtk > -10) {
		ballAtk -= 1.0;
		if (ballAtk <= -8) {
			ebR = 0;
			ebZoomR = 0;
			ebL = 0;
			ebZoomL = 0;
			return 1;
		}
	}
	
	return 0;
}

void sword() {
	swordhandle();
	swordbody();

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

void allFingersL() {

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.15, 0);

	glTranslatef(0, 0.2, 0.0);
	glRotatef(fingerLRtAngle, fingerLRt, 0, 0);
	glTranslatef(0, -0.2, 0.0);
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

void allFingersR() {

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glRotatef(30, 1, 0, 0);
	glTranslatef(0, -0.15, 0);

	glTranslatef(0, 0.2, 0.0);
	glRotatef(fingerRRtAngle, fingerRRt, 0, 0);
	glTranslatef(0, -0.2, 0.0);
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


void leftHand() {

	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glRotatef(180, 0, 1, 0);
		shoulder();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.56, 3.4, 0);
		glRotatef(-lArmWaveAngle, lArmWave, 0, 0);
		glRotatef(-lArmRtAngle, lArmRt, 0, 0);
		glTranslatef(-0.56, -3.4, 0);

		glPushMatrix();
			glTranslatef(-0.28, 0, 0);
			upperArm();

			glPushMatrix();
				//glTranslatef(-0.28, 0, 0);
				glTranslatef(0, 2.6, 0);
				glRotatef(-lWaveAngle, 0, lForeArmRtY, 0);
				glRotatef(-lForeArmRtAngle, lForeArmRtX, 0, 0);
				glTranslatef(0, -2.6, 0);
				upForeArm();
				foreArm();
					glPushMatrix();
						glTranslatef(0.34, 1.3, 0);
						glRotatef(-lPalmRtAngle, lPalmRt, 0, 0);
						glRotatef(-lPalmWpAngle, 0, lPalmWp, 0);
						glTranslatef(-0.34, -1.3, 0);
						palm();
						if (ebL) {
							glPushMatrix();
							glTranslatef(0.35, 1.0, -0.8 + ballAtk);
							glRotatef(ebRtL, 1, 1, 1);
							glScalef(0.1 + ebZoomL, 0.1 + ebZoomL, 0.1 + ebZoomL);
							energyBall();
							glPopMatrix();
						}

						glPushMatrix();
							glTranslatef(0, 0.65, 0.0);
							glRotatef(fingerLRtAngle, fingerLRt, 0, 0);
							glTranslatef(0, -0.65, 0.0);
							allFingersL();
						glPopMatrix();
						if (takeSword) {
							glPushMatrix();
								glTranslatef(0.3, 1.5, 0);
								glRotatef(90, 0, 0, 1);
								glTranslatef(3.305, -1.95, 0.0);
								sword();
							glPopMatrix();
						}
				
						glPushMatrix();
							glTranslatef(1.0, 0.1, -0.2);
							lThumb();
						glPopMatrix();
					glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void spikehammer() {
	spikehammertop();
	spikehammerhandle();
}

void rightHand() {
	shoulder();
	glPushMatrix();
		glTranslatef(0.56, 3.4, 0);
		glRotatef(-rArmWaveAngle, rArmWave, 0, 0);
		glRotatef(-rArmRtAngle, rArmRt, 0, 0);
		glTranslatef(-0.56, -3.4, 0);
		upperArm();
	
			glPushMatrix();
				glTranslatef(0, 2.6, 0);
				glRotatef(-rWaveAngle, 0, rForeArmRtY, 0);
				glRotatef(-rForeArmRtAngle, rForeArmRtX, 0, 0);
				glTranslatef(0, -2.6, 0);
				upForeArm();
				foreArm();
				glPushMatrix();
					glTranslatef(0.42, 1.3, 0);
					glRotatef(-rPalmRtAngle, rPalmRt, 0, 0);
					glRotatef(rPalmWpAngle, 0, rPalmWp, 0);
					glTranslatef(-0.42, -1.3, 0);
					palm();
					if (ebR) {
						glPushMatrix();
						glTranslatef(0.35, 1.0, -0.8 + ballAtk);
						glRotatef(ebRtR, 1, 1, 1);
						glScalef(0.1 + ebZoomR, 0.1 + ebZoomR, 0.1 + ebZoomR);
						energyBall();
						glPopMatrix();
					}
					thumb(0.2);
					glPushMatrix();
						glTranslatef(0, 0.65, 0.0);
						glRotatef(fingerRRtAngle, fingerRRt, 0, 0);
						glTranslatef(0, -0.65, 0.0);
						allFingersR();
					glPopMatrix();
					
					if (takeSH) {
						glPushMatrix();
							glTranslatef(0, 0.7, 0);
							glRotatef(-90, 0, 0, 1);
							glTranslatef(0, -1.95, 0.0);
							spikehammer();
						glPopMatrix();
						
					}
				glPopMatrix();
			glPopMatrix();

	glPopMatrix();
}



