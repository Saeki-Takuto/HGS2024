//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _MAIN_H_					//���̃}�N����`������ĂȂ�������
#define _MAIN_H_					//2�d�C���N���[�h�h�~�̃}�N����`
#include <windows.h>
#include "d3dx9.h"
#include "stdio.h"
#define DIRECTINPUT_VERSION (0x0800)//�r���h�̌x���Ώ��p�}�N��
#include "dinput.h"					//���͏����ɕK�v
#include "Xinput.h"//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"//�T�E���h�����ɕK�v



//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")											//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")											//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass"											//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Glitch Wars"		//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1600)													//�E�B���h�E�̕�
#define SCREEN_HEIGHT (900)													//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef enum
{
	MODE_TITLE=0,//�^�C�g�����
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g���
	MODE_BSOD,
	MODE_RANKING,
	MODE_TUTORIAL,
	MODE_MAX
}MODE;

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;				//���_���W
	float rhw;						//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;					//���_�J���[
	D3DXVECTOR2 tex;				//�e�N�X�`�����W
}VERTEX_2D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawDEBUG(float Playerposx,float Playerposy,float Playerposz);

#endif

