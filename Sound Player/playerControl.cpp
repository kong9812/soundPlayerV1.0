//=============================================================================
// < SoundTest�v���O���� >
// �v���C���[�̃R���g���[������ [playerControl.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "basic.h"
#include "input.h"
#include "sound.h"
#include "Collider.h"
#include "playerBackground.h"
#include "soundEffect.h"
#include "playerControl.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//------------�`�揈��
void DrawPlayerSongFont(void);				// �Ȗ�
void DrawPlayingPositionBarBG(void);		// �Đ��ʒu�o�[(�w�i)
void DrawPlayingPositionBar(void);			// �Đ��ʒu�o�[
void DrawVolumeBarNum(void);				// �e���ʃo�[�̐���
void DrawVolumeBarTag(void);				// �e���ʃo�[�̃^�O
void DrawVolumeBarBG(void);					// ���ʃo�[(�w�i)
void DrawVolumeBarMain(void);				// ���C�����ʃo�[
void DrawVolumeBarBalance(void);			// ���Ή��ʃo�[
void DrawReset(void);						// ���Z�b�g�̔w�i
void DrawPlayerResetFont(void);				// ���Z�b�g

//------------�X�V����
//----�ݒ�
void SetSoundPlayingVolume(void);			// ����
void SetSoundPlayingBalanceVolume(void);	// ���Ή���
void SetSoundPlayingPosition(HWND hWnd);	// �Đ��ʒu
void SetSoundPlayingFrequency(void);		// ���g��
void SetSoundPlayingLoop(void);				// ���[�v
void SetSoundPlayingReset(void);			// ���Z�b�g
//----���擾
void GetSoundPlayingVolume(void);			// ����
void GetSoundPlayingPosition(void);			// �Đ��ʒu

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPD3DXFONT			g_pD3DXFontSongName = NULL;		// �t�H���g�ւ̃|�C���^
LPD3DXFONT			g_pD3DXFontBalance = NULL;		// �t�H���g�ւ̃|�C���^
LPD3DXFONT			g_pD3DXFontReset = NULL;		// �t�H���g�ւ̃|�C���^

TEXTURE				volumeBarBG;					// ���ʃo�[�̔w�i
TEXTURE				positionBarBG;					// �Đ��ʒu�o�[�̔w�i
TEXTURE				positionBar;					// �Đ��ʒu�o�[
TEXTURE				positionBarBall;				// �Đ��ʒu��\���{�[��
TEXTURE				resetBG;						// ���Z�b�g�̔w�i
TEXTURE				resetKey;						// ���Z�b�g�̃L�[

MUSICPLAYER			songWk;							// �~���[�W�b�N�v���C���[�\����
VOLUMEBAR			volumeBarWk[VOLUME_BAR_MAX];	// ���ʃo�[�\����

float				SongFontCnt;					// �������[�v�p�J�E���^�[

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayerControl(int InitType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MUSICPLAYER *song = GetSong();

	// ���ڂ̏�����
	if (InitType == FIRST_INIT)
	{
		{	// �e�N�X�`���̏�����
			volumeBarBG.texture		= NULL;
			positionBarBG.texture	= NULL;
			positionBar.texture		= NULL;
			positionBarBall.texture = NULL;
			resetBG.texture			= NULL;
		}

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_DISK,						// �t�@�C���̖��O
		&positionBarBall.texture);			// �ǂݍ��ރ������[

		// �e�N�X�`���̓Ǎ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESET_KEY,					// �t�@�C���̖��O
		&resetKey.texture);					// �ǂݍ��ރ������[


		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)SONG_NAME_SIZE_Y, (INT)SONG_NAME_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontSongName);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontBalance);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET, 
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_MAIN].value);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_LEFT].value);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_NUM_SIZE_Y, (INT)VOLUME_BAR_NUM_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_RIGHT].value);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_MAIN].tag);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_LEFT].tag);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)VOLUME_BAR_TAG_SIZE_Y, (INT)VOLUME_BAR_TAG_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &volumeBarWk[BAR_RIGHT].tag);

		// ���\���p�t�H���g��ݒ�
		D3DXCreateFont(pDevice, (UINT)RESET_FONT_SIZE_Y, (INT)RESET_FONT_SIZE_X, 0, 0, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_SCRIPT, _T("Terminal"), &g_pD3DXFontReset);
	}

	{	// ���ʃo�[�̏�����
		// ����
		volumeBarWk[BAR_MAIN].length = 0.0f;
		volumeBarWk[BAR_LEFT].length = 0.0f;
		volumeBarWk[BAR_RIGHT].length = 0.0f;

		// ���W
		volumeBarWk[BAR_MAIN].texture.pos = VOLUME_BAR_MAIN_POS;
		volumeBarWk[BAR_LEFT].texture.pos = VOLUME_BAR_LEFT_POS;
		volumeBarWk[BAR_RIGHT].texture.pos = VOLUME_BAR_RIGHT_POS;
	}

	{	// �Đ��ʒu�o�[�̏�����
		positionBarBall.pos = PLAYING_POSITION_BAR_POS;
		positionBarBall.pos.y = PLAYING_POSITION_BAR_POINT_POS_Y;
	}

	{	// �T�E���h�̓Ǎ���
		song->soundBuffer		= LoadSound();						// ���[�h
		song->playPosByte		= 0;								// �Đ��ʒu(�o�C�g�P��)
		song->sizeByte			= 0;								// �T�C�Y(�o�C�g�P��)
		song->mainVolume		= 0.0f;								// ���C������
		song->balanceVolume		= 0l;								// ���E����(db)  ����=��>�E 0=�� ����=�E>��
		song->playPos			= 0.0f;								// �Đ��ʒu(�p�[�Z���g)
		song->effectNo			= NULL_SOUND_EFFECT;				// �G�t�F�N�g�̔ԍ�
		song->frequency			= (int)GetSoundInitFrequency();		// ���g��
	}

	{	// �Đ����[�h�̏�����
		song->playMode = E_DS8_FLAG_LOOP;
	}

	SongFontCnt = 0;

	// ���_���̓ǂݍ���
	MakeVtx4PointData(volumeBarBG.vertexWk, VOLUME_BAR_BG_POS, VOLUME_BAR_BG_SIZE_X, VOLUME_BAR_BG_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_MAIN].texture.vertexWk, volumeBarWk[BAR_MAIN].texture.pos, VOLUME_BAR_MAIN_SIZE_X, VOLUME_BAR_MAIN_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_LEFT].texture.vertexWk, volumeBarWk[BAR_LEFT].texture.pos, VOLUME_BAR_LEFT_SIZE_X, VOLUME_BAR_LEFT_SIZE_Y);
	MakeVtx4PointData(volumeBarWk[BAR_RIGHT].texture.vertexWk, volumeBarWk[BAR_RIGHT].texture.pos, VOLUME_BAR_RIGHT_SIZE_X, VOLUME_BAR_RIGHT_SIZE_Y);
	MakeVtx4PointData(positionBarBG.vertexWk, PLAYING_POSITION_BAR_BG_POS, PLAYING_POSITION_BAR_BG_SIZE_X, PLAYING_POSITION_BAR_BG_SIZE_Y);
	MakeVtx4PointData(positionBar.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_SIZE_X, PLAYING_POSITION_BAR_SIZE_Y);
	MakeVtxCenterData(positionBarBall.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y);
	MakeVtx4PointData(resetBG.vertexWk, RESET_BG_POS, RESET_BG_SIZE_X, RESET_BG_SIZE_Y);
	MakeVtx4PointData(resetKey.vertexWk, RESET_KEY_POS, RESET_KEY_SIZE_X, RESET_KEY_SIZE_Y);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayerControl(void)
{
	MUSICPLAYER *song = GetSong();
	VOLUMEBAR *volumeBar = GetVolumeBar(0);

	for (int i = 0; i < VOLUME_BAR_MAX; i++, volumeBar++)
	{
		if (volumeBar->texture.texture != NULL)
		{// �e�N�X�`���̊J��	  
			volumeBar->texture.texture->Release();
			volumeBar->texture.texture = NULL;
		}
	}

	if (volumeBarBG.texture != NULL)
	{// �e�N�X�`���̊J��	  
		volumeBarBG.texture->Release();
		volumeBarBG.texture = NULL;
	}

	if (positionBarBG.texture != NULL)
	{// �e�N�X�`���̊J��	
		positionBarBG.texture->Release();
		positionBarBG.texture = NULL;
	}

	if (positionBar.texture != NULL)
	{// �e�N�X�`���̊J��	
		positionBar.texture->Release();
		positionBar.texture = NULL;
	}

	if (positionBarBall.texture != NULL)
	{// �e�N�X�`���̊J��	
		positionBarBall.texture->Release();
		positionBarBall.texture = NULL;
	}

	if (resetBG.texture != NULL)
	{// �e�N�X�`���̊J��	
		resetBG.texture->Release();
		resetBG.texture = NULL;
	}

	if (resetKey.texture != NULL)
	{// �e�N�X�`���̊J��	
		resetKey.texture->Release();
		resetKey.texture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayerControl(HWND hWnd)
{
	// �ݒ菈��
	{
		// ����
		SetSoundPlayingVolume();

		// ���Ή���
		SetSoundPlayingBalanceVolume();

		// �Đ��ʒu
		SetSoundPlayingPosition(hWnd);

		// ���g��
		SetSoundPlayingFrequency();

		// ���Z�b�g
		SetSoundPlayingReset();
	}

	// �擾����
	{
		// ����
		GetSoundPlayingVolume();

		// �Đ��ʒu
		GetSoundPlayingPosition();
	}
}

//=============================================================================
// �Đ��E�ꎞ��~
//=============================================================================
void SetSoundPlayPause(void)
{
	MUSICPLAYER *song = GetSong();

	// �Đ�
	if (!IsPlaying(song->soundBuffer))
	{
		PlaySound(song->soundBuffer, song->playMode);
	}

	// �ꎞ��~
	else if (IsPlaying(song->soundBuffer))
	{
		PauseSound(song->soundBuffer);
	}
}

//=============================================================================
// ��~
//=============================================================================
void SetSoundStop(void)
{
	MUSICPLAYER *song = GetSong();

	StopSound(song->soundBuffer);			// ��~
}

//=============================================================================
// ���ʂ��擾
//=============================================================================
void GetSoundPlayingVolume(void)
{
	MUSICPLAYER *song = GetSong();

	// �擾
	song->mainVolume = (float)GetSoundVolume(song->soundBuffer);

	// ���ʃo�[�̒���
	volumeBarWk[BAR_MAIN].length = -(song->mainVolume / VOLUME_BAR_MAIN_FULL_VOLUME)*VOLUME_BAR_MAIN_SIZE_Y;
}

//=============================================================================
// ���ʂ�ݒ�
//=============================================================================
void SetSoundPlayingVolume(void)
{
	MUSICPLAYER *song = GetSong();

	if (!GetKeyboardPress(DIK_LSHIFT))
	{
		// ���ʒ���(UP)
		if (GetKeyboardPress(DIK_UP))
		{
			SetSoundVolume(song->soundBuffer, VOLUME_UP);
		}

		// ���ʒ���(DOWN)
		else if (GetKeyboardPress(DIK_DOWN))
		{
			SetSoundVolume(song->soundBuffer, VOLUME_DOWN);
		}
	}
}

//=============================================================================
// ���Ή��ʂ�ݒ�
//=============================================================================
void SetSoundPlayingBalanceVolume(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardPress(DIK_RIGHT))
	{
		song->balanceVolume += PAN_UNIT;

		// �I�[�o�t���[�h�~
		if (song->balanceVolume > DSBPAN_RIGHT)
		{
			song->balanceVolume = DSBPAN_RIGHT;
		}
	}

	else if (GetKeyboardPress(DIK_LEFT))
	{
		song->balanceVolume -= PAN_UNIT;

		// �I�[�o�t���[�h�~
		if (song->balanceVolume < DSBPAN_LEFT)
		{
			song->balanceVolume = DSBPAN_LEFT;
		}
	}

	// ���Ή��ʂ�ݒ�
	SetSoundBalanceVolume(song->soundBuffer, song->balanceVolume);

	// ���Ή��ʃo�[�̒���
	volumeBarWk[BAR_LEFT].length = (song->balanceVolume / VOLUME_BAR_LEFT_FULL_VOLUME)*VOLUME_BAR_LEFT_SIZE_Y;
	volumeBarWk[BAR_RIGHT].length = (-song->balanceVolume / VOLUME_BAR_RIGHT_FULL_VOLUME)*VOLUME_BAR_RIGHT_SIZE_Y;
}

//=============================================================================
// �Đ��ʒu���擾
//=============================================================================
void GetSoundPlayingPosition(void)
{
	MUSICPLAYER *song = GetSong();

	song->playPosByte = GetSoundCurrentPosition(song->soundBuffer,GET_PLAY);	// �Đ��ʒu���擾����
	song->sizeByte = GetSoundSize();											// �T�C�Y���擾����
	song->playPos = ((float)song->playPosByte / (float)song->sizeByte) * PERCENT;	// �Đ��ʒu�̃p�[�Z���g
}

//=============================================================================
// �Đ��ʒu��ݒ�
//=============================================================================
void SetSoundPlayingPosition(HWND hWnd)
{
	MUSICPLAYER *song = GetSong();

	// �Đ��ʒu
	if (CheckHitBB(GetMousePos(hWnd), positionBarBall.pos, CURSOR_SIZE, D3DXVECTOR2(PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y)))
	{
		// �����ꂽ
		if (IsMouseLeftPressed())
		{
			// 
			positionBarBall.pos.x = GetMousePos(hWnd).x;

			// �͈͂Ɏ��܂�
			if (positionBarBall.pos.x < PLAYING_POSITION_BAR_POS.x)
			{
				positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x;
			}
			else if (positionBarBall.pos.x > PLAYING_POSITION_BAR_SIZE_X)
			{
				positionBarBall.pos.x = PLAYING_POSITION_BAR_SIZE_X;
			}

			// �{�[���̈ʒu����Đ��ʒu�̃p�[�Z���g�֕ϊ�
			song->playPos = (positionBarBall.pos.x - PLAYING_POSITION_BAR_POS.x) * PERCENT / PLAYING_POSITION_BAR_SIZE_X;

			// �p�[�Z���g����o�C�g�֕ϊ�
			song->playPosByte = (DWORD)((song->playPos / PERCENT) * song->sizeByte);

			// �ݒ�
			SetSoundPosition(song->soundBuffer, SET_DISTANCE, song->playMode, song->playPosByte);
		}

		// ������ĂȂ�
		else if(!IsMouseLeftPressed())
		{
			// �Đ��ʒu�o�[
			positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x + (PLAYING_POSITION_BAR_SIZE_X*song->playPos / PERCENT);
		}
	}

	else
	{
		// �Đ��ʒu�o�[
		positionBarBall.pos.x = PLAYING_POSITION_BAR_POS.x + (PLAYING_POSITION_BAR_SIZE_X*song->playPos / PERCENT);
	}
}

//=============================================================================
// ���g����ݒ�
//=============================================================================
void SetSoundPlayingFrequency(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardPress(DIK_LSHIFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{
			song->frequency += FREQ_UNIT;

			// �ő�l
			if (song->frequency > DSBFREQUENCY_MAX)
			{
				song->frequency = DSBFREQUENCY_MAX;
			}
		}

		else
		{
			if (GetKeyboardPress(DIK_DOWN))
			{
				song->frequency -= FREQ_UNIT;

				// �ŏ��l
				if (song->frequency < DSBFREQUENCY_MIN)
				{ 

					song->frequency = DSBFREQUENCY_MIN;
				}
			}
		}
	}

	SetSoundFrequency(song->soundBuffer, song->frequency);
}

//=============================================================================
// ���[�v
//=============================================================================
void SetSoundPlayingLoop(void)
{
	MUSICPLAYER *song = GetSong();

	if (IsPlaying(song->soundBuffer))
	{	// �ꎞ��~
		PauseSound(song->soundBuffer);
	}

	if (song->playMode == D3DXPLAY_LOOP)
	{	// ��񂾂�
		song->playMode = D3DXPLAY_ONCE;
	}

	else if (song->playMode == D3DXPLAY_ONCE)
	{	// ���[�v
		song->playMode = D3DXPLAY_LOOP;
	}
}

//=============================================================================
// ���Z�b�g
//=============================================================================
void SetSoundPlayingReset(void)
{
	MUSICPLAYER *song = GetSong();

	if (GetKeyboardTrigger(DIK_R))
	{
		song->effectNo = NULL_SOUND_EFFECT;
		song->frequency = GetSoundInitFrequency();
		song->balanceVolume = 0;

		SetSoundFrequency(song->soundBuffer, song->frequency);
		SetSoundEffect(song->soundBuffer, song->playMode, song->effectNo);
		SetSoundBalanceVolume(song->soundBuffer, song->balanceVolume);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayerControl(void)
{
	// �Ȗ�
	DrawPlayerSongFont();			// �t�H���g

	// �Đ��ʒu�o�[
	DrawPlayingPositionBarBG();		// �w�i
	DrawPlayingPositionBar();		// �Đ��ʒu

	// ���ʃo�[
	DrawVolumeBarBG();				// �w�i
	DrawVolumeBarMain();			// ���C��
	DrawVolumeBarBalance();			// ���Ή���
	DrawVolumeBarNum();				// ����
	DrawVolumeBarTag();				// �^�O

	// ���Z�b�g
	DrawReset();					// �L�[�Ɣw�i
	DrawPlayerResetFont();			// ���Z�b�g
}

//=============================================================================
// �`�揈��(�Đ��ʒu�o�[�w�i)
//=============================================================================
void DrawPlayingPositionBarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, positionBarBG.texture);

	// ���ˌ��̐ݒ�(�S�F)
	SetAllDiffuseData(positionBarBG.vertexWk, PLAYING_POSITION_BAR_BG_COLOR);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBarBG.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(�Đ��ʒu�o�[)
//=============================================================================
void DrawPlayingPositionBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MUSICPLAYER *song = GetSong();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, positionBar.texture);

	// ���ˌ��̐ݒ�(�S�F)
	SetAllDiffuseData(positionBar.vertexWk, PLAYING_POSITION_BAR_COLOR);

	// ���_���W�̐ݒ�(�Q�[�W�p)
	SetVtx4PointGaugeDate(positionBar.vertexWk, PLAYING_POSITION_BAR_POS, PLAYING_POSITION_BAR_SIZE_X, PLAYING_POSITION_BAR_SIZE_Y, song->playPos / PERCENT, GAUGE_RIGHT);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBar.vertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, positionBarBall.texture);

	// ���_���W�̐ݒ�(���_���)
	SetVtx4PointData(positionBarBall.vertexWk, positionBarBall.pos, PLAYING_POSITION_BAR_POINT_SIZE_X, PLAYING_POSITION_BAR_POINT_SIZE_Y);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &positionBarBall.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���ʃo�[�w�i)
//=============================================================================
void DrawVolumeBarBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, volumeBarBG.texture);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetSingleDiffuseData(volumeBarBG.vertexWk, 0, VOLUME_BAR_BG_COLOR_B);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 1, VOLUME_BAR_BG_COLOR_B);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 2, VOLUME_BAR_BG_COLOR_A);
	SetSingleDiffuseData(volumeBarBG.vertexWk, 3, VOLUME_BAR_BG_COLOR_A);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarBG.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���ʃo�[���C��)
//=============================================================================
void DrawVolumeBarMain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, volumeBarWk[BAR_MAIN].texture.texture);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 0, VOLUME_BAR_MAIN_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 1, VOLUME_BAR_MAIN_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 2, VOLUME_BAR_MAIN_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_MAIN].texture.vertexWk, 3, VOLUME_BAR_MAIN_COLOR_B);

	// ���_���W�̐ݒ�(�Q�[�W�p)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_MAIN].texture.vertexWk, VOLUME_BAR_MAIN_POS, VOLUME_BAR_MAIN_SIZE_X, VOLUME_BAR_MAIN_SIZE_Y, volumeBarWk[BAR_MAIN].length, GAUGE_UP);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_MAIN].texture.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���Ή��ʃo�[)
//=============================================================================
void DrawVolumeBarBalance(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, volumeBarWk[BAR_LEFT].texture.texture);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 0, VOLUME_BAR_LEFT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 1, VOLUME_BAR_LEFT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 2, VOLUME_BAR_LEFT_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_LEFT].texture.vertexWk, 3, VOLUME_BAR_LEFT_COLOR_B);

	// ���_���W�̐ݒ�(�Q�[�W�p)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_LEFT].texture.vertexWk, VOLUME_BAR_LEFT_POS, VOLUME_BAR_LEFT_SIZE_X, VOLUME_BAR_LEFT_SIZE_Y, volumeBarWk[BAR_LEFT].length, GAUGE_UP);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_LEFT].texture.vertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, volumeBarWk[BAR_RIGHT].texture.texture);

	// ���ˌ��̐ݒ�(�꒸�_����)
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 0, VOLUME_BAR_RIGHT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 1, VOLUME_BAR_RIGHT_COLOR_A);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 2, VOLUME_BAR_RIGHT_COLOR_B);
	SetSingleDiffuseData(volumeBarWk[BAR_RIGHT].texture.vertexWk, 3, VOLUME_BAR_RIGHT_COLOR_B);

	// ���_���W�̐ݒ�(�Q�[�W�p)
	SetVtx4PointGaugeDate(volumeBarWk[BAR_RIGHT].texture.vertexWk, VOLUME_BAR_RIGHT_POS, VOLUME_BAR_RIGHT_SIZE_X, VOLUME_BAR_RIGHT_SIZE_Y, volumeBarWk[BAR_RIGHT].length, GAUGE_UP);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &volumeBarWk[BAR_RIGHT].texture.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// �`�揈��(���Z�b�g�̔w�i�ƃL�[)
//=============================================================================
void DrawReset(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, resetBG.texture);

	// ���ˌ��̐ݒ�(�S���_)
	SetAllDiffuseData(resetBG.vertexWk, RESET_BG_COLOR);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &resetBG.vertexWk, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, resetKey.texture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &resetKey.vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// �`�揈��(���Z�b�g)
//=============================================================================
void DrawPlayerResetFont(void)
{
	RECT rect = { (LONG)RESET_FONT_POS.x, (LONG)RESET_FONT_POS.y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	// ���Z�b�g
	sprintf(str, _T("RESET"));
	g_pD3DXFontReset->DrawText(NULL, str, -1, &rect, DT_LEFT, RESET_FONT_COLOR);

}

//=============================================================================
// �`�揈��(�Ȗ�)
//=============================================================================
void DrawPlayerSongFont(void)
{
	RECT rect = { SONG_NAME_POS_X, SONG_NAME_POS_Y,SCREEN_WIDTH , SCREEN_HEIGHT };
	char str[256];

	SongFontCnt += SONG_NAME_SCROLL_TIME;

	if (*GetSoundName((int)SongFontCnt) == '\0')
	{
		SongFontCnt = 0;
	}

	// �Ȗ�
	// char�z����A�ꕶ�����\������
	sprintf(str, _T("name:%s"), GetSoundName((int)SongFontCnt*2));


	g_pD3DXFontSongName->DrawText(NULL, str, -1, &rect, DT_LEFT, SONG_NAME_FONT_COLOR);
}

//=============================================================================
// �`�揈��(�e���ʃo�[�̐���)
//=============================================================================
void DrawVolumeBarNum(void)
{
	MUSICPLAYER *song = GetSong();
	char str[256];

	// �`��ʒu
	RECT rect = { (LONG)VOLUME_BAR_MAIN_NUM_POS_X,(LONG)(VOLUME_BAR_MAIN_POS.y + volumeBarWk[BAR_MAIN].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// ���C��
	sprintf(str, _T("%d%%"), (int)((song->mainVolume / VOLUME_BAR_MAIN_FULL_VOLUME) * PERCENT)+100);
	volumeBarWk[BAR_MAIN].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)VOLUME_BAR_LEFT_NUM_POS_X,(LONG)(VOLUME_BAR_LEFT_POS.y + volumeBarWk[BAR_LEFT].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// ��
	sprintf(str, _T("%d%%"), (int)(-(song->balanceVolume / VOLUME_BAR_LEFT_FULL_VOLUME) * 50) + 50);
	volumeBarWk[BAR_LEFT].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)VOLUME_BAR_RIGHT_NUM_POS_X,(LONG)(VOLUME_BAR_RIGHT_POS.y + volumeBarWk[BAR_RIGHT].length),SCREEN_WIDTH,SCREEN_HEIGHT };

	// �E
	sprintf(str, _T("%d%%"), (int)((song->balanceVolume / VOLUME_BAR_RIGHT_FULL_VOLUME)* 50) + 50);
	volumeBarWk[BAR_RIGHT].value->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_NUM_FONT_COLOR);
}

//=============================================================================
// �`�揈��(�e���ʃo�[�̃^�O)
//=============================================================================
void DrawVolumeBarTag(void)
{
	char str[256];

	// �`��ʒu
	RECT rect = { (LONG)VOLUME_BALANCE_TAG_POS_X,(LONG)VOLUME_BALANCE_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �o�����X
	sprintf(str, _T("balance"));
	g_pD3DXFontBalance->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BALANCE_TAG_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)VOLUME_BAR_MAIN_TAG_POS_X,(LONG)VOLUME_BAR_MAIN_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ���C��
	sprintf(str, _T("main"));
	volumeBarWk[BAR_MAIN].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_MAIN_TAG_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)VOLUME_BAR_LEFT_TAG_POS_X,(LONG)VOLUME_BAR_LEFT_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// ��
	sprintf(str, _T("left"));
	volumeBarWk[BAR_LEFT].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_LEFT_TAG_FONT_COLOR);

	// �`��ʒu
	rect = { (LONG)VOLUME_BAR_RIGHT_TAG_POS_X,(LONG)VOLUME_BAR_RIGHT_TAG_POS_Y,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �E
	sprintf(str, _T("right"));
	volumeBarWk[BAR_RIGHT].tag->DrawText(NULL, str, -1, &rect, DT_LEFT, VOLUME_BAR_RIGHT_TAG_FONT_COLOR);

}

//=============================================================================
// �Ȃ̏����擾
//=============================================================================
MUSICPLAYER *GetSong(void)
{
	return &songWk;
}

//=============================================================================
// ���ʃo�[�̏����擾
//=============================================================================
VOLUMEBAR *GetVolumeBar(int no)
{
	return &volumeBarWk[no];
}