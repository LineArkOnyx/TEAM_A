#pragma once
#include "DxLib.h"
#include "fstream"
#include "../MathPlus/MathPlus.h"
#include "../Input/Input.h"

// /* <<Switch で検索するとマップチップenumの追加に伴うswitch文へ飛べる */

// 各マップのデータ数
const int MAP_DATA_Y = 23;
const int MAP_DATA_X = 40;

// マップファイルのパス
const char MAP_DEFAULT[] = "Data/Map/map.csv";

// マップサイズ
const int MAP_SIZE = 32;


class MapData
{
protected:
	// マップチップ画像一覧
	enum MapChipType {
		MAPCHIP_NONE = -1,

		MAPCHIP_BLOCK,
		MAPCHIP_KUSA,

		MAPCHIP_MAX
	};
	MapChipType CurrentMCT;

	// 画像ハンドル
	int imgHundle[MAPCHIP_MAX];

public:
	MapData();
	~MapData();

	// ファイル読み込みフラグ
	bool isReadFile;

	// マップデータ
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };

	// ファイルからのマップデータ
	int m_FileReadMapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };

	// 初期化
	void Init();

	// 描画
	void Draw();

	// ファイルからの読み込み
	int ReadFile(const char* FilePath);
};

class MapEditor : public MapData
{
private:
	enum ControleIndex {
		CONTROLE_NONE = -1,

		CONTROLE_SET_MCT,
		CONTROLE_SELECT_MCT,
		CONTROLE_SAVE_MAP,

		CONTROLE_MAX,
	};	
	ControleIndex controleIndex;//現在コントロールしている情報の番号を保存
	int IndexBuf;

	int WriteFile(const char* FilePath);	//マップを保存
	int SetMCT(int* MouseX, int* MouseY);	//マップチップをセットする
	int SelectMCT(int num);	//セットするマップチップを選ぶ
public:
	MapEditor();
	~MapEditor();
	void Draw();
	int Loop(int *MouseX,int *MouseY);
};
