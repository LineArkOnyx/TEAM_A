#pragma once
#include"DxLib.h"

const float MUTEKI_TIME = 2.5f;	//���G����
const float MUTEKI_FADE = 0.1f;//�_�ŊԊu

//�v���C���[�̏�� : ���R�Y
enum PL_STATUS
{
	PL_NORMAL,
	PL_MOVE,
	PL_JUMP,
};

class Character
{
private:
	int  h, w, handle,Hp;
	float x, y,Next_x,Next_y, Gravity_Speed, ScreenX, ScreenY, HitSquareX, HitSquareY, ScreenNextX;
	bool JunpFrag
		, DebugFrag
		, ladderActiv			//��q���g���Ă��邩���ǂ������f����
		, UpJunpTrapFrag		//�W�����v������g�p�������m�F
		, sideLeftJunpTrapFrag, 
		sideRightJunpTrapFrag;
							
	//�ȉ����R�Y
	bool turn;	//���E�̔��]
	PL_STATUS status;	//�v���C���[�̏��
	int animaHandle;
	float mutekiCount;	//���G���Ԃ̃J�E���g
	float mutekiFade;	//�_��
	//�ȏ㉪�R�Y
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
	void DebugMove();		//�f�o�b�O�p�̑���
	void DebugSwaitch();
	void UnderConveyorPower();
	void UpConveyorPower();
	void UpJunpTrap();				//�΂˂ɏ��ƃW�����v����
	float GetPosX() { return x; }
	float GetPosY() { return y; }
	int GetW() { return w; }
	int GetH() { return h; }
	float GetScreenX() { return ScreenX; }
	float GetScreenY() { return ScreenY; }
	float GetNextPosX() { return Next_x; }
	float GetNextPosY() { return Next_y; }
	float SetPosX(float a) { x = a; return x; }
	float SetPosY(float a) { y = a; return y; }
	float SetNextPosX(float a) { Next_x = a; return Next_x; }
	float SetNextPosY(float a) { Next_y = a; return Next_y; }
	float SetGravitySpeed(float a) { Gravity_Speed =a; return Gravity_Speed; }
	float GetHitSquareX() { return HitSquareX; }
	float GetHitSquareY() { return HitSquareY; }
	int SetJunpFrag() { JunpFrag = false; return JunpFrag; }
	int SetladderActiv(bool a) { ladderActiv = a; return  ladderActiv; }
	int SetUpJunpTrapFrag(bool a) { UpJunpTrapFrag = a; return  UpJunpTrapFrag; }
	int GetHp() { return Hp; }
	int SetHp(int a) { Hp =a; return Hp; }
	PL_STATUS GetStatus() { return status; }
	void SetStatus(PL_STATUS set) { status = set; }
	void ChangeAnima();
	void Damage(int damage = 1);
	void GameOverFrg();	//�Q�[���I�[�o�[����
	void Dead_or_Alive();
};
extern Character character;