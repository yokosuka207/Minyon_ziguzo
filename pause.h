#pragma once

#include "main.h"

//====================
//マクロ定義
//=====================
typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}PAUSE;


//======================
//プロトタイプ宣言
//======================

void	InitPause();
void	UninitPause();
void	UpdatePause();
void	DrawPause();
//void	SetPause(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXCOLOR col);