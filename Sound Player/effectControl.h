//=============================================================================
//
// �G�t�F�N�g�̃R���g���[������ [effectControl.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _EFFECT_CONTROL_
#define _EFFECT_CONTROL_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �w�i
#define EFFECT_CONTROL_BG_POS				D3DXVECTOR3(1140.0f,185.0f,0.0f)
#define EFFECT_CONTROL_BG_COLOR				D3DXCOLOR(0.0f,0.0f,0.0f,0.5f)
#define EFFECT_CONTROL_BG_SIZE_X			(130)
#define EFFECT_CONTROL_BG_SIZE_Y			(175)

// �G�t�F�N�g
#define EFFECT_CONTROL_FONT_SIZE_X			(15)
#define EFFECT_CONTROL_FONT_SIZE_Y			(30)
#define EFFECT_CONTROL_FONT_INTERVAL		(5)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct		// �~���[�W�b�N�v���C���[�\����
{
	LPD3DXFONT	font;
	D3DXCOLOR	color;

}EFFECTCONTROL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffectControl(int InitType);	// ����������
void UninitEffectControl(void);				// �I������
void UpdateEffectControl(HWND hWnd);		// �X�V����
void DrawEffectControl(void);				// �`�揈��

#endif