/*================================================================================

	光を出すオブジェクト処理[issuer.h]

												Author: 齊藤 零登
												 Date : 2023/01/07
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "issuer.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "xinput.h"		// GamePad入力
#include "xkeyboard.h"	// Keyboard入力
#include "ray.h"

#include "mouse.h"

//**************************************************
// マクロ定義
//**************************************************
#define		ISSUER_MAX	4

//**************************************************
// グローバル変数
//**************************************************
ISSUER g_Issuer[ISSUER_MAX];
static char* g_IssuerTextureName = (char*)"data\\texture\\issuer.png";

//==================================================
// 初期化
//==================================================
void InitIssuer()
{
	// 各値の初期化
	// 全チェック
	for (int i = 0; i < ISSUER_MAX; i++) {
		g_Issuer[i].pos = D3DXVECTOR2(0.0f, 0.0f);	// 座標
		g_Issuer[i].size = D3DXVECTOR2(1.0f, 1.0f);	// サイズ
		g_Issuer[i].dir = D3DXVECTOR2(0.0f, 0.0f);		// 光線を出すベクトル
		g_Issuer[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_Issuer[i].texNo = LoadTexture(g_IssuerTextureName);	// テクスチャインデックス
		g_Issuer[i].rot = 0;	// 描画角度

		g_Issuer[i].PieceIndex = -1; // ピースの添え字格納

		g_Issuer[i].bAct = false;	// 作動フラグ
		g_Issuer[i].bUse = false;	// 使用フラグ
	}

	// デバッグ用

	SetIssuer(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(15.0f, 15.0f), 0, 0);
}

//==================================================
// 終了関数
//==================================================
void UninitIssuer()
{
}

//==================================================
// 更新関数
//==================================================
void UpdateIssuer()
{
	// 全チェック
	for (int i = 0; i < ISSUER_MAX; i++) {
		// 使用中
		if (g_Issuer[i].bUse) {
			DeleteRay(i);
			if (g_Issuer[i].bAct) {
				SetRay(g_Issuer[i].pos, D3DXVECTOR2(1.0f, 0.0f), i, g_Issuer[i].PieceIndex);
			}
		}
	}
}

//==================================================
// 描画関数
//==================================================
void DrawIssuer()
{
	// 全チェック
	for (int i = 0; i < ISSUER_MAX; i++) {
		// 使用中
		if (g_Issuer[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Issuer[i].texNo));

			SpriteDrawColorRotation(
				g_Issuer[i].pos.x, g_Issuer[i].pos.y, -0.1f,
				g_Issuer[i].size.x, g_Issuer[i].size.y, g_Issuer[i].rot * 90, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, -1.0f, 1
			);
		}
	}
}

//==================================================
// セット関数
//==================================================
void SetIssuer(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot, int PNo)
{
	// 全チェック
	for (int i = 0; i < ISSUER_MAX; i++) {
		// 使用中ではない
		if (!g_Issuer[i].bUse) {
			g_Issuer[i].pos = pos;
			g_Issuer[i].size = size;
			g_Issuer[i].rot = rot;
			g_Issuer[i].bUse = true;

			// 回転したときは作動フラグを保持する
			if (g_Issuer[i].PieceIndex != PNo) {
				g_Issuer[i].PieceIndex = PNo;
				g_Issuer[i].bAct = false;
			}
			// デバッグ用
			g_Issuer[i].bAct = true;

			break;
		}
	}
}

//==================================================
// デリート関数
//==================================================
void DeleteIssuer(int PNo)
{
	// 全チェック
	for (int i = 0; i < ISSUER_MAX; i++) {
		// ピースの番号が同じ
		if (g_Issuer[i].PieceIndex == PNo) {
			g_Issuer[i].bUse = false;
		}
	}
}




