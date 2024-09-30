//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "player.h"
#include "back.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "game.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "pause.h"
#include "particle.h"
#include "rankingscore.h"
#include "time.h"
#include "wave.h"
#include "memory.h"
#include "gauge.h"
#include "ui.h"

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState=0;//��ԊǗ��J�E���^�[
bool g_bPause = false;//�|�[�Y�����ǂ���

//�Q�[����ʂ̏���������
void InitGame(void)
{
	//�w�i�̏���������
	InitBack();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�v���C���[�̏���������
	InitPlayer();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�G�̏���������
	InitEnemy();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏���������
	InitScore();

	//�^�C���̏���������
	InitTime();

	//�������g�p�ʂ̏���������
	InitMemory();

	//�E�F�[�u�̏���������
	InitWave();

	//�Q�[�W�̏���������
	InitGauge();

	//UI�̏���������
	InitUi();

	//�|�[�Y�̏���������
	InitPause();

	g_gameState = GAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;

	g_bPause = false;//�|�[�Y����

	PlaySound(SOUND_LABEL_BGM03);
}

//�Q�[����ʂ̏I������
void UninitGame(void)
{
	//�|�[�Y�̏I������
	UninitPause();

	//UI�̏I������
	UninitUi();

	//�Q�[�W�̏���������
	UninitGauge();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

	//�v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�w�i�̏I������
	UninitBack();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C���̏I������
	UninitTime();

	//�������g�p�ʂ̏���������
	UninitMemory();

	//�E�F�[�u�̏I������
	UninitWave();

	//���y�̒�~
	StopSound();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	int nNum;
	int nNum2;
	int nNum3;
	if (KeyboardTrigger(DIK_P) == true|| JoypadTrigger(JOYKEY_START)==true)
	{//�|�[�Y�L�[(P)�������ꂽ

		if (g_bPause == false)
		{
			//�T�E���h�̐ݒ�
			PlaySound(SOUND_LABEL_SE04);
		}
		else
		{
			//�T�E���h�̐ݒ�
			PlaySound(SOUND_LABEL_SE05);

		}
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{//�|�[�Y��
		UpdatePause();
	}

	if (g_bPause == false)
	{//�|�[�Y���łȂ����
		//�w�i�̍X�V����
		UpdateBack();

		//�e�̍X�V����
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�Q�[�W�̍X�V����
		UpdateGauge();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�����̍X�V����
		UpdateExplosion();

		//�p�[�e�B�N���̏���������
		UpdateParticle();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�^�C���̍X�V����
		UpdateTime();

		//�������g�p�ʂ̍X�V����
		UpdateMemory();

		//UI�̍X�V����
		UpdateUi();

		//�E�F�[�u�̍X�V����
		UpdateWave();


		Enemy* pEnemy = GetEnemy();
		Player* pPlayer = GetPlayer();

		nNum2 = GetTime();
		nNum = GetNumEnemy();
		nNum3 = GetMemory();

		if (nNum <= 0)//�G���S�����񂾏ꍇ
		{
		}
		else if (pPlayer->bUse == false)
		{
			g_gameState = GAMESTATE_GAMEOVER;
		}
		else if (nNum2 <= 0)//���Ԃ�0�ɂȂ����ꍇ
		{
			g_gameState = GAMESTATE_END;
		}
		else if (nNum3>=100)
		{
			g_gameState = GAMESTATE_GAMEOVER;
		}


		switch (g_gameState)
		{
		case GAMESTATE_NORMAL://�ʏ���
			break;
		case GAMESTATE_END://�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				//���[�h�ݒ�(���U���g��ʂɈڍs)
				SetFade(MODE_RESULT);

				ResetRanking();

				//�����L���O�̐ݒ�
				SetRankingScore(GetScore());

				g_nCounterGameState = 0;
				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�

			}
			break;
		case GAMESTATE_GAMEOVER://�I�����
			g_nCounterGameState++;
			if (g_nCounterGameState >= 60)
			{
				SetMode(MODE_BSOD);

				ResetRanking();

				//�����L���O�̐ݒ�
				SetRankingScore(GetScore());

				g_nCounterGameState = 0;
				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
			}
			break;
		}
	}
}

//�Q�[����ʂ̕`�揈��
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBack();

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C���̕`�揈��
	DrawTime();

	//�������g�p�ʂ̕`�揈��
	DrawMemory();

	//�Q�[�W�̕`�揈��
	DrawGauge();

	//UI�̕`�揈��
	DrawUi();


	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//�Q�[���̏�Ԃ̐ݒ�
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//�Q�[���̏�Ԃ̎擾
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//�|�[�Y�̗L�������ݒ�
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}