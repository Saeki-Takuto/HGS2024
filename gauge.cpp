//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "gauge.h"
#include "bsod.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "enemy.h"
#include "memory.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGauge[MAX_UI] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;//���_�o�b�t�@�ւ̃|�C���^

void InitGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gaugeback.png",
		&g_pTextureGauge[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gauge.png",
		&g_pTextureGauge[1]);


	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(502.0f, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(502.0f, 60.0f, 0.0f);

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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 58.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 58.0f, 0.0f);

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
	g_pVtxBuffGauge->Unlock();

}

void UninitGauge(void)
{
	for (int nCnt = 0; nCnt > MAX_UI; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGauge[nCnt] != NULL)
		{
			g_pTextureGauge[nCnt]->Release();
			g_pTextureGauge[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}

}

void UpdateGauge(void)
{
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[1].pos = D3DXVECTOR3(GetMemory()*5.0f, 12.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GetMemory()*5.0f, 58.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();

}

void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureGauge[nCnt] != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureGauge[nCnt]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

}
