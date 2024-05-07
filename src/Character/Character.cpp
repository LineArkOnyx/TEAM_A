#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
#include"../Scene/Scene.h"
#include"../Map/Map.h"
#include"../PlayScene/PlayScene.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "data/play/��player64�~32.png" };		//�����ɃL�����̃p�X������
const float MOVE_SPEED = 5;	//�L�����̈ړ��X�s�[�h
const float GRAVITY_SPEED = 1;		//�d��
const float GRAVITY_LIMIT = 5;		//�d�͂̍ő�l
const int JUNPPOWER = 22;
void Character::Init()		//������
{
	x = 300.0f;			//X���W
	y = 800.0f;			//Y���W
	h = 64;				//�c��
	w = 32;				//����
	Next_x = x;			//X���W�̑O�̃t���[������肽��
	Next_y = y;			//Y���W�̑O�̃t���[������肽��
	Gravity_Speed = 0.0f;//�d��
	ScreenX = 0.0f;
	ScreenY = 0.0f;
	handle = LoadGraph(CHARACTER_PATH);		//���[�h
	JunpFrag = false;
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
void Character::Junp()
{
	if (JunpFrag == false)
	{
		if (Input::Key::Push(KEY_INPUT_W))
		{
			Gravity_Speed -= JUNPPOWER;
			JunpFrag = true;
		}
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
	DrawBox(x - ScreenX, y - ScreenY, x + w - ScreenX, y + h - ScreenY, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawFormatString(0, 75, GetColor(255, 255, 255), "JunpFrag = %d", JunpFrag);

	DrawRotaGraph(x+w/2- ScreenX, y+h/2- ScreenY, 1.0, 0.0, handle, true);		//�L�����N�^�[�`��
}
void Character::Update()		//�A�b�v�f�[�g
{	
	x = Next_x;		//�v�Z�����l������
	y = Next_y;		//�v�Z�����l������
}
void Character::StepHitSquare()					//�����蔻��𒲐߂���ʒu
{
	HitSquareX = x / 32;
	HitSquareY = y / 32;
}
void Character::Step()		//�����ɂ܂Ƃ߂�
{
	Move();
	Gravity();
	/*Junp();*/
	StepScreen();
	playSceen.Step();
	Update();
}
void Character::StepScreen()
{
	ScreenX = x - SCREEN_SIZE_X / 2;
	ScreenY = y - SCREEN_SIZE_Y / 2;						//Y���W�̃X�N���[��Y���W
}
void Character::GetMoveDirection(bool* _dirArray) 		//���E�㉺�̓����蔻��
{
	// �E�����̃`�F�b�N
	if (Next_x > x) {
		_dirArray[3] = true;
	}
	// �������̃`�F�b�N
	if (Next_x < x) {
		_dirArray[2] = true;
	}
	// �������̃`�F�b�N
	if (Next_y > y) {
		_dirArray[1] = true;
	}
	// �������̃`�F�b�N
	if (Next_y < y) {
		_dirArray[0] = true;
	}
}