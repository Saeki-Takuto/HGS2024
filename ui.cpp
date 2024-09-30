//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "ui.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUi[4] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;//���_�o�b�t�@�ւ̃|�C���^

//�^�C�g����ʂ̏���������
void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/memory.png",
		&g_pTextureUi[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/percent.png",
		&g_pTextureUi[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SCORE.png",
		&g_pTextureUi[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TIME.png",
		&g_pTextureUi[3]);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,50.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(170.0f,50.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,102.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(170.0f,102.0f,0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(270.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(320.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(270.0f, 102.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(320.0f, 102.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1400.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1550.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1400.0f, 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1550.0f, 50.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(750.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(850.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(750.0f, 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(850.0f, 50.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUi->Unlock();

}

//�^�C�g����ʂ̏I������
void UninitUi(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureUi[nCnt] != NULL)
		{
			g_pTextureUi[nCnt]->Release();
			g_pTextureUi[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}

	//�T�E���h�̒�~
	StopSound();
}

//�^�C�g����ʂ̍X�V����
void UpdateUi(void)
{
}

//�^�C�g����ʂ̕`�揈��
void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureUi[nCnt]);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}