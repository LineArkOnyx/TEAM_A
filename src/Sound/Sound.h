#pragma once

enum BGM_TYPE
{	
	//���y
	BGM_TITLE,	//�^�C�g�����
	BGM_PLAY,	//�v���C���
	BGM_RESULT,	//���U���g���
	BGM_GAMEOVER,	//�Q�[���I�[�o�[���

	//����
	BGM_FISH,		//�����\���
	BGM_FISHING,	//�ނ蒆
	BGM_RECOVERY,	//���A�[�������
	BGM_SEA,		//�C

	BGM_MAX_NUM
};

enum SE_TYPE
{
	SE_COIN,		    //�R�C��
	SE_DIVING,	        //�_�C�r���O
	SE_DOOR_OPEN,		//�h�A���J����
	SE_DOOR_CLOSE,		//�h�A��߂�
	SE_THORN_ONE,	    //�Ƃ�(�P��)�Ɏh����
	SE_THORN_PLURAL,	//�Ƃ�(����)�Ɏh����
	SE_LADDER,		    //�͂��������
	SE_SPRING,		    //�΂�
	SE_POWER_UP,		//�p���[�A�b�v��
	SE_LEVER,		    //���o�[��|��
	SE_SWIM,	    	//�j����
	SE_RUN_LAWN,		//�Ő��̏�𑖂�
	SE_EAT,		        //�H�ו����p�N�b
	SE_FOOTFALL,		//����(�P��)
	SE_STEP,		    //���݂���
	SE_BLOAK_DESTRUCTION, //�u���b�N���󂷉�
	SE_JANP,               //�W�����v
	SE_KYATAPIRA,          //�R���x�A

	SE_MAX_NUM
};

class Sound
{
public:
	//�T�E���h�܂Ƃߏ�����
	static void Init();
	static void Fin();

	class Bgm
	{
	private:
		//���n���h��
		static int handle[BGM_MAX_NUM];

	public:
		//BGM�̏�����
		static void Init();

		//BGM�̒ʏ폈���F���
		static void Play(int type);
		//BGM������Ă��邩
		static bool Check(int type);
		//BGM�̉��ʒ��߁F���,����(�߰��ð��)
		static void SetVolume(int type,int volume);
		//BGM�̒�~�F���
		static void StopSound(int type);
		//BGM�̔j���̏���
		static void Fin();
	};

	class Se
	{
	private:
		//���n���h��
		static int handle[SE_MAX_NUM];

	public:
		//SE�̏�����
		static void Init();

		//SE�̒ʏ폈���F���
		static void Play(int type);
		//SE������Ă��邩
		static bool Check(int type);
		//SE�̒�~
		static void Stop(int type);
		//SE�̉��ʒ��߁F���,����(�߰��ð��)
		static void SetVolume(int type,int volume);
		//SE�̔j���̏���
		static void Fin();
	};
};


/*�g�����w��
	//Fin�Ŏg��
	DeleteSoundMem(�Z�Z�Z);
	//�S�폜
	InitSoundMem();

	//BGM�̒�~
	StopSoundMem(Hundle);

	//���ʂ̐ݒ�i0�`255�j�i����80���̉��ʂŏo�́j
	ChangeVolumeSoundMem( 255 * 80 / 100, Handle );

	//���ʉ��̍Đ�
	PlaySoundMem(Hundle, DX_PLAYTYPE_BACK, true);
	//BGM�̍Đ�
	PlaySoundMem(Hundle, DX_PLAYTYPE_LOOP, true);
*/