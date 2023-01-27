#pragma once

#define D_LIFE_MAX	(3)
#define D_LIFE_SIZE_X (100)
#define D_LIFE_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ

	bool bUse;

}DOPPELGANGERLIFE;

HRESULT InitDoppelgangerLife();
void UninitDoppelgangerLife();
void UpdateDoppelgangerLife();
void DrawDoppelgangerLife();