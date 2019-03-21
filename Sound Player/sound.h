//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �� �F��
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
#define POS_UNIT	(10000l)
#define PAN_UNIT	(100l)
#define FREQ_UNIT	(100l)

//=============================================================================
// �萔��`
//=============================================================================
enum
{	// ���ʒ����p�t���O
	VOLUME_UP,
	VOLUME_DOWN,
	VOLUME_MULT
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

enum
{// �Đ��ʒu�̐ݒ�p�t���O
	SET_FORWARD,
	SET_REWIND,
	SET_DISTANCE
};

enum
{// �Đ��ʒu�̎擾�p�t���O
	GET_PLAY,
	GET_WRITE
};

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LPDIRECTSOUNDBUFFER8	LoadSound(void);									// �T�E���h�̃��[�h
HRESULT	InitSound(HWND hWnd);												// ������
void	UninitSound(void);													// ��Еt��
bool	openReadSound(HWND hWnd);											// �T�E���h�ǂݍ���
void	PauseSound(LPDIRECTSOUNDBUFFER8 pBuffer);							// �����~�߂�
void	StopSound(LPDIRECTSOUNDBUFFER8 pBuffer);							// �����~
void	PlaySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0);				// �����ƂɍĐ�
bool	IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);							// �Đ������ǂ���

// ���擾
LONG	GetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer);				// ���E�̉��ʂ��擾
DWORD	GetSoundSize(void);													// �T�C�Y���擾
int		GetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer);						// ���ʎ擾
DWORD	GetSoundCurrentPosition(LPDIRECTSOUNDBUFFER8 pBuffer,int type);		// �Đ��J�[�\���Ə������݃J�[�\���̈ʒu���擾
int		GetSoundInitFrequency(void);										// �������g�����擾
char	*GetSoundPass(void);												// �p�X���擾
char	*GetSoundName(int no);												// �t�@�C�������擾
											
// �ݒ�
void SetSoundPosition														// �Đ��ʒu�̐ݒ�
(LPDIRECTSOUNDBUFFER8 pBuffer, int type, int flag, long distance);																			
void SetSoundBalanceVolume													// ���E�̉��ʂ�ݒ�
(LPDIRECTSOUNDBUFFER8 pBuffer, LONG db);	
void SetSoundVolume															// ���ʒ���
(LPDIRECTSOUNDBUFFER8 pBuffer, int type);									
void SetSoundEffect															// �G�t�F�N�g
(LPDIRECTSOUNDBUFFER8 pBuffer, int flag, int effectNo);	
void SetSoundFrequency														// ���g����ݒ�
(LPDIRECTSOUNDBUFFER8 pBuffer, int freq);				

#endif