//=============================================================================
//
// �v���C���[�̃R���g���[������ [playerControl.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _PLAYER_CONTROL_H_
#define _PLAYER_CONTROL_H_

#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���ʃo�[(�w�i)
#define VOLUME_BAR_BG_POS					D3DXVECTOR3(20.0f,250.0f,0.0f)
#define VOLUME_BAR_BG_SIZE_X				(240.0f)
#define VOLUME_BAR_BG_SIZE_Y				(460.0f)
#define VOLUME_BAR_BG_COLOR_A				D3DXCOLOR(0.5f,0.5f,0.5f,255.0f)
#define VOLUME_BAR_BG_COLOR_B				D3DXCOLOR(0.0f,0.0f,0.0f,100.0f)

// ���ʃo�[(���C��)
#define VOLUME_BAR_MAIN_POS					D3DXVECTOR3(60.0f,310.0f,0.0f)
#define VOLUME_BAR_MAIN_SIZE_X				(40.0f)
#define VOLUME_BAR_MAIN_SIZE_Y				(380.0f)
#define VOLUME_BAR_MAIN_COLOR_A				D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)
#define VOLUME_BAR_MAIN_COLOR_B				D3DXCOLOR(255.0f,255.0f,255.0f,0.0f)
#define VOLUME_BAR_MAIN_FULL_VOLUME			(10000.0f)
#define VOLUME_BAR_MAIN_NUM_POS_X			(60.0f)
#define VOLUME_BAR_MAIN_TAG_POS_X			(60.0f)
#define VOLUME_BAR_MAIN_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_MAIN_TAG_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)

// ���ʃo�[(��)
#define VOLUME_BAR_LEFT_POS					D3DXVECTOR3(135.0f,500.0f,0.0f)
#define VOLUME_BAR_LEFT_SIZE_X				(40.0f)
#define VOLUME_BAR_LEFT_SIZE_Y				(190.0f)
#define VOLUME_BAR_LEFT_COLOR_A				D3DXCOLOR(0.0f,234.0f,126.0f,255.0f)
#define VOLUME_BAR_LEFT_COLOR_B				D3DXCOLOR(0.0f,234.0f,126.0f,0.0f)
#define VOLUME_BAR_LEFT_FULL_VOLUME			(10000.0f)
#define VOLUME_BAR_LEFT_NUM_POS_X			(135.0f)
#define VOLUME_BAR_LEFT_TAG_POS_X			(130.0f)
#define VOLUME_BAR_LEFT_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_LEFT_TAG_FONT_COLOR		D3DXCOLOR(0.0f,0.0f,255.0f,255.0f)

// ���ʃo�[(�E)
#define VOLUME_BAR_RIGHT_POS				D3DXVECTOR3(185.0f,500.0f,0.0f)
#define VOLUME_BAR_RIGHT_SIZE_X				(40.0f)
#define VOLUME_BAR_RIGHT_SIZE_Y				(190.0f)
#define VOLUME_BAR_RIGHT_COLOR_A			D3DXCOLOR(229.0f,0.0f,134.0f,255.0f)
#define VOLUME_BAR_RIGHT_COLOR_B			D3DXCOLOR(229.0f,0.0f,134.0f,0.0f)
#define VOLUME_BAR_RIGHT_FULL_VOLUME		(10000.0f)
#define VOLUME_BAR_RIGHT_NUM_POS_X			(185.0f)
#define VOLUME_BAR_RIGHT_TAG_POS_X			(180.0f)
#define VOLUME_BAR_RIGHT_TAG_POS_Y			(275.0f)
#define VOLUME_BAR_RIGHT_TAG_FONT_COLOR		D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)

// ���ʃo�[(�^�O)
#define VOLUME_BALANCE_TAG_POS_X			(145.0f)
#define VOLUME_BALANCE_TAG_POS_Y			(255.0f)
#define VOLUME_BALANCE_TAG_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define VOLUME_BAR_TAG_SIZE_X				(15.0f)
#define VOLUME_BAR_TAG_SIZE_Y				(30.0f)

// ���ʃo�[(�l)
#define VOLUME_BAR_NUM_SIZE_X				(10.0f)
#define VOLUME_BAR_NUM_SIZE_Y				(20.0f)
#define VOLUME_BAR_NUM_FONT_COLOR			D3DXCOLOR(0.0f,0.0f,0.0f,255.0f)

// �Ȗ�
#define SONG_NAME_POS_X						(20)
#define SONG_NAME_POS_Y						(20)
#define SONG_NAME_SIZE_X					(25)
#define SONG_NAME_SIZE_Y					(50)
#define SONG_NAME_FONT_COLOR				D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define SONG_NAME_SCROLL_TIME				(0.05f)

// �Đ��ʒu�o�[(�w�i)
#define PLAYING_POSITION_BAR_BG_POS			D3DXVECTOR3(20.0f,80.0f,0.0f)
#define PLAYING_POSITION_BAR_BG_SIZE_X		(240.0f)
#define PLAYING_POSITION_BAR_BG_SIZE_Y		(160.0f)
#define PLAYING_POSITION_BAR_BG_COLOR		D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)

// �Đ��ʒu�o�[
#define PLAYING_POSITION_BAR_POS			D3DXVECTOR3(20.0f,100.0f,0.0f)
#define PLAYING_POSITION_BAR_SIZE_X			(240.0f)
#define PLAYING_POSITION_BAR_SIZE_Y			(10.0f)
#define PLAYING_POSITION_BAR_COLOR			D3DXCOLOR(255.0f,0.0f,0.0f,255.0f)
#define PLAYING_POSITION_BAR_POINT_POS_Y	(95.0f)
#define PLAYING_POSITION_BAR_POINT_SIZE_X	(20)
#define PLAYING_POSITION_BAR_POINT_SIZE_Y	(20)

// ���Z�b�g
#define TEXTURE_RESET_KEY					_T("data/TEXTURE/Button/Rkey.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define RESET_KEY_POS						D3DXVECTOR3(1120.0f,650.0f,0.0f)
#define RESET_KEY_SIZE_X					(30)
#define RESET_KEY_SIZE_Y					(30)
#define RESET_BG_POS						D3DXVECTOR3(1010.0f,580.0f,0.0f)
#define RESET_BG_SIZE_X						(260)
#define RESET_BG_SIZE_Y						(120)
#define RESET_BG_COLOR						D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define RESET_FONT_POS						D3DXVECTOR3(1100.0f,600.0f,0.0f)
#define RESET_FONT_SIZE_X					(15)
#define RESET_FONT_SIZE_Y					(30)
#define RESET_FONT_COLOR					D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)

// �����Đ��\�̋Ȑ�
#define SONG_MAX							(1)

// ���ʃo�[�̐�
#define VOLUME_BAR_MAX						(3)
//*****************************************************************************
// �萔��`
//*****************************************************************************
enum VOLUME_BAR
{
	BAR_MAIN,
	BAR_LEFT,
	BAR_RIGHT
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~���[�W�b�N�v���C���[�\����
{
	LPDIRECTSOUNDBUFFER8	soundBuffer;		// �T�E���h�o�b�t�@
	DWORD					playPosByte;		// �Đ��ʒu(�o�C�g�P��)
	DWORD					sizeByte;			// �T�C�Y(�o�C�g�P��)
	LONG					balanceVolume;		// ���E����(db)  ����=��>�E 0=�� ����=�E>��
	float					mainVolume;			// ���C������
	float					playPos;			// �Đ��ʒu(�p�[�Z���g)
	int						effectNo;			// �G�t�F�N�g�̔ԍ�
	int						frequency;			// ���g��
	int						playMode;			// �Đ�����

}MUSICPLAYER;

typedef struct		// ���ʃo�[
{
	TEXTURE					texture;			// �e�N�X�`���\����(texture,vertexWk,pos)
	LPD3DXFONT				tag;				// �^�O
	LPD3DXFONT				value;				// ���l
	float					length;				// ����

}VOLUMEBAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerControl(int InitType);		// ����������
void UninitPlayerControl(void);					// �I������
void UpdatePlayerControl(HWND hWnd);			// �X�V����
void DrawPlayerControl(void);					// �`�揈��
MUSICPLAYER *GetSong(void);						// �Ȃ̏����擾
VOLUMEBAR *GetVolumeBar(int no);				// ���ʃo�[�̏����擾

//-----------------------------------------------------------------------------
void SetSoundPlayPause(void);					// �Đ��E�ꎞ��~ 
void SetSoundStop(void);						// ��~
void SetSoundPlayingLoop(void);					// ���[�v

#endif