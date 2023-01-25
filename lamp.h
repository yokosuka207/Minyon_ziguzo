//=============================================================================
//
//	街灯ヘッダー[lamp.h]
//															Author: 稲葉 陸斗
//															 Date : 2023/01/23
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================
#ifndef _LAMP_H_
#define _LAMP_H_

#include "main.h"
#include "lamp_switch.h"

#define LAMP_MAX (LAMP_SWITCH_MAX)

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 sp;
	D3DXCOLOR	color;
	float		rot;
	int			PieceIndex;
	int			SwitchIndex;//スイッチの番号が壁と同じなら処理が可能
	int			PaternNo;
	float		uv_w;
	float		uv_h;
	bool		UseFlag;
}LAMP;

HRESULT InitLamp();
void UninitLamp();
void UpdateLamp();
void DrawLamp();
void SetLamp(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int direction, int LampMax);
LAMP* GetLamp();
void DeleteLamp(int PieceNo);


#endif // !_LAMP_H_

















////=============================================================================
////
////	街灯ヘッダー[lamp.h]
////															Author: 稲葉 陸斗
////															 Date : 2023/01/23
////-----------------------------------------------------------------------------
////															Update:	22/12/06
////=============================================================================
//#ifndef _LAMP_H_
//#define _LAMP_H_
//
//#include "main.h"
//#include "lamp_switch.h"
//
//#define LAMP_MAX (LAMP_SWITCH_MAX * 4)
//
//typedef struct {
//	D3DXVECTOR2 pos;
//	D3DXVECTOR2 size;
//	D3DXVECTOR2 sp;
//	D3DXCOLOR	color;
//	float		rot;
//	int			PieceIndex;
//	int			SwitchIndex;//スイッチの番号が壁と同じなら処理が可能
//	int			LampMax;	//壁の個数（引数で変化）
//	int			PaternNo;
//	float		uv_w;
//	float		uv_h;
//	bool		UseFlag;
//}LAMP;
//
//HRESULT InitLamp();
//void UninitLamp();
//void UpdateLamp();
//void DrawLamp();
//void SetLamp(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int direction, int LampMax);
//LAMP* GetLamp();
//void DeleteLamp(int PieceNo);
//
//
//#endif // !_LAMP_H_