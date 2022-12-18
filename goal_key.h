//=============================================================================
//�S�[���p��
//
//�����/���Ԍ��C�@
//=============================================================================

#pragma once

#include "main.h"

//==============================================================
//�}�N����`
//==============================================================
#define GKEY_W		(15)
#define GKEY_H		(15)
#define GKEY_MAX	(1)

typedef struct 
{
	bool UseFlag;
	bool GetGKey;
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXCOLOR	col;
	float rot;
	float texno;
	float PaternNo;
	int NumPatern;
}GKey;

//==============================================================
//�v���g�^�C�v�錾
//==============================================================

HRESULT InitGKey();
void UninitGKey();
void UpdateGKey();
void DrawGKey();

void SetGKey(D3DXVECTOR2 pos, D3DXVECTOR2 size);
GKey* GetGKey();
