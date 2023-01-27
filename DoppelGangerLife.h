#pragma once

#define D_LIFE_MAX	(3)
#define D_LIFE_SIZE_X (100)
#define D_LIFE_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��

	bool bUse;

}DOPPELGANGERLIFE;

HRESULT InitDoppelgangerLife();
void UninitDoppelgangerLife();
void UpdateDoppelgangerLife();
void DrawDoppelgangerLife();