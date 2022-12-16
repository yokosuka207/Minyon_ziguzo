//=============================================================================
//
//高いところから落ちたら壊れるブロック処理
//
//制作者/座間研佑　制作日/2022/11/29
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define HIGH_SIZE_W (50)
#define HIGH_SIZE_H (10)
#define HIGH_MAX (10)
#define HIGH_SPEED (2.0f)

struct HIGH
{
	bool UseFlag;//構造体利用中フラグ
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Postion;//表示座標(中心座標)
	D3DXVECTOR2 sp;
	float rot;//回転角度
	int index;
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
HRESULT InitHigh();
void UninitHigh();
void UpdateHigh();
void DrawHigh();

void SetHigh(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index);
void DeleteHigh(int PieceNo);

HIGH* GetHigh();//BROKEN構造体の先頭ポインタを取得

//いろんなとこの名前が長くなりそうだったのでHighで統一しました、お赦しを