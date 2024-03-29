#pragma once

#define LIFE_MAX	(3)
#define LIFE_SIZE_X (100)
#define LIFE_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ

	bool bUse;

}PLAYERLIFE;

HRESULT InitPlayerLife();
void UninitPlayerLife();
void UpdatePlayerLife();
void DrawPlayerLife();