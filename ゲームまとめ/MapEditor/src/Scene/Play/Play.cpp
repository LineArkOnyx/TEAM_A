#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"


//������
void Play::Init()
{
	mapeditor.Init();
	MousePointBufX = 0;
	MousePointBufY = 0;
	
	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//�ʏ폈��
void Play::Step()
{
	mapeditor.Loop(&MousePointBufX,&MousePointBufY);

}

//�`�揈��
void Play::Draw()
{
	mapeditor.Draw();
}

//�I������
void Play::Fin()
{
	
	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
