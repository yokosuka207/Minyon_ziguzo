/*==============================================================================

   テクスチャの管理[texture.h]
   ロードの簡略化
   重複した画像はロードしない
														 Author :新保翔麻
														 Date   :6/13
--------------------------------------------------------------------------------*/

#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include"renderer.h"
#include"main.h"

///============================
//マクロ定義
//-----------------------------


///============================
//プロトタイプ宣言
//-----------------------------
int LoadTexture(char* filename);

void Uninittexture();
//テクスチャデータの取得
ID3D11ShaderResourceView**	GetTexture(int index);	//ポインタ変数のポインタ




#endif // !TEXTURE_H_
