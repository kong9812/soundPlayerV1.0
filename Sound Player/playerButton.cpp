//=============================================================================
// < SoundTest�v���O���� >
// �v���C���[�̃{�^������ [playerButton.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "Collider.h"
#include "playerControl.h"
#include "playerButton.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �`�揈��
void DrawButtonPlay(void);		// �Đ�
void DrawButtonPause(void);		// �ꎞ��~
void DrawButtonStop(void);		// ��~
void DrawButtonLoop(void);		// ���[�v
void DrawButtonFont(void);		// �{�^���̃t�H���g
void DrawButtonMute(void);		// �~���[�g
void DrawButtonForward(void);	// ������
void DrawButtonRewind(void);	// �����߂�

void DrawKeyUp(void);			// ��L�[
void DrawKeyDown(void);			// ���L�[
void DrawKeyLeft(void);			// ���L�[
void DrawKeyRight(void);		// �E�L�[

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYERBUTTON	buttonWk[BUTTON_MAX];
TEXTURE			key[KEY_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerButton(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_PLAY,						// �t�@�C���̖��O
		&buttonWk[BUTTON_PLAY].texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_PAUSE,						// �t�@�C���̖��O
		&buttonWk[BUTTON_PAUSE].texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_STOP,						// �t�@�C���̖��O
		&buttonWk[BUTTON_STOP].texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_LOOP,						// �t�@�C���̖��O
		&buttonWk[BUTTON_LOOP].texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_MUTE,						// �t�@�C���̖��O
		&buttonWk[BUTTON_MUTE].texture);			// �ǂݍ��ރ������[
	
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_FORWARD,						// �t�@�C���̖��O
		&buttonWk[BUTTON_FORWARD].texture);			// �ǂݍ��ރ������[
	
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BUTTON_REWIND,						// �t�@�C���̖��O
		&buttonWk[BUTTON_REWIND].texture);			// �ǂݍ��ރ������[


		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_UP,								// �t�@�C���̖��O
		&key[KEY_UP].texture);						// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_DOWN,							// �t�@�C���̖��O
		&key[KEY_DOWN].texture);					// �ǂݍ��ރ������[
		
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_LEFT,							// �t�@�C���̖��O
		&key[KEY_LEFT].texture);					// �ǂݍ��ރ������[
														
		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		TEXTURE_KEY_RIGHT,							// �t�@�C���̖��O
		&key[KEY_RIGHT].texture);					// �ǂݍ��ރ������[

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_PLAY_FONT_SIZE_Y, (INT)BUTTON_PLAY_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_PLAY].font);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_PAUSE_FONT_SIZE_Y, (INT)BUTTON_PAUSE_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_PAUSE].font);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_STOP_FONT_SIZE_Y, (INT)BUTTON_STOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_STOP].font);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_LOOP].font);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_MUTE].font);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_FORWARD].font);
		
		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)BUTTON_LOOP_FONT_SIZE_Y, (INT)BUTTON_LOOP_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &buttonWk[BUTTON_REWIND].font);

	}	

	{	// ���W�̏�����
		buttonWk[BUTTON_PLAY].pos		= BUTTON_PLAY_POS;
		buttonWk[BUTTON_PAUSE].pos		= BUTTON_PAUSE_POS;
		buttonWk[BUTTON_STOP].pos		= BUTTON_STOP_POS;
		buttonWk[BUTTON_LOOP].pos		= BUTTON_LOOP_POS;
		buttonWk[BUTTON_MUTE].pos		= BUTTON_MUTE_POS;
		buttonWk[BUTTON_FORWARD].pos	= BUTTON_FORWARD_POS;
		buttonWk[BUTTON_REWIND].pos		= BUTTON_REWIND_POS;

		key[KEY_UP].pos					= KEY_UP_POS;
		key[KEY_DOWN].pos				= KEY_DOWN_POS;
		key[KEY_LEFT].pos				= KEY_LEFT_POS;
		key[KEY_RIGHT].pos				= KEY_RIGHT_POS;
	}

	// ���_���̓ǂݍ���
	MakeVtxCenterData(buttonWk[BUTTON_PLAY].vertexWk, buttonWk[BUTTON_PLAY].pos, BUTTON_PLAY_SIZE_X, BUTTON_PLAY_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_PAUSE].vertexWk, buttonWk[BUTTON_PAUSE].pos, BUTTON_PAUSE_SIZE_X, BUTTON_PAUSE_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_STOP].vertexWk, buttonWk[BUTTON_STOP].pos, BUTTON_STOP_SIZE_X, BUTTON_STOP_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_LOOP].vertexWk, buttonWk[BUTTON_LOOP].pos, BUTTON_LOOP_SIZE_X, BUTTON_LOOP_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_MUTE].vertexWk, buttonWk[BUTTON_MUTE].pos, BUTTON_MUTE_SIZE_X, BUTTON_MUTE_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_FORWARD].vertexWk, buttonWk[BUTTON_FORWARD].pos, BUTTON_FORWARD_SIZE_X, BUTTON_FORWARD_SIZE_Y);
	MakeVtxCenterData(buttonWk[BUTTON_REWIND].vertexWk, buttonWk[BUTTON_REWIND].pos, BUTTON_REWIND_SIZE_X, BUTTON_REWIND_SIZE_Y);

	MakeVtxCenterData(key[KEY_UP].vertexWk, key[KEY_UP].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_DOWN].vertexWk, key[KEY_DOWN].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_LEFT].vertexWk, key[KEY_LEFT].pos, KEY_SIZE_X, KEY_SIZE_Y);
	MakeVtxCenterData(key[KEY_RIGHT].vertexWk, key[KEY_RIGHT].pos, KEY_SIZE_X, KEY_SIZE_Y);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerButton(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (buttonWk[i].texture != NULL)
		{// �e�N�X�`���̊J��	  
			buttonWk[i].texture->Release();
			buttonWk[i].texture = NULL;
		}
	}

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (key[i].texture != NULL)
		{// �e�N�X�`���̊J��	  
			key[i].texture->Release();
			key[i].texture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerButton(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	// �Đ��E�ꎞ��~
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_PLAY].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_PLAY_SIZE_X, BUTTON_PLAY_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_PLAY].vertexWk, BUTTON_PRESS_COLOR);
		SetAllDiffuseData(buttonWk[BUTTON_PAUSE].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundPlayPause();
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_PAUSE].vertexWk, BUTTON_NORMAL_COLOR);
		SetAllDiffuseData(buttonWk[BUTTON_PLAY].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// ��~
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_STOP].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_STOP_SIZE_X, BUTTON_STOP_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_STOP].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundStop();
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_STOP].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// ���[�v
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_LOOP].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_LOOP_SIZE_X, BUTTON_LOOP_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundPlayingLoop();
		}
	}

	else
	{
		if (song->playMode == E_DS8_FLAG_NONE)
		{
			SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_NORMAL_COLOR);
		}
		else if (song->playMode == E_DS8_FLAG_LOOP)
		{
			SetAllDiffuseData(buttonWk[BUTTON_LOOP].vertexWk, BUTTON_PRESS_COLOR);
		}
	}

	// �~���[�g
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_MUTE].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_MUTE_SIZE_X, BUTTON_MUTE_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_MUTE].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftTriggered() == true)
		{
			SetSoundVolume(song->soundBuffer, VOLUME_MULT);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_MUTE].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// ������
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_FORWARD].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_FORWARD_SIZE_X, BUTTON_FORWARD_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_FORWARD].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftPressed() == true)
		{
			SetSoundPosition(song->soundBuffer, SET_FORWARD, song->playMode, NULL);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_FORWARD].vertexWk, BUTTON_NORMAL_COLOR);
	}

	// �����߂�
	if (CheckHitBB(GetMousePos(hWnd), buttonWk[BUTTON_REWIND].pos, CURSOR_SIZE, D3DXVECTOR2(BUTTON_REWIND_SIZE_X, BUTTON_REWIND_SIZE_Y)))
	{
		SetAllDiffuseData(buttonWk[BUTTON_REWIND].vertexWk, BUTTON_PRESS_COLOR);

		if (IsMouseLeftPressed() == true)
		{
			SetSoundPosition(song->soundBuffer, SET_REWIND, song->playMode, NULL);
		}
	}

	else
	{
		SetAllDiffuseData(buttonWk[BUTTON_REWIND].vertexWk, BUTTON_NORMAL_COLOR);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerButton(void)
{
	MUSICPLAYER *song = GetSong();

	if (!IsPlaying(song->soundBuffer))
	{
		DrawButtonPlay();		// �Đ�
	}
	else if (IsPlaying(song->soundBuffer))
	{
		DrawButtonPause();		// �ꎞ��~
	}

	// ��~
	DrawButtonStop();

	// ���[�v
	DrawButtonLoop();

	// �~���[�g
	DrawButtonMute();

	// ������
	DrawButtonForward();

	// �����߂�
	DrawButtonRewind();

	// ��L�[
	DrawKeyUp();

	// ���L�[
	DrawKeyDown();

	// ���L�[
	DrawKeyLeft();

	// �E�L�[
	DrawKeyRight();

	// �{�^���̃t�H���g
	DrawButtonFont();
}

//=============================================================================
// �`�揈��(�Đ�)
//=============================================================================
void DrawButtonPlay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_PLAY].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_PLAY].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�ꎞ��~)
//=============================================================================
void DrawButtonPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_PAUSE].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_PAUSE].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(��~)
//=============================================================================
void DrawButtonStop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_STOP].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_STOP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���[�v)
//=============================================================================
void DrawButtonLoop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_LOOP].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_LOOP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�~���[�g)
//=============================================================================
void DrawButtonMute(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_MUTE].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_MUTE].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(������)
//=============================================================================
void DrawButtonForward(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_FORWARD].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_FORWARD].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�����߂�)
//=============================================================================
void DrawButtonRewind(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, buttonWk[BUTTON_REWIND].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &buttonWk[BUTTON_REWIND].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(��L�[)
//=============================================================================
void DrawKeyUp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, key[KEY_UP].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_UP].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���L�[)
//=============================================================================
void DrawKeyDown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, key[KEY_DOWN].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_DOWN].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���L�[)
//=============================================================================
void DrawKeyLeft(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, key[KEY_LEFT].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_LEFT].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�E�L�[)
//=============================================================================
void DrawKeyRight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, key[KEY_RIGHT].texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &key[KEY_RIGHT].vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�{�^���̃t�H���g)
//=============================================================================
void DrawButtonFont(void)
{
	MUSICPLAYER *song = GetSong();
	char str[256];

	// �`��ʒu
	RECT rect = { (LONG)BUTTON_PLAY_FONT_POS.x,(LONG)BUTTON_PLAY_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	if (!IsPlaying(song->soundBuffer))
	{
		// �Đ�(PLAY)
		sprintf(str, _T("PLAY"));
		buttonWk[BUTTON_PLAY].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_PLAY_FONT_COLOR);

	}
	else if (IsPlaying(song->soundBuffer))
	{
		// �`��ʒu
		rect = { (LONG)BUTTON_PAUSE_FONT_POS.x,(LONG)BUTTON_PAUSE_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

		// �ꎞ��~(PAUSE)
		sprintf(str, _T("PAUSE"));
		buttonWk[BUTTON_PAUSE].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_PAUSE_FONT_COLOR);
	}

	// �`��ʒu
	rect = { (LONG)BUTTON_STOP_FONT_POS.x,(LONG)BUTTON_STOP_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ��~(STOP)
	sprintf(str, _T("STOP"));
	buttonWk[BUTTON_STOP].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_STOP_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)BUTTON_LOOP_FONT_POS.x,(LONG)BUTTON_LOOP_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ���[�v(LOOP)
	sprintf(str, _T("LOOP"));
	buttonWk[BUTTON_LOOP].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_LOOP_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)BUTTON_MUTE_FONT_POS.x,(LONG)BUTTON_MUTE_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �~���[�g
	sprintf(str, _T("MUTE"));
	buttonWk[BUTTON_MUTE].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)BUTTON_FORWARD_FONT_POS.x,(LONG)BUTTON_FORWARD_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ������
	sprintf(str, _T("FORWARD"));
	buttonWk[BUTTON_FORWARD].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)BUTTON_REWIND_FONT_POS.x,(LONG)BUTTON_REWIND_FONT_POS.y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �����߂�
	sprintf(str, _T("REWIND"));
	buttonWk[BUTTON_REWIND].font->DrawText(NULL, str, -1, &rect, DT_LEFT, BUTTON_MUTE_FONT_COLOR);

}

//=============================================================================
// �{�^���̏����擾
//=============================================================================
PLAYERBUTTON *GetButton(int no)
{
	return &buttonWk[no];
}

