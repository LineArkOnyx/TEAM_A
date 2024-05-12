#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"
#include <math.h>

#define LOGO	"data/Title/TitleLogo.png"		// ���S
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

	m_Blend[0] = { 255 };				// ���ߗp�ϐ�
	m_Blend[1] = { 255 };
	m_Direction[0] = { 1 }; 			// ���ߕ����̕ύX
	m_Direction[1] = { 1 };
	m_BlendSpeed[0] = { 2 }; 			// ���߃X�s�[�h
	m_BlendSpeed[1] = { 15 };

	m_posX = m_effectrand;
	m_posY = SCREEN_SIZE_Y;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_posX2[i] = m_posX;
		m_posY2[i] = m_posY;
		m_speed[i] = EFFECT_SPEED;
		m_angle[i] = (2 * M_PI / EFFECT_NUM) * i;
	}
	m_gravity = GRAVITY;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_gravity2[i] = m_gravity;
	}

	m_R = 255;
	m_G = 0;
	m_B = 0;
	m_ColorSpeed = 15;

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�ʏ폈��
void Title::Step()
{
	// �G�t�F�N�g����
	m_gravity -= 0.1f;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_gravity2[i] += 0.1f;
	}
	m_posY -= 10.0f + m_gravity;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_posX2[i] += cos(m_angle[i]/m_gravity) * m_speed[i];
		m_posY2[i] += sin(m_angle[i]/m_gravity) * m_speed[i];
	}
	// �g�U�O����
	if (m_posY < -10.0f || m_posY > SCREEN_SIZE_Y) {
		m_effectrand = GetRand(SCREEN_SIZE_X - 10);
		m_posX = m_effectrand;
		m_gravity = GRAVITY;
		for (int i = 0; i < EFFECT_NUM; i++) {
			m_gravity2[i] = m_gravity;
		}
		m_posY = SCREEN_SIZE_Y;
	}
	// �g�U�㏈��
	if (m_gravity >= -10.0f) {
		for (int i = 0; i < EFFECT_NUM; i++) {
			m_posX2[i] = m_posX;
			m_posY2[i] = m_posY;
		}
	}

	// ������
	if (m_R == 255 && m_G == 0 && m_B < 255) {
		m_B += m_ColorSpeed;
	}
	else if (m_R > 0 && m_G == 0 && m_B == 255) {
		m_R -= m_ColorSpeed;
	}
	else if (m_R == 0 && m_G < 255 && m_B == 255) {
		m_G += m_ColorSpeed;
	}
	else if (m_R == 0 && m_G == 255 && m_B > 0) {
		m_B -= m_ColorSpeed;
	}
	else if (m_R < 255 && m_G == 255 && m_B == 0) {
		m_R += m_ColorSpeed;
	}
	else if (m_R == 255 && m_G > 0 && m_B == 0) {
		m_G -= m_ColorSpeed;
	}
	// 0��255�����Ȃ��悤����
	if (m_R < 0) {
		m_R = 0;
	}
	else if (m_R > 255) {
		m_R = 255;
	}
	else if (m_G < 0) {
		m_G = 0;
	}
	else if (m_G > 255) {
		m_G = 255;
	}
	else if (m_B < 0) {
		m_B = 0;
	}
	else if (m_B > 255) {
		m_B = 255;
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
		DrawBox(m_posX, m_posY, m_posX + 10, m_posY + 10, GetColor(m_R, m_G, m_B), true);

	for (int i = 0; i < EFFECT_NUM; i++) {
		DrawBox(m_posX2[i], m_posY2[i], m_posX2[i] + 10, m_posY2[i] + 10, GetColor(m_R, m_G, m_B), true);
	}

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
	//DeleteGraph(m_hndl[0]);
	//DeleteGraph(m_hndl[1]);
	//DeleteGraph(m_hndl[2]);

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
