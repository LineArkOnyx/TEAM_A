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
	CurrentMCT = MAPCHIP_KUSA;
	
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
					switch (m_FileReadMapData[y][x])	// <<Switch
					{
					case MAPCHIP_BLOCK:
						DrawBox(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE, GetColor(255, 255, 0), true);
						break;
					case MAPCHIP_KUSA:
						DrawBox(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE, GetColor(0, 191, 0), true);
						break;
					default:
						break;
					}
					DrawBox(x * MAP_SIZE, y * MAP_SIZE, x * MAP_SIZE + MAP_SIZE, y * MAP_SIZE + MAP_SIZE, GetColor(127, 127, 0), false);
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

	return 0;
}
int MapEditor::SetMCT(int* MouseX, int* MouseY) 
{
	GetMousePoint(MouseX, MouseY);		//マウス地点取得
	if (Input::Mouse::Keep(MOUSE_INPUT_LEFT) || Input::Mouse::Push(MOUSE_INPUT_LEFT)) {
		for (int y = 0; y < MAP_DATA_Y; y++){
			for (int x = 0; x < MAP_DATA_X; x++){
				if (Collision::Rect(x * MAP_SIZE, y * MAP_SIZE, MAP_SIZE, MAP_SIZE, *MouseX, *MouseY, 1, 1)) {
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
	switch (num)	// <<Switch
	{
	case 0:
		CurrentMCT = MAPCHIP_BLOCK;
		break;
	case 1:
		CurrentMCT = MAPCHIP_KUSA;
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
			if (IndexBuf <= 0) {
				IndexBuf = 0;
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