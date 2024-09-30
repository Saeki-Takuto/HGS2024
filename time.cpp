//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "time.h"
#include "main.h"
//�}�N����`
#define MAX_DIGIT (3)//�ő包

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTime;//�X�R�A�̈ʒu
int g_nTime;//�X�R�A�̒l
int nCntTimeSecond;

//�X�R�A�̏���������
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureTime);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);


	g_posTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
	g_nTime = 120;//�l������������
	nCntTime=0;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 845 + nCntTime * 30.0f, 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 845 + nCntTime * 30.0f + 30.0f, 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 845 + nCntTime * 30.0f, 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 845 + nCntTime * 30.0f + 30.0f, 100.0f, 0.0f);

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
	g_pVtxBuffTime->Unlock();
}

//�X�R�A�̏I������
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateTime(void)
{
	int aPosTexU[MAX_DIGIT];//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	int nCntTime;
	int nData1 = 100, nData2 = 10;

	nCntTimeSecond++;

	if (nCntTimeSecond >= 60)
	{
		nCntTimeSecond = 0;
		if (g_nTime != 0)
		{
			g_nTime--;
		}
	}

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		if (nCntTime == 0)
		{
			aPosTexU[0] = g_nTime / nData1;
		}
		else
		{
			aPosTexU[nCntTime] = (g_nTime % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffTime->Unlock();

}

//�X�R�A�̕`�揈��
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	int nCntTime;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		////�e�N�X�`���̐ݒ�
		////pDevice->SetTexture(0, NULL);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}

//�X�R�A�̐ݒ菈��
void SetTime(int nTime)
{
	int aPosTexU[MAX_DIGIT];//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_nTime = nTime;

	int nCntTime;
	int nData1 = 100, nData2 = 10;

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		if (nCntTime == 0)
		{
			aPosTexU[0] = nTime / nData1;
		}
		else
		{
			aPosTexU[nCntTime] = (nTime % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffTime->Unlock();

}

//�X�R�A�̉��Z����
void AddTime(int nValue)
{
	int aPosTexU[MAX_DIGIT];//�e���̐��l���i�[

	g_nTime += nValue;
	int nCntTime;
	int nData1 = 100, nData2 = 10;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntTime = 0; nCntTime < MAX_DIGIT; nCntTime++)
	{
		if (nCntTime == 0)
		{
			aPosTexU[0] = g_nTime / nData1;
		}
		else
		{
			aPosTexU[nCntTime] = (g_nTime % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntTime]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntTime]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffTime->Unlock();
}

//�X�R�A�擾
int GetTime(void)
{
	return g_nTime;
}