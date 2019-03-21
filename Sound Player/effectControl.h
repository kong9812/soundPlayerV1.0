//=============================================================================
//
// エフェクトのコントロール処理 [effectControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _EFFECT_CONTROL_
#define _EFFECT_CONTROL_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 背景
#define EFFECT_CONTROL_BG_POS				D3DXVECTOR3(1140.0f,185.0f,0.0f)
#define EFFECT_CONTROL_BG_COLOR				D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define EFFECT_CONTROL_BG_SIZE_X			(130)
#define EFFECT_CONTROL_BG_SIZE_Y			(175)

// エフェクト
#define EFFECT_CONTROL_FONT_SIZE_X			(15)
#define EFFECT_CONTROL_FONT_SIZE_Y			(30)
#define EFFECT_CONTROL_FONT_INTERVAL		(5)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// ミュージックプレイヤー構造体
{
	LPD3DXFONT	font;
	D3DXCOLOR	color;

}EFFECTCONTROL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffectControl(int InitType);	// 初期化処理
void UninitEffectControl(void);				// 終了処理
void UpdateEffectControl(HWND hWnd);		// 更新処理
void DrawEffectControl(void);				// 描画処理

#endif