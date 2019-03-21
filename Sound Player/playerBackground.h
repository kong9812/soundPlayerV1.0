//=============================================================================
//
// �v���C���[�̔w�i���� [playerBackground.h]
// Author : �� �F��
//
//=============================================================================
#ifndef _PLAYER_BACKGROUND_H_
#define _PLAYER_BACKGROUND_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// ���R�[�h�v���C���[
#define	TEXTURE_RECORD_PLAYER		_T("data/TEXTURE/wood.jpg")			// �ǂݍ��ރe�N�X�`���t�@�C����
// ���R�[�h�f�B�X�N				   
#define	TEXTURE_DISK				_T("data/TEXTURE/lpdisk.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���R�[�h�v���C���[								   
#define	TEXTURE_BACKGROUND			_T("data/TEXTURE/redTheme.jpg")		// �ǂݍ��ރe�N�X�`���t�@�C����
// ���R�[�h�A�[��								   
#define	TEXTURE_ARM					_T("data/TEXTURE/LpArm.png")		// �ǂݍ��ރe�N�X�`���t�@�C����

// ���W
#define RECORD_PLAYER_POS			D3DXVECTOR3(280.0f,0.0f,0.0f)
// �T�C�Y
#define RECORD_DISK_SIZE_X			(720)
#define RECORD_DISK_SIZE_Y			(720)
#define RECORD_ARM_SIZE_X			(200)
#define RECORD_ARM_SIZE_Y			(350)

// ���[�e�[�V����	
#define	LP_RECORD_MOVIE_Z			(-0.8f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayerBackground(int InitType);
void UninitPlayerBackground(void);
void UpdatePlayerBackground(void);
void DrawPlayerBackground(void);

#endif
