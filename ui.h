#ifndef _UI_H_
#define _UI_H_

#include "main.h"

typedef enum
{
	UI_CLEAR = 0,//�^�C�g�����
	UI_GAMEOVER,//�Q�[�����
	UI_MAX
}UI;

//�v���g�^�C�v�錾
void InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);

#endif

