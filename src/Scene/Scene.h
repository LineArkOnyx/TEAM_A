#pragma once
#include"../FrameRate/FrameRate.h"
#include"../Input/Input.h"

// define
#define	SCREEN_SIZE_X	800	// X�����̉�ʃT�C�Y���w��
#define	SCREEN_SIZE_Y	600	// Y�����̉�ʃT�C�Y���w��

enum SCENE_ID
{
	//�^�C�g���֘A
	SCENE_ID_INIT_TITLE = 0,
	SCENE_ID_LOOP_TITLE,
	SCENE_ID_FIN_TITLE,

	//�v���C�֘A
	SCENE_ID_INIT_PLAY,
	SCENE_ID_LOOP_PLAY,
	SCENE_ID_FIN_PLAY,

	//�Q�[���N���A�֘A
	SCENE_ID_INIT_RESULT,
	SCENE_ID_LOOP_RESULT,
	SCENE_ID_FIN_RESULT,

};

extern SCENE_ID g_CurrentSceneID;

//�V�[������
void Scene();