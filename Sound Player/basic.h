//=============================================================================
//
// ���_���� [basic.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _BASIC_H_
#define _BASIC_H_

//*****************************************************************************
// �萔��`
//*****************************************************************************
// �Q�[�W�����p
enum GAUGE_DIRECTION
{
	GAUGE_UP,
	GAUGE_RIGHT
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct
{
	LPDIRECT3DTEXTURE9	texture;
	VERTEX_2D			vertexWk[NUM_VERTEX];
	D3DXVECTOR3			pos;

}TEXTURE;

//*****************************************************************************
// �v���g�^�C�v�錾(���_�t�H�[�}�b�g)
//*****************************************************************************
// ���_�t�H�[�}�b�g
HRESULT MakeVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_�t�H�[�}�b�g(���S���W)
HRESULT MakeVtxCenterData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_�t�H�[�}�b�g(�����e�N�X�`�����_���)
HRESULT MakeCutVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, int PatternX, int PatternY, int cntPattern);

//*****************************************************************************
// �v���g�^�C�v�錾(���_���̐ݒ�)
//*****************************************************************************
// ���_���W�̐ݒ�(���_���)
void SetVtx4PointData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_���W�̐ݒ�(���S���W)
void SetVtxCenterData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY);

// ���_���W�̐ݒ�(��]�p)
void SetVtxRotData
(VERTEX_2D *vtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float angle, float Length);

// �e�N�X�`�����W�̐ݒ�(�X�N���[���p)
void SetTextureScrollData
(VERTEX_2D *vtx, float distance);

// ���_���W�̐ݒ�(�Q�[�W�p)
void SetVtx4PointGaugeDate
(VERTEX_2D *vtx, D3DXVECTOR3 pos, float SizeX, float SizeY, float Length, int dir);

// �e�N�X�`�����W�̐ݒ�(�����X�N���[���p)
void SetTextureNumData
(VERTEX_2D *vtx, float x);

// �e�N�X�`�����W�̐ݒ�(�A�j���[�V�����p)
void SetTextureAnimationData
(VERTEX_2D *vtx, int cntPattern, int PatternX, int PatternY);

// ���ˌ��̐ݒ�(�꒸�_����)
void SetSingleDiffuseData
(VERTEX_2D *vtx, int no, D3DCOLOR color);

// ���ˌ��̐ݒ�(�S���_)
void SetAllDiffuseData
(VERTEX_2D *vtx, D3DCOLOR color);

#endif