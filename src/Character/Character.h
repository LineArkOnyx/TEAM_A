#pragma once
#include"DxLib.h"
class Character
{
private:
	int  h, w, handle;
	float x, y,Next_x,Next_y, Gravity_Speed, ScreenX, ScreenY, HitSquareX, HitSquareY;
	bool JunpFrag,DebugFrag;
public:
	void Init();		//初期化
	void Move();		//移動処理
	void Gravity();		//重力
	void Draw();		//描画
	void Update();		//アップデート
	void StepScreen();
	void GetMoveDirection(bool* _dirArray);		//左右上下の当たり判定
	void StepHitSquare();					//当たり判定を調節する位置
	void Junp();
	void Step();		//ここにまとめる
	void DebugMove();		//デバッグ用の操作
	void DebugSwaitch();
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetW() { return w; }
	int GetH() { return h; }
	int GetScreenX() { return ScreenX; }
	int GetScreenY() { return ScreenY; }
	int GetNextPosX() { return Next_x; }
	int GetNextPosY() { return Next_y; }
	int SetPosX(int a) { x = a; return x; }
	int SetPosY(int a) { y = a; return y; }
	int SetNextPosX(int a) { Next_x = a; return Next_x; }
	int SetNextPosY(int a) { Next_y = a; return Next_y; }
	int SetGravitySpeed(float a) { Gravity_Speed =a; return Gravity_Speed; }
	int GetHitSquareX() { return HitSquareX; }
	int GetHitSquareY() { return HitSquareY; }
	int SetJunpFrag() { JunpFrag = false; return JunpFrag; }
};
extern Character character;