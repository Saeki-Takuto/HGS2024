//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "bsod.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBsod= {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBsod = NULL;//���_�o�b�t�@�ւ̃|�C���^
int nCntTimeBsod;

//�^�C�g����ʂ̏���������
void InitBsod(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/BSOD.png",
		&g_pTextureBsod);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBsod,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBsod->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(000.0f, 000.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	g_pVtxBuffBsod->Unlock();
	nCntTimeBsod = 0;

	//�T�E���h�̐ݒ�
	PlaySound(SOUND_LABEL_SE03);
}

//�^�C�g����ʂ̏I������
void UninitBsod(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBsod != NULL)
	{
		g_pTextureBsod->Release();
		g_pTextureBsod = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBsod != NULL)
	{
		g_pVtxBuffBsod->Release();
		g_pVtxBuffBsod = NULL;
	}
}

//�^�C�g����ʂ̍X�V����
void UpdateBsod(void)
{
	nCntTimeBsod++;

	if (nCntTimeBsod >= 300)
	{
		nCntTimeBsod=0;
		SetFade(MODE_RESULT);
	}

	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadPress(JOYKEY_START))
	{//����L�[(ENTER�L�[�ASTART�{�^��)�������ꂽ
		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
		SetFade(MODE_RESULT);
	}
}

//�^�C�g����ʂ̕`�揈��
void DrawBsod(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBsod, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBsod);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}