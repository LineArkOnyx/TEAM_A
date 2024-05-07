#pragma once
#include "../../MapEditor/MapEditor.h"

class Play
{
private:
	MapEditor mapeditor;
	int MousePointBufX;
	int MousePointBufY;
public:
	//‰Šú‰»
	void Init();
	//’Êíˆ—
	void Step();
	//•`‰æˆ—
	void Draw();
	//I—¹ˆ—
	void Fin();
};
