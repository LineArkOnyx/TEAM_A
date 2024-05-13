#include"DxLib.h"
#include"gameover.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//������
void Gameover::Init()
{
	m_hndl = LoadGraph("data/GameOver/GAMEOVER�摜.png");
	over1 = LoadGraph("data/GameOver/Gameover1.png");
	over2 = LoadGraph("data/GameOver/Gameover2.png");

	m_Blend = 255;		// ���ߗp�ϐ�
	m_Direction = 1;	// ���ߕ����̕ύX
	m_BlendSpeed = 15;	// ���߃X�s�[�h

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_GAMEOVER;
}

//�ʏ폈��
void Gameover::Step()
{

	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_GAMEOVER;
}

//�`�揈��
void Gameover::Draw()
{
	DrawGraph(0, 0, m_hndl, true);

	//�_�ŏ���
	rogocount++;
	if (rogocount <= 79) {
		DrawGraph(330, 300, over1, true);    //��ڂ�`��
	}
	if (rogocount >= 80) {
		DrawGraph(330, 300, over2, true);    //��ڂ�`��
	}
	if (rogocount >= 160) {
		rogocount = 0;    //�J�E���g��߂�
	}

	// ���ߏ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Blend);
	DrawFormatString(SCREEN_SIZE_X / 2.3, SCREEN_SIZE_Y / 1.125, GetColor(0, 255, 255), "Push Enter Key");
	m_Blend -= m_Direction * m_BlendSpeed;
	if (m_Blend <= 0 && m_Direction == 1)
	{
		m_Direction = -1;
	}
	else if (m_Blend >= 255 && m_Direction == -1)
	{
		m_Direction = 1;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

//�I������
void Gameover::Fin()
{
	DeleteGraph(m_hndl);
	rogocount = 0;    //�J�E���g��߂�

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}