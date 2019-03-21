//=============================================================================
//
// プレイヤーの背景処理 [playerBackground.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _PLAYER_BACKGROUND_H_
#define _PLAYER_BACKGROUND_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// レコードプレイヤー
#define	TEXTURE_RECORD_PLAYER		_T("data/TEXTURE/wood.jpg")			// 読み込むテクスチャファイル名
// レコードディスク				   
#define	TEXTURE_DISK				_T("data/TEXTURE/lpdisk.png")		// 読み込むテクスチャファイル名
// レコードプレイヤー								   
#define	TEXTURE_BACKGROUND			_T("data/TEXTURE/redTheme.jpg")		// 読み込むテクスチャファイル名
// レコードアーム								   
#define	TEXTURE_ARM					_T("data/TEXTURE/LpArm.png")		// 読み込むテクスチャファイル名

// 座標
#define RECORD_PLAYER_POS			D3DXVECTOR3(280.0f,0.0f,0.0f)
// サイズ
#define RECORD_DISK_SIZE_X			(720)
#define RECORD_DISK_SIZE_Y			(720)
#define RECORD_ARM_SIZE_X			(200)
#define RECORD_ARM_SIZE_Y			(350)

// ローテーション	
#define	LP_RECORD_MOVIE_Z			(-0.8f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerBackground(int InitType);
void UninitPlayerBackground(void);
void UpdatePlayerBackground(void);
void DrawPlayerBackground(void);

#endif
