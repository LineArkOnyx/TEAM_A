#pragma once

//�Q����P�ւ̐i�s�����ƈړ��ʁF��������������XY1  �������ꏊXY2  'x'��'y'�̂ǂ�����o����  ������
float GetMoving(float x1, float y1, float x2, float y2, char moji, float s);

//2�_�Ԃ̋����F�J�n�n�_XY�@�I���n�_XY
float GetDistance(float startX, float startY, float endX, float endY);

//1����2�ւ̊p�x(���W�A��)�F��������ꏊXY�@��������������XY
float GetAngle(float Ax, float Ay, float Bx, float By);

//�x�N�g���̓��ς����߂Đ�������Ԃ��F��������ꏊXY�@��������������XY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By);

//�x�N�^�[�̑����Z
VECTOR AddVec(VECTOR vecA, VECTOR vecB);
VECTOR AddVec(VECTOR vecA, float x = 0.0f, float y = 0.0f, float z = 0.0f);

//�x�N�^�[�̈����Z
VECTOR SudVec(VECTOR vecA, VECTOR vecB);

//�x�����W�A���ɕϊ��i�����F�x�j
float ChangeDegToRad(float degree);
//���W�A����x�ɕϊ��i�����F���W�A���j
float ChangeRadToDeg(float radian);

void Move(float degree, float speed, float& posX, float& posY);
void Move(float degree, float speed, float& posX, float& posY,bool direction);

//======================================================================================

//�����蔻��
class Collision
{
public:

	//�l�p�FX,Y�͍��W�AW�������AH���c��
	static bool Rect(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH);
	static bool Rect(float aX, float aY, int aW, int aH, float bX, float bY, int bW, int bH);

	//�l�p(3D)�F���ꂼ��̍��WVEC�Ƒ傫��VEC
	static bool Rect3D(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);

	//�~�`�F���ꂼ��̍��W�Ɣ��a
	static bool Circlr(int aX, int aY, int aR, int bX, int bY, int bR);

	//�~�`(3D)�F���ꂼ��̍��W�Ɣ��a
	static bool Circlr3D(VECTOR aPos, float aR, VECTOR bPos, float bR);
};