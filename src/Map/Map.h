#pragma once
#include"DxLib.h"
#define MAPCHIP_SIZW		(32)		//�}�b�v�`�b�v�̕�
#define MAPCHIP_SIZH		(32)		//�}�b�v�`�b�v�̏c
const int MAP_CHIP_X_NUM = 100;		//�}�b�v�`�b�v�̉�
const int MAP_CHIP_Y_NUM = 30;		//�}�b�v�`�b�v�̏c
class Map
{
private:

public:
	void Init();
	void Load();
	void Draw();
};
extern Map map;
