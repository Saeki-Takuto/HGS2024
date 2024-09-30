//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "enemy.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "particle.h"
#include "score.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int g_nNumEnemy;//�G�̑���

//�G�̏���������
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^
	int nCntENEMY;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy000.png",
		&g_pTextureEnemy[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy001.png",
		&g_pTextureEnemy[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial001.png",
		&g_pTextureEnemy[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial002.png",
		&g_pTextureEnemy[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial003.png",
		&g_pTextureEnemy[4]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial004.png",
		&g_pTextureEnemy[5]);



	for (nCntENEMY = 0; nCntENEMY < MAX_ENEMY; nCntENEMY++)
	{

		g_aEnemy[nCntENEMY].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu�̏�����

		g_aEnemy[nCntENEMY].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������

		g_aEnemy[nCntENEMY].nCntBull = 0;						//�e�̃J�E���g�̏�����

		g_aEnemy[nCntENEMY].nLife = 500;						//���C�t��500��

		g_aEnemy[nCntENEMY].bUse = false;						//�s�g�p�ɂ���

		g_aEnemy[nCntENEMY].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //�J���[�̏�����

		g_aEnemy[nCntENEMY].nType = 0;								//�^�C�v�̏�����

		g_aEnemy[nCntENEMY].state = {};								//�X�e�[�g�̏�����

		int nCounterState = 0;										//�X�e�[�g�J�E���g�̏�����

		g_nNumEnemy = 0;
	}

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntENEMY = 0; nCntENEMY < MAX_ENEMY; nCntENEMY++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_aEnemy[nCntENEMY].col);
		pVtx[1].col = D3DXCOLOR(g_aEnemy[nCntENEMY].col);
		pVtx[2].col = D3DXCOLOR(g_aEnemy[nCntENEMY].col);
		pVtx[3].col = D3DXCOLOR(g_aEnemy[nCntENEMY].col);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}

//�G�̏I������
void UninitEnemy(void)
{
	int nCntENEMY;
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//�e�N�X�`���̔j��
	for (nCntENEMY = 0; nCntENEMY < NUM_ENEMY; nCntENEMY++)
	{

		if (g_pTextureEnemy[nCntENEMY] != NULL)
		{
			g_pTextureEnemy[nCntENEMY]->Release();
			g_pTextureEnemy[nCntENEMY] = NULL;
		}

	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}

//�G�̕`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if(g_aEnemy[nCntEnemy].bUse==true)
		{
			int nType = g_aEnemy[nCntEnemy].nType;

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[nType]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}

	}

}

void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	Player* pPlayer;

	pPlayer = GetPlayer();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEnemy].nCntBull++;
				g_aEnemy[nCntEnemy].col.r = 1.0f;
				g_aEnemy[nCntEnemy].col.g = 1.0f;
				g_aEnemy[nCntEnemy].col.b = 1.0f;
				g_aEnemy[nCntEnemy].col.a = 1.0f;

				if (g_aEnemy[nCntEnemy].nCntBull >= 100)
				{
						//�e�̔��˕������v�Z
						D3DXVECTOR3 direction = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
						D3DXVec3Normalize(&direction, &direction);

						// �e�̐ݒ�
						SetBullet(g_aEnemy[nCntEnemy].pos, direction * 5.0f, 100, BULLETTYPE_ENEMY);
						g_aEnemy[nCntEnemy].nCntBull = 0;
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].col.r = 1.0f;
					g_aEnemy[nCntEnemy].col.g = 1.0f;
					g_aEnemy[nCntEnemy].col.b = 1.0f;
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			case ENEMYSTATE_DIE:
				g_aEnemy[nCntEnemy].col.a -= 0.1f;
				if (g_aEnemy[nCntEnemy].col.a <= 0.0f)
				{
					g_aEnemy[nCntEnemy].col.a = 0.0f;
					g_aEnemy[nCntEnemy].bUse = false;
					g_aEnemy[nCntEnemy].nCntBull = 0;
					g_nNumEnemy--;//�G�̑����J�E���g�_�E��
					SetParticle(g_aEnemy[nCntEnemy].pos, 30,10);
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntEnemy;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aEnemy[nCntEnemy].col);
			pVtx[1].col = D3DXCOLOR(g_aEnemy[nCntEnemy].col);
			pVtx[2].col = D3DXCOLOR(g_aEnemy[nCntEnemy].col);
			pVtx[3].col = D3DXCOLOR(g_aEnemy[nCntEnemy].col);

		}
	}
	g_pVtxBuffEnemy->Unlock();

}

//�G�̐ݒ菈��
void SetEnemy(D3DXVECTOR3 pos, int nType,int nLife)
{
	int nCntEnemy;
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].bUse = true;//�g�p���Ă����Ԃɂ���
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].nType = nType; // �G�̎�ނ�ݒ�
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

			if (g_aEnemy[nCntEnemy].nType < 2)
			{
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (WIDTHENEMY / 2), g_aEnemy[nCntEnemy].pos.y - (HEIGHTENEMY / 2), g_aEnemy[nCntEnemy].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (WIDTHENEMY / 2), g_aEnemy[nCntEnemy].pos.y - (HEIGHTENEMY / 2), g_aEnemy[nCntEnemy].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (WIDTHENEMY / 2), g_aEnemy[nCntEnemy].pos.y + (HEIGHTENEMY / 2), g_aEnemy[nCntEnemy].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (WIDTHENEMY / 2), g_aEnemy[nCntEnemy].pos.y + (HEIGHTENEMY / 2), g_aEnemy[nCntEnemy].pos.z);
			}
			else
			{
				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (WIDTHENEMY), g_aEnemy[nCntEnemy].pos.y - (HEIGHTENEMY), g_aEnemy[nCntEnemy].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (WIDTHENEMY), g_aEnemy[nCntEnemy].pos.y - (HEIGHTENEMY), g_aEnemy[nCntEnemy].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (WIDTHENEMY), g_aEnemy[nCntEnemy].pos.y + (HEIGHTENEMY), g_aEnemy[nCntEnemy].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (WIDTHENEMY), g_aEnemy[nCntEnemy].pos.y + (HEIGHTENEMY), g_aEnemy[nCntEnemy].pos.z);

			}

			g_nNumEnemy++;//�G�̑����J�E���g�A�b�v
			break;

		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock();
}

//�G�̎擾
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

void HitEnemy(int nCntEnemy, int nDamage)
{
	//VERTEX_2D* pVtx;							//���_���ւ̃|�C���^
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		AddScore(100);


		if (g_aEnemy[nCntEnemy].nLife <= 0)
		{
			g_aEnemy[nCntEnemy].nLife = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DIE;
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = 5;
			g_aEnemy[nCntEnemy].col.r = 1.0f;
			g_aEnemy[nCntEnemy].col.g = 0.0f;
			g_aEnemy[nCntEnemy].col.b = 0.0f;
		}
}

int GetNumEnemy()
{
	return g_nNumEnemy;
}