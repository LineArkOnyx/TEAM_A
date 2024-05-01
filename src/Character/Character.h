#pragma once
#include"DxLib.h"
class Character
{
private:
	int  h, w, handle;
	float x, y,Next_x,Next_y, Gravity_Speed;
public:
	void Init();
	void Move();
	void Gravity();
	void Draw();
	void Update();
	void Step();
};
extern Character character;