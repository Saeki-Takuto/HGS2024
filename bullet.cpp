//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "bullet.h"
#include "main.h"
#include "Bullet.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "effect.h"
#include "particle.h"

//�}�N����`
#define MAX_BULLET (128)//�e�̍ő吔
#define MAX_SPEED (5)	//�A�j���[�V�����X�s�[�h

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nLife;			//����
	BULLETTYPE type;	//�e���o���Ă镨�̃^�C�v
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[2] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];					//�e�̏��

//�e�̏���������
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							  "data/TEXTURE/bullet001.png",
							  &g_pTextureBullet[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/virus.png",
		&g_pTextureBullet[1]);


	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aBullet[nCntBullet].type = {};//�g�p���Ă��Ȃ���Ԃɂ���

	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet,
								NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x- (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y- (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x+ (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y- (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x- (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y+ (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x+ (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y+ (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//�e�̏I������
void UninitBullet(void)
{
	for (int nCnt = 0; nCnt > 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//�e�̍X�V����
void UpdateBullet(void)
{
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	int nCntBullet;

	int nDeb = 1;


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

				Enemy* pEnemy;//�G�̏��ւ̃|�C���^
				Player* pPlayer;
				int nCntEnemy;

				//�G�̎擾
				pEnemy = GetEnemy();

				pPlayer = GetPlayer();

				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				//g_aBullet[nCntBullet].move.x += 0.3f;
				//�ʒu�̍X�V
				g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
				g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
				g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

				if (g_aBullet[nCntBullet].type == BULLETTYPE_HOMING)
				{

				}

				pVtx += 4 * nCntBullet;

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y - (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y - (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y + (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y + (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);


				g_aBullet[nCntBullet].nLife--;

				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{//�v���C���[�̒e

					for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
					{
						if (pEnemy->bUse == true)
						{//�G���g�p����Ă���
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - WIDTHENEMY / 2 && g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + WIDTHENEMY / 2 && g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - HEIGHTENEMY / 2 && g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + HEIGHTENEMY / 2)
							{
								if (pEnemy->state != ENEMYSTATE_DIE)
								{
									HitEnemy(nCntEnemy, 50);
								}
								g_aBullet[nCntBullet].bUse = false;//�e���g�p���ĂȂ���Ԃɂ���
							}
						}
					}
				}
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY|| g_aBullet[nCntBullet].type == BULLETTYPE_HOMING)
				{//�G�̒e
						if (pPlayer->bUse == true)
						{//�v���C���[���g�p����Ă���
							if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - WIDTH / 2 && g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + WIDTH / 2 && g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - HEIGHT / 2 && g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + HEIGHT / 2)
							{
								HitPlayer(50);
								g_aBullet[nCntBullet].bUse = false;//�e���g�p���ĂȂ���Ԃɂ���
							}
						}
				}

				if (g_aBullet[nCntBullet].pos.x <= 0.0f || g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH|| g_aBullet[nCntBullet].pos.y <= 0.0f || g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)//�e����ʊO�ɂł�
				{
					g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
				}
				g_pVtxBuffBullet->Unlock();
		}
	}
}

//�e�̕`�揈��
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̏���
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBullet[0]);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBullet[1]);

			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4*nCntBullet,//���_�C���f�b�N�X
				2);
		}
	}
}

//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].bUse = true;//�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].type = type;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y - (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y - (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y + (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (WIDTHBULLET / 2), g_aBullet[nCntBullet].pos.y + (HEIGHTBULLET / 2), g_aBullet[nCntBullet].pos.z);
			break;
		}

		pVtx += 4;


	}
	g_pVtxBuffBullet->Unlock();

}