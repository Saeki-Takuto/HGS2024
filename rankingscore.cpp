//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "input.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "rankingscore.h"
#include <stdio.h>
#include "input.h"

//�}�N����`
#define MAX_RANK (5)
#define MAX_DIGIT (8)
#define MAX_POLYGON (MAX_RANK*MAX_DIGIT)

typedef struct
{
	D3DXVECTOR3 pos;
	int nScore;
}RankScore;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];

int g_nRankUpdate = -1;//�����L���O�̍X�V
int g_nTimeRanking;//�^�C�}�[

//�����L���O�̏���������
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankingScore);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	//������
	g_nTimeRanking = 0;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(590.0f, 250.0f + (nCntRank * 80.0f)+(20.0f*nCntRank), 0.0f);
		g_aRankScore[nCntRank].nScore = 0;
		for (int nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - WIDTHRANKINGSCORE / 2 + (WIDTHRANKINGSCORE * nCntScore);
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - HEIGHTRANKINGSCORE / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + WIDTHRANKINGSCORE / 2 + (WIDTHRANKINGSCORE * nCntScore);
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - HEIGHTRANKINGSCORE / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - WIDTHRANKINGSCORE / 2 + (WIDTHRANKINGSCORE * nCntScore);
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + HEIGHTRANKINGSCORE / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + WIDTHRANKINGSCORE / 2 + (WIDTHRANKINGSCORE * nCntScore);
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + HEIGHTRANKINGSCORE / 2;
			pVtx[3].pos.z = 0.0f;

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
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();
}

//�����L���O�̏I������
void UninitRankingScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//�����L���O�̍X�V����
void UpdateRankingScore(void)
{
	static int nCounter{};

	if (g_nRankUpdate != -1)
	{
		nCounter++;   //���Z

		//�Y���X�R�A��_��
		if (nCounter == 10)
		{
			VERTEX_2D* pVtx{};       //���_���̃|�C���^

		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
			g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankingScore->Unlock();
		}
		else if (nCounter == 20)
		{
			VERTEX_2D* pVtx{};       //���_���̃|�C���^

		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
			g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt1 = 0; nCnt1 < MAX_DIGIT; nCnt1++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

				pVtx += 4;
			}

			g_pVtxBuffRankingScore->Unlock();

			nCounter = 0;
		}

	}
	if (KeyboardTrigger(DIK_RETURN) == true|| JoypadTrigger(JOYKEY_A))
	{
		//�^�C�g��
		SetFade(MODE_TITLE);
	}
}

//�����L���O�̕`�揈��
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^
	int nCntRankScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRankScore = 0; nCntRankScore < MAX_POLYGON; nCntRankScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankingScore);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRankScore, 2);
	}
}

//�����L���O�̐ݒ菈��
void SetRankingScore(int nScore)
{
	int nCntRank;
	int nCntScore;
	int nData{};

	g_nRankUpdate = -1;//������

	//5�Ԗڂ̃X�R�A�Ɣ�r
	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate = MAX_RANK - 1;
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntScore = nCntRank + 1; nCntScore < MAX_RANK; nCntScore++)
		{
			if (g_aRankScore[nCntRank].nScore <= g_aRankScore[nCntScore].nScore)
			{
				nData = g_aRankScore[nCntRank].nScore;//�㏑���O�̃X�R�A��ۑ�
				g_aRankScore[nCntRank].nScore = g_aRankScore[nCntScore].nScore;//�u������
				g_aRankScore[nCntScore].nScore = nData;//�u�������f�[�^��ۑ�
			}
		}
	}

	//�X�R�A�������Ă�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (nScore == g_aRankScore[nCntRank].nScore)
		{
			g_nRankUpdate = nCntRank;
			break;
		}
	}

	WriteScore();//�X�R�A�̏����o��
}

void ResetRanking(void)
{
	FILE* pFile;//�t�@�C���̓ǂݍ���

	//�t�@�C�����J��
	pFile = fopen("data/RANKING/ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			//�t�@�C�����J�����ꍇ
			fscanf(pFile, "%d", &g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);

		return;
	}

	fclose(pFile);

}

//�X�R�A�����o��
void WriteScore(void)
{
	FILE* pFile;//�t�@�C���̓ǂݍ���

	//�t�@�C�����J��
	pFile = fopen("data/RANKING/ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			//�t�@�C�����J�����ꍇ
			fprintf(pFile, "%d\n", g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);

		return;
	}
	fclose(pFile);
}

//�����L���O�̃X�R�A�e�N�X�`������
void SetRankingScoreTexture(void)
{
	int aPosTexU[MAX_DIGIT] = {};//�e���̐������i�[
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	int nCntScore;
	int nData1 = 10000000, nData2 = 1000000;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtx, 0);

	//�����Ƃɕ�������
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
		{
			if (nCntScore == 0)
			{
				aPosTexU[0] = g_aRankScore[nCntRank].nScore / nData1;
			}
			else
			{
				aPosTexU[nCntScore] = g_aRankScore[nCntRank].nScore % nData1 / nData2;
				nData1 = nData1 / 10;
				nData2 = nData2 / 10;
			}

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntScore]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntScore]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0 + (0.1 * aPosTexU[nCntScore]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1 + (0.1 * aPosTexU[nCntScore]), 1.0f);

			pVtx += 4;
		}
		nData1 = 10000000, nData2 = 1000000;
	}
	//�A�����b�N
	g_pVtxBuffRankingScore->Unlock();
}