//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)								//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;							//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;				//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];							//�L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];							//�L�[�{�[�h�̃v���X���

XINPUT_STATE g_joykeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joykeyOldState;


//�L�[�{�[�h�̏���������
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̂ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//�L�[�{�[�h�̏I������
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();					//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard=NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//�L�[�{�[�h�̍X�V����
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();						//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//�L�[�{�[�h�̃v���X�����擾
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[���������u�Ԃ̏���
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//�L�[��b�����u�Ԃ̏���
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//�L�[��������Ă���Ԃ̏���
bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//�W���C�p�b�h�̏���������
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));
	
	//XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//�W���C�p�b�h�̏I������
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//�W���C�p�b�h�̍X�V����
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̓��͋@�\
	int nCntJoy;

	for (nCntJoy = 0; nCntJoy < JOYKEY_MAX; nCntJoy++)
	{
		g_joykeyOldState = g_joykeyState;//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		g_joykeyState = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}
}

//�W���C�p�b�h�̃v���X����ۑ�
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//�W���C�p�b�h���������u�Ԃ̏���
bool JoypadTrigger(JOYKEY key)
{
	bool TriggerPad = false;
	if (g_joykeyState.Gamepad.wButtons & (0x01 << key) && !(g_joykeyOldState.Gamepad.wButtons&(0x01<<key)))
	{
		TriggerPad = true;
	}
	return TriggerPad;
}

//�W���C�p�b�h�𗣂����u�Ԃ̏���
bool JoypadRelease(JOYKEY key)
{
	bool TriggerPad = false;
	if (g_joykeyOldState.Gamepad.wButtons & (0x01 << key) && !(g_joykeyState.Gamepad.wButtons & (0x01 << key)))
	{
		TriggerPad = true;
	}
	return TriggerPad;
}

//�W���C�p�b�h��������Ă���Ԃ̏���
bool JoypadRepeat(JOYKEY key)
{
	bool TriggerPad = false;
	if (g_joykeyOldState.Gamepad.wButtons & (0x01 << key) && (g_joykeyState.Gamepad.wButtons & (0x01 << key)))
	{
		TriggerPad = true;
	}
	return TriggerPad;
}

bool JoypadStickLX0(void)
{
	return (g_joykeyState.Gamepad.sThumbLX >=10000);
}

bool JoypadStickLX1(void)
{
	return (g_joykeyState.Gamepad.sThumbLX <= -10000);
}

bool JoypadStickLY0(void)
{
	return (g_joykeyState.Gamepad.sThumbLY >= 10000);
}

bool JoypadStickLY1(void)
{
	return (g_joykeyState.Gamepad.sThumbLY <= -10000);
}
