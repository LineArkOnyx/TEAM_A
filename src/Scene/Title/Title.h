#pragma once

#define EFFECT_NUM 180					// 拡散後のエフェクト数
#define EFFECT_SHOT 5					// 一度に拡散するエフェクト数
#define EFFECT_SPEED 5.0f				// 拡散後のエフェクト速度
#define M_PI 360

class Title
{
private:
	int m_sound;						// サウンドハンドル
	int m_hndl[3];						// 画像ハンドル

	int m_backrand;						// 背景乱数
	int m_effectrand;					// エフェクト乱数

	int m_Blend[2] = { 255, 255 };		// 透過用変数
	int m_Direction[2] = { 1, 1 };		// 透過方向の変更
	int m_BlendSpeed[2] = { 2, 15 };	// 透過スピード

	float m_posX, m_posY;				// エフェクトの座標
	float m_posX2[EFFECT_NUM],			// エフェクト拡散後の座標
		m_posY2[EFFECT_NUM];
	float m_speed[EFFECT_NUM];			// 拡散後の速度
	float m_angle[EFFECT_NUM];			// 拡散後の向き
	float m_gravity;					// エフェクトの重力
	float m_gravity2[EFFECT_NUM];		// 拡散後のエフェクトの重力

	int m_R, m_G, m_B;					// 色用変数 (虹色)
	int m_ColorSpeed;					// 色の変化スピード

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
