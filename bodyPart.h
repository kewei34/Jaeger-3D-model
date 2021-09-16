#pragma once

GLuint LoadBMP(const char* fileName);

void restore();

void bone(float boneLength);

void joint(float boneLength,float boneWidth);

void finger(float length);

void lowerFingers();

void upperFingers(float length);

void fingerJoint();

void allFingers();

void foreArm();

void upForeArm();

void palm();

void shoulder();

void upperArm();


void body();

void wholeBody();

void robot();

void moveRobot();

void leg();

void upperleg();

void lowerleg();


void changeMTex();

void changeFTex();

void changeATex();

void changeJTex();

void loadTex();

void delTex();