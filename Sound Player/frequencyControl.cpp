//=============================================================================
// < SoundTest�v���O���� >
// ���g���̃R���g���[������ [frequencyControl.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "playerControl.h"
#include "frequencyControl.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//------------�`�揈��
void DrawFrequencyControlBG(void);			// �w�i
void DrawFrequencyControlFont(void);		// ���g���̃t�H���g
void DrawFrequencyControlUp(void);			// ���g���R���g���[���[(Up)
void DrawFrequencyControlDown(void);		// ���g���R���g���[���[(Down)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TEXTURE frequencyControlBG;		// �w�i
TEXTURE frequencyControlUp;		// ���g���R���g���[���[(Up)
TEXTURE frequencyControlDown;	// ���g���R���g���[���[(Down)

FREQUENCYFONT frequencyNum;		// ���g���̃t�H���g

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT InitFrequencyControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (InitType == FIRST_INIT)
	{
		frequencyControlBG.texture = NULL;

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)FREQUENCY_NUM_FONT_SIZE_Y, (INT)FREQUENCY_NUM_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &frequencyNum.font);
	
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_SHIFT_UP,					// �t�@�C���̖��O
		&frequencyControlUp.texture);			// �ǂݍ��ރ������[
	
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_SHIFT_DOWN,					// �t�@�C���̖��O
		&frequencyControlDown.texture);			// �ǂݍ��ރ������[

	}

	{// ���W�̏�����
		frequencyControlBG.pos	 = FREQUENCY_CONTROL_BG_POS;
		frequencyControlUp.pos	 = KEY_SHIFT_UP_POS;
		frequencyControlDown.pos = KEY_SHIFT_DOWN_POS;
	}

	{// �t�H���g�F�̏�����
		frequencyNum.color = FREQUENCY_NUM_COLOR;
	}

	// ���_���̓ǂݍ���
	MakeVtx4PointData(frequencyControlBG.vertexWk, frequencyControlBG.pos, FREQUENCY_CONTROL_BG_SIZE_X, FREQUENCY_CONTROL_BG_SIZE_Y);
	MakeVtx4PointData(frequencyControlUp.vertexWk, frequencyControlUp.pos, KEY_SHIFT_SIZE_X, KEY_SHIFT_SIZE_Y);
	MakeVtx4PointData(frequencyControlDown.vertexWk, frequencyControlDown.pos, KEY_SHIFT_SIZE_X, KEY_SHIFT_SIZE_Y);


	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void UninitFrequencyControl(void)
{
	if (frequencyControlBG.texture != NULL)
	{// �e�N�X�`���̊J��	  
		frequencyControlBG.texture->Release();
		frequencyControlBG.texture = NULL;
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void DrawFrequencyControl(void)
{
	DrawFrequencyControlBG();	// �w�i
	DrawFrequencyControlFont();	// �t�H���g
	DrawFrequencyControlUp();	// ���g���R���g���[���[(Up)
	DrawFrequencyControlDown();	// ���g���R���g���[���[(Down)
}

//*****************************************************************************
// �`�揈��(�w�i)
//*****************************************************************************
void DrawFrequencyControlBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, frequencyControlBG.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(frequencyControlBG.vertexWk, FREQUENCY_CONTROL_BG_COLOR);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlBG.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// �`�揈��(���g���R���g���[���[Up)
//*****************************************************************************
void DrawFrequencyControlUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, frequencyControlUp.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlUp.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// �`�揈��(���g���R���g���[���[Down)
//*****************************************************************************
void DrawFrequencyControlDown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, frequencyControlDown.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &frequencyControlDown.vertexWk, sizeof(VERTEX_2D));
}

//*****************************************************************************
// �`�揈��(�t�H���g)
//*****************************************************************************
void DrawFrequencyControlFont(void)
{
	MUSICPLAYER *song = GetSong();
	RECT rect = { (LONG)FREQUENCY_NUM_POS.x, (LONG)FREQUENCY_NUM_POS.y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	// ���g��
	sprintf(str, _T("freq.:%d"),song->frequency);
	frequencyNum.font->DrawText(NULL, str, -1, &rect, DT_LEFT, frequencyNum.color);
}


