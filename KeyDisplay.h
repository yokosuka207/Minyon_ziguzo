#pragma once

#define KEYDISPLAY_MAX	(3)
#define KEYDISPLAY_SIZE_X (100)
#define KEYDISPLAY_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ

	bool bUse;

}KEYDISPLAY;

HRESULT InitKeyDisplay();
void UninitKeyDisplay();
void UpdateKeyDisplay();
void DrawKeyDisplay();