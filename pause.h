//==================================================================
//
//�L�����N�^�[���L�[���͂ő���ł���悤�ɂ��悤
//Author:Saeki Takuto
//
//==================================================================

#ifndef _PAUSE_H_	//���̃}�N����`������ĂȂ�������
#define _PAUSE_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//�|�[�Y���j���[
typedef enum
{
	PAUSE_MENU_CONTINUE=0,//�Q�[���ɖ߂�
	PAUSE_MENU_RETRY,//�Q�[������蒼��
	PAUSE_MENU_QUIT,//�^�C�g����ʂɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 col;
//};
//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif
