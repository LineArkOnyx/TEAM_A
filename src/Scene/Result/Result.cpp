#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//������
void Result::Init()
{

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Result::Step()
{
	m_hndl = LoadGraph("data/GameOver/��Gameover.png");

	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;

}

//�`�揈��
void Result::Draw()
{
	DrawGraph(0, 0, m_hndl, true);
	DrawFormatString(0, 0, GetColor(0, 255, 255), "Push Enter Key");

}

//�I������
void Result::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
