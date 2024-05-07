#pragma once
#include "DxLib.h"
#include "fstream"
#include "../MathPlus/MathPlus.h"
#include "../Input/Input.h"

// /* <<focus �Ō�������ƃ}�b�v�`�b�venum�̒ǉ��ɔ���switch���֔�ׂ� */

// �e�}�b�v�̃f�[�^��
const int MAP_DATA_Y = 32;
const int MAP_DATA_X = 128;

// �}�b�v�t�@�C���̃p�X
const char MAP_DEFAULT[] = "Data/Map/map.csv";

// �}�b�v�T�C�Y
const int MAP_SIZE = 32;


class MapData
{
protected:
	// �}�b�v�`�b�v�摜�ꗗ <<focus
	enum MapChipType {
		MAPCHIP_NONE = -1,

		MAPCHIP_BLOCK_0,		// �u���b�N������
		MAPCHIP_BLOCK_1,		// �u���b�N������
		MAPCHIP_BLOCK_2,		// �u���b�N������
		MAPCHIP_BLOCK_3,		// �u���b�N�劄��
		MAPCHIP_SOIL,			// �y
		MAPCHIP_SAND,			// ��
		MAPCHIP_WOOD_FLORE_0,	// �I�[�N�̃t���[�����O
		MAPCHIP_WOOD_FLORE_1,	// �V���J�o�̃t���[�����O
		MAPCHIP_WOOD_FLORE_2,	// �}�c�̃t���[�����O
		MAPCHIP_ICE,			// �X
		MAPCHIP_SNOW,			// ��
		MAPCHIP_GLASS,			// ��
		MAPCHIP_TREE_0,			// �؂P
		MAPCHIP_TREE_1,			// �؂Q
		MAPCHIP_TILE,			// �^�C��
		MAPCHIP_RAVA,			// �}�O�}
		MAPCHIP_STONE_0,		// �΃����K��
		MAPCHIP_STONE_1,		// �΃����K�Z
		MAPCHIP_STONE_BOX,		// �΂̃u���b�N
		MAPCHIP_STEAL,			// �X�`�[��
		MAPCHIP_NET,			// ����
		MAPCHIP_017,
		MAPCHIP_018,
		MAPCHIP_019,
		MAPCHIP_01A,
		MAPCHIP_01B,
		MAPCHIP_01C,
		MAPCHIP_01D,
		MAPCHIP_01E,
		MAPCHIP_01F,


		MAPCHIP_MAX
	};
	MapChipType CurrentMCT;

	int ScreenPosX;	//�X�N���[���̕`��n�_���Z�b�g����
	int ScreenPosY;
	// �摜�n���h��
	int imgHundle[MAPCHIP_MAX];

public:
	MapData();
	~MapData();

	// �t�@�C���ǂݍ��݃t���O
	bool isReadFile;

	// �}�b�v�f�[�^
	const int m_MapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };

	// �t�@�C������̃}�b�v�f�[�^
	int m_FileReadMapData[MAP_DATA_Y][MAP_DATA_X] = { 0 };

	// ������
	void Init();

	// �`��
	void Draw();

	// �t�@�C������̓ǂݍ���
	int ReadFile(const char* FilePath);
};

class MapEditor : public MapData
{
private:
	enum ControleIndex {// <<focus
		CONTROLE_NONE = -1,

		CONTROLE_SET_MCT,		//�}�b�v�`�b�v��I������
		CONTROLE_SELECT_MCT,	//�ݒu����`�b�v��I������
		CONTROLE_SAVE_MAP,		//�}�b�v�̃f�[�^��ۑ�����

		CONTROLE_MAX,
	};	
	ControleIndex controleIndex;//���݃R���g���[�����Ă�����̔ԍ���ۑ�
	int IndexBuf;

	int WriteFile(const char* FilePath);	//�}�b�v��ۑ�
	int SetMCT(int* MouseX, int* MouseY);	//�}�b�v�`�b�v���Z�b�g����
	int SelectMCT(int num);	//�Z�b�g����}�b�v�`�b�v��I��
public:
	MapEditor();
	~MapEditor();
	void Draw();
	int Loop(int *MouseX,int *MouseY);
};
