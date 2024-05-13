#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include"../../Character/Character.h"
#include"../../Map/Map.h"
//������
void Play::Init()
{
	//�L�����̏�����
	character.Init();
	//�}�b�v�̏�����
	map.Init();
	backgroundMapchip.Init();
	anime.Init();
	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{
	character.Step();
	anime.Step();
	if (Input::Key::Keep(KEY_INPUT_LSHIFT) && Input::Key::Push(KEY_INPUT_M)) {
		g_CurrentSceneID = SCENE_ID_INIT_EDITOR;
	}
}

//�`�揈��
void Play::Draw()
{
	backgroundMapchip.Draw();
	map.Draw();
	Effect::Draw();
	character.Draw();
}

//�I������
void Play::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
