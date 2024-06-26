#include"DxLib.h"
#include"Play.h"
#include"../Scene.h"


//初期化
void Play::Init()
{
	mapeditor.Init();
	MousePointBufX = 0;
	MousePointBufY = 0;
	
	//通常処理へ移動
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//通常処理
void Play::Step()
{
	mapeditor.Loop(&MousePointBufX,&MousePointBufY);

}

//描画処理
void Play::Draw()
{
	mapeditor.Draw();
}

//終了処理
void Play::Fin()
{
	
	//次のシーンに移動
	g_CurrentSceneID = SCENE_ID_INIT_RESULT;
}
