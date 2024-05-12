#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

#define LOGO	"data/Title/��TitleLogo.png"	// ���S
#define BACK	"data/Title/DaytimeBack.png"	// �w�i
#define BACK2	"data/Title/NightBack.png"		// �w�i.��
#define SKY		"data/Title/DaytimeSky.png"		// ��
#define SKY2	"data/Title/NightSky.png"		// ��

#define GRAVITY	0.05f							// �d�͂̒l

//������
void Title::Init()
{
	m_backrand = GetRand(1);	// ����0�`1
	m_effectrand = GetRand(SCREEN_SIZE_X - 10);

	m_posX = m_effectrand;
	m_posY = SCREEN_SIZE_Y;
	m_gravity = GRAVITY;

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�ʏ폈��
void Title::Step()
{
	// �w�i�����_��
	if (m_backrand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// ��
		m_hndl[1] = LoadGraph(BACK);	// �w�i
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// ���
		m_hndl[1] = LoadGraph(BACK2);	// �w�i
	}
	m_hndl[2] = LoadGraph(LOGO);		// ���S

	// �G�t�F�N�g����
	m_gravity -= 0.1f;
	m_posY -= 10.0f + m_gravity;
	if (m_posY < -10.0f || m_posY > SCREEN_SIZE_Y) {
		m_effectrand = GetRand(SCREEN_SIZE_X - 10);
		m_posX = m_effectrand;
		m_gravity = GRAVITY;
		m_posY = SCREEN_SIZE_Y;
	}
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//�`�揈��
void Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_hndl[0], true);			// ��
	DrawGraph(0, 0, m_hndl[1], true);			// �w�i

	// �G�t�F�N�g����
	if (m_gravity >= -10.0f)
		DrawBox(m_posX, m_posY, m_posX + 10, m_posY + 10, GetColor(0, 255, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

	// ���ߏ���
	for (int i = 0; i < 2; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Blend[i]);
		if (i == 0) {
			DrawGraph(0, 0, m_hndl[2], true);	// ���S
		}
		else {
			DrawFormatString(SCREEN_SIZE_X / 2.3, SCREEN_SIZE_Y / 1.125, GetColor(255, 0, 255), "Push Enter Key");
		}

		m_Blend[i] -= m_Direction[i] * m_BlendSpeed[i];
		if (m_Blend[i] <= 0 && m_Direction[i] == 1)
		{
			m_Direction[i] = -1;
		}
		else if (m_Blend[i] >= 255 && m_Direction[i] == -1)
		{
			m_Direction[i] = 1;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

//�I������
void Title::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
