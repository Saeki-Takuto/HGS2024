#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//�}�N����`
#define WIDTHTIME (50)
#define HEIGHTTIME (50)

//�v���g�^�C�v�錾
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int nTime);
void AddTime(int nValue);
int GetTime(void);

#endif
