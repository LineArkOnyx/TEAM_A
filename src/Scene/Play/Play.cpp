#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include"../../Character/Character.h"
#include"../../Map/Map.h"
//初期化
void Play::Init()
{
	//キャラの初期化
	character.Init();
	//マップの初期化
	map.Init();

	anime.Init();
	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void Play::Step()
{
	character.Step();
	anime.Step();
}

//描画処理
void Play::Draw()
{
	map.Draw();
	character.Draw();
}

//終了処理
void Play::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
