//=============================================================================
//
// �v���C���[�̃{�^������ [playerButton.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _PLAYER_BUTTON_H_
#define _PLAYER_BUTTON_H_

#include "sound.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Đ��{�^��
#define	TEXTURE_BUTTON_PLAY			_T("data/TEXTURE/Button/play.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_PLAY_POS				D3DXVECTOR3(40.0f,145.0f,0.0f)
#define BUTTON_PLAY_SIZE_X			(17.0f)
#define BUTTON_PLAY_SIZE_Y			(17.0f)
#define BUTTON_PLAY_FONT_POS		D3DXVECTOR3(20.0f,165.0f,0.0f)
#define BUTTON_PLAY_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_PLAY_FONT_SIZE_X		(12)
#define BUTTON_PLAY_FONT_SIZE_Y		(24)

// �ꎞ��~�{�^��
#define	TEXTURE_BUTTON_PAUSE		_T("data/TEXTURE/Button/pause.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_PAUSE_POS			D3DXVECTOR3(40.0f,145.0f,0.0f)
#define BUTTON_PAUSE_SIZE_X			(17.0f)
#define BUTTON_PAUSE_SIZE_Y			(17.0f)
#define BUTTON_PAUSE_FONT_POS		D3DXVECTOR3(20.0f,165.0f,0.0f)
#define BUTTON_PAUSE_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_PAUSE_FONT_SIZE_X	(12)
#define BUTTON_PAUSE_FONT_SIZE_Y	(24)

// ��~
#define	TEXTURE_BUTTON_STOP			_T("data/TEXTURE/Button/stop.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_STOP_POS				D3DXVECTOR3(100.0f,145.0f,0.0f)
#define BUTTON_STOP_SIZE_X			(17.0f)
#define BUTTON_STOP_SIZE_Y			(17.0f)
#define BUTTON_STOP_FONT_POS		D3DXVECTOR3(80.0f,165.0f,0.0f)
#define BUTTON_STOP_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_STOP_FONT_SIZE_X		(12)
#define BUTTON_STOP_FONT_SIZE_Y		(24)

// ���[�v
#define	TEXTURE_BUTTON_LOOP			_T("data/TEXTURE/Button/loop.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_LOOP_POS				D3DXVECTOR3(160.0f,145.0f,0.0f)
#define BUTTON_LOOP_SIZE_X			(17.0f)
#define BUTTON_LOOP_SIZE_Y			(17.0f)
#define BUTTON_LOOP_FONT_POS		D3DXVECTOR3(140.0f,165.0f,0.0f)
#define BUTTON_LOOP_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_LOOP_FONT_SIZE_X		(12)
#define BUTTON_LOOP_FONT_SIZE_Y		(24)

// �~���[�g
#define	TEXTURE_BUTTON_MUTE			_T("data/TEXTURE/Button/mute.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_MUTE_POS				D3DXVECTOR3(220.0f,145.0f,0.0f)
#define BUTTON_MUTE_SIZE_X			(17.0f)
#define BUTTON_MUTE_SIZE_Y			(17.0f)
#define BUTTON_MUTE_FONT_POS		D3DXVECTOR3(200.0f,165.0f,0.0f)
#define BUTTON_MUTE_FONT_COLOR		D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_MUTE_FONT_SIZE_X		(12)
#define BUTTON_MUTE_FONT_SIZE_Y		(24)

// ������
#define	TEXTURE_BUTTON_FORWARD		_T("data/TEXTURE/Button/fastForward.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_FORWARD_POS			D3DXVECTOR3(190.0f,200.0f,0.0f)
#define BUTTON_FORWARD_SIZE_X		(17.0f)
#define BUTTON_FORWARD_SIZE_Y		(17.0f)
#define BUTTON_FORWARD_FONT_POS		D3DXVECTOR3(160.0f,220.0f,0.0f)
#define BUTTON_FORWARD_FONT_COLOR	D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_FORWARD_FONT_SIZE_X	(12)
#define BUTTON_FORWARD_FONT_SIZE_Y	(24)

// �����߂�
#define	TEXTURE_BUTTON_REWIND		_T("data/TEXTURE/Button/rewind.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define BUTTON_REWIND_POS			D3DXVECTOR3(70.0f,200.0f,0.0f)
#define BUTTON_REWIND_SIZE_X		(17.0f)
#define BUTTON_REWIND_SIZE_Y		(17.0f)
#define BUTTON_REWIND_FONT_POS		D3DXVECTOR3(40.0f,220.0f,0.0f)
#define BUTTON_REWIND_FONT_COLOR	D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)
#define BUTTON_REWIND_FONT_SIZE_X	(12)
#define BUTTON_REWIND_FONT_SIZE_Y	(24)


// �{�^����������Ă��Ȃ����̐F
#define BUTTON_PRESS_COLOR			D3DXCOLOR(0.0f,255.0f,0.0f,255.0f)		// �����ꂽ���̐F(��)
#define BUTTON_NORMAL_COLOR			D3DXCOLOR(255.0f,255.0f,255.0f,255.0f)	// �����ꂽ���̐F(��)

// �w���p�̃e�N�X�`��
#define	TEXTURE_KEY_UP				_T("data/TEXTURE/Button/Upkey.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_KEY_DOWN			_T("data/TEXTURE/Button/Downkey.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_KEY_LEFT			_T("data/TEXTURE/Button/Leftkey.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_KEY_RIGHT			_T("data/TEXTURE/Button/Rightkey.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define KEY_UP_POS					D3DXVECTOR3(60.0f,690.0f,0.0f)
#define KEY_DOWN_POS				D3DXVECTOR3(100.0f,690.0f,0.0f)
#define KEY_LEFT_POS				D3DXVECTOR3(155.0f,690.0f,0.0f)
#define KEY_RIGHT_POS				D3DXVECTOR3(210.0f,690.0f,0.0f)
#define KEY_SIZE_X					(15.0f)
#define KEY_SIZE_Y					(15.0f)

// �}�E�X�ŉ�����{�^���̐�
#define BUTTON_MAX					(8)

// �w���p�̃e�N�X�`����
#define KEY_MAX						(4)

//*****************************************************************************
// �萔��`
//*****************************************************************************
enum BUTTON
{
	BUTTON_PLAY,
	BUTTON_PAUSE,
	BUTTON_STOP,
	BUTTON_LOOP,
	BUTTON_MUTE,
	BUTTON_FORWARD,
	BUTTON_REWIND
};

enum KEY
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~���[�W�b�N�v���C���[�\����
{
	LPDIRECT3DTEXTURE9		texture;				// �e�N�X�`���ւ̃|�C���^
	LPD3DXFONT				font;					// �����p�t�H���g
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// ���W

}PLAYERBUTTON;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerButton(int InitType);		// ����������
void UninitPlayerButton(void);				// �I������
void UpdatePlayerButton(HWND hWnd);			// �X�V����
void DrawPlayerButton(void);				// �`�揈��
PLAYERBUTTON *GetButton(int no);			// �{�^���̏����擾

#endif