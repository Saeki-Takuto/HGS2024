//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _EXPLOSION_H_	//���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);

//�}�N����`
#define WIDTHEXPLOSION (50)
#define HEIGHTEXPLOSION (50)
#define FLAMEEX (8)
#define SPEEDEX (5)


#endif
