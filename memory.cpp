//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "memory.h"
#include "main.h"
#include "enemy.h"
//�}�N����`
#define MAX_DIGIT (3)//�ő包

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMemory = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMemory = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMemory;//�X�R�A�̈ʒu
int g_nMemory;//�X�R�A�̒l
int nCntMemorySecond;
static int nState;

//�X�R�A�̏���������
void InitMemory(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntMemory;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureMemory);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMemory,
		NULL);


	g_posMemory = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
	g_nMemory = 0;//�l������������
	nCntMemory = 0;
	nState = 0;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMemory->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMemory = 0; nCntMemory < MAX_DIGIT; nCntMemory++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 1420 + nCntMemory * 30.0f, 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 1420 + nCntMemory * 30.0f + 30.0f, 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 1420 + nCntMemory * 30.0f, 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 1420 + nCntMemory * 30.0f + 30.0f, 100.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMemory->Unlock();
}

//�X�R�A�̏I������
void UninitMemory(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMemory != NULL)
	{
		g_pTextureMemory->Release();
		g_pTextureMemory = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMemory != NULL)
	{
		g_pVtxBuffMemory->Release();
		g_pVtxBuffMemory = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateMemory(void)
{
	int aPosTexU[MAX_DIGIT];//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	int nCntMemory;
	int nData1 = 100, nData2 = 10;

	g_nMemory=GetNumEnemy()*10;

	if (g_nMemory >= 100||nState==1)
	{
		g_nMemory = 100;
		nState = 1;
	}

	g_pVtxBuffMemory->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntMemory = 0; nCntMemory < MAX_DIGIT; nCntMemory++)
	{
		if (nCntMemory == 0)
		{
			aPosTexU[0] = g_nMemory / nData1;
		}
		else
		{
			aPosTexU[nCntMemory] = (g_nMemory % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffMemory->Unlock();

}

//�X�R�A�̕`�揈��
void DrawMemory(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	int nCntMemory;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMemory, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntMemory = 0; nCntMemory < MAX_DIGIT; nCntMemory++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMemory);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntMemory, 2);
	}
}

//�X�R�A�̐ݒ菈��
void SetMemory(int nMemory)
{
	int aPosTexU[MAX_DIGIT];//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_nMemory = nMemory;

	int nCntMemory;
	int nData1 = 100, nData2 = 10;

	g_pVtxBuffMemory->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntMemory = 0; nCntMemory < MAX_DIGIT; nCntMemory++)
	{
		if (nCntMemory == 0)
		{
			aPosTexU[0] = nMemory / nData1;
		}
		else
		{
			aPosTexU[nCntMemory] = (nMemory % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffMemory->Unlock();

}

//�X�R�A�̉��Z����
void AddMemory(int nValue)
{
	int aPosTexU[MAX_DIGIT];//�e���̐��l���i�[

	g_nMemory += nValue;
	int nCntMemory;
	int nData1 = 100, nData2 = 10;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_pVtxBuffMemory->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntMemory = 0; nCntMemory < MAX_DIGIT; nCntMemory++)
	{
		if (nCntMemory == 0)
		{
			aPosTexU[0] = g_nMemory / nData1;
		}
		else
		{
			aPosTexU[nCntMemory] = (g_nMemory % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntMemory]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntMemory]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffMemory->Unlock();
}

//�X�R�A�擾
int GetMemory(void)
{
	return g_nMemory;
}