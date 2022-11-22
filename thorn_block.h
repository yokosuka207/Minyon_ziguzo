/*==============================================================================

   トゲブロックヘッダー [thorn_block.h]
														 Author :座間研佑
														 Date   :2022/11/09

==============================================================================*/

#pragma once

#ifndef THORN_BLOCK_H_
#define THORN_BLOCK_H_

#include "main.h"
#include "renderer.h"

#define	THORN_BLOCK_MAX	64
#define THORN_BLOCK_H		30	//ブロックの縦サイズ
#define THORN_BLOCK_W		30	//ブロックの横サイズ

#define THORN_GRAND_H		30	//ブロックの縦サイズ
#define THORN_GRAND_W		135	//ブロックの横サイズ

#define THORN_SQUAER_H	40	//四隅ブロックの縦サイズ
#define THORN_SQUAER_W	40	//四隅ブロックの横サイズ

typedef enum
{
	THORN_GRAND_DOWN = 0,
	THORN_GRAND_LEFT,
	THORN_GRAND_UP,
	THORN_GRAND_RIGHT,
	THORN_GRAND_NONE,

}THORN_GRAND_TYPE;

typedef enum
{
	THORN_TYPE_GRAND = 0,
	THORN_TYPE_HARFGRAND,
	THORN_TYPE_CENTER,
	THORN_TYPE_T,
	THORN_TYPE_SQUARE,
	THORN_TYPE_NUM
}THORN_BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR2		Position;	//ポジション
	D3DXVECTOR2		Size;	//サイズ
	D3DXCOLOR		Col;	//色
	float			texno;	//テクスチャインデックス
	float			Rotation;	//角度
	bool			UseFlag;	//使用フラグ

}THORN_BLOCK;

HRESULT InitThornBlock();
void UninitThornBlock();
void UpdateThornBlock();
void DrawThornBlock();

void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, THORN_GRAND_TYPE type, THORN_BLOCK_TYPE btype, int pIndex);
THORN_BLOCK* GetThornBlock();

#endif // !THORN_BLOCK_H_
