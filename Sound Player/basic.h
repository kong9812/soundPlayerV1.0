//=============================================================================
//
// 頂点処理 [basic.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _BASIC_H_
#define _BASIC_H_

//*****************************************************************************
// 定数定義
//*****************************************************************************
// ゲージ方向用
enum GAUGE_DIRECTION
{
	GAUGE_UP,
	GAUGE_RIGHT
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	LPDIRECT3DTEXTURE9	texture;
	VERTEX_2D			vertexWk[NUM_VERTEX];
	D3DXVECTOR3			pos;

}TEXTURE;

//*****************************************************************************
// プロトタイプ宣言(頂点フォーマット)
//*****************************************************************************
// 頂点フォーマット
HRESULT MakeVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点フォーマット(中心座標)
HRESULT MakeVtxCenterData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点フォーマット(分割テクスチャ頂点情報)
HRESULT MakeCutVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern);

//*****************************************************************************
// プロトタイプ宣言(頂点情報の設定)
//*****************************************************************************
// 頂点座標の設定(頂点情報)
void SetVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点座標の設定(中心座標)
void SetVtxCenterData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// 頂点座標の設定(回転用)
void SetVtxRotData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle, float Length);

// テクスチャ座標の設定(スクロール用)
void SetTextureScrollData
(VERTEX_2D *vtx, float distance);

// 頂点座標の設定(ゲージ用)
void SetVtx4PointGaugeDate
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length, int dir);

// テクスチャ座標の設定(数字スクロール用)
void SetTextureNumData
(VERTEX_2D *vtx, float x);

// テクスチャ座標の設定(アニメーション用)
void SetTextureAnimationData
(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY);

// 反射光の設定(一頂点ずつ)
void SetSingleDiffuseData
(VERTEX_2D *vtx, int no, D3DCOLOR color);

// 反射光の設定(全頂点)
void SetAllDiffuseData
(VERTEX_2D *vtx, D3DCOLOR color);

#endif