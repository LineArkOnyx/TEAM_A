#include"DxLib.h"
#include"Map.h"
#include"../Character/Character.h"
int MapHandle[4] = { 0 };									//マップチップデータを入れる配列
int MapChipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];		//一つ目のマップ
Map map;
void Map::Init()
{
	Load();
	LoadDivGraph("Data/Map/MAP正規.png", 4, 2, 2, 32, 32, MapHandle);
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
			{
				DrawGraph(x * 32 - character.GetPosX(), y * 32 - character.GetPosY(), MapHandle[MapChipData[y][x]], true);
			}
		}
	}
}