#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "data/play/仮player64×32.png" };		//ここにキャラのパスを入れる
const float MOVE_SPEED = 5;	//キャラの移動スピード
const float GRAVITY_SPEED = 1;		//重力
const float GRAVITY_LIMIT = 5;		//重力の最大値
void Character::Init()		//初期化
{
	x = 0.0f;			//X座標
	y = 0.0f;			//Y座標
	h = 64;				//縦幅
	w = 32;				//横幅
	Next_x = x;			//X座標の前のフレームを取りたい
	Next_y = y;			//Y座標の前のフレームを取りたい
	Gravity_Speed = 0.0f;//重力
	handle = LoadGraph(CHARACTER_PATH);		//ロード
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
	DrawBox(x, y, x + w, y + h, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);

	DrawRotaGraph(x+w/2, y+h/2, 1.0, 0.0, handle, true);		//キャラクター描画
}
void Character::Update()		//アップデート
{	
	x = Next_x;		//計算した値を入れる
	y = Next_y;		//計算した値を入れる
}
void Character::Step()		//ここにまとめる
{
	Move();
	Gravity();
	Update();
}