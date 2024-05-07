#pragma once
#include"DxLib.h"
class Character
{
private:
	int  h, w, handle;
	float x, y,Next_x,Next_y, Gravity_Speed, ScreenX, ScreenY, HitSquareX, HitSquareY;
	bool JunpFrag;
public:
	void Init();		//������
	void Move();		//�ړ�����
	void Gravity();		//�d��
	void Draw();		//�`��
	void Update();		//�A�b�v�f�[�g
	void StepScreen();
	void GetMoveDirection(bool* _dirArray);		//���E�㉺�̓����蔻��
	void StepHitSquare();					//�����蔻��𒲐߂���ʒu
	void Junp();
	void Step();		//�����ɂ܂Ƃ߂�
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
	int GetHitSquareX() { return HitSquareX; }
	int GetHitSquareY() { return HitSquareY; }
	int SetJunpFrag() { JunpFrag = false; return JunpFrag; }
};
extern Character character;