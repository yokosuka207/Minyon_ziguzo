/*================================================================================

	光を出すオブジェクトヘッダー[issuer.h]

												Author: 齊藤 零登
												 Date : 2023/01/07
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _ISSUER_H_
#define _ISSUER_H_

#include "main.h"

//**************************************************
// 構造体
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;			// 座標
	D3DXVECTOR2		size;			// サイズ
	D3DXVECTOR2		dir;			// 光線を出すベクトル
	D3DXCOLOR		col;			// 色
	float			texNo;			// テクスチャインデックス
	float			rot;			// 角度
	
	int				PieceIndex;		// ピースの添え字格納

	bool			bAct;			// 作動フラグ
	bool			bUse;			// 使用フラグ

}ISSUER;

//**************************************************
// プロトタイプ宣言
//**************************************************
void InitIssuer();
void UninitIssuer();
void UpdateIssuer();
void DrawIssuer();

// セット関数
void SetIssuer(D3DXVECTOR2 pos, D3DXVECTOR2 size,float rot, int PNo);

// デリート関数
void DeleteIssuer(int PNo);

#endif // !_ISSUER_H_
