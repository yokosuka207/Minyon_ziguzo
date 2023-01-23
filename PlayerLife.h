#pragma once

#define LIFE_MAX	(3)
#define LIFE_SIZE_X (100)
#define LIFE_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//ï\é¶ç¿ïW
	D3DXVECTOR2 size;	//ëÂÇ´Ç≥

	bool bUse;

}PLAYERLIFE;

HRESULT InitPlayerLife();
void UninitPlayerLife();
void UpdatePlayerLife();
void DrawPlayerLife();