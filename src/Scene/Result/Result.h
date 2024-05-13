#pragma once

class Result
{
private:
	int m_hndl;
	int clear1;
	int clear2;
	int rogocount = 0;

	int m_Blend;		// 透過用変数
	int m_Direction;	// 透過方向の変更
	int m_BlendSpeed;	// 透過スピード

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
