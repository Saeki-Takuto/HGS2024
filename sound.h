//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���{�S��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM01 = 0,
	SOUND_LABEL_BGM02,
	SOUND_LABEL_BGM03,
	SOUND_LABEL_BGM04,
	SOUND_LABEL_BGM05,
	SOUND_LABEL_BGM06,
	SOUND_LABEL_SE01,
	SOUND_LABEL_SE02,
	SOUND_LABEL_SE03,
	SOUND_LABEL_SE04,
	SOUND_LABEL_SE05,
	SOUND_LABEL_SE06,
	SOUND_LABEL_SE07,
	SOUND_LABEL_SE08,
	SOUND_LABEL_SE09,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
