#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
#include"../Scene/Scene.h"
#include"../Map/Map.h"
#include"../PlayScene/PlayScene.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "data/play/仮player64×32.png" };		//ここにキャラのパスを入れる
const float MOVE_SPEED = 5;	//キャラの移動スピード
const float GRAVITY_SPEED = 1;		//重力
const float GRAVITY_LIMIT = 5;		//重力の最大値
const int JUNPPOWER = 22;
void Character::Init()		//初期化
{
	x = 300.0f;			//X座標
	y = 800.0f;			//Y座標
	h = 64;				//縦幅
	w = 32;				//横幅
	Next_x = x;			//X座標の前のフレームを取りたい
	Next_y = y;			//Y座標の前のフレームを取りたい
	Gravity_Speed = 0.0f;//重力
	ScreenX = 0.0f;
	ScreenY = 0.0f;
	handle = LoadGraph(CHARACTER_PATH);		//ロード
	JunpFrag = false;
}
void Character::Move()		//移動処理
{
	if (Input::Key::Keep(KEY_INPUT_A))	//Aキーを押したらtrue
	{
		Next_x -= MOVE_SPEED;
	}
	if (Input::Key::Keep(KEY_INPUT_D)) //Dキーを押したらtrue
	{
		Next_x += MOVE_SPEED;
	}
}
void Character::Junp()
{
	if (JunpFrag == false)
	{
		if (Input::Key::Push(KEY_INPUT_W))
		{
			Gravity_Speed -= JUNPPOWER;
			JunpFrag = true;
		}
	}
	
}
void Character::Gravity()	//重力処理
{
	Gravity_Speed += GRAVITY_SPEED;		//重力を入れる
	if (Gravity_Speed > GRAVITY_LIMIT)	//GRAVITY_LIMITを超えるとtrue
	{
		Gravity_Speed = GRAVITY_LIMIT;
		Next_y += Gravity_Speed;
	}
	else	//GRAVITY_LIMITを超えていない限りtrue
	{
		Next_y += Gravity_Speed;
	}
}	
void Character::Draw()		//描画
{
	DrawBox(x - ScreenX, y - ScreenY, x + w - ScreenX, y + h - ScreenY, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawFormatString(0, 75, GetColor(255, 255, 255), "JunpFrag = %d", JunpFrag);

	DrawRotaGraph(x+w/2- ScreenX, y+h/2- ScreenY, 1.0, 0.0, handle, true);		//キャラクター描画
}
void Character::Update()		//アップデート
{	
	x = Next_x;		//計算した値を入れる
	y = Next_y;		//計算した値を入れる
}
void Character::StepHitSquare()					//当たり判定を調節する位置
{
	HitSquareX = x / 32;
	HitSquareY = y / 32;
}
void Character::Step()		//ここにまとめる
{
	Move();
	Gravity();
	/*Junp();*/
	StepScreen();
	playSceen.Step();
	Update();
}
void Character::StepScreen()
{
	ScreenX = x - SCREEN_SIZE_X / 2;
	ScreenY = y - SCREEN_SIZE_Y / 2;						//Y座標のスクリーンY座標
}
void Character::GetMoveDirection(bool* _dirArray) 		//左右上下の当たり判定
{
	// 右方向のチェック
	if (Next_x > x) {
		_dirArray[3] = true;
	}
	// 左方向のチェック
	if (Next_x < x) {
		_dirArray[2] = true;
	}
	// 下方向のチェック
	if (Next_y > y) {
		_dirArray[1] = true;
	}
	// 左方向のチェック
	if (Next_y < y) {
		_dirArray[0] = true;
	}
}