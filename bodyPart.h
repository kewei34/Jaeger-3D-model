#pragma once

GLuint LoadBMP(const char* fileName);

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

void leftHand();

void rightHand();


bool moveLforeArmUp();

bool moveLforeArmDown();

void body();

void wholeBody();

void robot();

void leg();

void loadTex();

void delTex();