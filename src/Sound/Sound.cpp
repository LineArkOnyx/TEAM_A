#include"sound.h"
#include"DxLib.h"

int Sound::Bgm::handle[BGM_MAX_NUM];
int Sound::Se::handle[SE_MAX_NUM];

//BGMのパス
char bgmSoundPath[BGM_MAX_NUM][255] =
{
	//音楽
	"data/BGM/titleBGM.wav",	//タイトル
	"data/BGM/playBGM.wav",	//プレイ
	"data/BGM/resultBGM.wav",	//リザルト
	"data/BGM/gameoverBGM.wav",	//ゲームオーバー

	//環境音
	"data/sound/bgm/fish.mp3",		//魚が暴れる
	"data/sound/bgm/fishing.mp3",	//釣り中
	"data/sound/bgm/recovery.mp3",	//ルアー巻き取り
	"data/sound/bgm/sea.mp3",		//海
};

//音量
int soundVolume_bgm[BGM_MAX_NUM] =
{
	70,	//タイトル
	55,	//プレイ
	60,	//リザルト

	90,		//魚が暴れる
	70,		//釣り中
	70,		//ルアー巻き取り
	50,		//海
};

//SEのパス
char seSoundPath[SE_MAX_NUM][255] =
{
	"data/SE/コイン.wav",		        //コイン
	"data/SE/ダイビング.wav",		    //ダイビング
	"data/SE/ドアを開ける.wav",		    //ドアを開ける
	"data/SE/ドアを閉める.wav",		    //ドアを閉める
	"data/SE/とげ(単体)に刺さる.wav",	//とげ(単体)に刺さる
	"data/SE/とげ(複数)に刺さる.wav",	//とげ(複数)に刺さる
	"data/SE/はしごを上る.wav",		    //はしごを上る
	"data/SE/ばね.wav",		            //ばね
	"data/SE/パワーアップ音.wav",		//パワーアップ音
	"data/SE/レバーを倒す.wav",		    //レバーを倒す
	"data/SE/泳ぐ音.wav",		        //泳ぐ音
	"data/SE/芝生の上を走る.wav",		//芝生の上を走る
	"data/SE/食べ物をパクッ.wav",		//食べ物をパクッ
	"data/SE/足音(単体).wav",		    //足音(単体)
	"data/SE/踏みつけ音.wav",		    //踏みつけ音
	"data/SE/ブロックを壊す音.wav",		 //ブロックを壊す音
	"data/SE/ジャンプ.wav",		         //ジャンプ
	"data/SE/コンベア.wav",		         //コンベア
	
};

//音量
int soundVolume_se[SE_MAX_NUM] =
{
	80,			//コイン
	70,			//ダイビング
	75,			//ドアを開ける
	70,			//ドアを閉める
	70,			//とげ(単体)に刺さる
	100,		//とげ(複数)に刺さる
	70,			//はしごを上る
	70,			//ばね
	70,			//パワーアップ音
	70,			//レバーを倒す
	70,			//泳ぐ音
	70,			//芝生の上を走る
	60,			//食べ物をパクッ
	70,			//足音(単体)
	70,			//踏みつけ音
	70,			//ブロックを壊す音
	60,			//ジャンプ
	60,			//コンベア
};

//サウンドまとめ初期化
void Sound::Init()
{
	Bgm::Init();
	Se::Init();
}

//サウンドまとめ破棄
void Sound::Fin()
{
	Bgm::Fin();
	Se::Fin();
}

//BGMの初期化
void Sound::Bgm::Init()
{
	for (int i = 0; i < BGM_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(bgmSoundPath[i]);
		//ボリュームの設定
		ChangeVolumeSoundMem(255 * soundVolume_bgm[i] / 100, handle[i]);
	}
}
//BGMの通常処理：種類
void Sound::Bgm::Play(int type)
{
	//BGMの再生
	if (CheckSoundMem(handle[type]) == 0)
	{
		PlaySoundMem(handle[type], DX_PLAYTYPE_LOOP, true);
	}
}
////BGMが流れているか
bool Sound::Bgm::Check(int type)//123
{
	if (CheckSoundMem(handle[type]) == 1)
	{
		return false;   //鳴っていたら
	}
	else {
		return true;   //鳴っていなかったら
	}
}
//BGMの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Bgm::SetVolume(int type, int volume)
{
	//音量の設定（0～255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}
//BGMの停止：種類
void Sound::Bgm::StopSound(int type)
{
	//BGMの停止
	StopSoundMem(handle[type]);
}

void Sound::Bgm::Fin()
{
	//BGM破棄
	for (int i = 0; i < BGM_MAX_NUM; i++)
		DeleteSoundMem(handle[i]);
}

//SEの初期化
void Sound::Se::Init()
{
	for (int i = 0; i < SE_MAX_NUM; i++)
	{
		//読み込み
		handle[i] = LoadSoundMem(seSoundPath[i]);
		//ボリュームの設定
		int vo = soundVolume_se[i];
		SetVolume(i, vo);
	}
}
//SEの通常処理：種類
void Sound::Se::Play(int type)
{
	//効果音の再生
	PlaySoundMem(handle[type], DX_PLAYTYPE_BACK, true);
}
//SEが流れているか
bool Sound::Se::Check(int type)
{
	if (CheckSoundMem(handle[type]) == 1)
	{
		return false;   //鳴っていたら
	}
	else {
		return true;   //鳴っていなかったら
	}
}
//SEの停止
void Sound::Se::Stop(int type)
{
	//効果音を止める処理
	StopSoundMem(handle[type]);
}
//SEの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
void Sound::Se::SetVolume(int type, int volume)
{
	//音量の設定（0～255）（↓はvolume％の音量で出力）
	ChangeVolumeSoundMem(255 * volume / 100, handle[type]);
}

void Sound::Se::Fin()
{
	//SE破棄
	for (int i = 0; i < SE_MAX_NUM; i++)
		DeleteSoundMem(handle[i]);
}