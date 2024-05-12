#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGM�̃p�X
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//���y
	"data/sound/bgm/titleBGM.mp3",	//�^�C�g��
	"data/BGM/playBGM.wav",	//�v���C
	"data/sound/bgm/resultBGM.mp3",	//���U���g

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
	
};

//����
int soundVolume_se[SE_MAX_NUM] =
{
	80,			//�V�X�e��
	70,			//�ނ��
	75,			//���A�[����
	70,			//�������A�[�ɔ���
	90,			//����ނ���
	100,			//���Ԑ���
	70,			//�Q�[���I��
};

//�T�E���h�܂Ƃߏ�����
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
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
	PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
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
//SE�̉��ʒ��߁F���,����(�߰��ð��)
void Sound::Se::SetVolume(int type, int volume)
{
	//���ʂ̐ݒ�i0�`255�j�i����volume���̉��ʂŏo�́j
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}