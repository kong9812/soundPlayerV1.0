//=============================================================================
// < SoundTestプログラム >
// エフェクトのコントロール処理 [effectControl.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "Collider.h"
#include "input.h"
#include "playerControl.h"
#include "playerButton.h"
#include "soundEffect.h"
#include "effectControl.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//------------描画処理
void DrawEffectControlBG(void);				// 背景
void DrawEffectControlEffectFont(void);		// エフェクト

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TEXTURE			effectControlBG;			// エフェクトコントローラーの背景

EFFECTCONTROL	effect[EFFECT_MAX];			// エフェクト構造体
//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT InitEffectControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		{	// テクスチャの初期化
			effectControlBG.texture = NULL;
		}

		for (int i = 0; i < EFFECT_MAX; i++)
		{
			// 情報表示用フォントを設定
			D3DXCreateFont(pDevice, (UINT)EFFECT_CONTROL_FONT_SIZE_Y, (INT)EFFECT_CONTROL_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &effect[i].font);
		}
	}

	{// 背景の初期化
		effectControlBG.pos = EFFECT_CONTROL_BG_POS;
	}

	// フォント色の初期化
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect->color = BUTTON_NORMAL_COLOR;
	}

	// 頂点情報の読み込み
	MakeVtxCenterData(effectControlBG.vertexWk, effectControlBG.pos, EFFECT_CONTROL_BG_SIZE_X, EFFECT_CONTROL_BG_SIZE_Y);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void UninitEffectControl(void)
{
	if (effectControlBG.texture != NULL)
	{// テクスチャの開放	  
		effectControlBG.texture->Release();
		effectControlBG.texture = NULL;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void UpdateEffectControl(HWND hWnd)
{
	D3DXVECTOR3 effectPos[EFFECT_MAX];
	MUSICPLAYER *song = GetSong();

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effectPos[i].x = EFFECT_CONTROL_BG_POS.x - EFFECT_CONTROL_BG_SIZE_X / 2;
		effectPos[i].y = (EFFECT_CONTROL_BG_POS.y - EFFECT_CONTROL_BG_SIZE_Y) + (i * (EFFECT_CONTROL_FONT_SIZE_Y + EFFECT_CONTROL_FONT_INTERVAL));
		effectPos[i].z = 0.0f;

		// エフェクトフォントの当たり判定
		if (CheckHitBB(GetMousePos(hWnd), effectPos[i], CURSOR_SIZE / 32, D3DXVECTOR2(EFFECT_CONTROL_BG_SIZE_X, EFFECT_CONTROL_FONT_SIZE_Y)))
		{
			effect[i].color = BUTTON_PRESS_COLOR;
			effect[i].color = BUTTON_PRESS_COLOR;

			if (IsMouseLeftTriggered() == true)
			{
				song->effectNo = i;
				SetSoundEffect(song->soundBuffer, song->playMode, song->effectNo);
			}
		}

		else
		{
			effect[i].color = BUTTON_NORMAL_COLOR;
			effect[i].color = BUTTON_NORMAL_COLOR;
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void DrawEffectControl(void)
{
	DrawEffectControlBG();				// 背景
	DrawEffectControlEffectFont();		// エフェクト
}

//*****************************************************************************
// 描画処理(背景)
//*****************************************************************************
void DrawEffectControlBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, effectControlBG.texture);

	// 反射光の設定(全頂点)
	SetAllDiffuseData(effectControlBG.vertexWk, EFFECT_CONTROL_BG_COLOR);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &effectControlBG.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// 描画処理(エフェクト)
//*****************************************************************************
void DrawEffectControlEffectFont(void)
{
	RECT rect = { (LONG)EFFECT_CONTROL_BG_POS.x - EFFECT_CONTROL_BG_SIZE_X / 2, (LONG)EFFECT_CONTROL_BG_POS.y - EFFECT_CONTROL_BG_SIZE_Y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		switch(i)
		{
		case NULL_SOUND_EFFECT:
			// Null
			sprintf(str, _T("NULL"));
			break;
		case WATER_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Water"));
			break;
		case CHORUS_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Chorus"));
			break;
		case FLANGER_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Flanger"));
			break;
		case ECHO_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Echo"));
			break;
		case DISTORTION_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Dostortion"));
			break;
		case COMPRESSOR_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Compressor"));
			break;
		case PARAMEQ_SOUND_EFFECT:
			// Water
			sprintf(str, _T("ParamEQ"));
			break;
		case I3DL2REVERB_SOUND_EFFECT:
			// Water
			sprintf(str, _T("3DAudio"));
			break;
		case WAVES_REVERB_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Waves"));
			break;
		default:
			break;
		}

		// 描画
		effect[i].font->DrawText(NULL, str, -1, &rect, DT_LEFT, effect[i].color);

		// エフェクトフォントの座標Y = (エフェクト番号 * フォントの高さ) + フォントの間隔
		rect.top += (EFFECT_CONTROL_FONT_SIZE_Y + EFFECT_CONTROL_FONT_INTERVAL);

	}
}
