#include"DxLib.h"
#include"Scene.h"
#include"Title/Title.h"
#include"Play/Play.h"
#include"Result/Result.h"

SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_PLAY;

Title title;
Play play;
Result result;

void Scene()
{
	switch (g_CurrentSceneID)
	{
		//�^�C�g���V�[��������
	case SCENE_ID_INIT_TITLE:

		title.Init();

		break;

		//�^�C�g���V�[���ʏ폈��
	case SCENE_ID_LOOP_TITLE:

		title.Step();
		title.Draw();

		break;

		//�^�C�g���V�[���I������
	case SCENE_ID_FIN_TITLE:

		title.Fin();

		break;

//===========================================

		//�v���C�V�[��������
	case SCENE_ID_INIT_PLAY:

		play.Init();

		break;
		//�v���C�V�[���ʏ폈��
	case SCENE_ID_LOOP_PLAY:

		play.Step();
		play.Draw();

		break;
		//�v���C�V�[���I������
	case SCENE_ID_FIN_PLAY:

		play.Fin();

		break;

//===========================================

		//���U���g�V�[������������
	case SCENE_ID_INIT_RESULT:

		result.Init();

		break;

		//���U���g�V�[���ʏ폈��
	case SCENE_ID_LOOP_RESULT:

		result.Step();
		result.Draw();

		break;

		//���U���g�V�[���I������
	case SCENE_ID_FIN_RESULT:

		result.Fin();

		break;
	}
}
