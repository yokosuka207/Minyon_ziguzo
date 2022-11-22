//-----------------------------------------------
//分割ステージ
//SplitStage.h
// 製作者：新保翔麻：制作日：11/22
//-----------------------------------------------

#pragma once

#include "main.h"
#include "renderer.h"



typedef struct
{

	D3DXVECTOR2 Split3[3][3];
	D3DXVECTOR2 Split4[4][4];

}SplitStage;

void InitSplitStage();
void UninitSplitStage();
void UpdateSplitStage();
void DrawSplitStage();

SplitStage* GetSplitStage();