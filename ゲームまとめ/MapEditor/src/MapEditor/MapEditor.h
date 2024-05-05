#pragma once
#include "DxLib.h"
#include "fstream"
#include "../MathPlus/MathPlus.h"
#include "../Input/Input.h"

// /* <<Switch �Ō�������ƃ}�b�v�`�b�venum�̒ǉ��ɔ���switch���֔�ׂ� */

// �e�}�b�v�̃f�[�^��
const int MAP_DATA_Y = 23;
const int MAP_DATA_X = 40;

// �}�b�v�t�@�C���̃p�X
const char MAP_DEFAULT[] = "Data/Map/map.csv";

// �}�b�v�T�C�Y
const int MAP_SIZE = 32;


class MapData
{
protected:
	// �}�b�v�`�b�v�摜�ꗗ
	enum MapChipType {
		MAPCHIP_NONE = -1,

		MAPCHIP_BLOCK,
		MAPCHIP_KUSA,

		MAPCHIP_MAX
	};
	MapChipType CurrentMCT;

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
	enum ControleIndex {
		CONTROLE_NONE = -1,

		CONTROLE_SET_MCT,
		CONTROLE_SELECT_MCT,
		CONTROLE_SAVE_MAP,

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
