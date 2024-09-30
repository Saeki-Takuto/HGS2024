//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "particle.h"
#include "main.h"
#include "effect.h" 

//�}�N����`
#define MAX_PARTICLE (256)//�p�[�e�B�N���̍ő吔

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu(�����ʒu)
	int nLife;//����(��������)
	bool bUse;
	int nNumber;//���q�̐�
}Particle;

//�O���[�o���ϐ�
Particle g_aParticle[MAX_PARTICLE];

//����������
void InitParticle(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	int nCntParticle;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].nLife=0;
		g_aParticle[nCntParticle].bUse = false;
		g_aParticle[nCntParticle].nNumber = 0;
	}
}

//�X�V����
void UpdateParticle(void)
{
	VERTEX_2D* pVtx;
	int nCntParticle;
	int nCntApper;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	float fRadius;
	float fAngle;
	float fLength;
	int nLife;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//�p�[�e�B�N������
			for (nCntApper = 0; nCntApper < g_aParticle[nCntParticle].nNumber; nCntApper++)//���������������q�̐�
			{
				pos = g_aParticle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				fAngle=(float)(rand() % 629 - 314) / 100.0f;
				fLength = (float)(rand() % 20) / 10.0f + 0.2f;

				move.x = sinf(fAngle) * fLength;
				move.y = cosf(fAngle) * fLength;

				//�F�̎w��
				col = (1.0f, 1.0f, 1.0f, 1.0f);

				//���a�̐ݒ�
				fRadius = (float)(rand() % 100) / 10.0f + 0.5f;

				//�����̐ݒ�
				nLife = (float)(rand() % 1200) / 10.0f + 0.2;

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos, col, fRadius, nLife, move);
			}
			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aParticle[nCntParticle].nLife = 0;
				g_aParticle[nCntParticle].bUse = false;
				g_aParticle[nCntParticle].nNumber = 0;

			}
		}
	}
}

//�ݒ菈��
void SetParticle(D3DXVECTOR3 pos, int nLife,int nNumber)
{
	VERTEX_2D* pVtx;

	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].bUse = true;
			g_aParticle[nCntParticle].nNumber = nNumber;

			break;
		}
	}
}
