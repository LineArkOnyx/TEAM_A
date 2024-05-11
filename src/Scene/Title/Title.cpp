#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

#define LOGO	"data/Title/仮TitleLogo.png"
#define BACK	"data/Title/DaytimeBack.png"
#define BACK2	"data/Title/NightBack.png"
#define SKY		"data/Title/DaytimeSky.png"
#define SKY2	"data/Title/NightSky.png"

//初期化
void Title::Init()
{
	m_rand = GetRand(1);	// 0〜1

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{
	if (m_rand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// 空
		m_hndl[1] = LoadGraph(BACK);	// 背景
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// 夜空
		m_hndl[1] = LoadGraph(BACK2);	// 背景
	}
	m_hndl[2] = LoadGraph(LOGO);		// ロゴ
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//描画処理
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl[0], true);
	DrawGraph(0, 0, m_hndl[1], true);
	DrawGraph(0, 0, m_hndl[2], true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//終了処理
void Title::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
