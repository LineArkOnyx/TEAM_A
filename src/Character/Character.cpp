#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "a" };		//ここにキャラのパスを入れる
const float MOVE_SPEED = 5;	//キャラの移動スピード
const float GRAVITY_SPEED = 1;		//重力
const float GRAVITY_LIMIT = 5;		//重力の最大値
void Character::Init()		//初期化
{
	x = 0.0f;
	y = 0.0f;
	h = 64;
	w = 32;
	Next_x = x;
	Next_y = y;
	Gravity_Speed = 0.0f;
	handle = LoadGraph(CHARACTER_PATH);
}
void Character::Move()		//移動処理
{
	if (Input::Key::Keep(KEY_INPUT_A))
	{
		Next_x -= MOVE_SPEED;
	}
	if (Input::Key::Keep(KEY_INPUT_D))
	{
		Next_x += MOVE_SPEED;
	}
}
void Character::Gravity()	//重力処理
{
	Gravity_Speed += GRAVITY_SPEED;
	if (Gravity_Speed > GRAVITY_LIMIT)
	{
		Gravity_Speed = GRAVITY_LIMIT;
		Next_y += Gravity_Speed;
	}
	else
	{
		Next_y += Gravity_Speed;
	}
}	
void Character::Draw()		//描画
{
	DrawBox(x, y, x + w, y + h, GetColor(255, 255, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawRotaGraph(x, y, 1.0, 0.0, handle, true);
}
void Character::Update()
{
	x = Next_x;
	y = Next_y;
}
void Character::Step()		//ここにまとめる
{
	Move();
	Gravity();
	Update();
}