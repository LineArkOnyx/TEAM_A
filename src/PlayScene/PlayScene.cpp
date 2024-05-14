#include"DxLib.h"
#include"PlayScene.h"
#include"../Character/Character.h"
#include"../Map/Map.h"
#include"../MathPlus/MathPlus.h"
#include"../Scene/Scene.h"
#include"../Sound/Sound.h"
const int SQUARE_Y = 5;		//現在の位置からY軸の当たり判定の範囲を設定する
const int SQUARE_X = 10;	//現在の位置からX軸の当たり判定の範囲を設定する
const int SQUARE_Y_MAX = 27;	//どこまで当たり判定を取るか
const int SQUARE_Y_LOWEST = 1;	//どこまで当たり判定を取るか
const int SQUARE_X_MAX = 100;	//どこまで当たり判定を取るか
const int SQUARE_X_LOWEST = 0;	//どこまで当たり判定を取るか
PlaySceen playSceen;
void PlaySceen::Character_Hit_Map()
{
	character.StepHitSquare();
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//配列を超えたら
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//配列を超えたら
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			if(character.GetHitSquareX()> SQUARE_X_MAX)
				continue;
			//配列を超えたら
			if (character.GetHitSquareX() < SQUARE_X_LOWEST)
				continue;
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
			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// オブジェクトの情報
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			if (MapChipData[y][x] == -1|| MapChipData[y][x] == 40 || MapChipData[y][x] == 41 || MapChipData[y][x] == 46 ||  MapChipData[y][x] == 50 || MapChipData[y][x] == 43 || MapChipData[y][x] == 44 || MapChipData[y][x] == 45 || MapChipData[y][x] == 51 || MapChipData[y][x] == 52 || MapChipData[y][x] == 53 || MapChipData[y][x] == 54 || MapChipData[y][x] == 55 || MapChipData[y][x] == 56 || MapChipData[y][x] == 57 || MapChipData[y][x] == 58)
				continue;
			{
				//DrawBox(Bx-(int)character.GetScreenX(), By- (int)character.GetScreenY(), Bx + Bw- (int)character.GetScreenX(), By + Bh- (int)character.GetScreenY(), GetColor(255, 255, 255), false);
				//DrawBox(Ax - (int)character.GetScreenX(), Ay - (int)character.GetScreenY(), Ax + Aw - (int)character.GetScreenX(), Ay + Ah - (int)character.GetScreenY(), GetColor(255, 0, 0), false);

				Ay = (int)character.GetPosY();
				Ax = (int)character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[2]) 
					{
						// ★ここを考える
						// めり込み量を計算する
						int overlap = Bx + Bw - Ax;
						character.SetNextPosX((float)Ax + overlap);
					}
					// 右方向の修正
					//マリオの右側
					if (dirArray[3]) 
					{
						// ★ここを考える
						// めり込み量を計算する
						int overlap = Ax + Aw - Bx;
						character.SetNextPosX((float)Ax - overlap);
					}
				}
			}

		}
	}
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//配列を超えたら
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//配列を超えたら
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			if (character.GetHitSquareX() > SQUARE_X_MAX)
				continue;
			//配列を超えたら
			if (character.GetHitSquareX() < SQUARE_X_LOWEST)
				continue;
			// ★ここを考える
				// どの方向に進んでいたかチェック
				// ※Playerクラスに進む方向をチェックする関数を準備しています。

			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			// ★ここを考える
			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報
			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// オブジェクトの情報
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;

			if (MapChipData[y][x] == -1 || MapChipData[y][x] == 46 || MapChipData[y][x] == 41|| MapChipData[y][x] == 40 || MapChipData[y][x] == 50|| MapChipData[y][x] == 43 || MapChipData[y][x] == 44 || MapChipData[y][x] == 45 || MapChipData[y][x] == 51 || MapChipData[y][x] == 52 || MapChipData[y][x] == 53 || MapChipData[y][x] == 54 || MapChipData[y][x] == 55 || MapChipData[y][x] == 56 || MapChipData[y][x] == 57 || MapChipData[y][x] == 58)
				continue;
			{
				Ay = (int)character.GetNextPosY();
				Ax = (int)character.GetNextPosX();
				if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
				{
					if (dirArray[0]) {
						// ★ここを考える
						// めり込み量を計算する
						character.SetGravitySpeed(0.0);
						int overlap = By + Bh - Ay;
						character.SetNextPosY(((float)Ay + overlap));
						if (MapChipData[y][x] == 47 || MapChipData[y][x] == 48 || MapChipData[y][x] == 49)
						{
							character.UpConveyorPower();
						}
						if (MapChipData[y][x] == 6)
						{
							MapChipData[y][x] = -1;
							Effect::Play(EFFECT_TYPE_BREAK, Bx - character.GetScreenX(), By - character.GetScreenY());
							Sound::Se::Play(SE_BLOAK_DESTRUCTION);
						}
					}
					// 右方向の修正
					//マリオの右側
					if (dirArray[1]) 
					{
						if (character.GetStatus() == PL_JUMP)
						{
							character.SetStatus(PL_NORMAL);
						}
						// ★ここを考える
						// めり込み量を計算する
						character.SetJunpFrag();	//着地したらジャンプできるようにする
						character.Junp();			//着地してないとジャンプできない
						character.SetUpJunpTrapFrag(true);	//床に着地していればジャンプ台を起動できる
						int overlap = Ay + Ah - By;
						character.SetNextPosY((float)Ay - overlap);
						//ベルトコンベアーの当たり判定
						if (MapChipData[y][x] == 47 || MapChipData[y][x] == 48 || MapChipData[y][x] == 49)
						{
							character.UnderConveyorPower();
						}
						else {
							Sound::Se::Stop(SE_KYATAPIRA);   //SEの停止
						}
						
					}
				}
			}
		}
	}
	for (int y = (int)character.GetHitSquareY() - SQUARE_Y; character.GetHitSquareY() + SQUARE_Y > y; y++)
	{
		//配列を超えたら
		if (character.GetHitSquareY() > SQUARE_Y_MAX)
			continue;
		//配列を超えたら
		if (character.GetHitSquareY() < SQUARE_Y_LOWEST)
			continue;
		for (int x = (int)character.GetHitSquareX() - SQUARE_X; character.GetHitSquareX() + SQUARE_X > x; x++)
		{
			
			// ★ここを考える
			// 矩形の当たり判定用のデータを準備
			// プレイヤーの情報

			int Ax = (int)character.GetPosX();
			int Ay = (int)character.GetPosY();
			int Aw = (int)character.GetW();
			int Ah = (int)character.GetH();

			// オブジェクトの情報
			int Bx = x * 32;
			int By = y * 32;
			int Bw = MAPCHIP_SIZW;
			int Bh = MAPCHIP_SIZH;
			bool dirArray[4] = { false,false,false,false };
			character.GetMoveDirection(dirArray);
			if (MapChipData[y][x] == -1)
				continue; 

			//DrawBox(Bx - (int)character.GetScreenX(), By - (int)character.GetScreenY(), Bx + Bw - (int)character.GetScreenX(), By + Bh - (int)character.GetScreenY(), GetColor(255, 0, 255), false);
			if (Collision::Rect(Ax, Ay, Aw, Ah, Bx, By, Bw, Bh))
			{
				//はしごの当たり判定
				if (MapChipData[y][x] == 46)
				{	
					//梯子オンフラグを真に
					character.SetladderActiv(true);
				}
				//ばねの当たり判定
				if (MapChipData[y][x] == 41)
				{
					character.UpJunpTrap();
				}
				//ゴールの当たり判定
				if (MapChipData[y][x] == 40 || MapChipData[y][x] == 50)
				{
					Sound::Bgm::StopSound(BGM_PLAY);
					Sound::Fin();
					g_CurrentSceneID = SCENE_ID_INIT_RESULT;
				}
				//トラップ処理
				if (MapChipData[y][x] == 43|| MapChipData[y][x] == 44|| MapChipData[y][x] == 45)
				{
					DrawFormatString(0, 180, GetColor(255, 255, 255), "トラップヒット");

					if (MapChipData[y][x] == 44)
					{
						character.Damage(2);	//ダメージを２与える
					}
					else
					{
						character.Damage();	//ダメージを１与える
					}
					
				}
				//ここが回復アイテム
				if (MapChipData[y][x] == 58)
				{
					MapChipData[y][x] = -1;
					if (character.GetHp()>0)
					{
						character.SetHp(2);
						Effect::Play(EFFECT_TYPE_ITEM, Bx- character.GetScreenX(), By - character.GetScreenY());
						Sound::Se::Play(SE_EAT);
						Sound::Se::Play(SE_POWER_UP);
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