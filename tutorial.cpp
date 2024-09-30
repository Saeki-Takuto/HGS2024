//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
#include "bullet.h"
#include "effect.h"
#include "player.h"
#include "particle.h"
#include "enemy.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorial = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//���_�o�b�t�@�ւ̃|�C���^
int nCntTimeTutorial;

//�^�C�g����ʂ̏���������
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial.png",
		&g_pTextureTutorial);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorial->Unlock();
	nCntTimeTutorial = 0;
	//�T�E���h�̐ݒ�
	PlaySound(SOUND_LABEL_BGM06);

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�v���C���[�̏���������
	InitPlayer();

	InitParticle();

	InitScore();

	//�G�̏���������
	InitEnemy();

	SetEnemy(D3DXVECTOR3(200.0f, 250.0f, 0.0f), 2, 50);
	SetEnemy(D3DXVECTOR3(200.0f, 650.0f, 0.0f), 3, 50);
	SetEnemy(D3DXVECTOR3(1400.0f, 250.0f, 0.0f),4, 50);
	SetEnemy(D3DXVECTOR3(1400.0f, 650.0f, 0.0f),5, 50);
}

//�^�C�g����ʂ̏I������
void UninitTutorial(void)
{
	//�G�̏I������
	UninitEnemy();

	//�v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�X�R�A�̏I������
	UninitScore();

	//�e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//�T�E���h�̒�~
	StopSound();
}

//�^�C�g����ʂ̍X�V����
void UpdateTutorial(void)
{
	int nNum = GetNumEnemy();

	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadPress(JOYKEY_Y)||nNum<=0)
	{//����L�[(ENTER�L�[)�������ꂽ
		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
		SetFade(MODE_GAME);
	}

	//�e�̍X�V����
	UpdateBullet();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�G�̍X�V����
	UpdateEnemy();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();

	//�X�R�A�̍X�V����
	UpdateScore();
}

//�^�C�g����ʂ̕`�揈��
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

}