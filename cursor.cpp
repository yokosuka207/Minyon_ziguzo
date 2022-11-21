/*================================================================================
	cursor.cpp
 
		カーソル
												Author: SaitoReito
												 Date : 2022/09/12
================================================================================*/
#include "cursor.h"		// 自身
#include "sprite.h"		// スプライト
#include "texture.h"	// テクスチャ
#include "input.h"		// 入力

//--------------------------------------------------
// マクロ定義
//--------------------------------------------------
#define CURSOR_SIZE_W	(50)		// カーソルのポリゴンの横のサイズ
#define CURSOR_SIZE_H	(50)		// カーソルのポリゴンの縦のサイズ

#define CURSOR_SPEED	(2)		// カーソルの移動速度

//--------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------

//--------------------------------------------------
// グローバル変数
//--------------------------------------------------
static CURSOR g_Cursor;
static char *g_TextureName = (char*)"data\\texture\\cursor.png";


//==================================================
// カーソル初期化
//==================================================
HRESULT InitCursor()
{
	// カーソルの初期化
	{
		g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
		g_Cursor.pos = g_Cursor.oldPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Cursor.sp = D3DXVECTOR2(1.0f, 1.0f);
		g_Cursor.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Cursor.texNo = LoadTexture(g_TextureName);

		g_Cursor.useFlag = false;
	}

	return S_OK;
}

//==================================================
// カーソル終了処理
//==================================================
void UninitCursor()
{

}

//==================================================
// カーソル更新処理
//==================================================
void UpdateCursor()
{
	if (g_Cursor.useFlag) {
		//[----------移動----------
		if(GetKeyboardPress(DIK_T)) {			// Press	T
			g_Cursor.pos.x -= g_Cursor.sp.x;	// 左移動
		}
		if(GetKeyboardPress(DIK_Y)) {			// Press	Y
			g_Cursor.pos.x += g_Cursor.sp.x;	// 右移動
		}
		if(GetKeyboardPress(DIK_U)) {			// Press	U
			g_Cursor.pos.y -= g_Cursor.sp.y;	// 上移動
		}
		if(GetKeyboardPress(DIK_I)) {			// Press	I
			g_Cursor.pos.y += g_Cursor.sp.y;	// 下移動
		}
		//----------移動----------]

		//[----------壁判定 (壁の上下左右)----------
		if (g_Cursor.pos.y < SCREEN_LIMIT_UP || g_Cursor.pos.y > SCREEN_LIMIT_DOWN || g_Cursor.pos.x < SCREEN_LIMIT_LEFT || g_Cursor.pos.x > SCREEN_LIMIT_RIGHT) {
			g_Cursor.pos = g_Cursor.oldPos;
		}
		//-----------------------------------------]
	}
}

//==================================================
// カーソル表示処理
//==================================================
void DrawCursor()
{
	if (g_Cursor.useFlag) {
		// テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Cursor.texNo));
		// ポリゴンの描画
		SpriteDrawColorRotation(g_Cursor.pos.x, g_Cursor.pos.y, g_Cursor.size.x, g_Cursor.size.y, 0.0f, g_Cursor.color, 1.0f, 1.0f, 1.0f, 1);
	}
}

//==================================================
// カーソルセット関数
// 引数：中心座標, サイズ
//==================================================
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Cursor.pos = g_Cursor.oldPos = pos;
	g_Cursor.size = size;

	g_Cursor.useFlag = true;
}


//==================================================
// カーソルゲット関数
//==================================================
CURSOR* GetCurso()
{
	return &g_Cursor;
}

//==================================================
// カーソル削除関数
//==================================================
void DeleteCursor()
{
	g_Cursor.useFlag = false;
}
