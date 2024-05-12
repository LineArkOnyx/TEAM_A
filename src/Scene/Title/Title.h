#pragma once

class Title
{
private:
	int m_hndl[3];						// 画像ハンドル

	int m_backrand;						// 背景乱数
	int m_effectrand;					// エフェクト乱数

	int m_Blend[2] = { 255, 255 };		// 透過用変数
	int m_Direction[2] = { 1, 1 };		// 透過方向の変更
	int m_BlendSpeed[2] = { 2, 15 };	// 透過スピード

	float m_posX, m_posY;				// エフェクトの座標
	float m_gravity;					// エフェクトの重力

public:
	//初期化
	void Init();
	//通常処理
	void Step();
	//描画処理
	void Draw();
	//終了処理
	void Fin();
};
