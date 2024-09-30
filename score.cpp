//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "score.h"
#include "main.h"
//�}�N����`
#define MAX_DIGIT (8)//�ő包

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;//�X�R�A�̈ʒu
int g_nScore;//�X�R�A�̒l

//�X�R�A�̏���������
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_DIGIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);


	g_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);//�ʒu������������
	g_nScore = 0;//�l������������

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH-250+nCntScore*30.0f, 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 250 +nCntScore*30.0f+30.0f, 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 250 +nCntScore*30.0f, 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 250 +nCntScore*30.0f+30.0f, 100.0f, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//�X�R�A�̏I������
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//�X�R�A�̍X�V����
void UpdateScore(void)
{
}

//�X�R�A�̕`�揈��
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	int nCntScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		////�e�N�X�`���̐ݒ�
		////pDevice->SetTexture(0, NULL);


		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntScore, 2);
	}
}

//�X�R�A�̐ݒ菈��
void SetScore(int nScore)
{
	int aPosTexU[MAX_DIGIT];//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_nScore = nScore;

	int nCntScore;
	int nData1 = 10000000, nData2 = 1000000;

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
	{
		if (nCntScore==0)
		{
			aPosTexU[0] = nScore / nData1;
		}
		else
		{
			aPosTexU[nCntScore] = (nScore % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0+(0.1*aPosTexU[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1+(0.1 * aPosTexU[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntScore]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();

}

//�X�R�A�̉��Z����
void AddScore(int nValue)
{
	int aPosTexU[MAX_DIGIT];//�e���̐��l���i�[

	g_nScore += nValue;
	int nCntScore;
	int nData1 = 10000000, nData2 = 1000000;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
	{
		if (nCntScore == 0)
		{
			aPosTexU[0] = g_nScore / nData1;
		}
		else
		{
			aPosTexU[nCntScore] = (g_nScore % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntScore]), 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();
}

//�X�R�A�擾
int GetScore(void)
{
	return g_nScore;
}