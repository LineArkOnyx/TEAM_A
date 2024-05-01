#pragma once
#include"DxLib.h"
class Character
{
private:
	int x, y, h, w, handle, Gravity_Speed;
public:
	void Init();
	void Move();
	void Gravity();
	void Draw();
	void Step();
};