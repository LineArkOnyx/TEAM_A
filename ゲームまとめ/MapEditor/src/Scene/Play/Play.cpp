#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"


//‰Šú‰»
void Play::Init()
{
	mapeditor.Init();
	MousePointBufX = 0;
	MousePointBufY = 0;
	
	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//’Êíˆ—
void Play::Step()
{
	mapeditor.Loop(&MousePointBufX,&MousePointBufY);

}

//•`‰æˆ—
void Play::Draw()
{
	mapeditor.Draw();
}

//I—¹ˆ—
void Play::Fin()
{
	
	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
