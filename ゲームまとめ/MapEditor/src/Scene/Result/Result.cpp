#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"

//初期化
void Result::Init()
{

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Result::Step()
{


}

//描画処理
void Result::Draw()
{

}

//終了処理
void Result::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
