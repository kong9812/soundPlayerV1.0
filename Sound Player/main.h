//=============================================================================
//
// main処理 [main.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//=============================================================================
// グローバル変数
//=============================================================================
#define SCREEN_WIDTH	(1280)				// ウインドウの幅
#define SCREEN_HEIGHT	(720)				// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標
#define PERCENT			(100)				// パーセント計算用

#define	NUM_VERTEX		(4)					// 頂点数

#define HALF			(2)					// 半分に割る用(2)

#define NUM_POLYGON		(2)					// ポリゴン

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=============================================================================
// 構造体宣言
//=============================================================================
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// 定数定義(enum定義)
//*****************************************************************************
enum E_STAGE		// 画面遷移定数
{
	STAGE_TITLE,
	STAGE_START_GAME,
	STAGE_TUTORIAL,
	STAGE_PAUSE,
	STAGE_WIN,
	STAGE_LOSE
};

enum INIT			// 初期化定数
{
	FIRST_INIT,
	RE_INIT
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス取得関数

void SetStage(int stage);
void SetGameLoop(bool GameLoop);

void SetDebugTutorialMapPos(float MapPos);
void SetDebugStage01MapPos(float MapPos);
void SetPauseStage(int STAGE);
void InitGame(void);

#endif