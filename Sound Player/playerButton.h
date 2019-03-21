//=============================================================================
//
// プレイヤーのボタン処理 [playerButton.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _PLAYER_BUTTON_H_
#define _PLAYER_BUTTON_H_

#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 再生ボタン
#define	TEXTURE_BUTTON_PLAY			_T("data/TEXTURE/Button/play.png")		// 読み込むテクスチャファイル名
#define BUTTON_PLAY_POS				D3DXVECTOR3(40.0f,145.0f,0.0f)
#define BUTTON_PLAY_SIZE_X			(17.0f)
#define BUTTON_PLAY_SIZE_Y			(17.0f)
#define BUTTON_PLAY_FONT_POS		D3DXVECTOR3(20.0f,165.0f,0.0f)
#define BUTTON_PLAY_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_PLAY_FONT_SIZE_X		(12)
#define BUTTON_PLAY_FONT_SIZE_Y		(24)

// 一時停止ボタン
#define	TEXTURE_BUTTON_PAUSE		_T("data/TEXTURE/Button/pause.png")		// 読み込むテクスチャファイル名
#define BUTTON_PAUSE_POS			D3DXVECTOR3(40.0f,145.0f,0.0f)
#define BUTTON_PAUSE_SIZE_X			(17.0f)
#define BUTTON_PAUSE_SIZE_Y			(17.0f)
#define BUTTON_PAUSE_FONT_POS		D3DXVECTOR3(20.0f,165.0f,0.0f)
#define BUTTON_PAUSE_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_PAUSE_FONT_SIZE_X	(12)
#define BUTTON_PAUSE_FONT_SIZE_Y	(24)

// 停止
#define	TEXTURE_BUTTON_STOP			_T("data/TEXTURE/Button/stop.png")		// 読み込むテクスチャファイル名
#define BUTTON_STOP_POS				D3DXVECTOR3(100.0f,145.0f,0.0f)
#define BUTTON_STOP_SIZE_X			(17.0f)
#define BUTTON_STOP_SIZE_Y			(17.0f)
#define BUTTON_STOP_FONT_POS		D3DXVECTOR3(80.0f,165.0f,0.0f)
#define BUTTON_STOP_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_STOP_FONT_SIZE_X		(12)
#define BUTTON_STOP_FONT_SIZE_Y		(24)

// ループ
#define	TEXTURE_BUTTON_LOOP			_T("data/TEXTURE/Button/loop.png")		// 読み込むテクスチャファイル名
#define BUTTON_LOOP_POS				D3DXVECTOR3(160.0f,145.0f,0.0f)
#define BUTTON_LOOP_SIZE_X			(17.0f)
#define BUTTON_LOOP_SIZE_Y			(17.0f)
#define BUTTON_LOOP_FONT_POS		D3DXVECTOR3(140.0f,165.0f,0.0f)
#define BUTTON_LOOP_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_LOOP_FONT_SIZE_X		(12)
#define BUTTON_LOOP_FONT_SIZE_Y		(24)

// ミュート
#define	TEXTURE_BUTTON_MUTE			_T("data/TEXTURE/Button/mute.png")		// 読み込むテクスチャファイル名
#define BUTTON_MUTE_POS				D3DXVECTOR3(220.0f,145.0f,0.0f)
#define BUTTON_MUTE_SIZE_X			(17.0f)
#define BUTTON_MUTE_SIZE_Y			(17.0f)
#define BUTTON_MUTE_FONT_POS		D3DXVECTOR3(200.0f,165.0f,0.0f)
#define BUTTON_MUTE_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_MUTE_FONT_SIZE_X		(12)
#define BUTTON_MUTE_FONT_SIZE_Y		(24)

// 早送り
#define	TEXTURE_BUTTON_FORWARD		_T("data/TEXTURE/Button/fastForward.png")		// 読み込むテクスチャファイル名
#define BUTTON_FORWARD_POS			D3DXVECTOR3(190.0f,200.0f,0.0f)
#define BUTTON_FORWARD_SIZE_X		(17.0f)
#define BUTTON_FORWARD_SIZE_Y		(17.0f)
#define BUTTON_FORWARD_FONT_POS		D3DXVECTOR3(160.0f,220.0f,0.0f)
#define BUTTON_FORWARD_FONT_COLOR	D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_FORWARD_FONT_SIZE_X	(12)
#define BUTTON_FORWARD_FONT_SIZE_Y	(24)

// 巻き戻し
#define	TEXTURE_BUTTON_REWIND		_T("data/TEXTURE/Button/rewind.png")		// 読み込むテクスチャファイル名
#define BUTTON_REWIND_POS			D3DXVECTOR3(70.0f,200.0f,0.0f)
#define BUTTON_REWIND_SIZE_X		(17.0f)
#define BUTTON_REWIND_SIZE_Y		(17.0f)
#define BUTTON_REWIND_FONT_POS		D3DXVECTOR3(40.0f,220.0f,0.0f)
#define BUTTON_REWIND_FONT_COLOR	D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_REWIND_FONT_SIZE_X	(12)
#define BUTTON_REWIND_FONT_SIZE_Y	(24)


// ボタンが押されていない時の色
#define BUTTON_PRESS_COLOR			D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)		// 押された時の色(緑)
#define BUTTON_NORMAL_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)	// 押された時の色(白)

// 指示用のテクスチャ
#define	TEXTURE_KEY_UP				_T("data/TEXTURE/Button/Upkey.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_KEY_DOWN			_T("data/TEXTURE/Button/Downkey.png")	// 読み込むテクスチャファイル名
#define	TEXTURE_KEY_LEFT			_T("data/TEXTURE/Button/Leftkey.png")	// 読み込むテクスチャファイル名
#define	TEXTURE_KEY_RIGHT			_T("data/TEXTURE/Button/Rightkey.png")	// 読み込むテクスチャファイル名
#define KEY_UP_POS					D3DXVECTOR3(60.0f,690.0f,0.0f)
#define KEY_DOWN_POS				D3DXVECTOR3(100.0f,690.0f,0.0f)
#define KEY_LEFT_POS				D3DXVECTOR3(155.0f,690.0f,0.0f)
#define KEY_RIGHT_POS				D3DXVECTOR3(210.0f,690.0f,0.0f)
#define KEY_SIZE_X					(15.0f)
#define KEY_SIZE_Y					(15.0f)

// マウスで押せるボタンの数
#define BUTTON_MAX					(8)

// 指示用のテクスチャ数
#define KEY_MAX						(4)

//*****************************************************************************
// 定数定義
//*****************************************************************************
enum BUTTON
{
	BUTTON_PLAY,
	BUTTON_PAUSE,
	BUTTON_STOP,
	BUTTON_LOOP,
	BUTTON_MUTE,
	BUTTON_FORWARD,
	BUTTON_REWIND
};

enum KEY
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// ミュージックプレイヤー構造体
{
	LPDIRECT3DTEXTURE9		texture;				// テクスチャへのポインタ
	LPD3DXFONT				font;					// 説明用フォント
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 座標

}PLAYERBUTTON;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerButton(int InitType);		// 初期化処理
void UninitPlayerButton(void);				// 終了処理
void UpdatePlayerButton(HWND hWnd);			// 更新処理
void DrawPlayerButton(void);				// 描画処理
PLAYERBUTTON *GetButton(int no);			// ボタンの情報を取得

#endif