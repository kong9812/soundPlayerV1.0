//=============================================================================
//
// 周波数のコントロール処理 [frequencyControl.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _FREQUENCY_CONTROL_
#define _FREQUENCY_CONTROL_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 背景
#define FREQUENCY_CONTROL_BG_POS			D3DXVECTOR3(1010.0f,400.0f,0.0f)
#define FREQUENCY_CONTROL_BG_COLOR			D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define FREQUENCY_CONTROL_BG_SIZE_X			(260)
#define FREQUENCY_CONTROL_BG_SIZE_Y			(120)

// 周波数
#define FREQUENCY_NUM_POS					D3DXVECTOR2(1010.0f,410.0f)
#define FREQUENCY_NUM_COLOR					D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define FREQUENCY_NUM_FONT_SIZE_X			(20)
#define FREQUENCY_NUM_FONT_SIZE_Y			(40)

// 指示用のテクスチャ
#define	TEXTURE_KEY_SHIFT_UP				_T("data/TEXTURE/Button/ShiftUp.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_KEY_SHIFT_DOWN				_T("data/TEXTURE/Button/ShiftDown.png")		// 読み込むテクスチャファイル名
#define KEY_SHIFT_UP_POS					D3DXVECTOR3(1010.0f,470.0f,0.0f)
#define KEY_SHIFT_DOWN_POS					D3DXVECTOR3(1150.0f,470.0f,0.0f)
#define KEY_SHIFT_SIZE_X					(120.0f)
#define KEY_SHIFT_SIZE_Y					(30.0f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// ミュージックプレイヤー構造体
{
	LPD3DXFONT	font;
	D3DXCOLOR	color;

}FREQUENCYFONT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFrequencyControl(int InitType);		// 初期化
void UninitFrequencyControl(void);				// 終了
void DrawFrequencyControl(void);				// 描画

#endif