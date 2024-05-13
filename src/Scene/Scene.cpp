#include"DxLib.h"
#include"Scene.h"
#include"Title/Title.h"
#include"Play/Play.h"
#include"Result/Result.h"
#include"../Character/Character.h"
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

Title title;
Play play;
Result result;

void Scene()
{
	switch (g_CurrentSceneID)
	{
		//タイトルシーン初期化
	case SCENE_ID_INIT_TITLE:

		Effect::Init();
		Effect::Load(EFFECT_TYPE_ITEM,10);
		Effect::Load(EFFECT_TYPE_DAMAGE,10);
		Effect::Load(EFFECT_TYPE_BREAK,10);
		
		title.Init();

		break;

		//タイトルシーン通常処理
	case SCENE_ID_LOOP_TITLE:

		title.Step();
		title.Draw();

		break;

		//タイトルシーン終了処理
	case SCENE_ID_FIN_TITLE:

		title.Fin();

		break;

//===========================================

		//プレイシーン初期化
	case SCENE_ID_INIT_PLAY:
		play.Init();

		break;
		//プレイシーン通常処理
	case SCENE_ID_LOOP_PLAY:
		play.Step();
		Effect::Step();

		play.Draw();
		break;
		//プレイシーン終了処理
	case SCENE_ID_FIN_PLAY:

		play.Fin();

		break;

//===========================================

		//リザルトシーン初期化処理
	case SCENE_ID_INIT_RESULT:

		result.Init();

		break;

		//リザルトシーン通常処理
	case SCENE_ID_LOOP_RESULT:

		result.Step();
		result.Draw();

		break;

		//リザルトシーン終了処理
	case SCENE_ID_FIN_RESULT:

		result.Fin();

		Effect::Fin();

		break;
	}
}
