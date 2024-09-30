//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[2] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@�ւ̃|�C���^
int nCntTime;
int nCntPushTime;
int nCntFlash;
int FlashTime;
bool bPush;
//�^�C�g����ʂ̏���������
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Title003.png",
		&g_pTextureTitle[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Title002.png",
		&g_pTextureTitle[1]);

	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(200.0f,570.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(1400.0f,570.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(200.0f,770.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(1400.0f,770.0f,0.0f);

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
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̐ݒ�
	PlaySound(SOUND_LABEL_BGM01);

	nCntTime = NULL;
	nCntFlash = NULL;
	FlashTime = 30;
	nCntPushTime=NULL;
	bPush = false;

}

//�^�C�g����ʂ̏I������
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	StopSound();
}

//�^�C�g����ʂ̍X�V����
void UpdateTitle(void)
{
	nCntTime++;
	nCntFlash++;

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (nCntFlash==FlashTime)
	{
		pVtx += 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0,0,0,0);
		pVtx[1].col = D3DCOLOR_RGBA(0,0,0,0);
		pVtx[2].col = D3DCOLOR_RGBA(0,0,0,0);
		pVtx[3].col = D3DCOLOR_RGBA(0,0,0,0);
	}
	else if (nCntFlash >= FlashTime*2)
	{
		nCntFlash = 0;

		pVtx += 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	if (KeyboardTrigger(DIK_RETURN) == true|| JoypadTrigger(JOYKEY_A))
	{//����L�[(ENTER�L�[)�������ꂽ
		if (bPush == false)
		{
			bPush = true;
			//�T�E���h�̒�~
			StopSound();
			//�T�E���h�̐ݒ�
			PlaySound(SOUND_LABEL_SE08);
		}
	}

	if (bPush == true) 
	{
		FlashTime = 4;
		nCntPushTime++;

		if (nCntPushTime >= 180)
		{
			nCntPushTime=0;
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_TUTORIAL);
		}
	}

	if (nCntTime >= (60 * 46)&&bPush==false)
	{
		nCntTime = 0;
		SetFade(MODE_RANKING);
	}
}

//�^�C�g����ʂ̕`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt*4, 2);
	}

}