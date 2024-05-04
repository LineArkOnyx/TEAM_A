#include"DxLib.h"
#include"Map.h"
#include"../Character/Character.h"
int MapHandle[4] = { 0 };									//�}�b�v�`�b�v�f�[�^������z��
int MapChipData[MAP_CHIP_Y_NUM][MAP_CHIP_X_NUM];		//��ڂ̃}�b�v
Map map;
void Map::Init()
{
	Load();
	LoadDivGraph("Data/Map/MAP���K.png", 4, 2, 2, 32, 32, MapHandle);
}
void Map::Load()
{
	int mapIndexX = 0;
	int mapIndexY = 0;
	FILE* fp;

	fopen_s(&fp, "Data/Map/Map.csv", "r");
	while (true) {
		// ���l������ǂݍ���
		fscanf_s(fp, "%d", &MapChipData[mapIndexY][mapIndexX]);
		mapIndexX++;

		// �u,�v���΂����߂ɓǂݍ��݂����s
		char c = fgetc(fp);



		// EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (c == EOF)
		{
			break;
		}

		// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
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