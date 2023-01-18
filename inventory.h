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
#define INVENTORYBG_SIZE_X		(100)
#define INVENTORYBG_SIZE_Y		(SCREEN_HEIGHT)
#define INVENTORYBG_POS_X_REVESE		((SCREEN_WIDTH/2) +INVENTORYBG_SIZE_X / 2)
#define INVENTORYBG_POS_Y		(SCREEN_HEIGHT / 2)
#define INVENTORYBG_POS_X		(INVENTORYBG_SIZE_X / 2)


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
	int				PieNo;		// ピース番号

	D3DXVECTOR2		pos;		// 表示座標
	D3DXVECTOR2		scpos;		// 表示座標
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

void SetInventory(int PieNo);
KEEP_PUZZLE* GetInventory();
void DeleteInventory(int PieNo);
void DeleteInventoryMapCip(int PieNo);


#endif // !_INVENTORY_H_
