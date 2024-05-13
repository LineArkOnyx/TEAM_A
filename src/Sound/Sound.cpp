#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGM�̃p�X
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//���y
	"data/BGM/titleBGM.wav",	//�^�C�g��
	"data/BGM/playBGM.wav",	//�v���C
	"data/BGM/resultBGM.wav",	//���U���g
	"data/BGM/gameoverBGM.wav",	//�Q�[���I�[�o�[

	//����
	"data/sound/bgm/fish.mp3",		//�����\���
	"data/sound/bgm/fishing.mp3",	//�ނ蒆
	"data/sound/bgm/recovery.mp3",	//���A�[�������
	"data/sound/bgm/sea.mp3",		//�C
};

//����
int soundVolume_bgm[BGM_MAX_NUM] =
{
	70,	//�^�C�g��
	55,	//�v���C
	60,	//���U���g

	90,		//�����\���
	70,		//�ނ蒆
	70,		//���A�[�������
	50,		//�C
};

//SE�̃p�X
char seSoundPath[SE_MAX_NUM][255] =
{
	"data/SE/�R�C��.wav",		        //�R�C��
	"data/SE/�_�C�r���O.wav",		    //�_�C�r���O
	"data/SE/�h�A���J����.wav",		    //�h�A���J����
	"data/SE/�h�A��߂�.wav",		    //�h�A��߂�
	"data/SE/�Ƃ�(�P��)�Ɏh����.wav",	//�Ƃ�(�P��)�Ɏh����
	"data/SE/�Ƃ�(����)�Ɏh����.wav",	//�Ƃ�(����)�Ɏh����
	"data/SE/�͂��������.wav",		    //�͂��������
	"data/SE/�΂�.wav",		            //�΂�
	"data/SE/�p���[�A�b�v��.wav",		//�p���[�A�b�v��
	"data/SE/���o�[��|��.wav",		    //���o�[��|��
	"data/SE/�j����.wav",		        //�j����
	"data/SE/�Ő��̏�𑖂�.wav",		//�Ő��̏�𑖂�
	"data/SE/�H�ו����p�N�b.wav",		//�H�ו����p�N�b
	"data/SE/����(�P��).wav",		    //����(�P��)
	"data/SE/���݂���.wav",		    //���݂���
	"data/SE/�u���b�N���󂷉�.wav",		 //�u���b�N���󂷉�
	"data/SE/�W�����v.wav",		         //�W�����v
	"data/SE/�R���x�A.wav",		         //�R���x�A
	
};

//����
int soundVolume_se[SE_MAX_NUM] =
{
	80,			//�R�C��
	70,			//�_�C�r���O
	75,			//�h�A���J����
	70,			//�h�A��߂�
	70,			//�Ƃ�(�P��)�Ɏh����
	100,		//�Ƃ�(����)�Ɏh����
	70,			//�͂��������
	70,			//�΂�
	70,			//�p���[�A�b�v��
	70,			//���o�[��|��
	70,			//�j����
	70,			//�Ő��̏�𑖂�
	60,			//�H�ו����p�N�b
	70,			//����(�P��)
	70,			//���݂���
	70,			//�u���b�N���󂷉�
	60,			//�W�����v
	60,			//�R���x�A
};

//�T�E���h�܂Ƃߏ�����
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
}

//�T�E���h�܂Ƃߔj��
void Sound::Fin()
{
	Bgm::Fin();
	Se::Fin();
}

//BGM�̏�����
void Sound::Bgm::Init()
{
	for (int i = 0; i < BGM_MAX_NUM; i++)
	{
		//�ǂݍ���
		handle[i] = LoadSoundMem(bgmSoundPath[i]);
		//�{�����[���̐ݒ�
		ChangeVolumeSoundMem(255 * soundVolume_bgm[i] / 100, handle[i]);
	}
}
//BGM�̒ʏ폈���F���
void Sound::Bgm::Play(int type)
{
	//BGM�̍Đ�
	if (CheckSoundMem(handle[type]) == 0)
	{
		PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
	}
}
////BGM������Ă��邩
bool Sound::Bgm::Check(int type)//123
{
	if (CheckSoundMem(handle[type]) == 1)
	{
		return false;   //���Ă�����
	}
	else {
		return true;   //���Ă��Ȃ�������
	}
}
//BGM�̉��ʒ��߁F���,����(�߰��ð��)
void Sound::Bgm::SetVolume(int type, int volume)
{
	//���ʂ̐ݒ�i0�`255�j�i����volume���̉��ʂŏo�́j
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}
//BGM�̒�~�F���
void Sound::Bgm::StopSound(int type)
{
	//BGM�̒�~
	StopSoundMem(handle[type]);
}

void Sound::Bgm::Fin()
{
	//BGM�j��
	for (int i = 0; i < BGM_MAX_NUM; i++)
		DeleteSoundMem(handle[i]);
}

//SE�̏�����
void Sound::Se::Init()
{
	for (int i = 0; i < SE_MAX_NUM; i++)
	{
		//�ǂݍ���
		handle[i] = LoadSoundMem(seSoundPath[i]);
		//�{�����[���̐ݒ�
		int vo = soundVolume_se[i];
		SetVolume(i, vo);
	}
}
//SE�̒ʏ폈���F���
void Sound::Se::Play(int type)
{
	//���ʉ��̍Đ�
	PlaySoundMem(handle[type], DX_PLAYTYPE_BACK, true);
}
//SE������Ă��邩
bool Sound::Se::Check(int type)
{
	if (CheckSoundMem(handle[type]) == 1)
	{
		return false;   //���Ă�����
	}
	else {
		return true;   //���Ă��Ȃ�������
	}
}
//SE�̒�~
void Sound::Se::Stop(int type)
{
	//���ʉ����~�߂鏈��
	StopSoundMem(handle[type]);
}
//SE�̉��ʒ��߁F���,����(�߰��ð��)
void Sound::Se::SetVolume(int type, int volume)
{
	//���ʂ̐ݒ�i0�`255�j�i����volume���̉��ʂŏo�́j
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}

void Sound::Se::Fin()
{
	//SE�j��
	for (int i = 0; i < SE_MAX_NUM; i++)
		DeleteSoundMem(handle[i]);
}