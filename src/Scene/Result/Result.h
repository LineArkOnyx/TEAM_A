#pragma once

class Result
{
private:
	int m_hndl;

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
