//=============================================================================
// < SoundTest�v���O���� >
// �T�E���h���� [sound.cpp]
// Author : �� �F��
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "soundEffect.h"

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
IDirectSound8	*g_pDirectSound = NULL;	// �T�E���h�C���^�[�t�F�[�X
LONG			g_fvolume = 0l;			// ��������	
DWORD			dwResults;				// �G�t�F�N�g�̃C���f�b�N�X
DWORD			g_BGMsize = 0;			// �T�C�Y(Byte)
char            filename[MAX_PATH];		// �t�@�C���̃p�X
int				initFrequency = 0;		// �������g��
WIN32_FIND_DATA	find;					// �t�@�C�����

//=============================================================================
// �T�E���h�̏�����
// hWnd:�E�B���h�E�n���h��
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
	// DirectSound�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// �������x���ݒ� 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

//=============================================================================
// �T�E���h�̓ǂݍ���
//=============================================================================
bool openReadSound(HWND hWnd)
{
	OPENFILENAME ofn;
	char old_path[MAX_PATH];

	// �J�����g�f�B���N�g�������o��
	GetCurrentDirectory(MAX_PATH, old_path);

	filename[0] = '\0';
	ofn.hwndOwner = hWnd;
	memset(&ofn, 0, sizeof(OPENFILENAME));  //�\���̂�0�ŃN���A
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = "sound file(*.wav)\0*.wav\0all file(*.*)\0*.*\0\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrDefExt = "wav";

	if (GetOpenFileName(&ofn) != TRUE)
	{
		return FALSE;
	}

	// �t�@�C���������o��
	FindFirstFile(ofn.lpstrFile, &find);

	// �J�����g�f�B���N�g����ݒ肷��
	SetCurrentDirectory(old_path);

	return TRUE;
}

//=============================================================================
// ��Еt��
//=============================================================================
void UninitSound(void)
{
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}
}

//=============================================================================
// �T�E���h�̃��[�h
// no:�T�E���h�i���o�[�i�w�b�_�ɒ�`���ꂽ�񋓌^�萔�j
//=============================================================================
LPDIRECTSOUNDBUFFER8 LoadSound(void)
{
	// MMIO = �}���`���f�B�A���o�́A�̗��B
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;						// �o�b�t�@�ݒ�\����
	WAVEFORMATEX pcm;						// �ȃf�[�^�t�H�[�}�b�g�\����

	HMMIO hMmio = NULL;						// MMIO�n���h��
	MMIOINFO mmioInfo;						// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p

	LPVOID pBlock;							// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD  dwSize;							// �Z�J���_���o�b�t�@�̃T�C�Y


	// 1.�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)filename, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���

	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// �����������Ƃɓǂݍ���
	
	// �������g���̃o�b�N�A�b�v�����
	initFrequency = (int)pcm.nSamplesPerSec;

	if(size != formatChunk.cksize) 		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR) 		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.�f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���
	
	if(size != dataChunk.cksize)  		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// 6.�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));	// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);			// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFX;
	buff.dwBufferBytes = size;

	g_BGMsize = size;

	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// �T�E���h�o�b�t�@�����o��
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7.���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// �f�[�^�]��
	delete[] pData;					// ���̓ǂݍ��ݗ̈������

	// �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Đ��ʒu��0�ɖ߂�
	pBuffer->SetCurrentPosition(0);

	// �Z�J���_���o�b�t�@��Ԃ��Ă悤�₭����...
	return pBuffer;
}

//=============================================================================
// ����炷
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
// flag   :1(E_DS8_FLAG_LOOP)�Ȃ烋�[�v�Đ�
//=============================================================================
void PlaySound(  LPDIRECTSOUNDBUFFER8 pBuffer, int flag/*=0*/ )
{	// ��������炷�̂ŁA�ŏ�����炵�����ꍇ��SetCurrentPosition(0)�����邱��
	pBuffer->Play(0, 0, flag);
}

//=============================================================================
// �����~�߂�
//=============================================================================
void PauseSound( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )	// ���Ă�����
	{
		pBuffer->Stop();				// �Ӗ��I�ɂ�Pause�ɂȂ�B
	}
}

//=============================================================================
// �����~
//=============================================================================
void StopSound(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if (status & DSBSTATUS_PLAYING)	// ���Ă�����
	{
		pBuffer->Stop();
	}
	pBuffer->SetCurrentPosition(0);

}

//=============================================================================
// �Đ������ǂ������ׂ�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
//=============================================================================
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )
	{
		return true;
	}
	return false;
}

//=============================================================================
// ���Ή��ʂ��擾
//=============================================================================
LONG GetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	LONG db = 0l;
	pBuffer->GetPan((LPLONG)db);

	return db;
}

//=============================================================================
// ���Ή��ʂ�ݒ�
//=============================================================================
void SetSoundBalanceVolume(LPDIRECTSOUNDBUFFER8 pBuffer,LONG db)
{
	pBuffer->SetPan(db);

}

//=============================================================================
// ���ʎ擾
//=============================================================================
int GetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	return (int)g_fvolume;
}

//=============================================================================
// ���ʒ���
//=============================================================================
void SetSoundVolume(LPDIRECTSOUNDBUFFER8 pBuffer,int type)
{
	if (type == VOLUME_UP)
	{
		g_fvolume += 100l;
		if (g_fvolume > DSBVOLUME_MAX)
		{
			g_fvolume = DSBVOLUME_MAX;
		}
	}

	else if(type == VOLUME_DOWN)
	{
		g_fvolume -= 100l;

		if (g_fvolume < DSBVOLUME_MIN)
		{
			g_fvolume = DSBVOLUME_MIN;
		}
	}

	else if (type == VOLUME_MULT)
	{
		g_fvolume = DSBVOLUME_MIN;
	}

	pBuffer->SetVolume(g_fvolume);
}

//=============================================================================
// �G�t�F�N�g
//=============================================================================
void SetSoundEffect(LPDIRECTSOUNDBUFFER8 pBuffer, int flag, int effectNo)
{
	DWORD status;

	pBuffer->GetStatus(&status);

	if (status & DSBSTATUS_PLAYING)
	{
		pBuffer->Stop();

		// �G�t�F�N�g���L�q
		DSEFFECTDESC dsEffect;

		// �G�t�F�N�g�̏�����(�폜)
		pBuffer->SetFX(NULL, NULL, NULL);
		
		// �G�t�F�N�g�̕ύX����
		if (effectNo != NULL_SOUND_EFFECT)
		{
			memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
			dsEffect.dwSize = sizeof(DSEFFECTDESC);
			dsEffect.dwFlags = 0;
			dsEffect.guidDSFXClass = GetSoundEffectID(effectNo);

			// �G�t�F�N�g��ݒ�
			pBuffer->SetFX(1, &dsEffect, &dwResults);

			switch (dwResults)
			{
			case DSFXR_LOCHARDWARE:
				OutputDebugString("Effect was placed in hardware.");
				break;
			case DSFXR_LOCSOFTWARE:
				OutputDebugString("Effect was placed in software.");
				break;
			case DSFXR_UNALLOCATED:
				OutputDebugString("Effect is not yet allocated to hardware or software.");
				break;
			}
		}

		pBuffer->Play(0, 0, flag);

	}
}

//=============================================================================
// �Đ��J�[�\���Ə������݃J�[�\���̈ʒu���擾
//=============================================================================
DWORD GetSoundCurrentPosition(LPDIRECTSOUNDBUFFER8 pBuffer, int type)
{
	DWORD PlayCursor = 0;
	DWORD WriteCursor = 0;
	DWORD ReturnCusor = 0;
	pBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor);

	if (type == GET_PLAY)
	{
		ReturnCusor = PlayCursor;
	}

	else if (type == GET_WRITE)
	{
		ReturnCusor = WriteCursor;
	}

	return ReturnCusor;
}

//=============================================================================
// �Đ��ʒu�̐ݒ�(�O�i�E���)
//=============================================================================
void SetSoundPosition(LPDIRECTSOUNDBUFFER8 pBuffer, int type, int flag,long distance)
{
	DWORD status;
	DWORD PlayCursor = 0;
	DWORD WriteCursor = 0;
	bool play = false;

	// �Đ���ԂƍĐ��ʒu���擾����
	{
		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)
		{
			pBuffer->Stop();
			play = true;
		}
		pBuffer->GetCurrentPosition(&PlayCursor, &WriteCursor);
	}

	// �O�i
	if (type == SET_FORWARD)
	{
		PlayCursor += POS_UNIT;
	}

	// ���
	else if (type == SET_REWIND)
	{
		PlayCursor -= POS_UNIT;
	}

	else if (type = SET_DISTANCE)
	{
		PlayCursor = distance;
	}

	// �I�[�o�t���[�h�~
	if (PlayCursor > g_BGMsize)
	{
		PlayCursor = g_BGMsize;
	}

	// �ʒu�ݒ�
	pBuffer->SetCurrentPosition(PlayCursor);

	if (play == true)
	{
		pBuffer->Play(0, 0, flag);
	}
}


//=============================================================================
// ���g����ݒ�
//=============================================================================
void SetSoundFrequency(LPDIRECTSOUNDBUFFER8 pBuffer,int freq)
{
	pBuffer->SetFrequency((DWORD)freq);
}

//=============================================================================
// �T�C�Y���擾
//=============================================================================
DWORD GetSoundSize(void)
{
	return g_BGMsize;
}

//=============================================================================
// �p�X���擾
//=============================================================================
char *GetSoundPass(void)
{
	return filename;
}

//=============================================================================
// �t�@�C�������擾
//=============================================================================
char *GetSoundName(int no)
{
	return &find.cFileName[no];
}

//=============================================================================
// �������g�����擾
//=============================================================================
int GetSoundInitFrequency(void)
{
	return initFrequency;
}
