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
const float GRAVITY_LIMIT = 8;		//�d�͂̍ő�l
const float JUNP_LIMIT = 30;		//�W�����v���o����ő�l
const float JUNPPOWER = 28;
//const float CONBER
void Character::Init()		//������
{
	x = 800.0f;			//X���W
	y = 768.0f;			//Y���W
	h = 64;				//�c��
	w = 32;				//����
	Next_x = x;			//X���W�̑O�̃t���[������肽��
	Next_y = y;			//Y���W�̑O�̃t���[������肽��
	Gravity_Speed = 0.0f;//�d��
	ScreenX = x - SCREEN_SIZE_X / 2;
	ScreenY = 239;						//Y���W�̃X�N���[��Y���W
	handle = LoadGraph(CHARACTER_PATH);		//���[�h
	JunpFrag = false;
	DebugFrag = false;
	ladderActiv = false;
	turn = true;
	UpJunpTrapFrag = true;
	sideLeftJunpTrapFrag = true;
	status = PL_NORMAL;
}
void Character::Move()		//�ړ�����
{
	if (DebugFrag == false)
	{
		if (Input::Key::Keep(KEY_INPUT_A))	//A�L�[����������true
		{
			Next_x -= MOVE_SPEED;

			turn = false;

			if(status!=PL_JUMP)
			{
				status = PL_MOVE;
			}
		}
		if (Input::Key::Keep(KEY_INPUT_D)) //D�L�[����������true
		{
			Next_x += MOVE_SPEED;

			turn = true;

			if (status != PL_JUMP)
			{
				status = PL_MOVE;
			}
		}
		if (JunpFrag == false)
		{
			//�W�����v�����Ă��Ȃ��Ă΂˂ɏ������W�����v�ł���
			if (UpJunpTrapFrag == false)
			{
				if (Input::Key::Push(KEY_INPUT_UP))
				{
					Gravity_Speed -= JUNPPOWER-10;
					JunpFrag = true;

					status = PL_JUMP;
				}
			}
			
		}
		//	�K�i���I���Ȃ����
		if (ladderActiv == true)
		{
			if (Input::Key::Keep(KEY_INPUT_UP))	//A�L�[����������true
			{
				Next_y -= MOVE_SPEED;
			}
			if (Input::Key::Keep(KEY_INPUT_S))	//A�L�[����������true
			{
				Next_y += MOVE_SPEED;
			}

		}
		//�ړ���Ԃŗ�������ҋ@��ԂɂȂ�
		if(status == PL_MOVE)
		{
			if (Input::Key::Release(KEY_INPUT_A) || Input::Key::Release(KEY_INPUT_D))
			{
				status = PL_NORMAL;
			}
		}
	}
}
void Character::DebugSwaitch()
{
	if (Input::Key::Push(KEY_INPUT_P))
	{
		DebugFrag = true;
	}
	if (Input::Key::Push(KEY_INPUT_O))
	{
		DebugFrag = false;
	}
	if (DebugFrag == false)
	{
		DrawFormatString(0, 105, GetColor(255, 255, 255), "�v���C���[�h");
	}
	if (DebugFrag == true)
	{
		DrawFormatString(0, 105, GetColor(255, 255, 255), "�f�o�b�O���[�h");
	}
}
void Character::Junp()
{
	if (DebugFrag == false)
	{
		if (JunpFrag == false)
		{
			if (Input::Key::Push(KEY_INPUT_UP))
			{
				Gravity_Speed -= JUNPPOWER;
				JunpFrag = true;

				status = PL_JUMP;
			}
		}
	}
}
void Character::UpJunpTrap()
{
	//��񂵂��ł��Ȃ�����
	if (character.UpJunpTrapFrag == true)
	{
		UpJunpTrapFrag = false;
		Gravity_Speed -= JUNPPOWER;
	}
}
void Character::DebugMove()
{
	if (DebugFrag == true)
	{
		if (Input::Key::Keep(KEY_INPUT_A))	//A�L�[����������true
		{
			Next_x -= MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_D)) //D�L�[����������true
		{
			Next_x += MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_UP))	//A�L�[����������true
		{
			Next_y-= MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_S))	//A�L�[����������true
		{
			Next_y += MOVE_SPEED;
		}
	}
}
void Character::Gravity()	//�d�͏���
{
	if (DebugFrag == false)
	{
		//��q�t���O���U�Ȃ�d�͂�����
		if (ladderActiv == false)
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
			//�΂˂ƃW�����v�����ɉ����Ɛ�����Ԃ��琧��
			if (Gravity_Speed <-JUNP_LIMIT)
			{
				Gravity_Speed = -JUNP_LIMIT;
			}
		}
		else
		{
			ladderActiv = false;
			Gravity_Speed = 0.0f;
		}
	}
	
}	
void Character::Draw()		//�`��
{
	DrawBox(x - ScreenX, y - ScreenY, x + w - ScreenX, y + h - ScreenY, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawFormatString(0, 75, GetColor(255, 255, 255), "JunpFrag = %d", JunpFrag); 
	DrawFormatString(0, 90, GetColor(255, 255, 255), "DebugFrag = %d", DebugFrag);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "ScreenX = %0.2f", ScreenX);
	DrawFormatString(0, 135, GetColor(255, 255, 255), "ScreenY = %0.2f", ScreenY);
	DrawFormatString(0, 150, GetColor(255, 255, 255), "ladderActiv = %d", ladderActiv); 
	DrawFormatString(0, 165, GetColor(255, 255, 255), "UpJunpTrapFrag = %d", UpJunpTrapFrag);
	DrawRotaGraph(x+w/2- ScreenX, y+h/2- ScreenY, 1.0, 0.0, handle, true);		//�L�����N�^�[�`��

	anime.Draw(x + w / 2 - ScreenX, y + h / 2 - ScreenY, animaHandle, 1.0, 0.0, turn);
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
	DebugSwaitch();
	Move();
	DebugMove();
	Gravity();
	/*Junp();*/

	StepScreen();
	playSceen.Step();
	Update();

	ChangeAnima();
}
void Character::StepScreen()
{
	/*if (ScreenX >= 0&& ScreenX<=2000)*/
	{
		ScreenX = x - SCREEN_SIZE_X / 2;
	}
	
	ScreenY = 239;						//Y���W�̃X�N���[��Y���W
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
void Character::UnderConveyorPower()
{
	character.Next_x-= 3;
}
void Character::UpConveyorPower()
{
	character.Next_x += 3;
}
void Character::ChangeAnima()
{
	switch (status)
	{
	case PL_NORMAL:
		anime.SetType(ANIME_NORMAL, &animaHandle);
		break;

	case PL_MOVE:
		anime.SetType(ANIME_MOVE, &animaHandle);
		break;

	case PL_JUMP:
		anime.SetType(ANIME_JUMP, &animaHandle);
		break;

	default:
		break;
	}
}