/*==============================================================================

   トゲブロックヘッダー [thorn_block.h]
														 Author		:座間研佑
														 Date		:2022/11/09
														 最終更新	:2022/11/24
==============================================================================*/

#pragma once

#include "main.h"
#include "renderer.h"


//=============================================================================
//マクロ定義
//=============================================================================


#define	THORN_BLOCK_MAX (20)
#define THORN_BLOCK_H		25	//ブロックの縦サイズ
#define THORN_BLOCK_W		25	//ブロックの横サイズ

struct THORNBLOCK
{
	bool UseFlag;//構造体利用中フラグ
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Postion;//表示座標(中心座標)
	D3DXVECTOR2 sp;
	int			PieceIndex;
	float rot;//回転角度
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数

	int FrameWait;
};

//=============================================================================
//プロトタイプ宣言
//=============================================================================

HRESULT InitThornBlock();
void UninitThornBlock();
void UpdateThornBlock();
void DrawThornBlock();

//int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s);
void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
void DeleteThornBlock(int PieceNo);

THORNBLOCK* GetThornBlock();

