#pragma once

class Gameover
{
private:
	int m_hndl;
	int over1;
	int over2;
	int rogocount = 0;

	int m_Blend;		// ���ߗp�ϐ�
	int m_Direction;	// ���ߕ����̕ύX
	int m_BlendSpeed;	// ���߃X�s�[�h

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