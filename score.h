#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//マクロ定義
#define WIDTHSCORE (50)
#define HEIGHTSCORE (50)

//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif