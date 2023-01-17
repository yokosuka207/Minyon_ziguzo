//=============================================================================
//
//ワープ処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define WARP_SIZE_W (20)
#define WARP_SIZE_H (20)
#define WARP_MAX (2)
#define WARP_SPEED (2.0f)

//ワープ アニメーション
#define WARP_UV_W (1.0f / 4)
#define WARP_UV_H (1.0f / 4)

struct WARP
{
	bool UseFlag;//構造体利用中フラグ
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Position;//表示座標(中心座標)
	D3DXVECTOR2 sp;
	float rot;//回転角度
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数


	int		PieceIndex; //ピースの添え字格納

	int FrameWait;
};

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitWarp();
void UninitWarp();
void UpdateWarp();
void DrawWarp();

void cipSetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index);


int SetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size);

WARP* GetWarp();//WARP構造体の先頭ポインタを取得