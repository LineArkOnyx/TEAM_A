#include "MapEditor.h"
#include "../Scene/Scene.h"

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
	LoadDivGraph(MAP_CHIP, MAPCHIP_MAX, 10, 7, MAP_SIZE, MAP_SIZE, imgHundle);

	g_CurrentSceneID = SCENE_ID_LOOP_EDITOR;
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
		if (mapIndexY >= 32 || mapIndexX >= 128)
		{
			break;
		}
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
	
	GetMousePoint(MouseX, MouseY);		//�}�E�X�n�_�擾
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
	case 30:
		CurrentMCT = MAPCHIP_OFF_PARTS;	//OFF�p�[�c
		break;
	case 31:
		CurrentMCT = MAPCHIP_OFF_BLOCK;	// OFF�u���b�N
		break; 
	case 32:
		CurrentMCT = MAPCHIP_OFF_GRID;	// OFF�_��
		break;
	case 33:
		CurrentMCT = MAPCHIP_OFF_SWITCH;	// OFF�X�C�b�`
		break;
	case 34:
		CurrentMCT = MAPCHIP_OFF_SWITCH_BLOCK;// OFF�X�C�b�`�u���b�N
		break;
	case 35:
		CurrentMCT = MAPCHIP_ON_PARTS;	// ON�p�[�c
		break;
	case 36:
		CurrentMCT = MAPCHIP_ON_BLOCK;	// ON�u���b�N
		break;
	case 37:
		CurrentMCT = MAPCHIP_ON_GRID;	// ON�_��
		break;
	case 38:
		CurrentMCT = MAPCHIP_ON_SWITCH;	// ON�X�C�b�`
		break;
	case 39:
		CurrentMCT = MAPCHIP_ON_SWITCH_BLOCK;// ON�X�C�b�`�u���b�N
		break;
	case 40:
		CurrentMCT = MAPCHIP_DOOR_0;	// �h�A��
		break;
	case 41:
		CurrentMCT = MAPCHIP_SPRING_0;	// �o�l�c
		break;
	case 42:
		CurrentMCT = MAPCHIP_SPRING_1;	// �o�l��
		break;
	case 43:
		CurrentMCT = MAPCHIP_SPIKE_0;	// �g�Q
		break;
	case 44:
		CurrentMCT = MAPCHIP_SPIKE_1;	// �g�Q�g�Q
		break;
	case 45:
		CurrentMCT = MAPCHIP_SPIKE_2;	// �g�Q��
		break;
	case 46:
		CurrentMCT = MAPCHIP_STEAR;	// ��q
		break;
	case 47:
		CurrentMCT = MAPCHIP_COMBARE_0;	// �R���x�A���[
		break;
	case 48:
		CurrentMCT = MAPCHIP_COMBARE_1;	// �R���x�A����
		break;
	case 49:
		CurrentMCT = MAPCHIP_COMBARE_2;	// �R���x�A�E�[
		break;
	case 50:
		CurrentMCT = MAPCHIP_DOOR_1;	// �h�A��
		break;
	case 51:
		CurrentMCT = MAPCHIP_ARROW_0;	// ���ŔE
		break;
	case 52:
		CurrentMCT = MAPCHIP_ARROW_1;	// ���Ŕ�
		break;
	case 53:
		CurrentMCT = MAPCHIP_ARROW_2;	// ���Ŕ�
		break;
	case 54:
		CurrentMCT = MAPCHIP_ARROW_3;	// ���Ŕ�
		break;
	case 55:
		CurrentMCT = MAPCHIP_ARROW_4;	// ���ŔE�_
		break;
	case 56:
		CurrentMCT = MAPCHIP_ARROW_5;	// ���Ŕ��_
		break;
	case 57:
		CurrentMCT = MAPCHIP_ARROW_6;	// ���Ŕ�_
		break;
	case 58:
		CurrentMCT = MAPCHIP_APPLE_0;	// �����S
		break;
	case 59:
		CurrentMCT = MAPCHIP_APPLE_1;	// �������S
		break;
	case 60:
		CurrentMCT = MAPCHIP_BAWLE;	// �{�E��
		break;
	case 61:
		CurrentMCT = MAPCHIP_PEPPER;	// �g�E�K���V
		break;
	case 62:
		CurrentMCT = MAPCHIP_SPHERE_R;	// �ԋ�
		break;
	case 63:
		CurrentMCT = MAPCHIP_SPHERE_B;	// ��
		break;
	case 64:
		CurrentMCT = MAPCHIP_SPHERE_G;	// �΋�
		break;
	case 65:
		CurrentMCT = MAPCHIP_CAKE;	// �P�[�L
		break;
	case 66:
		CurrentMCT = MAPCHIP_COIN;	// �R�C��
		break;
	case 67:
		CurrentMCT = MAPCHIP_BRANK0;	// ��C
		break;
	case 68:
		CurrentMCT = MAPCHIP_BRANK1;	// ��C
		break;
	case 69:
		CurrentMCT = MAPCHIP_BRANK2;	// ��C
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