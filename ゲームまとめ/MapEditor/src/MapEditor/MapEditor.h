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

// マップチップのパス
const char MAP_CHIP[] = "Data/MapChip/bloak.png";

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
		MAPCHIP_ROAD,			// 丸石
		MAPCHIP_GLASS,			// 草
		MAPCHIP_TREE_0,			// 木１
		MAPCHIP_TREE_1,			// 木２
		MAPCHIP_TILE,			// タイル
		MAPCHIP_STONE_0,		// 石レンガ薄
		MAPCHIP_STONE_1,		// 石レンガ濃
		MAPCHIP_STEAL,			// スチール
		MAPCHIP_NET_0,			// 金網大
		MAPCHIP_NET_1,			// 金網小
		MAPCHIP_STONE_BOX,		// 石のブロック
		MAPCHIP_WATER_0_IN,		// 水中(薄
		MAPCHIP_WATER_1_IN,		// 水中(中
		MAPCHIP_WATER_2_IN,		// 水中(濃
		MAPCHIP_WATER_0_UP,		// 水面(薄
		MAPCHIP_WATER_1_UP,		// 水面(中
		MAPCHIP_WATER_2_UP,		// 水面(濃
		MAPCHIP_RAVA_IN,		// 溶岩中
		MAPCHIP_RAVA_UP,		// 溶岩面
		MAPCHIP_CHECK_POINT,	// 中間地点
		MAPCHIP_OFF_PARTS,		// OFFパーツ
		MAPCHIP_OFF_BLOCK,		// OFFブロック
		MAPCHIP_OFF_GRID,		// OFF点線
		MAPCHIP_OFF_SWITCH,		// OFFスイッチ
		MAPCHIP_OFF_SWITCH_BLOCK,// OFFスイッチブロック
		MAPCHIP_ON_PARTS,		// ONパーツ
		MAPCHIP_ON_BLOCK,		// ONブロック
		MAPCHIP_ON_GRID,		// ON点線
		MAPCHIP_ON_SWITCH,		// ONスイッチ
		MAPCHIP_ON_SWITCH_BLOCK,// ONスイッチブロック
		MAPCHIP_DOOR_0,			// ドア上
		MAPCHIP_SPRING_0,		// バネ縦
		MAPCHIP_SPRING_1,		// バネ横
		MAPCHIP_SPIKE_0,		// トゲ
		MAPCHIP_SPIKE_1,		// トゲトゲ
		MAPCHIP_SPIKE_2,		// トゲ丸
		MAPCHIP_STEAR,			// 梯子
		MAPCHIP_COMBARE_0,		// コンベア左端
		MAPCHIP_COMBARE_1,		// コンベア中央
		MAPCHIP_COMBARE_2,		// コンベア右端
		MAPCHIP_DOOR_1,			// ドア下
		MAPCHIP_ARROW_0,		// 矢印看板右
		MAPCHIP_ARROW_1,		// 矢印看板左
		MAPCHIP_ARROW_2,		// 矢印看板上
		MAPCHIP_ARROW_3,		// 矢印看板下
		MAPCHIP_ARROW_4,		// 矢印看板右棒
		MAPCHIP_ARROW_5,		// 矢印看板左棒
		MAPCHIP_ARROW_6,		// 矢印看板上棒
		MAPCHIP_APPLE_0,		// リンゴ
		MAPCHIP_APPLE_1,		// 金リンゴ
		MAPCHIP_BAWLE,			// ボウル
		MAPCHIP_PEPPER,			// トウガラシ
		MAPCHIP_SPHERE_R,		// 赤玉
		MAPCHIP_SPHERE_B,		// 青玉
		MAPCHIP_SPHERE_G,		// 緑玉
		MAPCHIP_CAKE,			// ケーキ
		MAPCHIP_COIN,			// コイン
		MAPCHIP_BRANK0,			// 空気
		MAPCHIP_BRANK1,			// 空気
		MAPCHIP_BRANK2,			// 空気

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
