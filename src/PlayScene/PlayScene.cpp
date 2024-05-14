#include"DxLib.h"
#include"PlayScene.h"
#include"../Character/Character.h"
#include"../Map/Map.h"
#include"../MathPlus/MathPlus.h"
#include"../Scene/Scene.h"
#include"../Sound/Sound.h"
const int SQUARE_Y = 5;		//���݂̈ʒu����Y���̓����蔻��͈̔͂�ݒ肷��
const int SQUARE_X = 10;	//���݂̈ʒu����X���̓����蔻��͈̔͂�ݒ肷��
const int SQUARE_Y_MAX = 27;	//�ǂ��܂œ����蔻�����邩
const int SQUARE_Y_LOWEST = 1;	//�ǂ��܂œ����蔻�����邩
const int SQUARE_X_MAX = 100;	//�ǂ��܂œ����蔻�����邩
const int SQUARE_X_LOWEST = 0;	//�ǂ��܂œ����蔻�����邩
PlaySceen playSceen;
void PlaySceen::Character_Hit_Map()
{
	character.StepHitSquare();
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//�z��𒴂�����
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//�z��𒴂�����
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			if(character.GetHitSquareX()> SQUARE_X_MAX)
				continue;
			//�z��𒴂�����
			if (character.GetHitSquareX() < SQUARE_X_LOWEST)
				continue;
			// ���������l����
			// �ǂ̕����ɐi��ł������`�F�b�N
			// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B
			DrawFormatString(0, 48, GetColor(255, 255, 255), "StepHitSquareY=%d", character.GetHitSquareY());
			DrawFormatString(0, 64, GetColor(255, 255, 255), "StepHitSquareX=%d", character.GetHitSquareX());
			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ���������l����
			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// �I�u�W�F�N�g�̏��
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			if (MapChipData[y][x] == -1|| MapChipData[y][x] == 40 || MapChipData[y][x] == 41 || MapChipData[y][x] == 46 ||  MapChipData[y][x] == 50 || MapChipData[y][x] == 43 || MapChipData[y][x] == 44 || MapChipData[y][x] == 45 || MapChipData[y][x] == 51 || MapChipData[y][x] == 52 || MapChipData[y][x] == 53 || MapChipData[y][x] == 54 || MapChipData[y][x] == 55 || MapChipData[y][x] == 56 || MapChipData[y][x] == 57 || MapChipData[y][x] == 58)
				continue;
			{
				//DrawBox(Bx-(int)character.GetScreenX(), By- (int)character.GetScreenY(), Bx + Bw- (int)character.GetScreenX(), By + Bh- (int)character.GetScreenY(), GetColor(255, 255, 255), false);
				//DrawBox(Ax - (int)character.GetScreenX(), Ay - (int)character.GetScreenY(), Ax + Aw - (int)character.GetScreenX(), Ay + Ah - (int)character.GetScreenY(), GetColor(255, 0, 0), false);

				Ay = (int)character.GetPosY();
				Ax = (int)character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[2]) 
					{
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						int overlap = Bx + Bw - Ax;
						character.SetNextPosX((float)Ax + overlap);
					}
					// �E�����̏C��
					//�}���I�̉E��
					if (dirArray[3]) 
					{
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ax + Aw - Bx;
						character.SetNextPosX((float)Ax - overlap);
					}
				}
			}

		}
	}
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//�z��𒴂�����
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//�z��𒴂�����
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			if (character.GetHitSquareX() > SQUARE_X_MAX)
				continue;
			//�z��𒴂�����
			if (character.GetHitSquareX() < SQUARE_X_LOWEST)
				continue;
			// ���������l����
				// �ǂ̕����ɐi��ł������`�F�b�N
				// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B

			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ���������l����
			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// �I�u�W�F�N�g�̏��
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;

			if (MapChipData[y][x] == -1 || MapChipData[y][x] == 46 || MapChipData[y][x] == 41|| MapChipData[y][x] == 40 || MapChipData[y][x] == 50|| MapChipData[y][x] == 43 || MapChipData[y][x] == 44 || MapChipData[y][x] == 45 || MapChipData[y][x] == 51 || MapChipData[y][x] == 52 || MapChipData[y][x] == 53 || MapChipData[y][x] == 54 || MapChipData[y][x] == 55 || MapChipData[y][x] == 56 || MapChipData[y][x] == 57 || MapChipData[y][x] == 58)
				continue;
			{
				Ay = (int)character.GetNextPosY();
				Ax = (int)character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[0]) {
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						character.SetGravitySpeed(0.0);
						int overlap = By + Bh - Ay;
						character.SetNextPosY(((float)Ay + overlap));
						if (MapChipData[y][x] == 47 || MapChipData[y][x] == 48 || MapChipData[y][x] == 49)
						{
							character.UpConveyorPower();
						}
						if (MapChipData[y][x] == 6)
						{
							MapChipData[y][x] = -1;
							Effect::Play(EFFECT_TYPE_BREAK, Bx - character.GetScreenX(), By - character.GetScreenY());
							Sound::Se::Play(SE_BLOAK_DESTRUCTION);
						}
					}
					// �E�����̏C��
					//�}���I�̉E��
					if (dirArray[1]) 
					{
						if (character.GetStatus() == PL_JUMP)
						{
							character.SetStatus(PL_NORMAL);
						}
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						character.SetJunpFrag();	//���n������W�����v�ł���悤�ɂ���
						character.Junp();			//���n���ĂȂ��ƃW�����v�ł��Ȃ�
						character.SetUpJunpTrapFrag(true);	//���ɒ��n���Ă���΃W�����v����N���ł���
						int overlap = Ay + Ah - By;
						character.SetNextPosY((float)Ay - overlap);
						//�x���g�R���x�A�[�̓����蔻��
						if (MapChipData[y][x] == 47 || MapChipData[y][x] == 48 || MapChipData[y][x] == 49)
						{
							character.UnderConveyorPower();
						}
						else {
							Sound::Se::Stop(SE_KYATAPIRA);   //SE�̒�~
						}
						
					}
				}
			}
		}
	}
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//�z��𒴂�����
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//�z��𒴂�����
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			
			// ���������l����
			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��

			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// �I�u�W�F�N�g�̏��
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			if (MapChipData[y][x] == -1)
				continue; 

			//DrawBox(Bx - (int)character.GetScreenX(), By - (int)character.GetScreenY(), Bx + Bw - (int)character.GetScreenX(), By + Bh - (int)character.GetScreenY(), GetColor(255, 0, 255), false);
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
			{
				//�͂����̓����蔻��
				if (MapChipData[y][x] == 46)
				{	
					//��q�I���t���O��^��
					character.SetladderActiv(true);
				}
				//�΂˂̓����蔻��
				if (MapChipData[y][x] == 41)
				{
					character.UpJunpTrap();
				}
				//�S�[���̓����蔻��
				if (MapChipData[y][x] == 40 || MapChipData[y][x] == 50)
				{
					Sound::Bgm::StopSound(BGM_PLAY);
					Sound::Fin();
					g_CurrentSceneID = SCENE_ID_INIT_RESULT;
				}
				//�g���b�v����
				if (MapChipData[y][x] == 43|| MapChipData[y][x] == 44|| MapChipData[y][x] == 45)
				{
					DrawFormatString(0, 180, GetColor(255, 255, 255), "�g���b�v�q�b�g");

					if (MapChipData[y][x] == 44)
					{
						character.Damage(2);	//�_���[�W���Q�^����
					}
					else
					{
						character.Damage();	//�_���[�W���P�^����
					}
					
				}
				//�������񕜃A�C�e��
				if (MapChipData[y][x] == 58)
				{
					MapChipData[y][x] = -1;
					if (character.GetHp()>0)
					{
						character.SetHp(2);
						Effect::Play(EFFECT_TYPE_ITEM, Bx- character.GetScreenX(), By - character.GetScreenY());
						Sound::Se::Play(SE_EAT);
						Sound::Se::Play(SE_POWER_UP);
					}
					
				}
			}
			
		}
	}
}
void PlaySceen::Step()
{
	Character_Hit_Map();
}