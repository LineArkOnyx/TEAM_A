#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"

//������
void Play::Init()
{

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{


}

//�`�揈��
void Play::Draw()
{

}

//�I������
void Play::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
