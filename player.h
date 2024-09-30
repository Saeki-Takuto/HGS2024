//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _PLAYER_H_//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_//2�d�C���N���[�h�h�~�̃}�N����`
#define FLAME (10)
#define SPEED (5)
#define WIDTH (100)
#define HEIGHT (150)

#include"main.h"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�o�����(�_��)
	PLAYERSTATE_NORMAL,//�ʏ���
	PLAYERSTATE_DAMAGE,//�_���[�W���
	PLAYERSTATE_DEATH,//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	PLAYERSTATE state;//�v���C���[�̏��
	D3DXVECTOR3 move;//�ړ���
	int nCounterState;//��ԊǗ��J�E���^�[
	int nLife;//�̗�
	bool bDisp;//�\�����邩���Ȃ���
	bool bUse;
}Player;


//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);

Player* GetPlayer(void);

#endif
