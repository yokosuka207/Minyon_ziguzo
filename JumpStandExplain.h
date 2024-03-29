#pragma once
#include "main.h"

#define EXPLAIN_MAX		(5)

#define EXPLAIN_SIZE	(30)
#define HINT_SIZE_X		(SCREEN_WIDTH / 2)
#define HINT_SIZE_Y		(SCREEN_HEIGHT / 2)

typedef struct
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ

	int		No;			//マップチップ番号
	int		tex;		
	int		PieceIndex;
	float  rot;

	int PiaceIndex;

	bool bUse;
	bool HintUse;
	bool CollisionUse;

}EXPLAIN;

HRESULT InitExplain();
void UninitExplain();
void UpdateExplain();
void DrawExplain();

void SetExplain(D3DXVECTOR2 pos, D3DXVECTOR2 size, int no, int direction, int q);
EXPLAIN* GetExplain();

void DeleteExplain(int PieceNo);