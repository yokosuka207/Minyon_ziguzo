//=============================================================================
//
//	ステージスイッチウォールヘッダー[switch.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================
#ifndef _SWITCHWALL_H_
#define _SWITCHWALL_H_

#include "main.h"
#include "switch.h"

#define SWITCHWALL_MAX (SWITCH_MAX)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 sp;
	D3DXCOLOR	color;
	int			PieceIndex;
	int			SwitchIndex;
	int			PaternNo;
	bool		UseFlag;
}SWITCHWALL;

HRESULT InitSwitchWall();
void UninitSwitchWall();
void UpdateSwitchWall();
void DrawSwitchwall();
void SetSwitchWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
SWITCHWALL* GetSwitchWall();
void DeleteSwitchWall(int PieceNo);


#endif // !_SWITCHWALL_H_
