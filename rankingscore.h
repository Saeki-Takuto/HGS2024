#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"

//�}�N����`
#define WIDTHRANKINGSCORE (60.0f)
#define HEIGHTRANKINGSCORE (100.0f)

//�v���g�^�C�v�錾
void InitRankingScore(void);//�X�R�A�̏�����
void UninitRankingScore(void);//�X�R�A�̏I��
void UpdateRankingScore(void);//�X�R�A�̍X�V
void DrawRankingScore(void);//�X�R�A�̕`��
void SetRankingScore(int nScore);//�X�R�A�̐ݒ�
void ResetRanking(void);//�����L���O���̏�����
void WriteScore(void);//�X�R�A�̏�������
void SetRankingScoreTexture(void);//�e�N�X�`���̏���


#endif