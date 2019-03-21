//=============================================================================
// < SoundTest�v���O���� >
// �G�t�F�N�g�̃R���g���[������ [effectControl.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "Collider.h"
#include "input.h"
#include "playerControl.h"
#include "playerButton.h"
#include "soundEffect.h"
#include "effectControl.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//------------�`�揈��
void DrawEffectControlBG(void);				// �w�i
void DrawEffectControlEffectFont(void);		// �G�t�F�N�g

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TEXTURE			effectControlBG;			// �G�t�F�N�g�R���g���[���[�̔w�i

EFFECTCONTROL	effect[EFFECT_MAX];			// �G�t�F�N�g�\����
//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitEffectControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		{	// �e�N�X�`���̏�����
			effectControlBG.texture = NULL;
		}

		for (int i = 0; i < EFFECT_MAX; i++)
		{
			// ���\���p�t�H���g��ݒ�
			D3DXCreateFont(pDevice, (UINT)EFFECT_CONTROL_FONT_SIZE_Y, (INT)EFFECT_CONTROL_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &effect[i].font);
		}
	}

	{// �w�i�̏�����
		effectControlBG.pos = EFFECT_CONTROL_BG_POS;
	}

	// �t�H���g�F�̏�����
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect->color = BUTTON_NORMAL_COLOR;
	}

	// ���_���̓ǂݍ���
	MakeVtxCenterData(effectControlBG.vertexWk, effectControlBG.pos, EFFECT_CONTROL_BG_SIZE_X, EFFECT_CONTROL_BG_SIZE_Y);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void UninitEffectControl(void)
{
	if (effectControlBG.texture != NULL)
	{// �e�N�X�`���̊J��	  
		effectControlBG.texture->Release();
		effectControlBG.texture = NULL;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void UpdateEffectControl(HWND hWnd)
{
	D3DXVECTOR3 effectPos[EFFECT_MAX];
	MUSICPLAYER *song = GetSong();

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effectPos[i].x = EFFECT_CONTROL_BG_POS.x - EFFECT_CONTROL_BG_SIZE_X / 2;
		effectPos[i].y = (EFFECT_CONTROL_BG_POS.y - EFFECT_CONTROL_BG_SIZE_Y) + (i * (EFFECT_CONTROL_FONT_SIZE_Y + EFFECT_CONTROL_FONT_INTERVAL));
		effectPos[i].z = 0.0f;

		// �G�t�F�N�g�t�H���g�̓����蔻��
		if (CheckHitBB(GetMousePos(hWnd), effectPos[i], CURSOR_SIZE / 32, D3DXVECTOR2(EFFECT_CONTROL_BG_SIZE_X, EFFECT_CONTROL_FONT_SIZE_Y)))
		{
			effect[i].color = BUTTON_PRESS_COLOR;
			effect[i].color = BUTTON_PRESS_COLOR;

			if (IsMouseLeftTriggered() == true)
			{
				song->effectNo = i;
				SetSoundEffect(song->soundBuffer, song->playMode, song->effectNo);
			}
		}

		else
		{
			effect[i].color = BUTTON_NORMAL_COLOR;
			effect[i].color = BUTTON_NORMAL_COLOR;
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawEffectControl(void)
{
	DrawEffectControlBG();				// �w�i
	DrawEffectControlEffectFont();		// �G�t�F�N�g
}

//*****************************************************************************
// �`�揈��(�w�i)
//*****************************************************************************
void DrawEffectControlBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, effectControlBG.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(effectControlBG.vertexWk, EFFECT_CONTROL_BG_COLOR);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &effectControlBG.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// �`�揈��(�G�t�F�N�g)
//*****************************************************************************
void DrawEffectControlEffectFont(void)
{
	RECT rect = { (LONG)EFFECT_CONTROL_BG_POS.x - EFFECT_CONTROL_BG_SIZE_X / 2, (LONG)EFFECT_CONTROL_BG_POS.y - EFFECT_CONTROL_BG_SIZE_Y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		switch(i)
		{
		case NULL_SOUND_EFFECT:
			// Null
			sprintf(str, _T("NULL"));
			break;
		case WATER_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Water"));
			break;
		case CHORUS_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Chorus"));
			break;
		case FLANGER_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Flanger"));
			break;
		case ECHO_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Echo"));
			break;
		case DISTORTION_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Dostortion"));
			break;
		case COMPRESSOR_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Compressor"));
			break;
		case PARAMEQ_SOUND_EFFECT:
			// Water
			sprintf(str, _T("ParamEQ"));
			break;
		case I3DL2REVERB_SOUND_EFFECT:
			// Water
			sprintf(str, _T("3DAudio"));
			break;
		case WAVES_REVERB_SOUND_EFFECT:
			// Water
			sprintf(str, _T("Waves"));
			break;
		default:
			break;
		}

		// �`��
		effect[i].font->DrawText(NULL, str, -1, &rect, DT_LEFT, effect[i].color);

		// �G�t�F�N�g�t�H���g�̍��WY = (�G�t�F�N�g�ԍ� * �t�H���g�̍���) + �t�H���g�̊Ԋu
		rect.top += (EFFECT_CONTROL_FONT_SIZE_Y + EFFECT_CONTROL_FONT_INTERVAL);

	}
}
