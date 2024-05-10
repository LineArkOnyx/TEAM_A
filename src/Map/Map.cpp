#include"DxLib.h"
#include"Map.h"
#include"../Character/Character.h"
const int MapPathMax = 60;
int MapHandle[MapPathMax] = { -1 };									//マップチップデータを入れる配列
int BackgroundMapHandle[MapPathMax] = { -1 };									//マップチップデータを入れる配列
int MapChipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];		//一つ目のマップ
int BackgroundMapchipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];		//マップチップのバックグラウンド
Map map;
BackgroundMapchip backgroundMapchip;
void Map::Init()
{
	for (int i = 0; i < MapPathMax; i++)
	{
		MapHandle[i] = -1;
	}
	Load();
	LoadDivGraph("Data/bloak/bloak.png", MapPathMax, 10, 6, 32, 32, MapHandle);
	
}
void Map::Load()
{
	int mapIndexX = 0;
	int mapIndexY = 0;
	FILE* fp;

	fopen_s(&fp, "Data/Map/Map.csv", "r");
	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &MapChipData[mapIndexY][mapIndexX]);
		mapIndexX++;

		// 「,」を飛ばすために読み込みを実行
		char c = fgetc(fp);



		// EOFの場合は読み込み終了
		if (c == EOF)
		{
			break;
		}

		// 改行コードの場合は保存先を変更する
		if (c == '\n')
		{
			mapIndexY++;
			mapIndexX = 0;
		}
	}
	fclose(fp);
}
void Map::Draw()
{


	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			if (MapChipData[y][x] == -1)
				continue;
			DrawGraph(x * 32- character.GetScreenX(), y * 32- character.GetScreenY(), MapHandle[MapChipData[y][x]], true);
		
		}
	}
}
//
void BackgroundMapchip::Init()
{
	for (int i = 0; i < MapPathMax; i++)
	{
		BackgroundMapHandle[i] = -1;
	}
	Load();
	LoadDivGraph("Data/bloak/bloak.png", MapPathMax, 10, 6, 32, 32, BackgroundMapHandle);

}
void BackgroundMapchip::Load()
{

	m_hndl = LoadGraph("data/PlayScene/背景(野原).png");


	int mapIndexX = 0;
	int mapIndexY = 0;
	FILE* fp;

	fopen_s(&fp, "data/BackgroundMap/BackgroundMap.csv", "r");
	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &BackgroundMapchipData[mapIndexY][mapIndexX]);
		mapIndexX++;

		// 「,」を飛ばすために読み込みを実行
		char c = fgetc(fp);



		// EOFの場合は読み込み終了
		if (c == EOF)
		{
			break;
		}

		// 改行コードの場合は保存先を変更する
		if (c == '\n')
		{
			mapIndexY++;
			mapIndexX = 0;
		}
	}
	fclose(fp);
}
void BackgroundMapchip::Draw()
{
	

	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			if (BackgroundMapchipData[y][x] == -1)
				continue;
			DrawGraph(x * 32 - character.GetScreenX(), y * 32 - character.GetScreenY(), BackgroundMapHandle[BackgroundMapchipData[y][x]], true);

		}
	}
	DrawGraph(0.05f-character.GetScreenX(),0.05f-character.GetScreenY(), m_hndl, true);
	DrawGraph(1920 - character.GetScreenX(), 0.05f - character.GetScreenY(), m_hndl, true);
}