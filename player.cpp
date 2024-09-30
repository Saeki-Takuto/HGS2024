//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "main.h"
#include "player.h"
#include "game.h"
#include "input.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "fade.h"
#include "particle.h"
#include "wave.h"


//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_CounterAnimPlayer;						//�A�j���[�V�����J�E���^�[
int g_nPatternAnimPlayer;						//�A�j���[�V�����p�^�[��No.
float g_fLengthPlayer;//�Ίp���̒���
float g_fAnglePlayer;//�Ίp���̊p�x
float g_Direction;	//����
Player g_player;

//�v���C���[�̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/rocket_02.png",
		&g_pTexturePlayer);

	g_CounterAnimPlayer=0;						//�A�j���[�V�����J�E���^�[��������
	g_nPatternAnimPlayer=0;						//�A�j���[�V�����p�^�[��No.��������
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f);		//�ʒu��������
	g_player.move= D3DXVECTOR3(0.0f,0.0f,0.0f);			//�ړ��ʂ�������
	g_Direction = 0.2;							//������������
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����������������
	g_player.bDisp = true;//��ʕ\����Ԃ�����������
	g_player.bUse = true;
	g_player.nLife = 2000;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;

	//�Ίp���̒������Z�o����
	g_fLengthPlayer = sqrtf(WIDTH * WIDTH + HEIGHT * HEIGHT) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_fAnglePlayer = atan2f(WIDTH, HEIGHT);


	//���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
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

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			g_player.nCounterState = PLAYERSTATE_NORMAL;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_pVtxBuffPlayer->Unlock();
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			return;
		}
		break;
	}


	if (KeyboardRepeat(DIK_A) == true||JoypadRepeat(JOYKEY_LEFT)||JoypadStickLX1())
	{//A�L�[�������ꂽ
		g_Direction = 0.2;
		if (KeyboardRepeat(DIK_W) == true|| JoypadRepeat(JOYKEY_UP) || JoypadStickLY0())
		{//A��W��������(����)
			g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
		}
		else if (KeyboardRepeat(DIK_S) == true|| JoypadRepeat(JOYKEY_DOWN) || JoypadStickLY1())
		{//A��S��������(����)
			g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
			g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
		}
		else if (KeyboardRepeat(DIK_D) == true|| JoypadRepeat(JOYKEY_RIGHT) || JoypadStickLX0())
		{//A��D��������(�����Ȃ�)
		}
		else
		{//A����������Ȃ�(��)
			g_player.move.x -= 3.0f;
		}
	}
	else if (KeyboardRepeat(DIK_D) == true|| JoypadRepeat(JOYKEY_RIGHT)|| JoypadStickLX0())
	{//D�L�[�������ꂽ
		g_Direction = -0.2;
		if (KeyboardRepeat(DIK_W) == true|| JoypadRepeat(JOYKEY_UP) || JoypadStickLY0())
		{//D��W��������(�E��)
			g_player.move.x += sinf(+D3DX_PI * 0.75f) * 3.0f;
			g_player.move.y += cosf(+D3DX_PI * 0.75f) * 3.0f;
		}
		else if (KeyboardRepeat(DIK_S) == true|| JoypadRepeat(JOYKEY_DOWN) || JoypadStickLY1())
		{//D��S��������(�E��)
			g_player.move.x += sinf(+D3DX_PI * 0.25f) * 3.0f;
			g_player.move.y += cosf(+D3DX_PI * 0.25f) * 3.0f;
		}
		else if (KeyboardRepeat(DIK_A) == true|| JoypadRepeat(JOYKEY_LEFT) || JoypadStickLX1())
		{//D��A��������(�����Ȃ�)
		}
		else
		{//D����������Ȃ�(�E)
			g_player.move.x += 3.0f;
		}
	}
	else if (KeyboardRepeat(DIK_W) == true|| JoypadRepeat(JOYKEY_UP) || JoypadStickLY0())
	{//W�L�[�������ꂽ
		if (KeyboardRepeat(DIK_S) == true|| JoypadRepeat(JOYKEY_DOWN) || JoypadStickLY1())
		{//W��S��������(�����Ȃ�)
		}
		else
		{//W����������(��)
			g_player.move.y -= 3.0;
		}
	}
	else if (KeyboardRepeat(DIK_S) == true|| JoypadRepeat(JOYKEY_DOWN) || JoypadStickLY1())
	{//S�L�[�������ꂽ
		if (KeyboardRepeat(DIK_W) == true|| JoypadRepeat(JOYKEY_UP) || JoypadStickLY0())
		{//S��W��������(�����Ȃ�)
		}
		else
		{//S����������(��)
			g_player.move.y += 3.0f;
		}
	}

	//if (KeyboardRepeat(DIK_UP) == true|| JoypadRepeat(JOYKEY_L3))
	//{//UP�L�[�������ꂽ(�g��)
	//	if (g_fLengthPlayer < 400)
	//	{
	//		g_fLengthPlayer += 10.0f;
	//	}
	//}
	//else if (KeyboardRepeat(DIK_DOWN) == true|| JoypadRepeat(JOYKEY_R3))
	//{//DOWN�L�[�������ꂽ(�k��)
	//	if (g_fLengthPlayer > 40)
	//	{
	//		g_fLengthPlayer -= 10.0f;
	//	}
	//}

	if (KeyboardRepeat(DIK_LEFT) == true|| KeyboardRepeat(DIK_Q) == true || JoypadRepeat(JOYKEY_L1) == true)
	{//LEFT�L�[�������ꂽ(�����v���)
		g_player.rot.z += 0.05f;
	}
	else if (KeyboardRepeat(DIK_RIGHT) == true||KeyboardRepeat(DIK_E) == true|| JoypadRepeat(JOYKEY_R1) == true)
	{//RIGHT�L�[�������ꂽ(���v���)
		g_player.rot.z -= 0.05f;
	}

	if (g_player.bUse == true)
	{
		if (KeyboardTrigger(DIK_SPACE) == true || JoypadTrigger(JOYKEY_A))
		{//SPACE
			//�e�̐ݒ�
			//SetBullet(g_player.pos, g_player.move);

			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 20.0f, cosf(g_player.rot.z + D3DX_PI) * 20.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			PlaySound(SOUND_LABEL_SE01);
		}
	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	if (g_player.pos.x >= SCREEN_WIDTH - 50)
	{
		g_player.pos.x = SCREEN_WIDTH - 50;
		g_player.move.x = 0.0f;

	}
	else if (g_player.pos.x <= 50)
	{
		g_player.pos.x = 50;
		g_player.move.x = 0.0f;
	}

	if (g_player.pos.y >= SCREEN_HEIGHT - 75)
	{
		g_player.pos.y = SCREEN_HEIGHT - 75;
		g_player.move.y = 0.0f;

	}
	else if (g_player.pos.y <= 75)
	{
		g_player.pos.y = 75;
		g_player.move.y = 0.0f;
	}

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.15f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_fAnglePlayer)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//g_CounterAnimPlayer++;							//�A�j���[�V�����J�E���^�[�����Z

	//if ((g_CounterAnimPlayer%SPEED)==0)
	//{//��莞�Ԍo��

	//	//�A�j���[�V�����p�^�[��No.���X�V
	//	g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % FLAME;

	//		//�e�N�X�`�����W�̐ݒ�
	//		pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, (g_nPatternAnimPlayer/5)*0.5);
	//		pVtx[1].tex = D3DXVECTOR2(g_Direction + g_nPatternAnimPlayer * 0.2f,(g_nPatternAnimPlayer / 5)*0.5);
	//		pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer * 0.2f, 0.5+(g_nPatternAnimPlayer / 5)*0.5);
	//		pVtx[3].tex = D3DXVECTOR2(g_Direction + g_nPatternAnimPlayer * 0.2f,0.5+(g_nPatternAnimPlayer / 5)*0.5);

	//	if (g_nPatternAnimPlayer>=10)
	//	{
	//		g_nPatternAnimPlayer = 0;				//�p�^�[��No.�������l�ɖ߂�
	//	}
	//}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}

//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}

//�v���C���[�̎擾
Player* GetPlayer(void)
{
	return &g_player;
}

//�v���C���[�̃q�b�g����
void HitPlayer(int nDamage)
{
	VERTEX_2D* pVtx;							//���_���ւ̃|�C���^

	if (g_player.nLife <= 0)
	{
		SetParticle(g_player.pos, 20,10);
		g_player.bDisp = false;
		g_player.bUse = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;
	}
	else
	{
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		g_pVtxBuffPlayer->Unlock();
	}
	HitWave(3);
}