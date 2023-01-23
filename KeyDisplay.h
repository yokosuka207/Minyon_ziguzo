#pragma once

#define KEYDISPLAY_MAX	(3)
#define KEYDISPLAY_SIZE_X (100)
#define KEYDISPLAY_SIZE_Y (100)

typedef struct
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��

	bool bUse;

}KEYDISPLAY;

HRESULT InitKeyDisplay();
void UninitKeyDisplay();
void UpdateKeyDisplay();
void DrawKeyDisplay();