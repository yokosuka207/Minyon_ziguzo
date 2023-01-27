//=============================================================================
//ゴール用鍵
//
//制作者/座間研佑　
//=============================================================================

#pragma once

#include "main.h"

//==============================================================
//マクロ定義
//==============================================================
//#define STORYKEY_SIZE	(1)
#define STORYKEY_MAX	(8)


typedef struct
{
	D3DXVECTOR2 pos;		//表示位置
	D3DXVECTOR2 size;		//サイズ
	D3DXCOLOR	col;		//色

	float	rot;				//回転
	int		no;				//マップチップ番号

	bool	bUse;			//使用中フラグ

	int		HaveSKey;			//鍵所持数

}STORYKEY;

//==============================================================
//プロトタイプ宣言
//==============================================================

HRESULT InitStoryKey();
void UninitStoryKey();
void UpdateStoryKey();
void DrawStoryKey();

void SetStoryKey(D3DXVECTOR2 p, D3DXVECTOR2 s, int no, int direction, int tex);
STORYKEY* GetStoryKey();
void DeleteStoryKey(int no);
