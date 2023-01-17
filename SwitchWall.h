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

#define SWITCHWALL_MAX (SWITCH_MAX * 4)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 sp;
	D3DXCOLOR	color;
	int			PieceIndex;
	int			SwitchIndex;//スイッチの番号が壁と同じなら処理が可能
	int			WallMax;	//壁の個数（引数で変化）
	int			PaternNo;
	float		uv_w;
	float		uv_h;
	bool		UseFlag;
}SWITCHWALL;

HRESULT InitSwitchWall();
void UninitSwitchWall();
void UpdateSwitchWall();
void DrawSwitchWall();
void SetSwitchWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo,int WallMax);
SWITCHWALL* GetSwitchWall();
void DeleteSwitchWall(int PieceNo);


#endif // !_SWITCHWALL_H_
