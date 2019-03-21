//=============================================================================
// < SoundTestプログラム >
// プレイヤーのボタン処理 [playerButton.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "Collider.h"
#include "playerControl.h"
#include "playerButton.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawButtonPlay(void);		// 再生
void DrawButtonPause(void);		// 一時停止
void DrawButtonStop(void);		// 停止
void DrawButtonLoop(void);		// ループ
void DrawButtonFont(void);		// ボタンのフォント
void DrawButtonMute(void);		// ミュート
void DrawButtonForward(void);	// 早送り
void DrawButtonRewind(void);	// 巻き戻し

void DrawKeyUp(void);			// 上キー
void DrawKeyDown(void);			// 下キー
void DrawKeyLeft(void);			// 左キー
void DrawKeyRight(void);		// 右キー

//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYERBUTTON	buttonWk[BUTTON_MAX];
TEXTURE			key[KEY_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerButton(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_PLAY,						// ファイルの名前
		&buttonWk[BUTTON_PLAY].texture);			// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_PAUSE,						// ファイルの名前
		&buttonWk[BUTTON_PAUSE].texture);			// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_STOP,						// ファイルの名前
		&buttonWk[BUTTON_STOP].texture);			// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_LOOP,						// ファイルの名前
		&buttonWk[BUTTON_LOOP].texture);			// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_MUTE,						// ファイルの名前
		&buttonWk[BUTTON_MUTE].texture);			// 読み込むメモリー
	
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_FORWARD,						// ファイルの名前
		&buttonWk[BUTTON_FORWARD].texture);			// 読み込むメモリー
	
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BUTTON_REWIND,						// ファイルの名前
		&buttonWk[BUTTON_REWIND].texture);			// 読み込むメモリー


		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_KEY_UP,								// ファイルの名前
		&key[KEY_UP].texture);						// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_KEY_DOWN,							// ファイルの名前
		&key[KEY_DOWN].texture);					// 読み込むメモリー
		
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_KEY_LEFT,							// ファイルの名前
		&key[KEY_LEFT].texture);					// 読み込むメモリー
														
		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_KEY_RIGHT,							// ファイルの名前
		&key[KEY_RIGHT].texture);					// 読み込むメモリー

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_PLAY_FONT_SIZE_Y, (INT)BUTTON_PLAY_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_PLAY].font);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_PAUSE_FONT_SIZE_Y, (INT)BUTTON_PAUSE_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_PAUSE].font);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_STOP_FONT_SIZE_Y, (INT)BUTTON_STOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_STOP].font);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_LOOP].font);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_MUTE].font);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_FORWARD].font);
		
		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_REWIND].font);

	}	

	{	// 座標の初期化
		buttonWk[BUTTON_PLAY].pos		= BUTTON_PLAY_POS;
		buttonWk[BUTTON_PAUSE].pos		= BUTTON_PAUSE_POS;
		buttonWk[BUTTON_STOP].pos		= BUTTON_STOP_POS;
		buttonWk[BUTTON_LOOP].pos		= BUTTON_LOOP_POS;
		buttonWk[BUTTON_MUTE].pos		= BUTTON_MUTE_POS;
		buttonWk[BUTTON_FORWARD].pos	= BUTTON_FORWARD_POS;
		buttonWk[BUTTON_REWIND].pos		= BUTTON_REWIND_POS;

		key[KEY_UP].pos					= KEY_UP_POS;
		key[KEY_DOWN].pos				= KEY_DOWN_POS;
		key[KEY_LEFT].pos				= KEY_LEFT_POS;
		key[KEY_RIGHT].pos				= KEY_RIGHT_POS;
	}

	// 頂点情報の読み込み
	MakeVtxCenterData(buttonWk[BUTTON_PLAY].vertexWk, buttonWk[BUTTON_PLAY].pos, BUTTON_PLAY_SIZE_X, BUTTON_PLAY_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_PAUSE].vertexWk, buttonWk[BUTTON_PAUSE].pos, BUTTON_PAUSE_SIZE_X, BUTTON_PAUSE_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_STOP].vertexWk, buttonWk[BUTTON_STOP].pos, BUTTON_STOP_SIZE_X, BUTTON_STOP_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_LOOP].vertexWk, buttonWk[BUTTON_LOOP].pos, BUTTON_LOOP_SIZE_X, BUTTON_LOOP_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_MUTE].vertexWk, buttonWk[BUTTON_MUTE].pos, BUTTON_MUTE_SIZE_X, BUTTON_MUTE_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_FORWARD].vertexWk, buttonWk[BUTTON_FORWARD].pos, BUTTON_FORWARD_SIZE_X, BUTTON_FORWARD_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_REWIND].vertexWk, buttonWk[BUTTON_REWIND].pos, BUTTON_REWIND_SIZE_X, BUTTON_REWIND_SIZE_Y);

	MakeVtxCenterData(key[KEY_UP].vertexWk, key[KEY_UP].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_DOWN].vertexWk, key[KEY_DOWN].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_LEFT].vertexWk, key[KEY_LEFT].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_RIGHT].vertexWk, key[KEY_RIGHT].pos, KEY_SIZE_X, KEY_SIZE_Y);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerButton(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (buttonWk[i].texture != NULL)
		{// テクスチャの開放	  
			buttonWk[i].texture->Release();
			buttonWk[i].texture = NULL;
		}
	}

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (key[i].texture != NULL)
		{// テクスチャの開放	  
			key[i].texture->Release();
			key[i].texture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerButton(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	// 再生・一時停止
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_PLAY].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_PLAY_SIZE_X, BUTTON_PLAY_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_PLAY].vertexWk, BUTTON_PRESS_COLOR);
		SetAllDiffuseData(buttonWk[BUTTON_PAUSE].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundPlayPause();
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_PAUSE].vertexWk, BUTTON_NORMAL_COLOR);
		SetAllDiffuseData(buttonWk[BUTTON_PLAY].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// 停止
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_STOP].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_STOP_SIZE_X, BUTTON_STOP_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_STOP].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundStop();
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_STOP].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// ループ
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_LOOP].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_LOOP_SIZE_X, BUTTON_LOOP_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundPlayingLoop();
		}
	}

	else
	{
		if (song->playMode == E_DS8_FLAG_NONE)
		{
			SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_NORMAL_COLOR);
		}
		else if (song->playMode == E_DS8_FLAG_LOOP)
		{
			SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_PRESS_COLOR);
		}
	}

	// ミュート
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_MUTE].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_MUTE_SIZE_X, BUTTON_MUTE_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_MUTE].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundVolume(song->soundBuffer, VOLUME_MULT);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_MUTE].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// 早送り
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_FORWARD].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_FORWARD_SIZE_X, BUTTON_FORWARD_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_FORWARD].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftPressed() == true)
		{
			SetSoundPosition(song->soundBuffer, SET_FORWARD, song->playMode, NULL);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_FORWARD].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// 巻き戻し
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_REWIND].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_REWIND_SIZE_X, BUTTON_REWIND_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_REWIND].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftPressed() == true)
		{
			SetSoundPosition(song->soundBuffer, SET_REWIND, song->playMode, NULL);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_REWIND].vertexWk, BUTTON_NORMAL_COLOR);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerButton(void)
{
	MUSICPLAYER *song = GetSong();

	if (!IsPlaying(song->soundBuffer))
	{
		DrawButtonPlay();		// 再生
	}
	else if (IsPlaying(song->soundBuffer))
	{
		DrawButtonPause();		// 一時停止
	}

	// 停止
	DrawButtonStop();

	// ループ
	DrawButtonLoop();

	// ミュート
	DrawButtonMute();

	// 早送り
	DrawButtonForward();

	// 巻き戻し
	DrawButtonRewind();

	// 上キー
	DrawKeyUp();

	// 下キー
	DrawKeyDown();

	// 左キー
	DrawKeyLeft();

	// 右キー
	DrawKeyRight();

	// ボタンのフォント
	DrawButtonFont();
}

//=============================================================================
// 描画処理(再生)
//=============================================================================
void DrawButtonPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_PLAY].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_PLAY].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(一時停止)
//=============================================================================
void DrawButtonPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_PAUSE].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_PAUSE].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(停止)
//=============================================================================
void DrawButtonStop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_STOP].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_STOP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(ループ)
//=============================================================================
void DrawButtonLoop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_LOOP].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_LOOP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(ミュート)
//=============================================================================
void DrawButtonMute(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_MUTE].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_MUTE].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(早送り)
//=============================================================================
void DrawButtonForward(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_FORWARD].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_FORWARD].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(巻き戻し)
//=============================================================================
void DrawButtonRewind(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, buttonWk[BUTTON_REWIND].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_REWIND].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(上キー)
//=============================================================================
void DrawKeyUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, key[KEY_UP].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_UP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(下キー)
//=============================================================================
void DrawKeyDown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, key[KEY_DOWN].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_DOWN].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(左キー)
//=============================================================================
void DrawKeyLeft(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, key[KEY_LEFT].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_LEFT].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(右キー)
//=============================================================================
void DrawKeyRight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, key[KEY_RIGHT].texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_RIGHT].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(ボタンのフォント)
//=============================================================================
void DrawButtonFont(void)
{
	MUSICPLAYER *song = GetSong();
	char str[256];

	// 描画位置
	RECT rect = { (LONG)BUTTON_PLAY_FONT_POS.x,(LONG)BUTTON_PLAY_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (!IsPlaying(song->soundBuffer))
	{
		// 再生(PLAY)
		sprintf(str, _T("PLAY"));
		buttonWk[BUTTON_PLAY].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_PLAY_FONT_COLOR);

	}
	else if (IsPlaying(song->soundBuffer))
	{
		// 描画位置
		rect = { (LONG)BUTTON_PAUSE_FONT_POS.x,(LONG)BUTTON_PAUSE_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

		// 一時停止(PAUSE)
		sprintf(str, _T("PAUSE"));
		buttonWk[BUTTON_PAUSE].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_PAUSE_FONT_COLOR);
	}

	// 描画位置
	rect = { (LONG)BUTTON_STOP_FONT_POS.x,(LONG)BUTTON_STOP_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 停止(STOP)
	sprintf(str, _T("STOP"));
	buttonWk[BUTTON_STOP].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_STOP_FONT_COLOR);

	// 描画位置
	rect = { (LONG)BUTTON_LOOP_FONT_POS.x,(LONG)BUTTON_LOOP_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ループ(LOOP)
	sprintf(str, _T("LOOP"));
	buttonWk[BUTTON_LOOP].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_LOOP_FONT_COLOR);

	// 描画位置
	rect = { (LONG)BUTTON_MUTE_FONT_POS.x,(LONG)BUTTON_MUTE_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ミュート
	sprintf(str, _T("MUTE"));
	buttonWk[BUTTON_MUTE].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

	// 描画位置
	rect = { (LONG)BUTTON_FORWARD_FONT_POS.x,(LONG)BUTTON_FORWARD_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 早送り
	sprintf(str, _T("FORWARD"));
	buttonWk[BUTTON_FORWARD].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

	// 描画位置
	rect = { (LONG)BUTTON_REWIND_FONT_POS.x,(LONG)BUTTON_REWIND_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 巻き戻し
	sprintf(str, _T("REWIND"));
	buttonWk[BUTTON_REWIND].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

}

//=============================================================================
// ボタンの情報を取得
//=============================================================================
PLAYERBUTTON *GetButton(int no)
{
	return &buttonWk[no];
}

