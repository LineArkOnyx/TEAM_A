#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//������
void Title::Init()
{

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//�ʏ폈��
void Title::Step()
{
	m_hndl = LoadGraph("data/Title/��Title.png");
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//�`�揈��
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl, true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//�I������
void Title::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
