//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "back.h"
#include "input.h"
#include "explosion.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"

//�}�N����`
#define NUM_PA (3)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePause[3] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//���_�o�b�t�@�ւ̃|�C���^
PAUSE_MENU g_PauseMenu;//�|�[�Y���j���[
int PauseSelect;

//�v���C���[�̏���������
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	int nCntPause;
	PauseSelect = 0;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/continue.png",
		&g_apTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RETRY.png",
		&g_apTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU.png",
		&g_apTexturePause[2]);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PA,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PA; nCntPause++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 1050.0f, 250.0f+(150*nCntPause), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 550.0f, 250.0f + (150 * nCntPause), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 1050.0f, 350.0f + (150 * nCntPause), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 550.0f, 350.0f + (150 * nCntPause), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

}

void UninitPause(void)
{
	int nCntPA;
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���̔j��
	for (nCntPA = 0; nCntPA < NUM_PA; nCntPA++)
	{

		if (g_apTexturePause[nCntPA] != NULL)
		{
			g_apTexturePause[nCntPA]->Release();
			g_apTexturePause[nCntPA] = NULL;
		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

void UpdatePause(void)
{
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^
	int nCntPause;

	if (KeyboardTrigger(DIK_DOWN) == true|| JoypadTrigger(JOYKEY_DOWN)==true)
	{//���������ꂽ
		PauseSelect++;
		if (PauseSelect >= PAUSE_MENU_MAX)
		{
			PauseSelect = 0;
		}
		PlaySound(SOUND_LABEL_SE07);
	}
	else if (KeyboardTrigger(DIK_UP) == true || JoypadTrigger(JOYKEY_UP)==true)
	{//�オ�����ꂽ
		PauseSelect--;
		if (PauseSelect < 0)
		{
			PauseSelect = PAUSE_MENU_MAX-1;
		}
		PlaySound(SOUND_LABEL_SE06);
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PA; nCntPause++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * PauseSelect;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_pVtxBuffPause->Unlock();


	if (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_A) == true)
	{
		switch (PauseSelect)
		{
		case PAUSE_MENU_CONTINUE://�R���e�j���[
			SetEnablePause(false);
			break;
		case PAUSE_MENU_RETRY://���g���C
			SetFade(MODE_GAME);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
}

void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^
	int nCntPA;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPA = 0; nCntPA < NUM_PA; nCntPA++)
	{
		if (g_apTexturePause[nCntPA] != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTexturePause[nCntPA]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPA * 4, 2);
		}
	}
}