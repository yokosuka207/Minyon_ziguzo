#pragma once

#define KEYDISPLAY_MAX	(3)
#define KEYDISPLAY_SIZE_X (100)
#define KEYDISPLAY_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//ï\é¶ç¿ïW
	D3DXVECTOR2 size;	//ëÂÇ´Ç≥

	bool bUse;

}KEYDISPLAY;

HRESULT InitKeyDisplay();
void UninitKeyDisplay();
void UpdateKeyDisplay();
void DrawKeyDisplay();