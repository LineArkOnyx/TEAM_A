#pragma once
#include"DxLib.h"
#define MAPCHIP_SIZW		(32)		//マップチップの幅
#define MAPCHIP_SIZH		(32)		//マップチップの縦

const int MAP_CHIP_X_NUM = 100;		//マップチップの横
const int MAP_CHIP_Y_NUM = 30;		//マップチップの縦
class Map
{
private:

public:
	void Init();
	void Load();
	void Draw();
};

class BackgroundMapchip
{
private:
	int m_hndl;  //画像用ハンドル

public:
	void Init();
	void Load();
	void Draw();


};
extern Map map;
extern BackgroundMapchip backgroundMapchip;
extern int MapChipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];					//一つ目のマップ
extern int BackgroundMapchipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];		//マップチップのバックグラウンド