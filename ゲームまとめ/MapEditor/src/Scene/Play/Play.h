#pragma once
#include "../../MapEditor/MapEditor.h"

class Play
{
private:
	MapEditor mapeditor;
	int MousePointBufX;
	int MousePointBufY;
public:
	//������
	void Init();
	//�ʏ폈��
	void Step();
	//�`�揈��
	void Draw();
	//�I������
	void Fin();
};
