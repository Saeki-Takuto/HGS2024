#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

typedef enum
{
	RESULT_CLEAR = 0,//�^�C�g�����
	RESULT_GAMEOVER,//�Q�[�����
	RESULT_MAX
}RESULT;

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif

