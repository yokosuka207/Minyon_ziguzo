//-----------------------------------------------
//分割ステージ
//SplitStage.h
// 製作者：新保翔麻：制作日：11/22
//-----------------------------------------------

#pragma once

#include "main.h"
#include "renderer.h"

#define SPLIT_STAGE_SIZE_3	(180*3)
#define SPLIT_STAGE_SIZE_4	(180*4)

#define SPLIT_SIZE	(180)

typedef struct
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	int texNo;		// テクスチャ番号

	D3DXVECTOR2 Split3[3][3];
	D3DXVECTOR2 Split4[4][4];

}SplitStage;

void InitSplitStage();
void UninitSplitStage();
void UpdateSplitStage();
void DrawSplitStage();

SplitStage* GetSplitStage();