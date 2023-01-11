/*================================================================================

	光線ヘッダー[ray.h]

												Author: 齊藤 零登
												 Date : 2023/01/09
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "main.h"

//**************************************************
// 構造体
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;			// 座標
	D3DXVECTOR2		StartPos;		// 始点座標
	D3DXVECTOR2		EndPos;			// 終点座標
	D3DXVECTOR2		size;			// サイズ
	D3DXVECTOR2		dir;			// 光線を出すベクトル
	D3DXCOLOR		col;			// 色
	float			texNo;			// テクスチャインデックス
	float			rot;			// 角度
	
	int				PieceIndex;		// ピースの添え字格納
	int				IssuerIndex;	// 発射装置の番号
	
	bool			bUse;			// 使用フラグ

}RAY;

//**************************************************
// プロトタイプ宣言
//**************************************************
void InitRay();
void UninitRay();
void UpdateRay();
void DrawRay();

// セット関数
void SetRay(D3DXVECTOR2 SPos, D3DXVECTOR2 dir, int INo, int PNo);

// デリート関数
void DeleteRayP(int PNo);
void DeleteRay(int INo);

#endif // !_RAY_H_
