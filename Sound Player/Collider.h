//=============================================================================
//
// 当たり判定 [Collider.h]
// Author : 蔡 友剛
//
//=============================================================================
#ifndef _COLLIDER_
#define _COLLIDER_


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// BB当たり判定
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
// BC当たり判定
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);


#endif
