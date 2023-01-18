#pragma once

#define LIFE_MAX	(3)
#define LIFE_SIZE_X (30)
#define LIFE_SIZE_Y (60)

typedef struct
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��

	bool bUse;

}PLAYERLIFE;

HRESULT InitPlayerLife();
void UninitPlayerLife();
void UpdatePlayerLife();
void DrawPlayerLife();