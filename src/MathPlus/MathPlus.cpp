#include"DxLib.h"
#define _USE_MATH_DEFINES	//円周率
#include<math.h>

#include"MathPlus.h"

//２から１への進行方向と移動量：動かしたいものXY1  向かう場所XY2  XとYのどちらを出すか  増加量
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

//2点間の距離：開始地点XY　終了地点XY
float GetDistance(float startX, float startY, float endX, float endY)
{
	float num = 0.0f;
	num = ((startX - endX) * (startX - endX)) + ((startY - endY) * (startY - endY));
	num = sqrtf(num);

	return num;
}

//1から2への角度(ラジアン)：向かせる場所XY　向かせたいものXY
float GetAngle(float Ax, float Ay, float Bx, float By)
{
	float num = 0.0f;
	num=atan2f(By - Ay, Bx - Ax);

	return num;
}

//ベクトルの内積を求めて正か負を返す：向かせたいものXY　向かせる場所XY
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

//ベクターの足し算
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

//ベクターの引き算
VECTOR SudVec(VECTOR vecA, VECTOR vecB)
{
	VECTOR ret;

	ret.x = vecA.x - vecB.x;
	ret.y = vecA.y - vecB.y;
	ret.z = vecA.z - vecB.z;

	return ret;
}

//度をラジアンに変換（引数：度）
float ChangeDegToRad(float degree)
{
	return degree * (float)M_PI / 180.0f;
}

//ラジアンを度に変換（引数：ラジアン）
float ChangeRadToDeg(float radian)
{
	return radian * 180.0f / (float)M_PI;
}

//向いてる方向に進む：斜辺, 移動量, 格納先
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

//IsHitRectの定義（四角）
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

//IsHitRectの定義（四角）：3D
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


//IsHitCircleの定義（円形）
bool Collision::Circlr(int aX, int aY, int aR, int bX, int bY, int bR)
{
	if ((aR + bR) * (aR + bR) > (aX - bX) * (aX - bX) + (aY - bY) * (aY - bY))
	{
		return true;
	}
	return false;
}

//IsHitCircleの定義（円形）：3D
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
