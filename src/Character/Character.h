#pragma once
#include"DxLib.h"

const float MUTEKI_TIME = 2.5f;	//無敵時間
const float MUTEKI_FADE = 0.1f;//点滅間隔

//プレイヤーの状態 : 岡山産
enum PL_STATUS
{
	PL_NORMAL,
	PL_MOVE,
	PL_JUMP,
};

class Character
{
private:
	int  h, w, handle,Hp;
	float x, y,Next_x,Next_y, Gravity_Speed, ScreenX, ScreenY, HitSquareX, HitSquareY, ScreenNextX;
	bool JunpFrag
		, DebugFrag
		, ladderActiv			//梯子を使っているかかどうか判断する
		, UpJunpTrapFrag		//ジャンプ台を一回使用したか確認
		, sideLeftJunpTrapFrag, 
		sideRightJunpTrapFrag;
							
	//以下岡山産
	bool turn;	//左右の反転
	PL_STATUS status;	//プレイヤーの状態
	int animaHandle;
	float mutekiCount;	//無敵時間のカウント
	float mutekiFade;	//点滅
	//以上岡山産
public:
	void Init();		//初期化
	void Move();		//移動処理
	void Gravity();		//重力
	void Draw();		//描画
	void Update();		//アップデート
	void StepScreen();
	void GetMoveDirection(bool* _dirArray);		//左右上下の当たり判定
	void StepHitSquare();					//当たり判定を調節する位置
	void Junp();
	void Step();		//ここにまとめる
	void DebugMove();		//デバッグ用の操作
	void DebugSwaitch();
	void UnderConveyorPower();
	void UpConveyorPower();
	void UpJunpTrap();				//ばねに乗るとジャンプする
	float GetPosX() { return x; }
	float GetPosY() { return y; }
	int GetW() { return w; }
	int GetH() { return h; }
	float GetScreenX() { return ScreenX; }
	float GetScreenY() { return ScreenY; }
	float GetNextPosX() { return Next_x; }
	float GetNextPosY() { return Next_y; }
	float SetPosX(float a) { x = a; return x; }
	float SetPosY(float a) { y = a; return y; }
	float SetNextPosX(float a) { Next_x = a; return Next_x; }
	float SetNextPosY(float a) { Next_y = a; return Next_y; }
	float SetGravitySpeed(float a) { Gravity_Speed =a; return Gravity_Speed; }
	float GetHitSquareX() { return HitSquareX; }
	float GetHitSquareY() { return HitSquareY; }
	int SetJunpFrag() { JunpFrag = false; return JunpFrag; }
	int SetladderActiv(bool a) { ladderActiv = a; return  ladderActiv; }
	int SetUpJunpTrapFrag(bool a) { UpJunpTrapFrag = a; return  UpJunpTrapFrag; }
	int GetHp() { return Hp; }
	int SetHp(int a) { Hp =a; return Hp; }
	PL_STATUS GetStatus() { return status; }
	void SetStatus(PL_STATUS set) { status = set; }
	void ChangeAnima();
	void Damage(int damage = 1);
	void GameOverFrg();	//ゲームオーバー判定
	void Dead_or_Alive();
};
extern Character character;