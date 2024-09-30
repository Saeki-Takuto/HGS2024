//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _INPUT_H_	//���̃}�N����`������ĂȂ�������
#define _INPUT_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0,//�\���L�[(��)
	JOYKEY_DOWN,//�\���L�[(��)
	JOYKEY_LEFT,//�\���L�[(��)
	JOYKEY_RIGHT,
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_L1,
	JOYKEY_R1,
	JOYKEY_L2,
	JOYKEY_R2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);



HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoypadTrigger(JOYKEY key);
bool JoypadRelease(JOYKEY key);
bool JoypadRepeat(JOYKEY key);
bool JoypadStickLX0(void);
bool JoypadStickLX1(void);
bool JoypadStickLY0(void);
bool JoypadStickLY1(void);
bool JoypadStickRX0(void);
bool JoypadStickRX1(void);
bool JoypadStickRY0(void);
bool JoypadStickRY1(void);


#endif