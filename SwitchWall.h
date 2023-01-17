//=============================================================================
//
//	�X�e�[�W�X�C�b�`�E�H�[���w�b�_�[[switch.h]
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
	int			SwitchIndex;//�X�C�b�`�̔ԍ����ǂƓ����Ȃ珈�����\
	int			WallMax;	//�ǂ̌��i�����ŕω��j
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
