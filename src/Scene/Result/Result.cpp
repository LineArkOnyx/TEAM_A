#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"

//������
void Result::Init()
{

	//�ʏ폈���ֈړ�
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//�ʏ폈��
void Result::Step()
{


}

//�`�揈��
void Result::Draw()
{

}

//�I������
void Result::Fin()
{

	//���̃V�[���Ɉړ�
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
