#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE=0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ���
	GAMESTATE_END,//�I�����
	GAMESTATE_GAMEOVER,//�Q�[���I�[�o�[
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
void SetEnablePause(bool bPause);
void SetEnableBsod(bool bBsod);
GAMESTATE GetGameState(void);
#endif

