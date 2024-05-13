#include "MapEditor.h"
#include "../Scene/Scene.h"

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
	LoadDivGraph(MAP_CHIP, MAPCHIP_MAX, 10, 7, MAP_SIZE, MAP_SIZE, imgHundle);

	g_CurrentSceneID = SCENE_ID_LOOP_EDITOR;
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
					DrawGraph(x * MAP_SIZE + ScreenPosX, y * MAP_SIZE + ScreenPosY, imgHundle[mapchipType], true);
					
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
		if (mapIndexY >= 32 || mapIndexX >= 128)
		{
			break;
		}
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
void MapData::Exit()
{
	for (int i = 0; i < MAPCHIP_MAX; i++) {
		DeleteGraph(imgHundle[i]);
	}
	isReadFile = false;
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
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

					if (CurrentMCT == MAPCHIP_DOOR_0 && y < MAP_DATA_Y - 1){
						m_FileReadMapData[y + 1][x] = MAPCHIP_DOOR_1;
					}
					if (CurrentMCT == MAPCHIP_DOOR_1 && y > 1) {
						m_FileReadMapData[y - 1][x] = MAPCHIP_DOOR_0;
					}

					if (CurrentMCT == MAPCHIP_COMBARE_1 && x < MAP_DATA_X - 1 && x > 1 && m_FileReadMapData[y][x + 1] != MAPCHIP_COMBARE_1) {
						m_FileReadMapData[y][x - 1] = MAPCHIP_COMBARE_0;
					}
					if (CurrentMCT == MAPCHIP_COMBARE_1 && x < MAP_DATA_X - 1 && x > 1 && m_FileReadMapData[y][x - 1] != MAPCHIP_COMBARE_1) {
						m_FileReadMapData[y][x + 1] = MAPCHIP_COMBARE_2;
					}
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
	case 30:
		CurrentMCT = MAPCHIP_OFF_PARTS;	//OFFパーツ
		break;
	case 31:
		CurrentMCT = MAPCHIP_OFF_BLOCK;	// OFFブロック
		break; 
	case 32:
		CurrentMCT = MAPCHIP_OFF_GRID;	// OFF点線
		break;
	case 33:
		CurrentMCT = MAPCHIP_OFF_SWITCH;	// OFFスイッチ
		break;
	case 34:
		CurrentMCT = MAPCHIP_OFF_SWITCH_BLOCK;// OFFスイッチブロック
		break;
	case 35:
		CurrentMCT = MAPCHIP_ON_PARTS;	// ONパーツ
		break;
	case 36:
		CurrentMCT = MAPCHIP_ON_BLOCK;	// ONブロック
		break;
	case 37:
		CurrentMCT = MAPCHIP_ON_GRID;	// ON点線
		break;
	case 38:
		CurrentMCT = MAPCHIP_ON_SWITCH;	// ONスイッチ
		break;
	case 39:
		CurrentMCT = MAPCHIP_ON_SWITCH_BLOCK;// ONスイッチブロック
		break;
	case 40:
		CurrentMCT = MAPCHIP_DOOR_0;	// ドア上
		break;
	case 41:
		CurrentMCT = MAPCHIP_SPRING_0;	// バネ縦
		break;
	case 42:
		CurrentMCT = MAPCHIP_SPRING_1;	// バネ横
		break;
	case 43:
		CurrentMCT = MAPCHIP_SPIKE_0;	// トゲ
		break;
	case 44:
		CurrentMCT = MAPCHIP_SPIKE_1;	// トゲトゲ
		break;
	case 45:
		CurrentMCT = MAPCHIP_SPIKE_2;	// トゲ丸
		break;
	case 46:
		CurrentMCT = MAPCHIP_STEAR;	// 梯子
		break;
	case 47:
		CurrentMCT = MAPCHIP_COMBARE_0;	// コンベア左端
		break;
	case 48:
		CurrentMCT = MAPCHIP_COMBARE_1;	// コンベア中央
		break;
	case 49:
		CurrentMCT = MAPCHIP_COMBARE_2;	// コンベア右端
		break;
	case 50:
		CurrentMCT = MAPCHIP_DOOR_1;	// ドア下
		break;
	case 51:
		CurrentMCT = MAPCHIP_ARROW_0;	// 矢印看板右
		break;
	case 52:
		CurrentMCT = MAPCHIP_ARROW_1;	// 矢印看板左
		break;
	case 53:
		CurrentMCT = MAPCHIP_ARROW_2;	// 矢印看板上
		break;
	case 54:
		CurrentMCT = MAPCHIP_ARROW_3;	// 矢印看板下
		break;
	case 55:
		CurrentMCT = MAPCHIP_ARROW_4;	// 矢印看板右棒
		break;
	case 56:
		CurrentMCT = MAPCHIP_ARROW_5;	// 矢印看板左棒
		break;
	case 57:
		CurrentMCT = MAPCHIP_ARROW_6;	// 矢印看板上棒
		break;
	case 58:
		CurrentMCT = MAPCHIP_APPLE_0;	// リンゴ
		break;
	case 59:
		CurrentMCT = MAPCHIP_APPLE_1;	// 金リンゴ
		break;
	case 60:
		CurrentMCT = MAPCHIP_BAWLE;	// ボウル
		break;
	case 61:
		CurrentMCT = MAPCHIP_PEPPER;	// トウガラシ
		break;
	case 62:
		CurrentMCT = MAPCHIP_SPHERE_R;	// 赤玉
		break;
	case 63:
		CurrentMCT = MAPCHIP_SPHERE_B;	// 青玉
		break;
	case 64:
		CurrentMCT = MAPCHIP_SPHERE_G;	// 緑玉
		break;
	case 65:
		CurrentMCT = MAPCHIP_CAKE;	// ケーキ
		break;
	case 66:
		CurrentMCT = MAPCHIP_COIN;	// コイン
		break;
	case 67:
		CurrentMCT = MAPCHIP_BRANK0;	// 空気
		break;
	case 68:
		CurrentMCT = MAPCHIP_BRANK1;	// 空気
		break;
	case 69:
		CurrentMCT = MAPCHIP_BRANK2;	// 空気
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
		if (Input::Key::Keep(KEY_INPUT_LSHIFT) && Input::Key::Push(KEY_INPUT_F)) {
			g_CurrentSceneID = SCENE_ID_FIN_EDITOR;
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