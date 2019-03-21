//=============================================================================
// < SoundTest�v���O���� >
// �v���C���[�̔w�i���� [playerBackground.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "playerControl.h"
#include "playerBackground.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawPlayerBackground(void);		// �w�i
void DrawRecordPlayer(void);			// ���R�[�h�v���C���[
void DrawLPrecord(void);				// ���R�[�h�f�B�X�N
void DrawLPArm(void);					// ���R�[�h�v���C���[�̃A�[��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TEXTURE					playerBackground;	// �w�i
TEXTURE					recordPlayer;		// ���R�[�h�v���C���[
TEXTURE					LPrecord;			// ���R�[�h�f�B�X�N
TEXTURE					LPArm;				// ���R�[�h�v���C���[�̃A�[��

D3DXVECTOR3				g_Door01Pos;		// ���W

D3DXVECTOR3				LPrecordMovie;		// �ړ���
float					LPrecordAngle;		// �p�x
float					LPrecordLength;		// ���S���璸�_�܂ł̋���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerBackground(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BACKGROUND,							// �t�@�C���̖��O
		&playerBackground.texture);					// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RECORD_PLAYER,						// �t�@�C���̖��O
		&recordPlayer.texture);						// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DISK,								// �t�@�C���̖��O
		&LPrecord.texture);							// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_ARM,								// �t�@�C���̖��O
		&LPArm.texture);							// �ǂݍ��ރ������[		
	}

	{
		LPArm.pos = D3DXVECTOR3(775.0f, 50.0f, 0.0f);
		playerBackground.pos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����ʒu
		recordPlayer.pos		= RECORD_PLAYER_POS;				// �����ʒu
		LPrecord.pos = D3DXVECTOR3(									// �����ʒu
					RECORD_PLAYER_POS.x + RECORD_DISK_SIZE_X / HALF,
					RECORD_PLAYER_POS.y + RECORD_DISK_SIZE_Y / HALF, LP_RECORD_MOVIE_Z);

	}

	LPrecordMovie		= D3DXVECTOR3(0.0f, 0.0f, LP_RECORD_MOVIE_Z);			// �����ړ���
	LPrecordAngle		= atan2f(RECORD_DISK_SIZE_Y, RECORD_DISK_SIZE_X);		// �p�x��������
	LPrecordLength		= D3DXVec2Length(&D3DXVECTOR2(							// ���S���璸�_�܂ł̋���
						RECORD_DISK_SIZE_Y / HALF,
						RECORD_DISK_SIZE_X / HALF));

	// ���_�t�H�[�}�b�g(���쌠�錾)
	MakeVtx4PointData(playerBackground.vertexWk, playerBackground.pos, SCREEN_WIDTH, SCREEN_HEIGHT);
	MakeVtx4PointData(recordPlayer.vertexWk, recordPlayer.pos, RECORD_DISK_SIZE_X, RECORD_DISK_SIZE_Y);
	MakeVtx4PointData(LPrecord.vertexWk, LPrecord.pos, RECORD_DISK_SIZE_X, RECORD_DISK_SIZE_Y);
	MakeVtx4PointData(LPArm.vertexWk, LPArm.pos, RECORD_ARM_SIZE_X, RECORD_ARM_SIZE_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerBackground(void)
{
	if (playerBackground.texture != NULL)
	{// �e�N�X�`���̊J��
		playerBackground.texture->Release();
		playerBackground.texture = NULL;
	}

	if (recordPlayer.texture != NULL)
	{// �e�N�X�`���̊J��
		recordPlayer.texture->Release();
		recordPlayer.texture = NULL;
	}

	if (LPrecord.texture != NULL)
	{// �e�N�X�`���̊J��	  
		LPrecord.texture->Release();
		LPrecord.texture = NULL;
	}

	if (LPArm.texture != NULL)
	{// �e�N�X�`���̊J��	  
		LPArm.texture->Release();
		LPArm.texture = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerBackground(void)
{
	MUSICPLAYER *song = GetSong();
	
	LPrecordMovie.z = LP_RECORD_MOVIE_Z + (2 * D3DX_PI*song->playPos / 100);			// �Đ��̈ʒu�ɂ���ƈړ�����
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerBackground(void)
{
	DrawPlayerBackground();	// �w�i
	DrawRecordPlayer();		// ���R�[�h�v���C���[
	DrawLPrecord();			// ���R�[�h�f�B�X�N
	DrawLPArm();			// ���R�[�h�v���C���[�̃A�[��
}

//=============================================================================
// �`�揈��(�w�i)
//=============================================================================
void DrawPlayerBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, playerBackground.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, playerBackground.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���R�[�h�v���C���[)
//=============================================================================
void DrawRecordPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, recordPlayer.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, recordPlayer.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���R�[�h�f�B�X�N)
//=============================================================================
void DrawLPrecord(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, LPrecord.texture);

	// ���_���W�̐ݒ�(��]�p)
	SetVtxRotData(LPrecord.vertexWk, LPrecord.pos, LPrecordMovie, LPrecordAngle, LPrecordLength);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LPrecord.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���R�[�h�v���C���[�̃A�[��)
//=============================================================================
void DrawLPArm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, LPArm.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, LPArm.vertexWk, sizeof(VERTEX_2D));
}
