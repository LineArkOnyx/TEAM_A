#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

#define LOGO	"data/Title/仮TitleLogo.png"	// ロゴ
#define BACK	"data/Title/DaytimeBack.png"	// 背景
#define BACK2	"data/Title/NightBack.png"		// 背景.夜
#define SKY		"data/Title/DaytimeSky.png"		// 空
#define SKY2	"data/Title/NightSky.png"		// 青空

#define GRAVITY	0.05f							// 重力の値

//初期化
void Title::Init()
{
	m_backrand = GetRand(1);	// 乱数0〜1
	m_effectrand = GetRand(SCREEN_SIZE_X - 10);

	m_posX = m_effectrand;
	m_posY = SCREEN_SIZE_Y;
	m_gravity = GRAVITY;

	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//通常処理
void Title::Step()
{
	// 背景ランダム
	if (m_backrand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// 空
		m_hndl[1] = LoadGraph(BACK);	// 背景
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// 夜空
		m_hndl[1] = LoadGraph(BACK2);	// 背景
	}
	m_hndl[2] = LoadGraph(LOGO);		// ロゴ

	// エフェクト処理
	m_gravity -= 0.1f;
	m_posY -= 10.0f + m_gravity;
	if (m_posY < -10.0f || m_posY > SCREEN_SIZE_Y) {
		m_effectrand = GetRand(SCREEN_SIZE_X - 10);
		m_posX = m_effectrand;
		m_gravity = GRAVITY;
		m_posY = SCREEN_SIZE_Y;
	}
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//描画処理
void Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_hndl[0], true);			// 空
	DrawGraph(0, 0, m_hndl[1], true);			// 背景

	// エフェクト処理
	if (m_gravity >= -10.0f)
		DrawBox(m_posX, m_posY, m_posX + 10, m_posY + 10, GetColor(0, 255, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

	// 透過処理
	for (int i = 0; i < 2; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Blend[i]);
		if (i == 0) {
			DrawGraph(0, 0, m_hndl[2], true);	// ロゴ
		}
		else {
			DrawFormatString(SCREEN_SIZE_X / 2.3, SCREEN_SIZE_Y / 1.125, GetColor(255, 0, 255), "Push Enter Key");
		}

		m_Blend[i] -= m_Direction[i] * m_BlendSpeed[i];
		if (m_Blend[i] <= 0 && m_Direction[i] == 1)
		{
			m_Direction[i] = -1;
		}
		else if (m_Blend[i] >= 255 && m_Direction[i] == -1)
		{
			m_Direction[i] = 1;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

//終了処理
void Title::Fin()
{

	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
