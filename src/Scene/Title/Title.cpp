#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"

//‰Šú‰»
void Title::Init()
{

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//’Êíˆ—
void Title::Step()
{
	m_hndl = LoadGraph("data/Title/‰¼Title.png");
	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//•`‰æˆ—
void Title::Draw()
{
	DrawGraph(0, 0, m_hndl, true);
	DrawFormatString(0, 0, GetColor(255, 0, 255), "Push Enter Key");

}

//I—¹ˆ—
void Title::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
