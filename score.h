#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�}�N����`
#define WIDTHSCORE (50)
#define HEIGHTSCORE (50)

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif