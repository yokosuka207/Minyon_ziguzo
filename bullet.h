
//=============================================================================
//
//バレット処理
//
//制作者/SORA　
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "enemy.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define BULLET_MAX (100)
#define BULLET_SPEED (4.0f)
#define BULLET_SIZE_W (ENEMY_SIZE_W)
#define BULLET_SIZE_H (ENEMY_SIZE_H / 3)

struct BULLET
{
	bool use;//構造体利用中フラグ
	float w, h;//BOXサイズ
	D3DXVECTOR2 pos;//表示座標(中心座標)
	D3DXVECTOR2 sp;//移動座標
	float rot;//回転角度
	float texno;//テクスチャインデックス
	D3DXCOLOR col;//色
	float PaternNo;//パターン番号
	float uv_w;//横サイズ
	float uv_h;//縦サイズ
	int NumPatern;//横枚数
	bool hit;
	int Damage; //弾によるダメージ
};

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();
BULLET* GetBullet();//BULLET構造体の先頭ポインタを取得
void SetBullet(D3DXVECTOR2 pos,D3DXVECTOR2 size, D3DXVECTOR2 spd);//弾発生
