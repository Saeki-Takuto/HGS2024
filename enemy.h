//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _ENEMY_H_//���̃}�N����`s������ĂȂ�������
#define _ENEMY_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"

//�}�N����`
#define MAX_ENEMY (128)
#define NUM_ENEMY (6)//�G�̎��
#define WIDTHENEMY (150)
#define HEIGHTENEMY (150)

typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ���
	ENEMYSTATE_DAMAGE,//�_���[�W���
	ENEMYSTATE_DIE,//���S���
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nCntBull;
	int nLife;
	bool bUse;
	D3DXCOLOR col;
	int nType;
	ENEMYSTATE state;
	int nCounterState;
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int nLife);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy();

#endif
