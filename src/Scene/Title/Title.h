#pragma once

#define EFFECT_NUM 180					// �g�U��̃G�t�F�N�g��
#define EFFECT_SHOT 5					// ��x�Ɋg�U����G�t�F�N�g��
#define EFFECT_SPEED 5.0f				// �g�U��̃G�t�F�N�g���x
#define M_PI 360

class Title
{
private:
	int m_sound;						// �T�E���h�n���h��
	int m_hndl[3];						// �摜�n���h��

	int m_backrand;						// �w�i����
	int m_effectrand;					// �G�t�F�N�g����

	int m_Blend[2] = { 255, 255 };		// ���ߗp�ϐ�
	int m_Direction[2] = { 1, 1 };		// ���ߕ����̕ύX
	int m_BlendSpeed[2] = { 2, 15 };	// ���߃X�s�[�h

	float m_posX, m_posY;				// �G�t�F�N�g�̍��W
	float m_posX2[EFFECT_NUM],			// �G�t�F�N�g�g�U��̍��W
		m_posY2[EFFECT_NUM];
	float m_speed[EFFECT_NUM];			// �g�U��̑��x
	float m_angle[EFFECT_NUM];			// �g�U��̌���
	float m_gravity;					// �G�t�F�N�g�̏d��
	float m_gravity2[EFFECT_NUM];		// �g�U��̃G�t�F�N�g�̏d��

	int m_R, m_G, m_B;					// �F�p�ϐ� (���F)
	int m_ColorSpeed;					// �F�̕ω��X�s�[�h

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
