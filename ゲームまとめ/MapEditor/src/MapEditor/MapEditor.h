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

// �}�b�v�`�b�v�̃p�X
const char MAP_CHIP[] = "Data/MapChip/bloak.png";

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
		MAPCHIP_ROAD,			// �ې�
		MAPCHIP_GLASS,			// ��
		MAPCHIP_TREE_0,			// �؂P
		MAPCHIP_TREE_1,			// �؂Q
		MAPCHIP_TILE,			// �^�C��
		MAPCHIP_STONE_0,		// �΃����K��
		MAPCHIP_STONE_1,		// �΃����K�Z
		MAPCHIP_STEAL,			// �X�`�[��
		MAPCHIP_NET_0,			// ���ԑ�
		MAPCHIP_NET_1,			// ���ԏ�
		MAPCHIP_STONE_BOX,		// �΂̃u���b�N
		MAPCHIP_WATER_0_IN,		// ����(��
		MAPCHIP_WATER_1_IN,		// ����(��
		MAPCHIP_WATER_2_IN,		// ����(�Z
		MAPCHIP_WATER_0_UP,		// ����(��
		MAPCHIP_WATER_1_UP,		// ����(��
		MAPCHIP_WATER_2_UP,		// ����(�Z
		MAPCHIP_RAVA_IN,		// �n�⒆
		MAPCHIP_RAVA_UP,		// �n���
		MAPCHIP_CHECK_POINT,	// ���Ԓn�_
		MAPCHIP_OFF_PARTS,		// OFF�p�[�c
		MAPCHIP_OFF_BLOCK,		// OFF�u���b�N
		MAPCHIP_OFF_GRID,		// OFF�_��
		MAPCHIP_OFF_SWITCH,		// OFF�X�C�b�`
		MAPCHIP_OFF_SWITCH_BLOCK,// OFF�X�C�b�`�u���b�N
		MAPCHIP_ON_PARTS,		// ON�p�[�c
		MAPCHIP_ON_BLOCK,		// ON�u���b�N
		MAPCHIP_ON_GRID,		// ON�_��
		MAPCHIP_ON_SWITCH,		// ON�X�C�b�`
		MAPCHIP_ON_SWITCH_BLOCK,// ON�X�C�b�`�u���b�N
		MAPCHIP_DOOR_0,			// �h�A��
		MAPCHIP_SPRING_0,		// �o�l�c
		MAPCHIP_SPRING_1,		// �o�l��
		MAPCHIP_SPIKE_0,		// �g�Q
		MAPCHIP_SPIKE_1,		// �g�Q�g�Q
		MAPCHIP_SPIKE_2,		// �g�Q��
		MAPCHIP_STEAR,			// ��q
		MAPCHIP_COMBARE_0,		// �R���x�A���[
		MAPCHIP_COMBARE_1,		// �R���x�A����
		MAPCHIP_COMBARE_2,		// �R���x�A�E�[
		MAPCHIP_DOOR_1,			// �h�A��
		MAPCHIP_ARROW_0,		// ���ŔE
		MAPCHIP_ARROW_1,		// ���Ŕ�
		MAPCHIP_ARROW_2,		// ���Ŕ�
		MAPCHIP_ARROW_3,		// ���Ŕ�
		MAPCHIP_ARROW_4,		// ���ŔE�_
		MAPCHIP_ARROW_5,		// ���Ŕ��_
		MAPCHIP_ARROW_6,		// ���Ŕ�_
		MAPCHIP_APPLE_0,		// �����S
		MAPCHIP_APPLE_1,		// �������S
		MAPCHIP_BAWLE,			// �{�E��
		MAPCHIP_PEPPER,			// �g�E�K���V
		MAPCHIP_SPHERE_R,		// �ԋ�
		MAPCHIP_SPHERE_B,		// ��
		MAPCHIP_SPHERE_G,		// �΋�
		MAPCHIP_CAKE,			// �P�[�L
		MAPCHIP_COIN,			// �R�C��
		MAPCHIP_BRANK0,			// ��C
		MAPCHIP_BRANK1,			// ��C
		MAPCHIP_BRANK2,			// ��C

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
