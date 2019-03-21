//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//=============================================================================
// グローバル変数
//=============================================================================
#define POS_UNIT	(10000l)
#define PAN_UNIT	(100l)
#define FREQ_UNIT	(100l)

//=============================================================================
// 定数定義
//=============================================================================
enum
{	// 音量調整用フラグ
	VOLUME_UP,
	VOLUME_DOWN,
	VOLUME_MULT
};

enum
{	// 再生用フラグ
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

enum
{// 再生位置の設定用フラグ
	SET_FORWARD,
	SET_REWIND,
	SET_DISTANCE
};

enum
{// 再生位置の取得用フラグ
	GET_PLAY,
	GET_WRITE
};

//=============================================================================
// プロトタイプ宣言
//=============================================================================
LPDIRECTSOUNDBUFFER8	LoadSound(void);									// サウンドのロード
HRESULT	InitSound(HWND hWnd);												// 初期化
void	UninitSound(void);													// 後片付け
bool	openReadSound(HWND hWnd);											// サウンド読み込み
void	PauseSound(LPDIRECTSOUNDBUFFER8 pBuffer);							// 音を止める
void	StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);							// 音を停止
void	PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0);				// 音ごとに再生
bool	IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);							// 再生中かどうか

// 情報取得
LONG	GetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer);				// 左右の音量を取得
DWORD	GetSoundSize(void);													// サイズを取得
int		GetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer);						// 音量取得
DWORD	GetSoundCurrentPosition(LPDIRECTSOUNDBUFFER8 pBuffer,int type);		// 再生カーソルと書き込みカーソルの位置を取得
int		GetSoundInitFrequency(void);										// 初期周波数を取得
char	*GetSoundPass(void);												// パスを取得
char	*GetSoundName(int no);												// ファイル名を取得
											
// 設定
void SetSoundPosition														// 再生位置の設定
(LPDIRECTSOUNDBUFFER8 pBuffer, int type, int flag, long distance);																			
void SetSoundBalanceVolume													// 左右の音量を設定
(LPDIRECTSOUNDBUFFER8 pBuffer, LONG db);	
void SetSoundVolume															// 音量調整
(LPDIRECTSOUNDBUFFER8 pBuffer, int type);									
void SetSoundEffect															// エフェクト
(LPDIRECTSOUNDBUFFER8 pBuffer, int flag, int effectNo);	
void SetSoundFrequency														// 周波数を設定
(LPDIRECTSOUNDBUFFER8 pBuffer, int freq);				

#endif