//=============================================================================
//
//	ステージ街灯スイッチヘッダー[lamp_switch.h]
//															Author: 稲葉 陸斗
//															 Date : 2023/01/23
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#ifndef _LAMP_SWITCH_H_
#define _LAMP_SWITCH_H_

#include "main.h"

#define LAMP_SWITCH_MAX (3)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	color;
	float		rot;
	int			PieceIndex;
	int			LampSwitchIndex;
	bool		PressFlag;
	bool		UseFlag;
	bool		NotPressed;

	int			PaternNo;

}LAMP_SWITCH;

HRESULT InitLampSwitch();
void UninitLampSwitch();
void UpdateLampSwitch();
void DrawLampSwitch();
void SetLampSwitch(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo);
LAMP_SWITCH* GetLampSwitch();
void DeleteLampSwitch(int PieceNo);

#endif // !_LAMP_SWITCH_H_