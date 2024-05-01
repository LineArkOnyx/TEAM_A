#pragma once
#include"DxLib.h"
class Character
{
private:
	int  h, w, handle;
	float x, y,Next_x,Next_y, Gravity_Speed;
public:
	void Init();		//初期化
	void Move();		//移動処理
	void Gravity();		//重力
	void Draw();		//描画
	void Update();		//アップデート
	void Step();		//ここにまとめる
};
extern Character character;