#pragma once

class Title
{
private:
	int m_hndl[3];						// �摜�n���h��

	int m_backrand;						// �w�i����
	int m_effectrand;					// �G�t�F�N�g����

	int m_Blend[2] = { 255, 255 };		// ���ߗp�ϐ�
	int m_Direction[2] = { 1, 1 };		// ���ߕ����̕ύX
	int m_BlendSpeed[2] = { 2, 15 };	// ���߃X�s�[�h

	float m_posX, m_posY;				// �G�t�F�N�g�̍��W
	float m_gravity;					// �G�t�F�N�g�̏d��

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
