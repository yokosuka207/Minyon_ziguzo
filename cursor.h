/*================================================================================

	カーソルヘッダー[cursor.h]

												Author: 齊藤 零登
												 Date : 2022/11/21
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef CURSOR_H_
#define CURSOR_H_

#include "main.h"
#include "renderer.h"

//--------------------------------------------------
// マクロ定義
//--------------------------------------------------
typedef struct
{
	D3DXVECTOR2 size;			// BOXサイズ
	D3DXVECTOR2 pos;			// 表示座標（中心座標）
	D3DXVECTOR2 oldPos;			// 1フレーム前の座標
	D3DXVECTOR2 sp;				// スピード
	D3DXCOLOR color;			// 色
	int	type;					// テクスチャの状態
	float texNo;				// テクスチャインデックス
	int RotIndex;	//回転した数
	bool pFlag;	//プレーヤーがいるかどうか
	bool useFlag;				// 使用中フラグ
}CURSOR;

//--------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------
//[----------基本関数----------
HRESULT InitCursor();
void UninitCursor();
void UpdateCursor();
void DrawCursor();
//----------基本関数----------]

//----------カーソルセット関数----------
// 引数：中心座標, サイズ
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size);

//----------カーソルゲット関数----------
// 返値：カーソル構造体のポインタ
CURSOR* GetCurso();		// ゲット関数

//----------カーソル削除関数----------
void DeleteCursor();

#endif // !CURSOR_H_
