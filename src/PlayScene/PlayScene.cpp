#include"DxLib.h"
#include"PlayScene.h"
#include"../Character/Character.h"
#include"../Map/Map.h"
#include"../MathPlus/MathPlus.h"
const int SQUARE_Y = 5;		//現在の位置からY軸の当たり判定の範囲を設定する
const int SQUARE_X = 10;	//現在の位置からX軸の当たり判定の範囲を設定する
const int SQUARE_Y_MAX = 27;	//どこまで当たり判定を取るか
const int SQUARE_Y_LOWEST = 1;	//どこまで当たり判定を取るか
PlaySceen playSceen;
void PlaySceen::Character_Hit_Map()
{
	character.StepHitSquare();
	for (int y = character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//配列を超えたら
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//配列を超えたら
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			// ★ここを考える
				// どの方向に進んでいたかチェック
				// ※Playerクラスに進む方向をチェックする関数を準備しています。
			DrawFormatString(0, 48, GetColor(255, 255, 255), "StepHitSquareY=%d", character.GetHitSquareY());
			DrawFormatString(0, 64, GetColor(255, 255, 255), "StepHitSquareX=%d", character.GetHitSquareX());
			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ★ここを考える
			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = character.GetPosX();
			int Ay = character.GetPosY();
			int Aw = character.GetW();
			int Ah = character.GetH();

			// オブジェクトの情報
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			if (MapChipData[y][x] == -1)
				continue;
			{
				DrawBox(Bx-character.GetScreenX(), By- character.GetScreenY(), Bx + Bw- character.GetScreenX(), By + Bh- character.GetScreenY(), GetColor(255, 255, 255), false);
				DrawBox(Ax - character.GetScreenX(), Ay - character.GetScreenY(), Ax + Aw - character.GetScreenX(), Ay + Ah - character.GetScreenY(), GetColor(255, 0, 0), false);

				Ay = character.GetPosY();
				Ax = character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[2]) {
						// ★ここを考える
						// めり込み量を計算する
						int overlap = Bx + Bw - Ax;
						character.SetNextPosX(Ax + overlap);
					}
					// 右方向の修正
					//マリオの右側
					if (dirArray[3]) {
						// ★ここを考える
						// めり込み量を計算する
						int overlap = Ax + Aw - Bx;
						character.SetNextPosX(Ax - overlap);
					}
				}
			}

		}
	}
	for (int y = character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//配列を超えたら
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//配列を超えたら
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			// ★ここを考える
				// どの方向に進んでいたかチェック
				// ※Playerクラスに進む方向をチェックする関数を準備しています。

			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ★ここを考える
			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = character.GetPosX();
			int Ay = character.GetPosY();
			int Aw = character.GetW();
			int Ah = character.GetH();

			// オブジェクトの情報
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;

			if (MapChipData[y][x] == -1)
				continue;
			{
				Ay = character.GetNextPosY();
				Ax = character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[0]) {
						// ★ここを考える
						// めり込み量を計算する
						int overlap = By + Bh - Ay;
						character.SetNextPosY((Ay + overlap));
						character.SetGravitySpeed(0.0f);
					}
					// 右方向の修正
					//マリオの右側
					if (dirArray[1]) {
						// ★ここを考える
						// めり込み量を計算する
						character.SetJunpFrag();	//着地したらジャンプできるようにする
						character.Junp();			//着地してないとジャンプできない
						int overlap = Ay + Ah - By;
						character.SetNextPosY(Ay - overlap);
						
					}
				}
			}
		}
	}
}
void PlaySceen::Step()
{
	Character_Hit_Map();
}