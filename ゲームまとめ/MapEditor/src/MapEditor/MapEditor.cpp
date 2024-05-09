#include "MapEditor.h"


MapData::MapData()
{

}
MapData::~MapData()
{
	
}
// 初期化
void MapData::Init()
{
	if (ReadFile(MAP_DEFAULT) == 0) {
		isReadFile = true;
	}
	ScreenPosX = 0;
	ScreenPosY = 0;
	CurrentMCT = MAPCHIP_BLOCK_0;
	LoadDivGraph(MAP_CHIP, MAPCHIP_MAX, 10, 6, MAP_SIZE, MAP_SIZE, imgHundle);
}
// 描画


void MapData::Draw()
{
	// マップチップの描画

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// ブロックを描画
			if (isReadFile) {
				int mapchipType = m_FileReadMapData[y][x];
				if (m_FileReadMapData[y][x] != MAPCHIP_NONE) {
					DrawGraph(x * MAP_SIZE, y * MAP_SIZE, imgHundle[mapchipType], true);
					
					DrawBox(x * MAP_SIZE + ScreenPosX, y * MAP_SIZE + ScreenPosY, x * MAP_SIZE + MAP_SIZE + ScreenPosX, y * MAP_SIZE + MAP_SIZE + ScreenPosY, GetColor(127, 127, 0), false);
				}
			}
			else {
				if (m_MapData[y][x] != MAPCHIP_NONE) {
					int mapchipType = m_MapData[y][x];
					DrawGraph(x * MAP_SIZE, y * MAP_SIZE, imgHundle[mapchipType], true);
				}
			}
		}
	}

}
// ファイルからの読み込み
int MapData::ReadFile(const char *FilePath)
{
	FILE* fp;
	if (fopen_s(&fp, FilePath, "r") != 0) {
		return -1;
	}

	int mapIndexX = 0;
	int mapIndexY = 0;

	while (true) {
		// 数値部分を読み込む
		fscanf_s(fp, "%d", &m_FileReadMapData[mapIndexY][mapIndexX]);
		mapIndexX++;
		// 「,」を飛ばすために読み込みを実行
		char c = fgetc(fp);
		// EOFの場合は読み込み終了
		if (c == EOF) {
			break;
		}
		// 改行コードの場合は保存先を変更する
		if (c == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
	}
	fclose(fp);
	return 0;
}




int MapEditor::WriteFile(const char* FilePath)
{
	std::ofstream data_file(FilePath);

	for (int mapIndexY = 0; mapIndexY < MAP_DATA_Y; mapIndexY++)
	{
		for (int mapIndexX = 0; mapIndexX < MAP_DATA_X; mapIndexX++)
		{
			data_file << m_FileReadMapData[mapIndexY][mapIndexX];
			if (mapIndexX < MAP_DATA_X - 1) {
				data_file << ",";
			}
		}
		data_file << std::endl;
	}
	data_file.close();

	return 0;
}
int MapEditor::SetMCT(int* MouseX, int* MouseY) 
{
	GetMousePoint(MouseX, MouseY);		//マウス地点取得
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT) || Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
		for (int y = 0; y < MAP_DATA_Y; y++){
			for (int x = 0; x < MAP_DATA_X; x++){
				if (Collision::Rect(x * MAP_SIZE, y * MAP_SIZE, MAP_SIZE, MAP_SIZE, *MouseX - ScreenPosX, *MouseY - ScreenPosY, 1, 1)) {
					m_FileReadMapData[y][x] = CurrentMCT;
				}
			}
		}
	}
	else {
		return -1;
	}
	return 0;
}
int MapEditor::SelectMCT(int num)
{
	switch (num)	// <<focus
	{
	case -1:
		CurrentMCT = MAPCHIP_BRANK0;	// 空気
		break;
	case 0:
		CurrentMCT = MAPCHIP_BLOCK_0;	// ブロック無割れ
		break;
	case 1:
		CurrentMCT = MAPCHIP_BLOCK_1;	// ブロック小割れ
		break;
	case 2:
		CurrentMCT = MAPCHIP_BLOCK_2;	// ブロック中割れ
		break;
	case 3:
		CurrentMCT = MAPCHIP_BLOCK_3;	// ブロック大割れ
		break;
	case 4:
		CurrentMCT = MAPCHIP_SOIL;	// 土
		break;
	case 5:
		CurrentMCT = MAPCHIP_SAND;	// 砂
		break;
	case 6:
		CurrentMCT = MAPCHIP_WOOD_FLORE_0;	// オークのフローリング
		break;
	case 7:
		CurrentMCT = MAPCHIP_WOOD_FLORE_1;	// シラカバのフローリング
		break;
	case 8:
		CurrentMCT = MAPCHIP_WOOD_FLORE_2;	// マツのフローリング
		break;
	case 9:
		CurrentMCT = MAPCHIP_ICE;	// 氷
		break;
	case 10:
		CurrentMCT = MAPCHIP_ROAD;	// 丸石
		break;
	case 11:
		CurrentMCT = MAPCHIP_GLASS;	// 草
		break;
	case 12:
		CurrentMCT = MAPCHIP_TREE_0;	// 木１
		break;
	case 13:
		CurrentMCT = MAPCHIP_TREE_1;	// 木２
		break;
	case 14:
		CurrentMCT = MAPCHIP_TILE;	// タイル
		break;
	case 15:
		CurrentMCT = MAPCHIP_STONE_0;	// 石レンガ薄
		break;
	case 16:
		CurrentMCT = MAPCHIP_STONE_1;	// 石レンガ濃
		break;
	case 17:
		CurrentMCT = MAPCHIP_STEAL;	// スチール
		break;
	case 18:
		CurrentMCT = MAPCHIP_NET_0;	// 金網大
		break;
	case 19:
		CurrentMCT = MAPCHIP_NET_1;	// 金網小
		break;
	case 20:
		CurrentMCT = MAPCHIP_STONE_BOX;	// 石のブロック
		break;
	case 21:
		CurrentMCT = MAPCHIP_WATER_0_IN;	// 水中(薄
		break;
	case 22:
		CurrentMCT = MAPCHIP_WATER_1_IN;	// 水中(中
		break;
	case 23:
		CurrentMCT = MAPCHIP_WATER_2_IN;	// 水中(濃
		break;
	case 24:
		CurrentMCT = MAPCHIP_WATER_0_UP;	// 水面(薄
		break;
	case 25:
		CurrentMCT = MAPCHIP_WATER_1_UP;	// 水面(中
		break;
	case 26:
		CurrentMCT = MAPCHIP_WATER_2_UP;	// 水面(濃
		break;
	case 27:
		CurrentMCT = MAPCHIP_RAVA_IN;	// 溶岩中
		break;
	case 28:
		CurrentMCT = MAPCHIP_RAVA_UP;	// 溶岩面
		break;
	case 29:
		CurrentMCT = MAPCHIP_CHECK_POINT;	// 中間地点
		break;

	default:
		return -1;
		break;
	}
	return 0;
}

MapEditor::MapEditor()
{
	controleIndex = CONTROLE_SET_MCT;
	IndexBuf = 0;
	
}
MapEditor::~MapEditor()
{

}
void MapEditor::Draw()
{
	__super::Draw();
	DrawBox(0, 0, 300, 20, GetColor(0, 0, 0), true);
	switch (controleIndex)
	{
	case CONTROLE_SET_MCT:

		DrawFormatString(0, 0, GetColor(255, 0, 0), "マップチップセット可能");

		break;

	case CONTROLE_SELECT_MCT:

		DrawFormatString(0, 0, GetColor(255, 0, 0), "マップチップを選択");
		DrawBox(0,20,100,120, GetColor(0, 0, 0), true);
		DrawFormatString(10, 60, GetColor(255, 0, 0), "<< %d >>", IndexBuf);
		DrawGraph(35, 50, imgHundle[CurrentMCT], 0);
		break;

	case CONTROLE_SAVE_MAP:

		DrawFormatString(0, 0, GetColor(255, 0, 0), "マップを保存");

		break;

	default:
		break;
	}
}
int MapEditor::Loop(int* MouseX, int* MouseY)
{
	switch (controleIndex)
	{
	case CONTROLE_SET_MCT:
		// マップチップのセット---------------------------------------------------------------------------------
		SetMCT(MouseX, MouseY);
		if (Input::Key::Push(KEY_INPUT_M)) {
			controleIndex = CONTROLE_SELECT_MCT;
		}
		if (Input::Key::Push(KEY_INPUT_S)) {
			controleIndex = CONTROLE_SAVE_MAP;
		}

		if (Input::Key::Keep(KEY_INPUT_RIGHT)) {
			ScreenPosX -= 4;
		}
		if (Input::Key::Keep(KEY_INPUT_LEFT)) {
			ScreenPosX += 4;
		}
		if (Input::Key::Keep(KEY_INPUT_DOWN)) {
			ScreenPosY -= 4;
		}
		if (Input::Key::Keep(KEY_INPUT_UP)) {
			ScreenPosY += 4;
		}

		break;
		//------------------------------------------------------------------------------------------------------

		// マップチップの選択-----------------------------------------------------------------------------------
	case CONTROLE_SELECT_MCT:
		if (Input::Key::Push(KEY_INPUT_RIGHT))
		{
			IndexBuf++;
			if (IndexBuf >= MAPCHIP_MAX) {
				IndexBuf = MAPCHIP_MAX;
			}
		}
		if (Input::Key::Push(KEY_INPUT_LEFT))
		{
			IndexBuf--;
			if (IndexBuf <= -1) {
				IndexBuf = -1;
			}
		}
		SelectMCT(IndexBuf);
		if (Input::Key::Push(KEY_INPUT_RETURN)) {
			controleIndex = CONTROLE_SET_MCT;
		}
		break;
		//------------------------------------------------------------------------------------------------------

		// マップの保存-----------------------------------------------------------------------------------------
	case CONTROLE_SAVE_MAP:

		Sleep(1000);
		WriteFile(MAP_DEFAULT);
		controleIndex = CONTROLE_SET_MCT;

		break;
		//------------------------------------------------------------------------------------------------------
	default:
		break;
	}
	
	
	
	return 0;
}