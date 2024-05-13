#include"DxLib.h"
#include"Scene.h"
#include"Title/Title.h"
#include"Play/Play.h"
#include"Result/Result.h"
#include"../Map/MapEditor.h"
#include"../Character/Character.h"
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

Title title;
Play play;
Result result;
MapEditor mapeditor;
int EMouseBufX = 0;
int EMouseBufY = 0;

void Scene()
{
	switch (g_CurrentSceneID)
	{
		//�^�C�g���V�[��������
	case SCENE_ID_INIT_TITLE:

		Effect::Init();
		Effect::Load(EFFECT_TYPE_ITEM,10);
		Effect::Load(EFFECT_TYPE_DAMAGE,10);
		Effect::Load(EFFECT_TYPE_BLOCK,10);
		Effect::Load(EFFECT_TYPE_BREAK,10);
		
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
		Effect::Step();

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

		Effect::Fin();

		break;

//===========================================

		//�G�f�B�^�V�[������������
	case SCENE_ID_INIT_EDITOR:

		mapeditor.Init();

		break;

		//�G�f�B�^�V�[���ʏ폈��
	case SCENE_ID_LOOP_EDITOR:
		GetMousePoint(&EMouseBufX, &EMouseBufY);
		mapeditor.Loop(&EMouseBufX, &EMouseBufY);
		mapeditor.Draw();

		break;

		//�G�f�B�^�V�[���I������
	case SCENE_ID_FIN_EDITOR:
		mapeditor.Exit();

		break;
	}
}
