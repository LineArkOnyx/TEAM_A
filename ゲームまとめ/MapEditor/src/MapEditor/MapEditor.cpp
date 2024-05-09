#include "MapEditor.h"


MapData::MapData()
{

}
MapData::~MapData()
{
	
}
// ������
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
// �`��


void MapData::Draw()
{
	// �}�b�v�`�b�v�̕`��

	for (int y = 0; y < MAP_DATA_Y; y++)
	{
		for (int x = 0; x < MAP_DATA_X; x++)
		{
			// �u���b�N��`��
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
// �t�@�C������̓ǂݍ���
int MapData::ReadFile(const char *FilePath)
{
	FILE* fp;
	if (fopen_s(&fp, FilePath, "r") != 0) {
		return -1;
	}

	int mapIndexX = 0;
	int mapIndexY = 0;

	while (true) {
		// ���l������ǂݍ���
		fscanf_s(fp, "%d", &m_FileReadMapData[mapIndexY][mapIndexX]);
		mapIndexX++;
		// �u,�v���΂����߂ɓǂݍ��݂����s
		char c = fgetc(fp);
		// EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (c == EOF) {
			break;
		}
		// ���s�R�[�h�̏ꍇ�͕ۑ����ύX����
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
	GetMousePoint(MouseX, MouseY);		//�}�E�X�n�_�擾
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
		CurrentMCT = MAPCHIP_BRANK0;	// ��C
		break;
	case 0:
		CurrentMCT = MAPCHIP_BLOCK_0;	// �u���b�N������
		break;
	case 1:
		CurrentMCT = MAPCHIP_BLOCK_1;	// �u���b�N������
		break;
	case 2:
		CurrentMCT = MAPCHIP_BLOCK_2;	// �u���b�N������
		break;
	case 3:
		CurrentMCT = MAPCHIP_BLOCK_3;	// �u���b�N�劄��
		break;
	case 4:
		CurrentMCT = MAPCHIP_SOIL;	// �y
		break;
	case 5:
		CurrentMCT = MAPCHIP_SAND;	// ��
		break;
	case 6:
		CurrentMCT = MAPCHIP_WOOD_FLORE_0;	// �I�[�N�̃t���[�����O
		break;
	case 7:
		CurrentMCT = MAPCHIP_WOOD_FLORE_1;	// �V���J�o�̃t���[�����O
		break;
	case 8:
		CurrentMCT = MAPCHIP_WOOD_FLORE_2;	// �}�c�̃t���[�����O
		break;
	case 9:
		CurrentMCT = MAPCHIP_ICE;	// �X
		break;
	case 10:
		CurrentMCT = MAPCHIP_ROAD;	// �ې�
		break;
	case 11:
		CurrentMCT = MAPCHIP_GLASS;	// ��
		break;
	case 12:
		CurrentMCT = MAPCHIP_TREE_0;	// �؂P
		break;
	case 13:
		CurrentMCT = MAPCHIP_TREE_1;	// �؂Q
		break;
	case 14:
		CurrentMCT = MAPCHIP_TILE;	// �^�C��
		break;
	case 15:
		CurrentMCT = MAPCHIP_STONE_0;	// �΃����K��
		break;
	case 16:
		CurrentMCT = MAPCHIP_STONE_1;	// �΃����K�Z
		break;
	case 17:
		CurrentMCT = MAPCHIP_STEAL;	// �X�`�[��
		break;
	case 18:
		CurrentMCT = MAPCHIP_NET_0;	// ���ԑ�
		break;
	case 19:
		CurrentMCT = MAPCHIP_NET_1;	// ���ԏ�
		break;
	case 20:
		CurrentMCT = MAPCHIP_STONE_BOX;	// �΂̃u���b�N
		break;
	case 21:
		CurrentMCT = MAPCHIP_WATER_0_IN;	// ����(��
		break;
	case 22:
		CurrentMCT = MAPCHIP_WATER_1_IN;	// ����(��
		break;
	case 23:
		CurrentMCT = MAPCHIP_WATER_2_IN;	// ����(�Z
		break;
	case 24:
		CurrentMCT = MAPCHIP_WATER_0_UP;	// ����(��
		break;
	case 25:
		CurrentMCT = MAPCHIP_WATER_1_UP;	// ����(��
		break;
	case 26:
		CurrentMCT = MAPCHIP_WATER_2_UP;	// ����(�Z
		break;
	case 27:
		CurrentMCT = MAPCHIP_RAVA_IN;	// �n�⒆
		break;
	case 28:
		CurrentMCT = MAPCHIP_RAVA_UP;	// �n���
		break;
	case 29:
		CurrentMCT = MAPCHIP_CHECK_POINT;	// ���Ԓn�_
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

		DrawFormatString(0, 0, GetColor(255, 0, 0), "�}�b�v�`�b�v�Z�b�g�\");

		break;

	case CONTROLE_SELECT_MCT:

		DrawFormatString(0, 0, GetColor(255, 0, 0), "�}�b�v�`�b�v��I��");
		DrawBox(0,20,100,120, GetColor(0, 0, 0), true);
		DrawFormatString(10, 60, GetColor(255, 0, 0), "<< %d >>", IndexBuf);
		DrawGraph(35, 50, imgHundle[CurrentMCT], 0);
		break;

	case CONTROLE_SAVE_MAP:

		DrawFormatString(0, 0, GetColor(255, 0, 0), "�}�b�v��ۑ�");

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
		// �}�b�v�`�b�v�̃Z�b�g---------------------------------------------------------------------------------
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

		// �}�b�v�`�b�v�̑I��-----------------------------------------------------------------------------------
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

		// �}�b�v�̕ۑ�-----------------------------------------------------------------------------------------
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