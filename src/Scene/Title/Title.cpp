#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

#define LOGO	"data/Title/��TitleLogo.png"
#define BACK	"data/Title/DaytimeBack.png"
#define BACK2	"data/Title/NightBack.png"
#define SKY		"data/Title/DaytimeSky.png"
#define SKY2	"data/Title/NightSky.png"

//������
void Title::Init()
{
	m_rand = GetRand(1);	// 0�`1

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�ʏ폈��
void Title::Step()
{
	if (m_rand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// ��
		m_hndl[1] = LoadGraph(BACK);	// �w�i
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// ���
		m_hndl[1] = LoadGraph(BACK2);	// �w�i
	}
	m_hndl[2] = LoadGraph(LOGO);		// ���S
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//�`�揈��
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl[0], true);
	DrawGraph(0, 0, m_hndl[1], true);
	DrawGraph(0, 0, m_hndl[2], true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//�I������
void Title::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
