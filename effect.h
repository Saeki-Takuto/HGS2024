#pragma once
//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�e�̎��
typedef enum
{
	EFFECTTYPE_PLAYER = 0,//�v���C���[�̎擾
	EFFECTTYPE_ENEMY,//�G�̒e
	EFFECTTYPE_MAX
}EFFECTTYPE;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife,D3DXVECTOR3 move);



//�}�N����`
#define WIDTHEFFECT (1000)
#define HEIGHTEFFECT (1000)

#endif
