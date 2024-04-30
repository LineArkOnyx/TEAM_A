#include"DxLib.h"
#define _USE_MATH_DEFINES	//�~����
#include<math.h>

#include"MathPlus.h"

//�Q����P�ւ̐i�s�����ƈړ��ʁF��������������XY1  �������ꏊXY2  X��Y�̂ǂ�����o����  ������
float GetMoving(float x1, float y1, float x2, float y2, char moji,float s)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float n = x * x + y * y;

	n = sqrtf(n);

	if (moji == 'x')
	{
		return x / n * s;
	}
	else if (moji == 'y')
	{
		return y / n * s;
	}
	return 0;
}

//2�_�Ԃ̋����F�J�n�n�_XY�@�I���n�_XY
float GetDistance(float startX, float startY, float endX, float endY)
{
	float num = 0.0f;
	num = ((startX - endX) * (startX - endX)) + ((startY - endY) * (startY - endY));
	num = sqrtf(num);

	return num;
}

//1����2�ւ̊p�x(���W�A��)�F��������ꏊXY�@��������������XY
float GetAngle(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;
	num=atan2f(By - Ay, Bx - Ax);

	return num;
}

//�x�N�g���̓��ς����߂Đ�������Ԃ��F��������������XY�@��������ꏊXY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;

	num = Bx * Ax + By * Ay;
	if (num > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�x�N�^�[�̑����Z
VECTOR AddVec(VECTOR vecA, VECTOR vecB)
{
	VECTOR ret;

	ret.x = vecA.x + vecB.x;
	ret.y = vecA.y + vecB.y;
	ret.z = vecA.z + vecB.z;

	return ret;
}
VECTOR AddVec(VECTOR vecA, float x, float y, float z)
{
	VECTOR ret;

	ret.x = vecA.x + x;
	ret.y = vecA.y + y;
	ret.z = vecA.z + z;

	return ret;
}

//�x�N�^�[�̈����Z
VECTOR SudVec(VECTOR vecA, VECTOR vecB)
{
	VECTOR ret;

	ret.x = vecA.x - vecB.x;
	ret.y = vecA.y - vecB.y;
	ret.z = vecA.z - vecB.z;

	return ret;
}

//�x�����W�A���ɕϊ��i�����F�x�j
float ChangeDegToRad(float degree)
{
	return degree * (float)M_PI / 180.0f;
}

//���W�A����x�ɕϊ��i�����F���W�A���j
float ChangeRadToDeg(float radian)
{
	return radian * 180.0f / (float)M_PI;
}

//�����Ă�����ɐi�ށF�Ε�, �ړ���, �i�[��
void Move(float degree, float speed, float& posX, float& posY)
{
	float speedY = 0, speedX = 0;
	speedX = cosf(degree) * speed;
	speedY = sinf(degree) * speed;

	posY += speedY;
	posX += speedX;
}
void Move(float degree, float speed, float& posX, float& posY, bool direction)
{
	float speedY = 0, speedX = 0;
	speedX = cosf(degree) * speed;
	speedY = sinf(degree) * speed;

	posY += speedY;
	posX += speedX;

	if (speedX < 0)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}
}

//======================================================================================

//IsHitRect�̒�`�i�l�p�j
bool Collision::Rect(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH)
{
	if (bX < aX + aW &&
		bX + bW > aX &&
		bY + bH > aY &&
		bY < aY + aH)
	{
		return true;
	}
	return false;
}
bool Collision::Rect(float aX, float aY, int aW, int aH, float bX, float bY, int bW, int bH)
{
	if (bX < aX + aW &&
		bX + bW > aX &&
		bY + bH > aY &&
		bY < aY + aH)
	{
		return true;
	}
	return false;
}

//IsHitRect�̒�`�i�l�p�j�F3D
bool Collision::Rect3D(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize)
{
	if (bPos.x < aPos.x + aSize.x &&
		bPos.x + bSize.x > aPos.x &&

		bPos.y < aPos.y + aSize.y &&
		bPos.y + bSize.y > aPos.y &&

		bPos.z < aPos.z + aSize.z &&
		bPos.z + bSize.z > aPos.z
		)
	{
		return true;
	}
	return false;
}


//IsHitCircle�̒�`�i�~�`�j
bool Collision::Circlr(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY))
	{
		return true;
	}
	return false;
}

//IsHitCircle�̒�`�i�~�`�j�F3D
bool Collision::Circlr3D(VECTOR aPos, float aR, VECTOR bPos, float bR)
{
	if ((aR + bR) * (aR + bR) >
		(aPos.x - bPos.x) * (aPos.x - bPos.x) +
		(aPos.y - bPos.y) * (aPos.y - bPos.y) +
		(aPos.z - bPos.z) * (aPos.z - bPos.z))
	{
		return true;
	}
	return false;
}
