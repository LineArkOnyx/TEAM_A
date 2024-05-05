#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//初期化
void Title::Init()
{

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{
	m_hndl = LoadGraph("data/Title/仮Title.png");
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//描画処理
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl, true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//終了処理
void Title::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
