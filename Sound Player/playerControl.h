//=============================================================================
//
// プレイヤーのコントロール処理 [playerControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _PLAYER_CONTROL_H_
#define _PLAYER_CONTROL_H_

#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 音量バー(背景)
#define VOLUME_BAR_BG_POS					D3DXVECTOR3(20.0f,250.0f,0.0f)
#define VOLUME_BAR_BG_SIZE_X				(240.0f)
#define VOLUME_BAR_BG_SIZE_Y				(460.0f)
#define VOLUME_BAR_BG_COLOR_A				D3DXCOLOR(0.5f,0.5f,0.5f,255.0f)
#define VOLUME_BAR_BG_COLOR_B				D3DXCOLOR(0.0f,0.0f,0.0f,100.0f)

// 音量バー(メイン)
#define VOLUME_BAR_MAIN_POS					D3DXVECTOR3(60.0f,310.0f,0.0f)
#define VOLUME_BAR_MAIN_SIZE_X				(40.0f)
#define VOLUME_BAR_MAIN_SIZE_Y				(380.0f)
#define VOLUME_BAR_MAIN_COLOR_A				D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
#define VOLUME_BAR_MAIN_COLOR_B				D3DXCOLOR(255.0f,255.0f,255.0f,0.0f)
#define VOLUME_BAR_MAIN_FULL_VOLUME			(10000.0f)
#define VOLUME_BAR_MAIN_NUM_POS_X			(60.0f)
#define VOLUME_BAR_MAIN_TAG_POS_X			(60.0f)
#define VOLUME_BAR_MAIN_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_MAIN_TAG_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)

// 音量バー(左)
#define VOLUME_BAR_LEFT_POS					D3DXVECTOR3(135.0f,500.0f,0.0f)
#define VOLUME_BAR_LEFT_SIZE_X				(40.0f)
#define VOLUME_BAR_LEFT_SIZE_Y				(190.0f)
#define VOLUME_BAR_LEFT_COLOR_A				D3DXCOLOR(0.0f,234.0f,126.0f,255.0f)
#define VOLUME_BAR_LEFT_COLOR_B				D3DXCOLOR(0.0f,234.0f,126.0f,0.0f)
#define VOLUME_BAR_LEFT_FULL_VOLUME			(10000.0f)
#define VOLUME_BAR_LEFT_NUM_POS_X			(135.0f)
#define VOLUME_BAR_LEFT_TAG_POS_X			(130.0f)
#define VOLUME_BAR_LEFT_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_LEFT_TAG_FONT_COLOR		D3DXCOLOR(0.0f,0.0f,255.0f,255.0f)

// 音量バー(右)
#define VOLUME_BAR_RIGHT_POS				D3DXVECTOR3(185.0f,500.0f,0.0f)
#define VOLUME_BAR_RIGHT_SIZE_X				(40.0f)
#define VOLUME_BAR_RIGHT_SIZE_Y				(190.0f)
#define VOLUME_BAR_RIGHT_COLOR_A			D3DXCOLOR(229.0f,0.0f,134.0f,255.0f)
#define VOLUME_BAR_RIGHT_COLOR_B			D3DXCOLOR(229.0f,0.0f,134.0f,0.0f)
#define VOLUME_BAR_RIGHT_FULL_VOLUME		(10000.0f)
#define VOLUME_BAR_RIGHT_NUM_POS_X			(185.0f)
#define VOLUME_BAR_RIGHT_TAG_POS_X			(180.0f)
#define VOLUME_BAR_RIGHT_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_RIGHT_TAG_FONT_COLOR		D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)

// 音量バー(タグ)
#define VOLUME_BALANCE_TAG_POS_X			(145.0f)
#define VOLUME_BALANCE_TAG_POS_Y			(255.0f)
#define VOLUME_BALANCE_TAG_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define VOLUME_BAR_TAG_SIZE_X				(15.0f)
#define VOLUME_BAR_TAG_SIZE_Y				(30.0f)

// 音量バー(値)
#define VOLUME_BAR_NUM_SIZE_X				(10.0f)
#define VOLUME_BAR_NUM_SIZE_Y				(20.0f)
#define VOLUME_BAR_NUM_FONT_COLOR			D3DXCOLOR(0.0f,0.0f,0.0f,255.0f)

// 曲名
#define SONG_NAME_POS_X						(20)
#define SONG_NAME_POS_Y						(20)
#define SONG_NAME_SIZE_X					(25)
#define SONG_NAME_SIZE_Y					(50)
#define SONG_NAME_FONT_COLOR				D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define SONG_NAME_SCROLL_TIME				(0.05f)

// 再生位置バー(背景)
#define PLAYING_POSITION_BAR_BG_POS			D3DXVECTOR3(20.0f,80.0f,0.0f)
#define PLAYING_POSITION_BAR_BG_SIZE_X		(240.0f)
#define PLAYING_POSITION_BAR_BG_SIZE_Y		(160.0f)
#define PLAYING_POSITION_BAR_BG_COLOR		D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)

// 再生位置バー
#define PLAYING_POSITION_BAR_POS			D3DXVECTOR3(20.0f,100.0f,0.0f)
#define PLAYING_POSITION_BAR_SIZE_X			(240.0f)
#define PLAYING_POSITION_BAR_SIZE_Y			(10.0f)
#define PLAYING_POSITION_BAR_COLOR			D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)
#define PLAYING_POSITION_BAR_POINT_POS_Y	(95.0f)
#define PLAYING_POSITION_BAR_POINT_SIZE_X	(20)
#define PLAYING_POSITION_BAR_POINT_SIZE_Y	(20)

// リセット
#define TEXTURE_RESET_KEY					_T("data/TEXTURE/Button/Rkey.png")		// 読み込むテクスチャファイル名
#define RESET_KEY_POS						D3DXVECTOR3(1120.0f,650.0f,0.0f)
#define RESET_KEY_SIZE_X					(30)
#define RESET_KEY_SIZE_Y					(30)
#define RESET_BG_POS						D3DXVECTOR3(1010.0f,580.0f,0.0f)
#define RESET_BG_SIZE_X						(260)
#define RESET_BG_SIZE_Y						(120)
#define RESET_BG_COLOR						D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define RESET_FONT_POS						D3DXVECTOR3(1100.0f,600.0f,0.0f)
#define RESET_FONT_SIZE_X					(15)
#define RESET_FONT_SIZE_Y					(30)
#define RESET_FONT_COLOR					D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)

// 同時再生可能の曲数
#define SONG_MAX							(1)

// 音量バーの数
#define VOLUME_BAR_MAX						(3)
//*****************************************************************************
// 定数定義
//*****************************************************************************
enum VOLUME_BAR
{
	BAR_MAIN,
	BAR_LEFT,
	BAR_RIGHT
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// ミュージックプレイヤー構造体
{
	LPDIRECTSOUNDBUFFER8	soundBuffer;		// サウンドバッファ
	DWORD					playPosByte;		// 再生位置(バイト単位)
	DWORD					sizeByte;			// サイズ(バイト単位)
	LONG					balanceVolume;		// 左右音量(db)  負数=左>右 0=中 正数=右>左
	float					mainVolume;			// メイン音量
	float					playPos;			// 再生位置(パーセント)
	int						effectNo;			// エフェクトの番号
	int						frequency;			// 周波数
	int						playMode;			// 再生方式

}MUSICPLAYER;

typedef struct		// 音量バー
{
	TEXTURE					texture;			// テクスチャ構造体(texture,vertexWk,pos)
	LPD3DXFONT				tag;				// タグ
	LPD3DXFONT				value;				// 数値
	float					length;				// 長さ

}VOLUMEBAR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerControl(int InitType);		// 初期化処理
void UninitPlayerControl(void);					// 終了処理
void UpdatePlayerControl(HWND hWnd);			// 更新処理
void DrawPlayerControl(void);					// 描画処理
MUSICPLAYER *GetSong(void);						// 曲の情報を取得
VOLUMEBAR *GetVolumeBar(int no);				// 音量バーの情報を取得

//-----------------------------------------------------------------------------
void SetSoundPlayPause(void);					// 再生・一時停止 
void SetSoundStop(void);						// 停止
void SetSoundPlayingLoop(void);					// ループ

#endif