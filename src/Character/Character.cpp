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
const float GRAVITY_LIMIT = 8;		//重力の最大値
const float JUNP_LIMIT = 30;		//ジャンプが出来る最大値
const float JUNPPOWER = 28;
//const float CONBER
void Character::Init()		//初期化
{
	x = 800.0f;			//X座標
	y = 768.0f;			//Y座標
	h = 64;				//縦幅
	w = 32;				//横幅
	Next_x = x;			//X座標の前のフレームを取りたい
	Next_y = y;			//Y座標の前のフレームを取りたい
	Gravity_Speed = 0.0f;//重力
	ScreenX = x - SCREEN_SIZE_X / 2;
	ScreenY = 239;						//Y座標のスクリーンY座標
	handle = LoadGraph(CHARACTER_PATH);		//ロード
	JunpFrag = false;
	DebugFrag = false;
	ladderActiv = false;
	turn = true;
	UpJunpTrapFrag = true;
	sideLeftJunpTrapFrag = true;
	status = PL_NORMAL;
}
void Character::Move()		//移動処理
{
	if (DebugFrag == false)
	{
		if (Input::Key::Keep(KEY_INPUT_A))	//Aキーを押したらtrue
		{
			Next_x -= MOVE_SPEED;

			turn = false;

			if(status!=PL_JUMP)
			{
				status = PL_MOVE;
			}
		}
		if (Input::Key::Keep(KEY_INPUT_D)) //Dキーを押したらtrue
		{
			Next_x += MOVE_SPEED;

			turn = true;

			if (status != PL_JUMP)
			{
				status = PL_MOVE;
			}
		}
		if (JunpFrag == false)
		{
			//ジャンプをしていなくてばねに乗ったらジャンプできる
			if (UpJunpTrapFrag == false)
			{
				if (Input::Key::Push(KEY_INPUT_UP))
				{
					Gravity_Speed -= JUNPPOWER-10;
					JunpFrag = true;

					status = PL_JUMP;
				}
			}
			
		}
		//	階段がオンなら入る
		if (ladderActiv == true)
		{
			if (Input::Key::Keep(KEY_INPUT_UP))	//Aキーを押したらtrue
			{
				Next_y -= MOVE_SPEED;
			}
			if (Input::Key::Keep(KEY_INPUT_S))	//Aキーを押したらtrue
			{
				Next_y += MOVE_SPEED;
			}

		}
		//移動状態で離したら待機状態になる
		if(status == PL_MOVE)
		{
			if (Input::Key::Release(KEY_INPUT_A) || Input::Key::Release(KEY_INPUT_D))
			{
				status = PL_NORMAL;
			}
		}
	}
}
void Character::DebugSwaitch()
{
	if (Input::Key::Push(KEY_INPUT_P))
	{
		DebugFrag = true;
	}
	if (Input::Key::Push(KEY_INPUT_O))
	{
		DebugFrag = false;
	}
	if (DebugFrag == false)
	{
		DrawFormatString(0, 105, GetColor(255, 255, 255), "プレイモード");
	}
	if (DebugFrag == true)
	{
		DrawFormatString(0, 105, GetColor(255, 255, 255), "デバッグモード");
	}
}
void Character::Junp()
{
	if (DebugFrag == false)
	{
		if (JunpFrag == false)
		{
			if (Input::Key::Push(KEY_INPUT_UP))
			{
				Gravity_Speed -= JUNPPOWER;
				JunpFrag = true;

				status = PL_JUMP;
			}
		}
	}
}
void Character::UpJunpTrap()
{
	//一回しかできない処理
	if (character.UpJunpTrapFrag == true)
	{
		UpJunpTrapFrag = false;
		Gravity_Speed -= JUNPPOWER;
	}
}
void Character::DebugMove()
{
	if (DebugFrag == true)
	{
		if (Input::Key::Keep(KEY_INPUT_A))	//Aキーを押したらtrue
		{
			Next_x -= MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_D)) //Dキーを押したらtrue
		{
			Next_x += MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_UP))	//Aキーを押したらtrue
		{
			Next_y-= MOVE_SPEED;
		}
		if (Input::Key::Keep(KEY_INPUT_S))	//Aキーを押したらtrue
		{
			Next_y += MOVE_SPEED;
		}
	}
}
void Character::Gravity()	//重力処理
{
	if (DebugFrag == false)
	{
		//梯子フラグが偽なら重力を消す
		if (ladderActiv == false)
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
			//ばねとジャンプ同時に押すと吹き飛ぶから制御
			if (Gravity_Speed <-JUNP_LIMIT)
			{
				Gravity_Speed = -JUNP_LIMIT;
			}
		}
		else
		{
			ladderActiv = false;
			Gravity_Speed = 0.0f;
		}
	}
	
}	
void Character::Draw()		//描画
{
	DrawBox(x - ScreenX, y - ScreenY, x + w - ScreenX, y + h - ScreenY, GetColor(0, 0, 255),false);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Next_x = %0.2f", Next_x);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "Next_y = %0.2f", Next_y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "Gravity_Speed = %0.2f", Gravity_Speed);
	DrawFormatString(0, 75, GetColor(255, 255, 255), "JunpFrag = %d", JunpFrag); 
	DrawFormatString(0, 90, GetColor(255, 255, 255), "DebugFrag = %d", DebugFrag);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "ScreenX = %0.2f", ScreenX);
	DrawFormatString(0, 135, GetColor(255, 255, 255), "ScreenY = %0.2f", ScreenY);
	DrawFormatString(0, 150, GetColor(255, 255, 255), "ladderActiv = %d", ladderActiv); 
	DrawFormatString(0, 165, GetColor(255, 255, 255), "UpJunpTrapFrag = %d", UpJunpTrapFrag);
	DrawRotaGraph(x+w/2- ScreenX, y+h/2- ScreenY, 1.0, 0.0, handle, true);		//キャラクター描画

	anime.Draw(x + w / 2 - ScreenX, y + h / 2 - ScreenY, animaHandle, 1.0, 0.0, turn);
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
	DebugSwaitch();
	Move();
	DebugMove();
	Gravity();
	/*Junp();*/

	StepScreen();
	playSceen.Step();
	Update();

	ChangeAnima();
}
void Character::StepScreen()
{
	/*if (ScreenX >= 0&& ScreenX<=2000)*/
	{
		ScreenX = x - SCREEN_SIZE_X / 2;
	}
	
	ScreenY = 239;						//Y座標のスクリーンY座標
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
void Character::UnderConveyorPower()
{
	character.Next_x-= 3;
}
void Character::UpConveyorPower()
{
	character.Next_x += 3;
}
void Character::ChangeAnima()
{
	switch (status)
	{
	case PL_NORMAL:
		anime.SetType(ANIME_NORMAL, &animaHandle);
		break;

	case PL_MOVE:
		anime.SetType(ANIME_MOVE, &animaHandle);
		break;

	case PL_JUMP:
		anime.SetType(ANIME_JUMP, &animaHandle);
		break;

	default:
		break;
	}
}