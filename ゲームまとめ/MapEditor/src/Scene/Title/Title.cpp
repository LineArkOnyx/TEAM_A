#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"

//初期化
void Title::Init()
{

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{

	
}

//描画処理
void Title::Draw()
{

}

//終了処理
void Title::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
