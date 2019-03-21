//=============================================================================
// < SoundTestプログラム >
// サウンドエフェクト番号表 [soundEffect.cpp]
// Author : 蔡 友剛
//
//=============================================================================
#include "main.h"
#include "sound.h"
#include "soundEffect.h"


//=============================================================================
// enumの定義を参照してIDを戻す関数
// 引数:[int] no
// 戻り値:[GUID] effectID
//=============================================================================
GUID GetSoundEffectID(int no)
{
	GUID effectID;

	switch (no)
	{
	case WATER_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_GARGLE;
		break;
	case CHORUS_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_CHORUS;
		break;
	case FLANGER_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_FLANGER;
		break;
	case ECHO_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_ECHO;
		break;
	case DISTORTION_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_DISTORTION;
		break;
	case COMPRESSOR_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_COMPRESSOR;
		break;
	case PARAMEQ_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_PARAMEQ;
		break;
	case I3DL2REVERB_SOUND_EFFECT:
		effectID = GUID_DSFX_STANDARD_I3DL2REVERB;
		break;
	case WAVES_REVERB_SOUND_EFFECT:
		effectID = GUID_DSFX_WAVES_REVERB;
		break;
	default:
		break;
	}

	return effectID;
}