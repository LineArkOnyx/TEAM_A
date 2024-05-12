#include"DxLib.h"
#include"Result.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//‰Šú‰»
void Result::Init()
{

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_RESULT;
}

//’Êíˆ—
void Result::Step()
{
	m_hndl = LoadGraph("data/GameOver/‰¼Gameover.png");

	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_RESULT;

}

//•`‰æˆ—
void Result::Draw()
{
	DrawGraph(0, 0, m_hndl, true);

	// “§‰ßˆ—
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

//I—¹ˆ—
void Result::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
