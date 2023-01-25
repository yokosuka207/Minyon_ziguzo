#pragma once

#define MOVE_BLOCK_SIZE	(20)
#define MOVE_BLOCK_MAX  (5)

typedef struct
{
	D3DXVECTOR2 pos;	//表示座標
	D3DXVECTOR2 size;	//大きさ
	D3DXVECTOR2 oldpos;
	D3DXVECTOR2 oldoldpos;
	D3DXVECTOR2 sp;		//スピード

	int			PieceIndex;
	int			NowPieceIndex;

	bool bUse;	

	bool GetMoveBlock;
	bool MoveFlag;
	bool MoveBlockNotMove;

}MOVEBLOCK;

HRESULT InitMoveBlock();
void UninitMoveBlock();
void UpdateMoveBlock();
void DrawMoveBlock();
void SetMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
void DeleteMoveBlock(int PieceNo);

MOVEBLOCK* GetMoveBlock();
