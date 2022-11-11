/*==============================================================================

   ブロック管理 [block.h]
														  Author :新保翔麻
														 Date   :10/18
--------------------------------------------------------------------------------*/
#pragma once

#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include "renderer.h"
#include"puzzlecip.h"

#define	BLOCK_MAX	64
#define BLOCK_H		30	//ブロックの縦サイズ
#define BLOCK_W		30	//ブロックの横サイズ

#define GRAND_H		30	//ブロックの縦サイズ
#define GRAND_W		135	//ブロックの横サイズ

#define SQUAER_H	40	//四隅ブロックの縦サイズ
#define SQUAER_W	40	//四隅ブロックの横サイズ

typedef enum
{
	GRAND_DOWN=0,
	GRAND_LEFT,
	GRAND_UP,
	GRAND_RIGHT,
	GRAND_NONE,

}GRAND_TYPE;

typedef enum
{
	TYPE_GRAND =0,
	TYPE_HARFGRAND,
	TYPE_CENTER,
	TYPE_T,
	TYPE_SQUARE,
	TYPE_ZYUUZI,
	TYPE_TATE,
	TYPE_BOX,
	TYPE_COVER,
	TYPE_NUM
}BLOCK_TYPE;

typedef struct
{
	D3DXVECTOR2		Position;	//ポジション
	D3DXVECTOR2		Size;	//サイズ
	D3DXCOLOR		Col;	//色
	float			texno;	//テクスチャインデックス
	float			Rotation;	//角度
	bool			UseFlag;	//使用フラグ

}BLOCK;

HRESULT InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();

void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void SetBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size,GRAND_TYPE type,BLOCK_TYPE btype,int pIndex,CIP_TYPE ctype);
BLOCK* GetBlock();

#endif // !BLOCK_H_
