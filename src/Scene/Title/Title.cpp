#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

#define LOGO	"data/Title/‰¼TitleLogo.png"
#define BACK	"data/Title/DaytimeBack.png"
#define BACK2	"data/Title/NightBack.png"
#define SKY		"data/Title/DaytimeSky.png"
#define SKY2	"data/Title/NightSky.png"

//‰Šú‰»
void Title::Init()
{
	m_rand = GetRand(1);	// 0`1

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//’Êíˆ—
void Title::Step()
{
	if (m_rand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// ‹ó
		m_hndl[1] = LoadGraph(BACK);	// ”wŒi
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// –é‹ó
		m_hndl[1] = LoadGraph(BACK2);	// ”wŒi
	}
	m_hndl[2] = LoadGraph(LOGO);		// ƒƒS
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//•`‰æˆ—
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl[0], true);
	DrawGraph(0, 0, m_hndl[1], true);
	DrawGraph(0, 0, m_hndl[2], true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//I—¹ˆ—
void Title::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
