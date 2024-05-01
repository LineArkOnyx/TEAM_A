#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"
#include"../../Character/Character.h"
//‰Šú‰»
void Play::Init()
{
	character.Init();
	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//’Êíˆ—
void Play::Step()
{
	character.Step();
}

//•`‰æˆ—
void Play::Draw()
{
	character.Draw();
}

//I—¹ˆ—
void Play::Fin()
{

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
