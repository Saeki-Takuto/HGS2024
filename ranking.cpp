//==================================================================
//
//GlitchWars
//Author:Saeki Takuto
//
//==================================================================

#include "ranking.h"
#include "rankingscore.h"
#include "rankset.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
int nCntTimeRanking = NULL;

//�����L���O�̏���������
void InitRanking(void)
{
	InitRankSet();//���ʂ̏�����

	InitRankingScore();//�����L���O�̃X�R�A�̏�����

	ResetRanking();//�����L���O�̃��Z�b�g

	SetRankingScoreTexture();//�����L���O�̃e�N�X�`������

	//�T�E���h�̐ݒ�
	PlaySound(SOUND_LABEL_BGM02);

	nCntTimeRanking = NULL;
}

//�����L���O�̏I������
void UninitRanking(void)
{
	UninitRankSet();//���ʂ̏I��
	
	UninitRankingScore();//�����L���O�̃X�R�A�̏�����

	StopSound();
}

//�����L���O�̍X�V����
void UpdateRanking(void)
{
	UpdateRankSet();//���ʂ̍X�V

	UpdateRankingScore();//�����L���O�̃X�R�A�̍X�V

	nCntTimeRanking++;

	if (nCntTimeRanking >= (60 * 10))
	{
		nCntTimeRanking = 0;
		SetFade(MODE_TITLE);
	}

}

//�����L���O�̕`�揈��
void DrawRanking(void)
{
	DrawRankSet();//���ʂ̕`��

	DrawRankingScore();//�����L���O�̃X�R�A�̍X�V
}