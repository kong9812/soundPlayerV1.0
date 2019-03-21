//=============================================================================
// < SoundTestプログラム >
// 周波数のコントロール処理 [frequencyControl.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "playerControl.h"
#include "frequencyControl.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//------------描画処理
void DrawFrequencyControlBG(void);			// 背景
void DrawFrequencyControlFont(void);		// 周波数のフォント
void DrawFrequencyControlUp(void);			// 周波数コントローラー(Up)
void DrawFrequencyControlDown(void);		// 周波数コントローラー(Down)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TEXTURE frequencyControlBG;		// 背景
TEXTURE frequencyControlUp;		// 周波数コントローラー(Up)
TEXTURE frequencyControlDown;	// 周波数コントローラー(Down)

FREQUENCYFONT frequencyNum;		// 周波数のフォント

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitFrequencyControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		frequencyControlBG.texture = NULL;

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)FREQUENCY_NUM_FONT_SIZE_Y, (INT)FREQUENCY_NUM_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &frequencyNum.font);
	
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_KEY_SHIFT_UP,					// ファイルの名前
		&frequencyControlUp.texture);			// 読み込むメモリー
	
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_KEY_SHIFT_DOWN,					// ファイルの名前
		&frequencyControlDown.texture);			// 読み込むメモリー

	}

	{// 座標の初期化
		frequencyControlBG.pos	 = FREQUENCY_CONTROL_BG_POS;
		frequencyControlUp.pos	 = KEY_SHIFT_UP_POS;
		frequencyControlDown.pos = KEY_SHIFT_DOWN_POS;
	}

	{// フォント色の初期化
		frequencyNum.color = FREQUENCY_NUM_COLOR;
	}

	// 頂点情報の読み込み
	MakeVtx4PointData(frequencyControlBG.vertexWk, frequencyControlBG.pos, FREQUENCY_CONTROL_BG_SIZE_X, FREQUENCY_CONTROL_BG_SIZE_Y);
	MakeVtx4PointData(frequencyControlUp.vertexWk, frequencyControlUp.pos, KEY_SHIFT_SIZE_X, KEY_SHIFT_SIZE_Y);
	MakeVtx4PointData(frequencyControlDown.vertexWk, frequencyControlDown.pos, KEY_SHIFT_SIZE_X, KEY_SHIFT_SIZE_Y);


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitFrequencyControl(void)
{
	if (frequencyControlBG.texture != NULL)
	{// テクスチャの開放	  
		frequencyControlBG.texture->Release();
		frequencyControlBG.texture = NULL;
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawFrequencyControl(void)
{
	DrawFrequencyControlBG();	// 背景
	DrawFrequencyControlFont();	// フォント
	DrawFrequencyControlUp();	// 周波数コントローラー(Up)
	DrawFrequencyControlDown();	// 周波数コントローラー(Down)
}

//*****************************************************************************
// 描画処理(背景)
//*****************************************************************************
void DrawFrequencyControlBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, frequencyControlBG.texture);

	// 反射光の設定(全頂点)
	SetAllDiffuseData(frequencyControlBG.vertexWk, FREQUENCY_CONTROL_BG_COLOR);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlBG.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// 描画処理(周波数コントローラーUp)
//*****************************************************************************
void DrawFrequencyControlUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, frequencyControlUp.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlUp.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// 描画処理(周波数コントローラーDown)
//*****************************************************************************
void DrawFrequencyControlDown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, frequencyControlDown.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlDown.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// 描画処理(フォント)
//*****************************************************************************
void DrawFrequencyControlFont(void)
{
	MUSICPLAYER *song = GetSong();
	RECT rect = { (LONG)FREQUENCY_NUM_POS.x, (LONG)FREQUENCY_NUM_POS.y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	// 周波数
	sprintf(str, _T("freq.:%d"),song->frequency);
	frequencyNum.font->DrawText(NULL, str, -1, &rect, DT_LEFT, frequencyNum.color);
}


