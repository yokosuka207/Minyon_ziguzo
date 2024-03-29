//=============================================================================
//
//	ステージスイッチヘッダー[switch.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "main.h"

#define SWITCH_MAX (5)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	float		rot;
	int			PieceIndex;
	int			SwitchIndex;
	bool		PressFlag;
	bool		UseFlag;
	bool		NotPressed;

	int			PaternNo;

}SWITCH;

HRESULT InitSwitch();
void UninitSwitch();
void UpdateSwitch();
void DrawSwitch();
void SetSwitch(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int PieceNo);
SWITCH* GetSwitch();
void DeleteSwitch(int PieceNo);

#endif // !_SWITCH_H_
