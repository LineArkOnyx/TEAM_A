#pragma once

class Result
{
private:
	int m_hndl;

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
