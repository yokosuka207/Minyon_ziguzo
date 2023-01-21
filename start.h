#ifndef _START_H_
#define _START_H_

#include "main.h"

#define START_MAX (2)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	float		rot;
	int			PieceIndex;
	bool		GoalFlag;
	bool		UseFlag;

	int			PaternNo;

}START;

HRESULT InitStart();
void UninitStart();
void UpdateStart();
void DrawStart();
void SetStart(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo);
START* GetStart();
void DeleteStart(int PieceNo);

#endif // !_START_H_

