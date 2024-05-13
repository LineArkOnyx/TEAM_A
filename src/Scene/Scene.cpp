#include"DxLib.h"
#include"Scene.h"
#include"Title/Title.h"
#include"Play/Play.h"
#include"Result/Result.h"
#include"Gameover/gameover.h"
#include"../Map/MapEditor.h"
#include"../Character/Character.h"
#include"../Sound/Sound.h"
SCENE_ID g_CurrentSceneID = SCENE_ID_INIT_TITLE;

Title title;
Play play;
Result result;
Gameover gameover;
MapEditor mapeditor;
int EMouseBufX = 0;
int EMouseBufY = 0;

void Scene()
{
	switch (g_CurrentSceneID)
	{
		//タイトルシーン初期化
	case SCENE_ID_INIT_TITLE:

		Effect::Init();
		Effect::Load(EFFECT_TYPE_ITEM,10);
		Effect::Load(EFFECT_TYPE_DAMAGE,10);
		Effect::Load(EFFECT_TYPE_BLOCK,10);
		Effect::Load(EFFECT_TYPE_BREAK,10);

		Sound::Init();
		
		title.Init();

		break;

		//タイトルシーン通常処理
	case SCENE_ID_LOOP_TITLE:

		title.Step();
		title.Draw();
		Sound::Bgm::Play(BGM_TITLE);

		break;

		//タイトルシーン終了処理
	case SCENE_ID_FIN_TITLE:
		Sound::Fin();
		title.Fin();

		break;

//===========================================

		//プレイシーン初期化
	case SCENE_ID_INIT_PLAY:
		play.Init();
		Sound::Init();

		break;
		//プレイシーン通常処理
	case SCENE_ID_LOOP_PLAY:
		play.Step();
		Effect::Step();
		Sound::Bgm::Play(BGM_PLAY);

		play.Draw();
		break;
		//プレイシーン終了処理
	case SCENE_ID_FIN_PLAY:
		Sound::Fin();
		Sound::Bgm::StopSound(BGM_PLAY);
		play.Fin();

		break;

//===========================================

		//リザルトシーン初期化処理
	case SCENE_ID_INIT_RESULT:

		result.Init();
		Sound::Init();

		break;

		//リザルトシーン通常処理
	case SCENE_ID_LOOP_RESULT:

		result.Step();
		result.Draw();
		Sound::Bgm::Play(BGM_RESULT);

		break;

		//リザルトシーン終了処理
	case SCENE_ID_FIN_RESULT:

		result.Fin();

		Effect::Fin();
		Sound::Bgm::StopSound(BGM_RESULT);
		Sound::Fin();

		break;

//===========================================

	//ゲームオーバー初期化処理
	case SCENE_ID_INIT_GAMEOVER:

		gameover.Init();
		Sound::Init();

		break;

		//ゲームオーバー通常処理
	case SCENE_ID_LOOP_GAMEOVER:

		gameover.Step();
		gameover.Draw();
		Sound::Bgm::Play(BGM_GAMEOVER);
		Sound::Bgm::StopSound(BGM_PLAY);

		break;

		//ゲームオーバー終了処理
	case SCENE_ID_FIN_GAMEOVER:

		gameover.Fin();

		Effect::Fin();
		Sound::Bgm::StopSound(BGM_GAMEOVER);
		Sound::Fin();

		break;

//===========================================

		//エディタシーン初期化処理
	case SCENE_ID_INIT_EDITOR:

		mapeditor.Init();

		break;

		//エディタシーン通常処理
	case SCENE_ID_LOOP_EDITOR:
		GetMousePoint(&EMouseBufX, &EMouseBufY);
		mapeditor.Loop(&EMouseBufX, &EMouseBufY);
		mapeditor.Draw();

		break;

		//エディタシーン終了処理
	case SCENE_ID_FIN_EDITOR:
		mapeditor.Exit();

		break;
	}
}
