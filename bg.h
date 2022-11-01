/*==============================================================================

   背景管理 [bg.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/
#pragma once

#include "main.h"
#include "renderer.h"
typedef struct
{
	//この四つがあれば取り敢えず表示できる
	D3DXVECTOR3		Position;	//表示座標
	D3DXCOLOR		Color;		//表示色
	float			Rotation;	//角度
	D3DXVECTOR2		Size;		//ポリゴンのサイズ
		//float w, h;	//ボックスサイズ
	float texno;	//テクスチャインデックス

	bool UseFlag;	//使用フラグ

}BG;

HRESULT BgInit();
void BgUninit();
void BgUpdate();
void BgDraw();
void SetVertexBG(float PosX, float PosY, int Size_W, int Size_H, float Kakudo, D3DXCOLOR COL, float sokudo);
