#pragma once

class Result
{
private:
	int m_hndl;

	int m_Blend = 255;		//���ߗp�ϐ�
	int m_Direction = 1;	//���ߕ����̕ύX
	int m_BlendSpeed = 15;	//���߃X�s�[�h

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
