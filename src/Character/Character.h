#pragma once
#include"DxLib.h"
class Character
{
private:
	int  h, w, handle;
	float x, y,Next_x,Next_y, Gravity_Speed;
public:
	void Init();		//������
	void Move();		//�ړ�����
	void Gravity();		//�d��
	void Draw();		//�`��
	void Update();		//�A�b�v�f�[�g
	void Step();		//�����ɂ܂Ƃ߂�
};
extern Character character;