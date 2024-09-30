//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "back.h"
#include "input.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "pause.h"
#include "particle.h"
#include "rankingscore.h"
#include "time.h"
#include "memory.h"

//�O���[�o���ϐ��錾
GAMESTATE g_gameState = GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState=0;//��ԊǗ��J�E���^�[
bool g_bPause = false;//�|�[�Y�����ǂ���

//�Q�[����ʂ̏���������
void InitGame(void)
{
	//�w�i�̏���������
	InitBack();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏���������
	InitScore();

	//�^�C���̏���������
	InitTime();

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

	//�����̏I������
	UninitExplosion();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�w�i�̏I������
	UninitBack();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C���̏I������
	UninitTime();

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

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�����̍X�V����
		UpdateExplosion();

		//�p�[�e�B�N���̏���������
		UpdateParticle();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�^�C���̍X�V����
		UpdateTime();

		nNum2 = GetTime();

		if (KeyboardTrigger(DIK_O) == true)
		{
			g_gameState = GAMESTATE_GAMEOVER;
		}
		else if (KeyboardTrigger(DIK_C) == true)
		{
			g_gameState = GAMESTATE_END;
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

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�����̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C���̕`�揈��
	DrawTime();

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