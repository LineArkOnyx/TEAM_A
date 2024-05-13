#pragma once

enum BGM_TYPE
{	
	//音楽
	BGM_TITLE,	//タイトル画面
	BGM_PLAY,	//プレイ画面
	BGM_RESULT,	//リザルト画面
	BGM_GAMEOVER,	//ゲームオーバー画面

	//環境音
	BGM_FISH,		//魚が暴れる
	BGM_FISHING,	//釣り中
	BGM_RECOVERY,	//ルアー巻き取り
	BGM_SEA,		//海

	BGM_MAX_NUM
};

enum SE_TYPE
{
	SE_COIN,		    //コイン
	SE_DIVING,	        //ダイビング
	SE_DOOR_OPEN,		//ドアを開ける
	SE_DOOR_CLOSE,		//ドアを閉める
	SE_THORN_ONE,	    //とげ(単体)に刺さる
	SE_THORN_PLURAL,	//とげ(複数)に刺さる
	SE_LADDER,		    //はしごを上る
	SE_SPRING,		    //ばね
	SE_POWER_UP,		//パワーアップ音
	SE_LEVER,		    //レバーを倒す
	SE_SWIM,	    	//泳ぐ音
	SE_RUN_LAWN,		//芝生の上を走る
	SE_EAT,		        //食べ物をパクッ
	SE_FOOTFALL,		//足音(単体)
	SE_STEP,		    //踏みつけ音
	SE_BLOAK_DESTRUCTION, //ブロックを壊す音
	SE_JANP,               //ジャンプ
	SE_KYATAPIRA,          //コンベア

	SE_MAX_NUM
};

class Sound
{
public:
	//サウンドまとめ初期化
	static void Init();
	static void Fin();

	class Bgm
	{
	private:
		//音ハンドル
		static int handle[BGM_MAX_NUM];

	public:
		//BGMの初期化
		static void Init();

		//BGMの通常処理：種類
		static void Play(int type);
		//BGMが流れているか
		static bool Check(int type);
		//BGMの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
		static void SetVolume(int type,int volume);
		//BGMの停止：種類
		static void StopSound(int type);
		//BGMの破棄の処理
		static void Fin();
	};

	class Se
	{
	private:
		//音ハンドル
		static int handle[SE_MAX_NUM];

	public:
		//SEの初期化
		static void Init();

		//SEの通常処理：種類
		static void Play(int type);
		//SEが流れているか
		static bool Check(int type);
		//SEの停止
		static void Stop(int type);
		//SEの音量調節：種類,音量(ﾊﾟｰｾﾝﾃｰｼﾞ)
		static void SetVolume(int type,int volume);
		//SEの破棄の処理
		static void Fin();
	};
};


/*使い方指南
	//Finで使う
	DeleteSoundMem(〇〇〇);
	//全削除
	InitSoundMem();

	//BGMの停止
	StopSoundMem(Hundle);

	//音量の設定（0～255）（↓は80％の音量で出力）
	ChangeVolumeSoundMem( 255 * 80 / 100, Handle );

	//効果音の再生
	PlaySoundMem(Hundle, DX_PLAYTYPE_BACK, true);
	//BGMの再生
	PlaySoundMem(Hundle, DX_PLAYTYPE_LOOP, true);
*/