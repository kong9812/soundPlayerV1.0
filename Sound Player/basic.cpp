//=============================================================================
//
// 頂点処理 [basic.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "basic.h"

//=============================================================================
// 頂点フォーマット(頂点情報)
// 引数:頂点情報格納ワーク	座標X,Y,Z	サイズX,Y
//=============================================================================
HRESULT MakeVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	// 頂点座標の設定
	vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y, pos.z);
	vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
	vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + SizeY, pos.z);

	// rhwの設定
	vtx[0].rhw =
	vtx[1].rhw =
	vtx[2].rhw =
	vtx[3].rhw = 1.0f;

	// 反射光の設定
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点フォーマット(中心座標)
//=============================================================================
HRESULT MakeVtxCenterData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vtx[0].vtx.x = pos.x - SizeX;
	vtx[0].vtx.y = pos.y - SizeY;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = pos.x + SizeX;
	vtx[1].vtx.y = pos.y - SizeY;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = pos.x - SizeX;
	vtx[2].vtx.y = pos.y + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = pos.x + SizeX;
	vtx[3].vtx.y = pos.y + SizeY;
	vtx[3].vtx.z = 0.0f;

	// rhwの設定
	vtx[0].rhw =
	vtx[1].rhw =
	vtx[2].rhw =
	vtx[3].rhw = 1.0f;

	// 反射光の設定
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点フォーマット(分割テクスチャ頂点情報)
// 引数:頂点情報格納ワーク	座標X,Y,Z	サイズX,Y
//=============================================================================
HRESULT MakeCutVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern)
{
	// 頂点座標の設定
	vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
	vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y, pos.z);
	vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
	vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + SizeY, pos.z);

	// rhwの設定
	vtx[0].rhw =
	vtx[1].rhw =
	vtx[2].rhw =
	vtx[3].rhw = 1.0f;

	// 反射光の設定
	vtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定(頂点情報)
// 引数:頂点情報格納ワーク	座標X,Y,Z	サイズX,Y
//=============================================================================
void SetVtx4PointData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	// 頂点座標の設定
	vtx[0].vtx.x = pos.x;
	vtx[0].vtx.y = pos.y;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = pos.x + SizeX;
	vtx[1].vtx.y = pos.y;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = pos.x;
	vtx[2].vtx.y = pos.y + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = pos.x + SizeX;
	vtx[3].vtx.y = pos.y + SizeY;
	vtx[3].vtx.z = 0.0f;
}

//=============================================================================
// 頂点座標の設定(中心座標)
//=============================================================================
void SetVtxCenterData(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vtx[0].vtx.x = pos.x - SizeX;
	vtx[0].vtx.y = pos.y - SizeY;
	vtx[0].vtx.z = 0.0f;

	vtx[1].vtx.x = pos.x + SizeX;
	vtx[1].vtx.y = pos.y - SizeY;
	vtx[1].vtx.z = 0.0f;

	vtx[2].vtx.x = pos.x - SizeX;
	vtx[2].vtx.y = pos.y + SizeY;
	vtx[2].vtx.z = 0.0f;

	vtx[3].vtx.x = pos.x + SizeX;
	vtx[3].vtx.y = pos.y + SizeY;
	vtx[3].vtx.z = 0.0f;
}


//=============================================================================
// 頂点座標の設定(回転)
//=============================================================================
void SetVtxRotData(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle,float Length)
{
	// 頂点座標の設定
	vtx[0].vtx.x = pos.x - cosf(angle + rot.z) * Length;
	vtx[0].vtx.y = pos.y - sinf(angle + rot.z) * Length;
	vtx[0].vtx.z = 0.0f;						 

	vtx[1].vtx.x = pos.x + cosf(angle - rot.z) * Length;
	vtx[1].vtx.y = pos.y - sinf(angle - rot.z) * Length;
	vtx[1].vtx.z = 0.0f;						 
												 
	vtx[2].vtx.x = pos.x - cosf(angle - rot.z) * Length;
	vtx[2].vtx.y = pos.y + sinf(angle - rot.z) * Length;
	vtx[2].vtx.z = 0.0f;						 
												 
	vtx[3].vtx.x = pos.x + cosf(angle + rot.z) * Length;
	vtx[3].vtx.y = pos.y + sinf(angle + rot.z) * Length;
	vtx[3].vtx.z = 0.0f;
}

//=============================================================================
// 頂点座標の設定(ゲージ用)
//=============================================================================
void SetVtx4PointGaugeDate(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length,int dir)
{
	// 上向き
	if (dir == GAUGE_UP)
	{
		// 頂点座標の設定
		vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y + Length, pos.z);
		vtx[1].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + Length, pos.z);
		vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
		vtx[3].vtx = D3DXVECTOR3(pos.x + SizeX, pos.y + SizeY, pos.z);
	}

	// 右向き
	else if (dir == GAUGE_RIGHT)
	{
		// 頂点座標の設定
		vtx[0].vtx = D3DXVECTOR3(pos.x, pos.y, pos.z);
		vtx[1].vtx = D3DXVECTOR3(pos.x + (SizeX * Length), pos.y, pos.z);
		vtx[2].vtx = D3DXVECTOR3(pos.x, pos.y + SizeY, pos.z);
		vtx[3].vtx = D3DXVECTOR3(pos.x + (SizeX * Length), pos.y + SizeY, pos.z);
	}
}

//=============================================================================
// テクスチャ座標の設定(数字スクロール用)
//=============================================================================
void SetTextureNumData(VERTEX_2D *vtx, float x)
{
	// テクスチャ座標の設定
	vtx[0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
	vtx[1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
	vtx[2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
	vtx[3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
}

//=============================================================================
// テクスチャ座標の設定(背景スクロール用)
//=============================================================================
void SetTextureScrollData(VERTEX_2D *vtx, float distance)
{
	// テクスチャ座標の設定
	vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + distance);
	vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + distance);
	vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + distance);
	vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + distance);
}

//=============================================================================
// テクスチャ座標の設定(アニメーション用)
//=============================================================================
void SetTextureAnimationData(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY)
{
	// テクスチャ座標の設定
	int x = cntPattern % PatternX;
	int y = cntPattern / PatternX;
	float sizeX = 1.0f / PatternX;
	float sizeY = 1.0f / PatternY;

	vtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	vtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	vtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	vtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 反射光の設定(一頂点ずつ)
//=============================================================================
void SetSingleDiffuseData(VERTEX_2D *vtx, int no, D3DCOLOR color)
{
	// 反射光の設定
	vtx[no].diffuse = color;
}

//=============================================================================
// 反射光の設定(全頂点)
//=============================================================================
void SetAllDiffuseData(VERTEX_2D *vtx, D3DCOLOR color)
{
	// 反射光の設定
	vtx[0].diffuse = color;
	vtx[1].diffuse = color;
	vtx[2].diffuse = color;
	vtx[3].diffuse = color;
}
