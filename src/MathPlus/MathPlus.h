#pragma once

//２から１への進行方向と移動量：動かしたいものXY1  向かう場所XY2  'x'と'y'のどちらを出すか  増加量
float GetMoving(float x1, float y1, float x2, float y2, char moji, float s);

//2点間の距離：開始地点XY　終了地点XY
float GetDistance(float startX, float startY, float endX, float endY);

//1から2への角度(ラジアン)：向かせる場所XY　向かせたいものXY
float GetAngle(float Ax, float Ay, float Bx, float By);

//ベクトルの内積を求めて正か負を返す：向かせる場所XY　向かせたいものXY
bool GetInnerProduct(float Ax, float Ay, float Bx, float By);

//ベクターの足し算
VECTOR AddVec(VECTOR vecA, VECTOR vecB);
VECTOR AddVec(VECTOR vecA, float x = 0.0f, float y = 0.0f, float z = 0.0f);

//ベクターの引き算
VECTOR SudVec(VECTOR vecA, VECTOR vecB);

//度をラジアンに変換（引数：度）
float ChangeDegToRad(float degree);
//ラジアンを度に変換（引数：ラジアン）
float ChangeRadToDeg(float radian);

void Move(float degree, float speed, float& posX, float& posY);
void Move(float degree, float speed, float& posX, float& posY,bool direction);

//======================================================================================

//当たり判定
class Collision
{
public:

	//四角：X,Yは座標、Wが横幅、Hが縦幅
	static bool Rect(int aX, int aY, int aW, int aH, int bX, int bY, int bW, int bH);
	static bool Rect(float aX, float aY, int aW, int aH, float bX, float bY, int bW, int bH);

	//四角(3D)：それぞれの座標VECと大きさVEC
	static bool Rect3D(VECTOR aPos, VECTOR aSize, VECTOR bPos, VECTOR bSize);

	//円形：それぞれの座標と半径
	static bool Circlr(int aX, int aY, int aR, int bX, int bY, int bR);

	//円形(3D)：それぞれの座標と半径
	static bool Circlr3D(VECTOR aPos, float aR, VECTOR bPos, float bR);
};