#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "main.h"

//�}�N����`
#define WIDTHMEMORY (50)
#define HEIGHTMEMORY (50)

//�v���g�^�C�v�錾
void InitMemory(void);
void UninitMemory(void);
void UpdateMemory(void);
void DrawMemory(void);
void SetMemory(int nMemory);
void AddMemory(int nValue);
int GetMemory(void);

#endif
