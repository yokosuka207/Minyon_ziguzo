/*================================================================================
	
	インベントリヘッダー[Inventory.h]
 		
												Author: 齊藤 零登
												 Date : 2022/11/02
----------------------------------------------------------------------------------
Update:
	2022/11/01 Saito
	2022/11/02 Saito
	2022/11/04 Saito
	2022/11/16 Saito
================================================================================*/
#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "main.h"

//**************************************************
// マクロ定義
//**************************************************


//**************************************************
// 構造体
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		size;		// 表示サイズ
	D3DXCOLOR		color;		// カラー
	float			texno;		// テクスチャインデックス番号
}KEEP_PUZZLE_BG;

typedef struct
{
	float			PieNo;		// ピース番号

	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		size;		// 表示サイズ
	D3DXCOLOR		color;		// カラー
	float			texno;		// テクスチャインデックス番号

	bool			IsIn;		// 下のポケットの中にいるか
	bool			IsCatch;	// マウスにつかまれているか
	bool			IsUse;		// 使っているか
}KEEP_PUZZLE;


//**************************************************
// プロトタイプ宣言
//**************************************************
HRESULT InitInventory();
void UninitInventory();
void UpdateInventory();
void DrawInventory();

void SetInventory(float PieNo);
KEEP_PUZZLE* GetInventory();


#endif // !_INVENTORY_H_
