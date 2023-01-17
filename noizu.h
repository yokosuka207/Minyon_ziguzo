#pragma once
#include "main.h"
#include "renderer.h"

#define NOIZU_UV_W (1.0f / 2)
#define NOIZU_UV_H (1.0f / 2)


typedef struct
{
	//この四つがあれば取り敢えず表示できる
	D3DXVECTOR2		Position;	//表示座標
	D3DXCOLOR		Color;		//表示色
	float			Rotation;	//角度
	D3DXVECTOR2		Size;		//ポリゴンのサイズ
		//float w, h;	//ボックスサイズ
	float texno;	//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数

	bool UseFlag;	//使用フラグ

}NOIZU;

HRESULT InitNoizu();
void UninitNoizu();
void UpdateNoizu();
void DrawNoizu();

