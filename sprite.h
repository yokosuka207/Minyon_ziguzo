/*==============================================================================
スプライト描画
   ポリゴン分け[sprite.h]
														 Author :新保翔麻
														 Date   :6/13
--------------------------------------------------------------------------------*/
#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_

//インクルード
#include"main.h"

//================================
//マクロ定義
//================================




//================================
//プロトタイプ宣言
//外部のプログラムに使ってほしい関数
//================================





void	SpriteDrawColorRotation(float, float, int, int, float, D3DXCOLOR, 
	 float PaternNo, float uv_w, float uv_h, int NumPatern);	//三角形用頂点格納処理
void	SpriteInit();//初期化
void	SpriteUninit();//終了処理
void	SpriteDrawColorBlockRotation(float, float, int, int, float, D3DXCOLOR,
	float, float PaternNo, float uv_w, float uv_h, int NumPatern);	//三角形用頂点格納処理

#endif // !SPRITTE_H_

