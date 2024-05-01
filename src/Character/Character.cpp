#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "a" };		//�����ɃL�����̃p�X������
const float MOVE_SPEED = 5;	//�L�����̈ړ��X�s�[�h
const float GRAVITY_SPEED = 1;		//�d��
const float GRAVITY_LIMIT = 5;		//�d�͂̍ő�l
void Character::Init()		//������
{
	x = 0.0f;
	y = 0.0f;
	h = 64;
	w = 32;
	Next_x = x;
	Next_y = y;
	Gravity_Speed = 0.0f;
	handle = LoadGraph(CHARACTER_PATH);
}
void Character::Move()		//�ړ�����
{
	if (Input::Key::Keep(KEY_INPUT_A))
	{
		Next_x -= MOVE_SPEED;
	}
	if (Input::Key::Keep(KEY_INPUT_D))
	{
		Next_x += MOVE_SPEED;
	}
}
void Character::Gravity()	//�d�͏���
{
	Gravity_Speed += GRAVITY_SPEED;
	if (Gravity_Speed > GRAVITY_LIMIT)
	{
		Gravity_Speed = GRAVITY_LIMIT;
		Next_y += Gravity_Speed;
	}
	else
	{
		Next_y += Gravity_Speed;
	}
}	
void Character::Draw()		//�`��
{
	DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawRotaGraph(x, y, 1.0, 0.0, handle, true);
}
void Character::Update()
{
	x = Next_x;
	y = Next_y;
}
void Character::Step()		//�����ɂ܂Ƃ߂�
{
	Move();
	Gravity();
	Update();
}