#pragma once
#include "DxLib.h"
#include "fstream"
#include "../MathPlus/MathPlus.h"
#include "../Input/Input.h"

// /* <<focus で検索するとマップチップenumの追加に伴うswitch文へ飛べる */

// 各マップのデータ数
const int MAP_DATA_Y = 32;
const int MAP_DATA_X = 128;

// マップファイルのパス
const char MAP_DEFAULT[] = "Data/Map/map.csv";

// マップサイズ
const int MAP_SIZE = 32;


class MapData
{
protected:
	// マップチップ画像一覧 <<focus
	enum MapChipType {
		MAPCHIP_NONE = -1,

		MAPCHIP_BLOCK_0,		// ブロック無割れ
		MAPCHIP_BLOCK_1,		// ブロック小割れ
		MAPCHIP_BLOCK_2,		// ブロック中割れ
		MAPCHIP_BLOCK_3,		// ブロック大割れ
		MAPCHIP_SOIL,			// 土
		MAPCHIP_SAND,			// 砂
		MAPCHIP_WOOD_FLORE_0,	// オークのフローリング
		MAPCHIP_WOOD_FLORE_1,	// シラカバのフローリング
		MAPCHIP_WOOD_FLORE_2,	// マツのフローリング
		MAPCHIP_ICE,			// 氷
		MAPCHIP_SNOW,			// 雪
		MAPCHIP_GLASS,			// 草
		MAPCHIP_TREE_0,			// 木１
		MAPCHIP_TREE_1,			// 木２
		MAPCHIP_TILE,			// タイル
		MAPCHIP_RAVA,			// マグマ
		MAPCHIP_STONE_0,		// 石レンガ薄
		MAPCHIP_STONE_1,		// 石レンガ濃
		MAPCHIP_STONE_BOX,		// 石のブロック
		MAPCHIP_STEAL,			// スチール
		MAPCHIP_NET,			// 金網
		MAPCHIP_017,
		MAPCHIP_018,
		MAPCHIP_019,
		MAPCHIP_01A,
		MAPCHIP_01B,
		MAPCHIP_01C,
		MAPCHIP_01D,
		MAPCHIP_01E,
		MAPCHIP_01F,


		MAPCHIP_MAX
	};
	MapChipType CurrentMCT;

	int ScreenPosX;	//スクリーンの描画地点をセットする
	int ScreenPosY;
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
	enum ControleIndex {// <<focus
		CONTROLE_NONE = -1,

		CONTROLE_SET_MCT,		//マップチップを選択する
		CONTROLE_SELECT_MCT,	//設置するチップを選択する
		CONTROLE_SAVE_MAP,		//マップのデータを保存する

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
