#pragma once

class Title
{
private:
	int m_hndl[3];
	int m_rand;

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
