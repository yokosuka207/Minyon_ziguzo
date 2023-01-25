//=============================================================================
//
//壊れるブロック処理
//
//制作者/菊地 空　
//=============================================================================
#pragma once
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
#include "main.h"
//=============================================================================
//マクロ定義
//=============================================================================
#define FALLBLOCK_W (20)
#define FALLBLOCK_H (20)
#define FALLBLOCK_MAX (40)
typedef struct
{

	bool UseFlag;	//構造体利用中フラグ
	D3DXVECTOR2 Size;	//BOXサイズ
	D3DXVECTOR2 Position;	//表示座標(中心座標)
	D3DXVECTOR2 oldpos;	//1フレーム前の座標
	D3DXVECTOR2 sp;
	int PieceIndex;
	float rot;	//回転角度
	float texno;	//テクスチャインデックス
	D3DXCOLOR col;	//色
	float PaternNo;	//パターン番号
	float uv_w;	//横サイズ
	float uv_h;	//縦サイズ
	//bool fall; //落下
	//bool getfall;//落下の開始
	int NumPatern;	//横枚数

	int FrameWait;
}FALLBLOCK;


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitFallBlock();
void UninitFallBlock();
void UpdateFallBlock();
void DrawFallBlock();

FALLBLOCK*GetFallBlock();
void SetFallBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size ,int PieceNo);
void DeleteFallBlock(int PieceNo);

