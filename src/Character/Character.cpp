#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "data/play/��player64�~32.png" };		//�����ɃL�����̃p�X������
const float MOVE_SPEED = 5;	//�L�����̈ړ��X�s�[�h
const float GRAVITY_SPEED = 1;		//�d��
const float GRAVITY_LIMIT = 5;		//�d�͂̍ő�l
void Character::Init()		//������
{
	x = 0.0f;			//X���W
	y = 0.0f;			//Y���W
	h = 64;				//�c��
	w = 32;				//����
	Next_x = x;			//X���W�̑O�̃t���[������肽��
	Next_y = y;			//Y���W�̑O�̃t���[������肽��
	Gravity_Speed = 0.0f;//�d��
	handle = LoadGraph(CHARACTER_PATH);		//���[�h
}
void Character::Move()		//�ړ�����
{
	if (Input::Key::Keep(KEY_INPUT_A))	//A�L�[����������true
	{
		Next_x -= MOVE_SPEED;
	}
	if (Input::Key::Keep(KEY_INPUT_D)) //D�L�[����������true
	{
		Next_x += MOVE_SPEED;
	}
}
void Character::Gravity()	//�d�͏���
{
	Gravity_Speed += GRAVITY_SPEED;		//�d�͂�����
	if (Gravity_Speed > GRAVITY_LIMIT)	//GRAVITY_LIMIT�𒴂����true
	{
		Gravity_Speed = GRAVITY_LIMIT;
		Next_y += Gravity_Speed;
	}
	else	//GRAVITY_LIMIT�𒴂��Ă��Ȃ�����true
	{
		Next_y += Gravity_Speed;
	}
}	
void Character::Draw()		//�`��
{
	DrawBox(x, y, x + w, y + h, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);

	DrawRotaGraph(x+w/2, y+h/2, 1.0, 0.0, handle, true);		//�L�����N�^�[�`��
}
void Character::Update()		//�A�b�v�f�[�g
{	
	x = Next_x;		//�v�Z�����l������
	y = Next_y;		//�v�Z�����l������
}
void Character::Step()		//�����ɂ܂Ƃ߂�
{
	Move();
	Gravity();
	Update();
}