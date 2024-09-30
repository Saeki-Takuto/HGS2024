//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _BULLET_H_	//���̃}�N����`������ĂȂ�������
#define _BULLET_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,//�v���C���[�̎擾
	BULLETTYPE_ENEMY,//�G�̒e
	BULLETTYPE_HOMING,
	BULLETTYPE_MAX
}BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife,BULLETTYPE type);



//�}�N����`
#define WIDTHBULLET (30)
#define HEIGHTBULLET (30)

#endif
