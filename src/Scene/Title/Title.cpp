#include"DxLib.h"
#include"Title.h"
#include"../Scene.h"
#include "../../Input/Input.h"
#include <math.h>

#define LOGO	"data/Title/TitleLogo.png"		// ƒƒS
#define BACK	"data/Title/DaytimeBack.png"	// ”wŒi
#define BACK2	"data/Title/NightBack.png"		// ”wŒi.–é
#define SKY		"data/Title/DaytimeSky.png"		// ‹ó
#define SKY2	"data/Title/NightSky.png"		// Â‹ó

#define GRAVITY	0.05f							// d—Í‚Ì’l

//‰Šú‰»
void Title::Init()
{
	m_backrand = GetRand(1);	// —”0`1
	m_effectrand = GetRand(SCREEN_SIZE_X - 10);

	// ”wŒiƒ‰ƒ“ƒ_ƒ€
	if (m_backrand == 0) {
		m_hndl[0] = LoadGraph(SKY);		// ‹ó
		m_hndl[1] = LoadGraph(BACK);	// ”wŒi
	}
	else {
		m_hndl[0] = LoadGraph(SKY2);	// –é‹ó
		m_hndl[1] = LoadGraph(BACK2);	// ”wŒi
	}
	m_hndl[2] = LoadGraph(LOGO);		// ƒƒS

	m_Blend[0] = { 255 };				// “§‰ß—p•Ï”
	m_Blend[1] = { 255 };
	m_Direction[0] = { 1 }; 			// “§‰ß•ûŒü‚Ì•ÏX
	m_Direction[1] = { 1 };
	m_BlendSpeed[0] = { 2 }; 			// “§‰ßƒXƒs[ƒh
	m_BlendSpeed[1] = { 15 };

	m_posX = m_effectrand;
	m_posY = SCREEN_SIZE_Y;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_posX2[i] = m_posX;
		m_posY2[i] = m_posY;
		m_speed[i] = EFFECT_SPEED;
		m_angle[i] = (2 * M_PI / EFFECT_NUM) * i;
	}
	m_gravity = GRAVITY;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_gravity2[i] = m_gravity;
	}

	m_R = 255;
	m_G = 0;
	m_B = 0;
	m_ColorSpeed = 15;

	//’Êíˆ—‚ÖˆÚ“®
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//’Êíˆ—
void Title::Step()
{
	// ƒGƒtƒFƒNƒgˆ—
	m_gravity -= 0.1f;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_gravity2[i] += 0.1f;
	}
	m_posY -= 10.0f + m_gravity;
	for (int i = 0; i < EFFECT_NUM; i++) {
		m_posX2[i] += cos(m_angle[i]/m_gravity) * m_speed[i];
		m_posY2[i] += sin(m_angle[i]/m_gravity) * m_speed[i];
	}
	// ŠgU‘Oˆ—
	if (m_posY < -10.0f || m_posY > SCREEN_SIZE_Y) {
		m_effectrand = GetRand(SCREEN_SIZE_X - 10);
		m_posX = m_effectrand;
		m_gravity = GRAVITY;
		for (int i = 0; i < EFFECT_NUM; i++) {
			m_gravity2[i] = m_gravity;
		}
		m_posY = SCREEN_SIZE_Y;
	}
	// ŠgUŒãˆ—
	if (m_gravity >= -10.0f) {
		for (int i = 0; i < EFFECT_NUM; i++) {
			m_posX2[i] = m_posX;
			m_posY2[i] = m_posY;
		}
	}

	// “øˆ—
	if (m_R == 255 && m_G == 0 && m_B < 255) {
		m_B += m_ColorSpeed;
	}
	else if (m_R > 0 && m_G == 0 && m_B == 255) {
		m_R -= m_ColorSpeed;
	}
	else if (m_R == 0 && m_G < 255 && m_B == 255) {
		m_G += m_ColorSpeed;
	}
	else if (m_R == 0 && m_G == 255 && m_B > 0) {
		m_B -= m_ColorSpeed;
	}
	else if (m_R < 255 && m_G == 255 && m_B == 0) {
		m_R += m_ColorSpeed;
	}
	else if (m_R == 255 && m_G > 0 && m_B == 0) {
		m_G -= m_ColorSpeed;
	}
	// 0‚Æ255’´‚¦‚È‚¢‚æ‚¤’²®
	if (m_R < 0) {
		m_R = 0;
	}
	else if (m_R > 255) {
		m_R = 255;
	}
	else if (m_G < 0) {
		m_G = 0;
	}
	else if (m_G > 255) {
		m_G = 255;
	}
	else if (m_B < 0) {
		m_B = 0;
	}
	else if (m_B > 255) {
		m_B = 255;
	}

	
	if (Input::Key::Push(KEY_INPUT_RETURN) != 0)
		g_CurrentSceneID = SCENE_ID_FIN_TITLE;

}

//•`‰æˆ—
void Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, 0, m_hndl[0], true);			// ‹ó
	DrawGraph(0, 0, m_hndl[1], true);			// ”wŒi

	// ƒGƒtƒFƒNƒgˆ—
	if (m_gravity >= -10.0f)
		DrawBox(m_posX, m_posY, m_posX + 10, m_posY + 10, GetColor(m_R, m_G, m_B), true);

	for (int i = 0; i < EFFECT_NUM; i++) {
		DrawBox(m_posX2[i], m_posY2[i], m_posX2[i] + 10, m_posY2[i] + 10, GetColor(m_R, m_G, m_B), true);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

	// “§‰ßˆ—
	for (int i = 0; i < 2; i++) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Blend[i]);
		if (i == 0) {
			DrawGraph(0, 0, m_hndl[2], true);	// ƒƒS
		}
		else {
			DrawFormatString(SCREEN_SIZE_X / 2.3, SCREEN_SIZE_Y / 1.125, GetColor(255, 0, 255), "Push Enter Key");
		}

		m_Blend[i] -= m_Direction[i] * m_BlendSpeed[i];
		if (m_Blend[i] <= 0 && m_Direction[i] == 1)
		{
			m_Direction[i] = -1;
		}
		else if (m_Blend[i] >= 255 && m_Direction[i] == -1)
		{
			m_Direction[i] = 1;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

//I—¹ˆ—
void Title::Fin()
{
	//DeleteGraph(m_hndl[0]);
	//DeleteGraph(m_hndl[1]);
	//DeleteGraph(m_hndl[2]);

	//Ÿ‚ÌƒV[ƒ“‚ÉˆÚ“®
	g_CurrentSceneID = SCENE_ID_INIT_PLAY;
}
