//=============================================================================
// < SoundTestプログラム >
// プレイヤーのコントロール処理 [playerControl.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "playerBackground.h"
#include "soundEffect.h"
#include "playerControl.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//------------描画処理
void DrawPlayerSongFont(void);				// 曲名
void DrawPlayingPositionBarBG(void);		// 再生位置バー(背景)
void DrawPlayingPositionBar(void);			// 再生位置バー
void DrawVolumeBarNum(void);				// 各音量バーの数字
void DrawVolumeBarTag(void);				// 各音量バーのタグ
void DrawVolumeBarBG(void);					// 音量バー(背景)
void DrawVolumeBarMain(void);				// メイン音量バー
void DrawVolumeBarBalance(void);			// 相対音量バー
void DrawReset(void);						// リセットの背景
void DrawPlayerResetFont(void);				// リセット

//------------更新処理
//----設定
void SetSoundPlayingVolume(void);			// 音量
void SetSoundPlayingBalanceVolume(void);	// 相対音量
void SetSoundPlayingPosition(HWND hWnd);	// 再生位置
void SetSoundPlayingFrequency(void);		// 周波数
void SetSoundPlayingLoop(void);				// ループ
void SetSoundPlayingReset(void);			// リセット
//----情報取得
void GetSoundPlayingVolume(void);			// 音量
void GetSoundPlayingPosition(void);			// 再生位置

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPD3DXFONT			g_pD3DXFontSongName = NULL;		// フォントへのポインタ
LPD3DXFONT			g_pD3DXFontBalance = NULL;		// フォントへのポインタ
LPD3DXFONT			g_pD3DXFontReset = NULL;		// フォントへのポインタ

TEXTURE				volumeBarBG;					// 音量バーの背景
TEXTURE				positionBarBG;					// 再生位置バーの背景
TEXTURE				positionBar;					// 再生位置バー
TEXTURE				positionBarBall;				// 再生位置を表すボール
TEXTURE				resetBG;						// リセットの背景
TEXTURE				resetKey;						// リセットのキー

MUSICPLAYER			songWk;							// ミュージックプレイヤー構造体
VOLUMEBAR			volumeBarWk[VOLUME_BAR_MAX];	// 音量バー構造体

float				SongFontCnt;					// 文字ループ用カウンター

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MUSICPLAYER *song = GetSong();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		{	// テクスチャの初期化
			volumeBarBG.texture		= NULL;
			positionBarBG.texture	= NULL;
			positionBar.texture		= NULL;
			positionBarBall.texture = NULL;
			resetBG.texture			= NULL;
		}

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_DISK,						// ファイルの名前
		&positionBarBall.texture);			// 読み込むメモリー

		// テクスチャの読込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
		TEXTURE_RESET_KEY,					// ファイルの名前
		&resetKey.texture);					// 読み込むメモリー


		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)SONG_NAME_SIZE_Y, (INT)SONG_NAME_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontSongName);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontBalance);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET, 
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_MAIN].value);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_LEFT].value);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_RIGHT].value);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_MAIN].tag);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_LEFT].tag);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_RIGHT].tag);

		// 情報表示用フォントを設定
		D3DXCreateFont(pDevice, (UINT)RESET_FONT_SIZE_Y, (INT)RESET_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontReset);
	}

	{	// 音量バーの初期化
		// 長さ
		volumeBarWk[BAR_MAIN].length = 0.0f;
		volumeBarWk[BAR_LEFT].length = 0.0f;
		volumeBarWk[BAR_RIGHT].length = 0.0f;

		// 座標
		volumeBarWk[BAR_MAIN].texture.pos = VOLUME_BAR_MAIN_POS;
		volumeBarWk[BAR_LEFT].texture.pos = VOLUME_BAR_LEFT_POS;
		volumeBarWk[BAR_RIGHT].texture.pos = VOLUME_BAR_RIGHT_POS;
	}

	{	// 再生位置バーの初期化
		positionBarBall.pos = PLAYING_POSITION_BAR_POS;
		positionBarBall.pos.y = PLAYING_POSITION_BAR_POINT_POS_Y;
	}

	{	// サウンドの読込み
		song->soundBuffer		= LoadSound();						// ロード
		song->playPosByte		= 0;								// 再生位置(バイト単位)
		song->sizeByte			= 0;								// サイズ(バイト単位)
		song->mainVolume		= 0.0f;								// メイン音量
		song->balanceVolume		= 0l;								// 左右音量(db)  負数=左>右 0=中 正数=右>左
		song->playPos			= 0.0f;								// 再生位置(パーセント)
		song->effectNo			= NULL_SOUND_EFFECT;				// エフェクトの番号
		song->frequency			= (int)GetSoundInitFrequency();		// 周波数
	}

	{	// 再生モードの初期化
		song->playMode = E_DS8_FLAG_LOOP;
	}

	SongFontCnt = 0;

	// 頂点情報の読み込み
	MakeVtx4PointData(volumeBarBG.vertexWk, VOLUME_BAR_BG_POS, VOLUME_BAR_BG_SIZE_X, VOLUME_BAR_BG_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_MAIN].texture.vertexWk, volumeBarWk[BAR_MAIN].texture.pos, VOLUME_BAR_MAIN_SIZE_X, VOLUME_BAR_MAIN_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_LEFT].texture.vertexWk, volumeBarWk[BAR_LEFT].texture.pos, VOLUME_BAR_LEFT_SIZE_X, VOLUME_BAR_LEFT_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_RIGHT].texture.vertexWk, volumeBarWk[BAR_RIGHT].texture.pos, VOLUME_BAR_RIGHT_SIZE_X, VOLUME_BAR_RIGHT_SIZE_Y);
	MakeVtx4PointData(positionBarBG.vertexWk, PLAYING_POSITION_BAR_BG_POS, PLAYING_POSITION_BAR_BG_SIZE_X, PLAYING_POSITION_BAR_BG_SIZE_Y);
	MakeVtx4PointData(positionBar.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_SIZE_X, PLAYING_POSITION_BAR_SIZE_Y);
	MakeVtxCenterData(positionBarBall.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y);
	MakeVtx4PointData(resetBG.vertexWk, RESET_BG_POS, RESET_BG_SIZE_X, RESET_BG_SIZE_Y);
	MakeVtx4PointData(resetKey.vertexWk, RESET_KEY_POS, RESET_KEY_SIZE_X, RESET_KEY_SIZE_Y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerControl(void)
{
	MUSICPLAYER *song = GetSong();
	VOLUMEBAR *volumeBar = GetVolumeBar(0);

	for (int i = 0; i < VOLUME_BAR_MAX; i++, volumeBar++)
	{
		if (volumeBar->texture.texture != NULL)
		{// テクスチャの開放	  
			volumeBar->texture.texture->Release();
			volumeBar->texture.texture = NULL;
		}
	}

	if (volumeBarBG.texture != NULL)
	{// テクスチャの開放	  
		volumeBarBG.texture->Release();
		volumeBarBG.texture = NULL;
	}

	if (positionBarBG.texture != NULL)
	{// テクスチャの開放	
		positionBarBG.texture->Release();
		positionBarBG.texture = NULL;
	}

	if (positionBar.texture != NULL)
	{// テクスチャの開放	
		positionBar.texture->Release();
		positionBar.texture = NULL;
	}

	if (positionBarBall.texture != NULL)
	{// テクスチャの開放	
		positionBarBall.texture->Release();
		positionBarBall.texture = NULL;
	}

	if (resetBG.texture != NULL)
	{// テクスチャの開放	
		resetBG.texture->Release();
		resetBG.texture = NULL;
	}

	if (resetKey.texture != NULL)
	{// テクスチャの開放	
		resetKey.texture->Release();
		resetKey.texture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerControl(HWND hWnd)
{
	// 設定処理
	{
		// 音量
		SetSoundPlayingVolume();

		// 相対音量
		SetSoundPlayingBalanceVolume();

		// 再生位置
		SetSoundPlayingPosition(hWnd);

		// 周波数
		SetSoundPlayingFrequency();

		// リセット
		SetSoundPlayingReset();
	}

	// 取得処理
	{
		// 音量
		GetSoundPlayingVolume();

		// 再生位置
		GetSoundPlayingPosition();
	}
}

//=============================================================================
// 再生・一時停止
//=============================================================================
void SetSoundPlayPause(void)
{
	MUSICPLAYER *song = GetSong();

	// 再生
	if (!IsPlaying(song->soundBuffer))
	{
		PlaySound(song->soundBuffer, song->playMode);
	}

	// 一時停止
	else if (IsPlaying(song->soundBuffer))
	{
		PauseSound(song->soundBuffer);
	}
}

//=============================================================================
// 停止
//=============================================================================
void SetSoundStop(void)
{
	MUSICPLAYER *song = GetSong();

	StopSound(song->soundBuffer);			// 停止
}

//=============================================================================
// 音量を取得
//=============================================================================
void GetSoundPlayingVolume(void)
{
	MUSICPLAYER *song = GetSong();

	// 取得
	song->mainVolume = (float)GetSoundVolume(song->soundBuffer);

	// 音量バーの長さ
	volumeBarWk[BAR_MAIN].length = -(song->mainVolume / VOLUME_BAR_MAIN_FULL_VOLUME)*VOLUME_BAR_MAIN_SIZE_Y;
}

//=============================================================================
// 音量を設定
//=============================================================================
void SetSoundPlayingVolume(void)
{
	MUSICPLAYER *song = GetSong();

	if (!GetKeyboardPress(DIK_LSHIFT))
	{
		// 音量調整(UP)
		if (GetKeyboardPress(DIK_UP))
		{
			SetSoundVolume(song->soundBuffer, VOLUME_UP);
		}

		// 音量調整(DOWN)
		else if (GetKeyboardPress(DIK_DOWN))
		{
			SetSoundVolume(song->soundBuffer, VOLUME_DOWN);
		}
	}
}

//=============================================================================
// 相対音量を設定
//=============================================================================
void SetSoundPlayingBalanceVolume(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardPress(DIK_RIGHT))
	{
		song->balanceVolume += PAN_UNIT;

		// オーバフロー防止
		if (song->balanceVolume > DSBPAN_RIGHT)
		{
			song->balanceVolume = DSBPAN_RIGHT;
		}
	}

	else if (GetKeyboardPress(DIK_LEFT))
	{
		song->balanceVolume -= PAN_UNIT;

		// オーバフロー防止
		if (song->balanceVolume < DSBPAN_LEFT)
		{
			song->balanceVolume = DSBPAN_LEFT;
		}
	}

	// 相対音量を設定
	SetSoundBalanceVolume(song->soundBuffer, song->balanceVolume);

	// 相対音量バーの長さ
	volumeBarWk[BAR_LEFT].length = (song->balanceVolume / VOLUME_BAR_LEFT_FULL_VOLUME)*VOLUME_BAR_LEFT_SIZE_Y;
	volumeBarWk[BAR_RIGHT].length = (-song->balanceVolume / VOLUME_BAR_RIGHT_FULL_VOLUME)*VOLUME_BAR_RIGHT_SIZE_Y;
}

//=============================================================================
// 再生位置を取得
//=============================================================================
void GetSoundPlayingPosition(void)
{
	MUSICPLAYER *song = GetSong();

	song->playPosByte = GetSoundCurrentPosition(song->soundBuffer,GET_PLAY);	// 再生位置を取得する
	song->sizeByte = GetSoundSize();											// サイズを取得する
	song->playPos = ((float)song->playPosByte / (float)song->sizeByte) * PERCENT;	// 再生位置のパーセント
}

//=============================================================================
// 再生位置を設定
//=============================================================================
void SetSoundPlayingPosition(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	// 再生位置
	if (CheckHitBB(GetMousePos(hWnd), positionBarBall.pos, CURSOR_SIZE, D3DXVECTOR2(PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y)))
	{
		// 押された
		if (IsMouseLeftPressed())
		{
			// 
			positionBarBall.pos.x = GetMousePos(hWnd).x;

			// 範囲に収まる
			if (positionBarBall.pos.x < PLAYING_POSITION_BAR_POS.x)
			{
				positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x;
			}
			else if (positionBarBall.pos.x > PLAYING_POSITION_BAR_SIZE_X)
			{
				positionBarBall.pos.x = PLAYING_POSITION_BAR_SIZE_X;
			}

			// ボールの位置から再生位置のパーセントへ変換
			song->playPos = (positionBarBall.pos.x - PLAYING_POSITION_BAR_POS.x) * PERCENT / PLAYING_POSITION_BAR_SIZE_X;

			// パーセントからバイトへ変換
			song->playPosByte = (DWORD)((song->playPos / PERCENT) * song->sizeByte);

			// 設定
			SetSoundPosition(song->soundBuffer, SET_DISTANCE, song->playMode, song->playPosByte);
		}

		// 押されてない
		else if(!IsMouseLeftPressed())
		{
			// 再生位置バー
			positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x + (PLAYING_POSITION_BAR_SIZE_X*song->playPos / PERCENT);
		}
	}

	else
	{
		// 再生位置バー
		positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x + (PLAYING_POSITION_BAR_SIZE_X*song->playPos / PERCENT);
	}
}

//=============================================================================
// 周波数を設定
//=============================================================================
void SetSoundPlayingFrequency(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardPress(DIK_LSHIFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{
			song->frequency += FREQ_UNIT;

			// 最大値
			if (song->frequency > DSBFREQUENCY_MAX)
			{
				song->frequency = DSBFREQUENCY_MAX;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_DOWN))
			{
				song->frequency -= FREQ_UNIT;

				// 最小値
				if (song->frequency < DSBFREQUENCY_MIN)
				{ 

					song->frequency = DSBFREQUENCY_MIN;
				}
			}
		}
	}

	SetSoundFrequency(song->soundBuffer, song->frequency);
}

//=============================================================================
// ループ
//=============================================================================
void SetSoundPlayingLoop(void)
{
	MUSICPLAYER *song = GetSong();

	if (IsPlaying(song->soundBuffer))
	{	// 一時停止
		PauseSound(song->soundBuffer);
	}

	if (song->playMode == D3DXPLAY_LOOP)
	{	// 一回だけ
		song->playMode = D3DXPLAY_ONCE;
	}

	else if (song->playMode == D3DXPLAY_ONCE)
	{	// ループ
		song->playMode = D3DXPLAY_LOOP;
	}
}

//=============================================================================
// リセット
//=============================================================================
void SetSoundPlayingReset(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardTrigger(DIK_R))
	{
		song->effectNo = NULL_SOUND_EFFECT;
		song->frequency = GetSoundInitFrequency();
		song->balanceVolume = 0;

		SetSoundFrequency(song->soundBuffer, song->frequency);
		SetSoundEffect(song->soundBuffer, song->playMode, song->effectNo);
		SetSoundBalanceVolume(song->soundBuffer, song->balanceVolume);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerControl(void)
{
	// 曲名
	DrawPlayerSongFont();			// フォント

	// 再生位置バー
	DrawPlayingPositionBarBG();		// 背景
	DrawPlayingPositionBar();		// 再生位置

	// 音量バー
	DrawVolumeBarBG();				// 背景
	DrawVolumeBarMain();			// メイン
	DrawVolumeBarBalance();			// 相対音量
	DrawVolumeBarNum();				// 数字
	DrawVolumeBarTag();				// タグ

	// リセット
	DrawReset();					// キーと背景
	DrawPlayerResetFont();			// リセット
}

//=============================================================================
// 描画処理(再生位置バー背景)
//=============================================================================
void DrawPlayingPositionBarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, positionBarBG.texture);

	// 反射光の設定(全色)
	SetAllDiffuseData(positionBarBG.vertexWk, PLAYING_POSITION_BAR_BG_COLOR);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBarBG.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(再生位置バー)
//=============================================================================
void DrawPlayingPositionBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MUSICPLAYER *song = GetSong();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, positionBar.texture);

	// 反射光の設定(全色)
	SetAllDiffuseData(positionBar.vertexWk, PLAYING_POSITION_BAR_COLOR);

	// 頂点座標の設定(ゲージ用)
	SetVtx4PointGaugeDate(positionBar.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_SIZE_X, PLAYING_POSITION_BAR_SIZE_Y, song->playPos / PERCENT, GAUGE_RIGHT);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBar.vertexWk, sizeof(VERTEX_2D));

	// テクスチャの設定
	pDevice->SetTexture(0, positionBarBall.texture);

	// 頂点座標の設定(頂点情報)
	SetVtx4PointData(positionBarBall.vertexWk, positionBarBall.pos, PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBarBall.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(音量バー背景)
//=============================================================================
void DrawVolumeBarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, volumeBarBG.texture);

	// 反射光の設定(一頂点ずつ)
	SetSingleDiffuseData(volumeBarBG.vertexWk, 0, VOLUME_BAR_BG_COLOR_B);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 1, VOLUME_BAR_BG_COLOR_B);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 2, VOLUME_BAR_BG_COLOR_A);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 3, VOLUME_BAR_BG_COLOR_A);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarBG.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(音量バーメイン)
//=============================================================================
void DrawVolumeBarMain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, volumeBarWk[BAR_MAIN].texture.texture);

	// 反射光の設定(一頂点ずつ)
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 0, VOLUME_BAR_MAIN_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 1, VOLUME_BAR_MAIN_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 2, VOLUME_BAR_MAIN_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 3, VOLUME_BAR_MAIN_COLOR_B);

	// 頂点座標の設定(ゲージ用)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_MAIN].texture.vertexWk, VOLUME_BAR_MAIN_POS, VOLUME_BAR_MAIN_SIZE_X, VOLUME_BAR_MAIN_SIZE_Y, volumeBarWk[BAR_MAIN].length, GAUGE_UP);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_MAIN].texture.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(相対音量バー)
//=============================================================================
void DrawVolumeBarBalance(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, volumeBarWk[BAR_LEFT].texture.texture);

	// 反射光の設定(一頂点ずつ)
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 0, VOLUME_BAR_LEFT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 1, VOLUME_BAR_LEFT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 2, VOLUME_BAR_LEFT_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 3, VOLUME_BAR_LEFT_COLOR_B);

	// 頂点座標の設定(ゲージ用)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_LEFT].texture.vertexWk, VOLUME_BAR_LEFT_POS, VOLUME_BAR_LEFT_SIZE_X, VOLUME_BAR_LEFT_SIZE_Y, volumeBarWk[BAR_LEFT].length, GAUGE_UP);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_LEFT].texture.vertexWk, sizeof(VERTEX_2D));

	// テクスチャの設定
	pDevice->SetTexture(0, volumeBarWk[BAR_RIGHT].texture.texture);

	// 反射光の設定(一頂点ずつ)
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 0, VOLUME_BAR_RIGHT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 1, VOLUME_BAR_RIGHT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 2, VOLUME_BAR_RIGHT_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 3, VOLUME_BAR_RIGHT_COLOR_B);

	// 頂点座標の設定(ゲージ用)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_RIGHT].texture.vertexWk, VOLUME_BAR_RIGHT_POS, VOLUME_BAR_RIGHT_SIZE_X, VOLUME_BAR_RIGHT_SIZE_Y, volumeBarWk[BAR_RIGHT].length, GAUGE_UP);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_RIGHT].texture.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(リセットの背景とキー)
//=============================================================================
void DrawReset(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, resetBG.texture);

	// 反射光の設定(全頂点)
	SetAllDiffuseData(resetBG.vertexWk, RESET_BG_COLOR);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &resetBG.vertexWk, sizeof(VERTEX_2D));

	// テクスチャの設定
	pDevice->SetTexture(0, resetKey.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &resetKey.vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// 描画処理(リセット)
//=============================================================================
void DrawPlayerResetFont(void)
{
	RECT rect = { (LONG)RESET_FONT_POS.x, (LONG)RESET_FONT_POS.y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	// リセット
	sprintf(str, _T("RESET"));
	g_pD3DXFontReset->DrawText(NULL, str, -1, &rect, DT_LEFT, RESET_FONT_COLOR);

}

//=============================================================================
// 描画処理(曲名)
//=============================================================================
void DrawPlayerSongFont(void)
{
	RECT rect = { SONG_NAME_POS_X, SONG_NAME_POS_Y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	SongFontCnt += SONG_NAME_SCROLL_TIME;

	if (*GetSoundName((int)SongFontCnt) == '\0')
	{
		SongFontCnt = 0;
	}

	// 曲名
	// char配列を、一文字ずつ表示する
	sprintf(str, _T("name:%s"), GetSoundName((int)SongFontCnt*2));


	g_pD3DXFontSongName->DrawText(NULL, str, -1, &rect, DT_LEFT, SONG_NAME_FONT_COLOR);
}

//=============================================================================
// 描画処理(各音量バーの数字)
//=============================================================================
void DrawVolumeBarNum(void)
{
	MUSICPLAYER *song = GetSong();
	char str[256];

	// 描画位置
	RECT rect = { (LONG)VOLUME_BAR_MAIN_NUM_POS_X,(LONG)(VOLUME_BAR_MAIN_POS.y + volumeBarWk[BAR_MAIN].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// メイン
	sprintf(str, _T("%d%%"), (int)((song->mainVolume / VOLUME_BAR_MAIN_FULL_VOLUME) * PERCENT)+100);
	volumeBarWk[BAR_MAIN].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);

	// 描画位置
	rect = { (LONG)VOLUME_BAR_LEFT_NUM_POS_X,(LONG)(VOLUME_BAR_LEFT_POS.y + volumeBarWk[BAR_LEFT].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// 左
	sprintf(str, _T("%d%%"), (int)(-(song->balanceVolume / VOLUME_BAR_LEFT_FULL_VOLUME) * 50) + 50);
	volumeBarWk[BAR_LEFT].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);

	// 描画位置
	rect = { (LONG)VOLUME_BAR_RIGHT_NUM_POS_X,(LONG)(VOLUME_BAR_RIGHT_POS.y + volumeBarWk[BAR_RIGHT].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// 右
	sprintf(str, _T("%d%%"), (int)((song->balanceVolume / VOLUME_BAR_RIGHT_FULL_VOLUME)* 50) + 50);
	volumeBarWk[BAR_RIGHT].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);
}

//=============================================================================
// 描画処理(各音量バーのタグ)
//=============================================================================
void DrawVolumeBarTag(void)
{
	char str[256];

	// 描画位置
	RECT rect = { (LONG)VOLUME_BALANCE_TAG_POS_X,(LONG)VOLUME_BALANCE_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// バランス
	sprintf(str, _T("balance"));
	g_pD3DXFontBalance->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BALANCE_TAG_FONT_COLOR);

	// 描画位置
	rect = { (LONG)VOLUME_BAR_MAIN_TAG_POS_X,(LONG)VOLUME_BAR_MAIN_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// メイン
	sprintf(str, _T("main"));
	volumeBarWk[BAR_MAIN].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_MAIN_TAG_FONT_COLOR);

	// 描画位置
	rect = { (LONG)VOLUME_BAR_LEFT_TAG_POS_X,(LONG)VOLUME_BAR_LEFT_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 左
	sprintf(str, _T("left"));
	volumeBarWk[BAR_LEFT].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_LEFT_TAG_FONT_COLOR);

	// 描画位置
	rect = { (LONG)VOLUME_BAR_RIGHT_TAG_POS_X,(LONG)VOLUME_BAR_RIGHT_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// 右
	sprintf(str, _T("right"));
	volumeBarWk[BAR_RIGHT].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_RIGHT_TAG_FONT_COLOR);

}

//=============================================================================
// 曲の情報を取得
//=============================================================================
MUSICPLAYER *GetSong(void)
{
	return &songWk;
}

//=============================================================================
// 音量バーの情報を取得
//=============================================================================
VOLUMEBAR *GetVolumeBar(int no)
{
	return &volumeBarWk[no];
}