#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//初期化
void Result::Init()
{
	m_hndl = LoadGraph("data/Clear/GAMECLEAR.png");
	clear1 = LoadGraph("data/Clear/c2.png");
	clear2 = LoadGraph("data/Clear/2c2.png");

	m_Blend = 255;		// 透過用変数
	m_Direction = 1;	// 透過方向の変更
	m_BlendSpeed = 15;	// 透過スピード

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//通常処理
void Result::Step()
{

	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;
}

//描画処理
void Result::Draw()
{
	DrawGraph(0, 0, m_hndl, true);

	//点滅処理
	rogocount++;
	if (rogocount <= 79) {
		DrawGraph(500, 350, clear1, true);    //一つ目を描画
	}
	if (rogocount >= 80) {
		DrawGraph(500, 350, clear2, true);    //二つ目を描画
	}
	if (rogocount >= 160) {
		rogocount = 0;    //カウントを戻す
	}

	// 透過処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Blend);
	DrawFormatString(SCREEN_SIZE_X / 2.3, SCREEN_SIZE_Y / 1.125, GetColor(0, 255, 255), "Push Enter Key");
	m_Blend -= m_Direction * m_BlendSpeed;
	if (m_Blend <= 0 && m_Direction == 1)
	{
		m_Direction = -1;
	}
	else if (m_Blend >= 255 && m_Direction == -1)
	{
		m_Direction = 1;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

//終了処理
void Result::Fin()
{
	DeleteGraph(m_hndl);
	rogocount = 0;    //カウントを戻す

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
