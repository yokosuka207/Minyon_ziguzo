#pragma once
#include "main.h"

#define EXPLAIN_SIZE	(30)
#define HINT_SIZE_X		(SCREEN_WIDTH / 2)
#define HINT_SIZE_Y		(SCREEN_HEIGHT / 2)

typedef struct
{
	D3DXVECTOR2 pos;	//ï\é¶ç¿ïW
	D3DXVECTOR2 size;	//ëÂÇ´Ç≥

	int		No;

	bool bUse;
	bool HintUse;
	bool CollisionUse;

}EXPLAIN;

HRESULT InitExplain();
void UninitExplain();
void UpdateExplain();
void DrawExplain();

void SetExplain(D3DXVECTOR2 pos);
EXPLAIN* GetExplain();