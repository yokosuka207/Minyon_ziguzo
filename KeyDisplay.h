#pragma once

#define KEYDISPLAY_MAX	(3)
#define KEYDISPLAY_SIZE_X (80)
#define KEYDISPLAY_SIZE_Y (80)

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