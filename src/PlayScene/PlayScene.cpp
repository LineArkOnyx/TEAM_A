#include"DxLib.h"
#include"PlayScene.h"
#include"../Character/Character.h"
#include"../Map/Map.h"
#include"../MathPlus/MathPlus.h"
const int SQUARE_Y = 5;		//���݂̈ʒu����Y���̓����蔻��͈̔͂�ݒ肷��
const int SQUARE_X = 10;	//���݂̈ʒu����X���̓����蔻��͈̔͂�ݒ肷��
const int SQUARE_Y_MAX = 27;	//�ǂ��܂œ����蔻�����邩
const int SQUARE_Y_LOWEST = 1;	//�ǂ��܂œ����蔻�����邩
PlaySceen playSceen;
void PlaySceen::Character_Hit_Map()
{
	character.StepHitSquare();
	for (int y = character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//�z��𒴂�����
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//�z��𒴂�����
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
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
			int Ax = character.GetPosX();
			int Ay = character.GetPosY();
			int Aw = character.GetW();
			int Ah = character.GetH();

			// �I�u�W�F�N�g�̏��
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			if (MapChipData[y][x] == -1)
				continue;
			{
				DrawBox(Bx-character.GetScreenX(), By- character.GetScreenY(), Bx + Bw- character.GetScreenX(), By + Bh- character.GetScreenY(), GetColor(255, 255, 255), false);
				DrawBox(Ax - character.GetScreenX(), Ay - character.GetScreenY(), Ax + Aw - character.GetScreenX(), Ay + Ah - character.GetScreenY(), GetColor(255, 0, 0), false);

				Ay = character.GetPosY();
				Ax = character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[2]) {
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						int overlap = Bx + Bw - Ax;
						character.SetNextPosX(Ax + overlap);
					}
					// �E�����̏C��
					//�}���I�̉E��
					if (dirArray[3]) {
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						int overlap = Ax + Aw - Bx;
						character.SetNextPosX(Ax - overlap);
					}
				}
			}

		}
	}
	for (int y = character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//�z��𒴂�����
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//�z��𒴂�����
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			// ���������l����
				// �ǂ̕����ɐi��ł������`�F�b�N
				// ��Player�N���X�ɐi�ޕ������`�F�b�N����֐����������Ă��܂��B

			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ���������l����
			// ��`�̓����蔻��p�̃f�[�^������
			// �v���C���[�̏��
			int Ax = character.GetPosX();
			int Ay = character.GetPosY();
			int Aw = character.GetW();
			int Ah = character.GetH();

			// �I�u�W�F�N�g�̏��
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;

			if (MapChipData[y][x] == -1)
				continue;
			{
				Ay = character.GetNextPosY();
				Ax = character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[0]) {
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						int overlap = By + Bh - Ay;
						character.SetNextPosY((Ay + overlap));
						character.SetGravitySpeed(0.0f);
					}
					// �E�����̏C��
					//�}���I�̉E��
					if (dirArray[1]) {
						// ���������l����
						// �߂荞�ݗʂ��v�Z����
						character.SetJunpFrag();	//���n������W�����v�ł���悤�ɂ���
						character.Junp();			//���n���ĂȂ��ƃW�����v�ł��Ȃ�
						int overlap = Ay + Ah - By;
						character.SetNextPosY(Ay - overlap);
						
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