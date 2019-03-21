//=============================================================================
// < SoundTestプログラム >
// プレイヤーの背景処理 [playerBackground.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "playerControl.h"
#include "playerBackground.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// 描画処理
void DrawPlayerBackground(void);		// 背景
void DrawRecordPlayer(void);			// レコードプレイヤー
void DrawLPrecord(void);				// レコードディスク
void DrawLPArm(void);					// レコードプレイヤーのアーム

//*****************************************************************************
// グローバル変数
//*****************************************************************************
TEXTURE					playerBackground;	// 背景
TEXTURE					recordPlayer;		// レコードプレイヤー
TEXTURE					LPrecord;			// レコードディスク
TEXTURE					LPArm;				// レコードプレイヤーのアーム

D3DXVECTOR3				g_Door01Pos;		// 座標

D3DXVECTOR3				LPrecordMovie;		// 移動量
float					LPrecordAngle;		// 角度
float					LPrecordLength;		// 中心から頂点までの距離

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayerBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 一回目の初期化
	if (InitType == FIRST_INIT)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_BACKGROUND,							// ファイルの名前
		&playerBackground.texture);					// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RECORD_PLAYER,						// ファイルの名前
		&recordPlayer.texture);						// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_DISK,								// ファイルの名前
		&LPrecord.texture);							// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_ARM,								// ファイルの名前
		&LPArm.texture);							// 読み込むメモリー		
	}

	{
		LPArm.pos = D3DXVECTOR3(775.0f, 50.0f, 0.0f);
		playerBackground.pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 初期位置
		recordPlayer.pos		= RECORD_PLAYER_POS;				// 初期位置
		LPrecord.pos = D3DXVECTOR3(									// 初期位置
					RECORD_PLAYER_POS.x + RECORD_DISK_SIZE_X / HALF,
					RECORD_PLAYER_POS.y + RECORD_DISK_SIZE_Y / HALF, LP_RECORD_MOVIE_Z);

	}

	LPrecordMovie		= D3DXVECTOR3(0.0f, 0.0f, LP_RECORD_MOVIE_Z);			// 初期移動量
	LPrecordAngle		= atan2f(RECORD_DISK_SIZE_Y, RECORD_DISK_SIZE_X);		// 角度を初期化
	LPrecordLength		= D3DXVec2Length(&D3DXVECTOR2(							// 中心から頂点までの距離
						RECORD_DISK_SIZE_Y / HALF,
						RECORD_DISK_SIZE_X / HALF));

	// 頂点フォーマット(著作権宣言)
	MakeVtx4PointData(playerBackground.vertexWk, playerBackground.pos, SCREEN_WIDTH, SCREEN_HEIGHT);
	MakeVtx4PointData(recordPlayer.vertexWk, recordPlayer.pos, RECORD_DISK_SIZE_X, RECORD_DISK_SIZE_Y);
	MakeVtx4PointData(LPrecord.vertexWk, LPrecord.pos, RECORD_DISK_SIZE_X, RECORD_DISK_SIZE_Y);
	MakeVtx4PointData(LPArm.vertexWk, LPArm.pos, RECORD_ARM_SIZE_X, RECORD_ARM_SIZE_Y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayerBackground(void)
{
	if (playerBackground.texture != NULL)
	{// テクスチャの開放
		playerBackground.texture->Release();
		playerBackground.texture = NULL;
	}

	if (recordPlayer.texture != NULL)
	{// テクスチャの開放
		recordPlayer.texture->Release();
		recordPlayer.texture = NULL;
	}

	if (LPrecord.texture != NULL)
	{// テクスチャの開放	  
		LPrecord.texture->Release();
		LPrecord.texture = NULL;
	}

	if (LPArm.texture != NULL)
	{// テクスチャの開放	  
		LPArm.texture->Release();
		LPArm.texture = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayerBackground(void)
{
	MUSICPLAYER *song = GetSong();
	
	LPrecordMovie.z = LP_RECORD_MOVIE_Z + (2 * D3DX_PI*song->playPos / 100);			// 再生の位置によっと移動する
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayerBackground(void)
{
	DrawPlayerBackground();	// 背景
	DrawRecordPlayer();		// レコードプレイヤー
	DrawLPrecord();			// レコードディスク
	DrawLPArm();			// レコードプレイヤーのアーム
}

//=============================================================================
// 描画処理(背景)
//=============================================================================
void DrawPlayerBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, playerBackground.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, playerBackground.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(レコードプレイヤー)
//=============================================================================
void DrawRecordPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, recordPlayer.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, recordPlayer.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(レコードディスク)
//=============================================================================
void DrawLPrecord(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, LPrecord.texture);

	// 頂点座標の設定(回転用)
	SetVtxRotData(LPrecord.vertexWk, LPrecord.pos, LPrecordMovie, LPrecordAngle, LPrecordLength);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LPrecord.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 描画処理(レコードプレイヤーのアーム)
//=============================================================================
void DrawLPArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, LPArm.texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LPArm.vertexWk, sizeof(VERTEX_2D));
}
