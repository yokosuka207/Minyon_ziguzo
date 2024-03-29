//=============================================================================
//
//壊れるブロック処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//マクロ定義
//=============================================================================

#define BROKEN_SIZE_W (50)
#define BROKEN_SIZE_H (10)
#define BROKEN_MAX (20)
#define BROKEN_ANIME_MAX (4)
#define BROKEN_SPEED (2.0f)

struct BROKEN
{
	bool UseFlag;//構造体利用中フラグ
	bool DrawFlag;//アニメーション
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Postion;//表示座標(中心座標)
	D3DXVECTOR2 sp;
	float rot;//回転角度
	int index;	//ピースの番号
	int Number;	//ピースの何番目のブロックか
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数

	int FrameWait;

	bool breakFlag;	//壊れたかどうか
};

struct BROKEN_ANIME {
	bool UseFlag;
	D3DXVECTOR2 Size;//BOXサイズ
	D3DXVECTOR2 Postion;//表示座標(中心座標)
	int index;	//ピースの番号
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数
};

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitBroken();
void UninitBroken();
void UpdateBroken();
void DrawBroken();

void SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index,int number);
void SetBrokenAnime(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index);
void DeleteBroken(int PieceNo);
BROKEN* GetBroken();//BROKEN構造体の先頭ポインタを取得