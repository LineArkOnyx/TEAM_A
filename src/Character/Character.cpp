#include"DxLib.h"
#include"Character.h"
#include"../Input/Input.h"
Character character;
const char CHARACTER_PATH[] = { "a" };
void Character::Init()
{
	x = 0;
	y = 0;
	h = 64;
	w = 32;
	handle = LoadGraph(CHARACTER_PATH);
}
void Character::Move()
{
	if (Input::Key::Keep(KEY_INPUT_A))
	{

	}
	if (Input::Key::Keep(KEY_INPUT_D))
	{

	}
}
void Character::Gravity()
{

}
void Character::Draw()
{
	DrawRotaGraph(x, y, 1.0, 0.0, handle, true);
}
void Character::Step()
{

}