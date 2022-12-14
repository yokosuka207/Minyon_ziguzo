#pragma once

#define MOVE_BLOCK_SIZE	(20)
#define MOVE_BLOCK_MAX  (5)

typedef struct
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��
	D3DXVECTOR2 oldpos;
	D3DXVECTOR2 sp;		//�X�s�[�h

	int			PieceIndex;

	bool bUse;	

	bool GetMoveBlock;

}MOVEBLOCK;

HRESULT InitMoveBlock();
void UninitMoveBlock();
void UpdateMoveBlock();
void DrawMoveBlock();
void SetMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
void DeleteMoveBlock(int PieceNo);

MOVEBLOCK* GetMoveBlock();
