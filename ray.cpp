/*================================================================================

	光線処理[ray.h]

												Author: 齊藤 零登
												 Date : 2023/01/09
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "ray.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"

#include "cursor.h"
#include "issuer.h"
#include "block.h"
#include "MapChip.h"

//**************************************************
// マクロ定義
//**************************************************
#define		RAY_MAX	16

//**************************************************
// グローバル変数
//**************************************************
RAY g_Ray[RAY_MAX];
static char* g_RayTextureName = (char*)"data\\texture\\yello.jpg";

//==================================================
// 初期化
//==================================================
void InitRay()
{
	// 各値の初期化
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		g_Ray[i].pos = D3DXVECTOR2(0.0f, 0.0f);				// 座標
		g_Ray[i].StartPos = D3DXVECTOR2(0.0f, 0.0f);		// 始点座標
		g_Ray[i].EndPos = D3DXVECTOR2(0.0f, 0.0f);			// 終点座標
		g_Ray[i].size = D3DXVECTOR2(1.0f, 10.0f);			// サイズ
		g_Ray[i].dir = D3DXVECTOR2(0.0f, 0.0f);				// 光線を出すベクトル
		g_Ray[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_Ray[i].texNo = LoadTexture(g_RayTextureName);		// テクスチャインデックス
		g_Ray[i].rot = 0;									// 角度

		g_Ray[i].PieceIndex = -1;							// ピースの添え字格納
		g_Ray[i].IssuerIndex = -1;							// 発射装置の番号

		g_Ray[i].bUse = false;								// 使用フラグ
	}
}

//==================================================
// 終了関数
//==================================================
void UninitRay()
{
}

//==================================================
// 更新関数
//==================================================
void UpdateRay()
{
	// ブロックもらう
	BLOCK* pBlock = GetBlock();
	// ピースをもらう
	Piece* pPiece = GetPiece();
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		// 使用中
		if (g_Ray[i].bUse) {
			int j = 0;
			g_Ray[i].EndPos = g_Ray[i].StartPos;
			while (1) {
				g_Ray[i].EndPos += g_Ray[i].dir;
				// 画面外との判定
				if (!CollisionBB(g_Ray[i].EndPos, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT))){
					break;
				}
				// ブロックとの当たり判定
				for (int i = 0; i < BLOCK_MAX; i++){
					if (CollisionBB(g_Ray[i].EndPos, pBlock[i].Position, D3DXVECTOR2(0.0f, 0.0f), pBlock[i].Size)) {
						break;
					}
				}
				// ピースとの当たり判定
				for (int i = 0; i < PUZZLE_MAX; i++) {
					if (!CollisionBB(g_Ray[i].EndPos, pPiece[i].pos, D3DXVECTOR2(0.0f, 0.0f), pPiece[i].size)) {
						break;
					}
				}
				j++;
				if (j > 1000)break;
			}

			// 光線を作る
			D3DXVECTOR2 Length = g_Ray[i].EndPos - g_Ray[i].StartPos;
			g_Ray[i].size.x = D3DXVec2Length(&Length);

			g_Ray[i].rot = atan2(Length.x, Length.y);

			g_Ray[i].pos.x = g_Ray[i].size.x / 2;
			g_Ray[i].pos.y = g_Ray[i].size.y / 2;
		}
	}
}

//==================================================
// 描画関数
//==================================================
void DrawRay()
{
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		// 使用中
		if (g_Ray[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Ray[i].texNo));

			SpriteDrawColorRotation(
				g_Ray[i].pos.x, g_Ray[i].pos.y, -0.1f,
				g_Ray[i].size.x, g_Ray[i].size.y, g_Ray[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, -1.0f, 1
			);
		}
	}
}

//==================================================
// セット関数
//==================================================
void SetRay(D3DXVECTOR2 SPos, D3DXVECTOR2 dir, int INo, int PNo)
{
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		// 使用中ではない
		if (!g_Ray[i].bUse) {
			g_Ray[i].StartPos = SPos;
			g_Ray[i].dir = dir;
			g_Ray[i].IssuerIndex = INo;
			g_Ray[i].PieceIndex = PNo;
			g_Ray[i].bUse = true;

			break;
		}
	}
}

//==================================================
// デリート関数
//==================================================
void DeleteRayP(int PNo)
{
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		// ピースの番号が同じ
		if (g_Ray[i].PieceIndex == PNo) {
			g_Ray[i].bUse = false;
		}
	}
}

void DeleteRay(int INo)
{
	// 全チェック
	for (int i = 0; i < RAY_MAX; i++) {
		// ピースの番号が同じ
		if (g_Ray[i].IssuerIndex == INo) {
			g_Ray[i].bUse = false;
		}
	}
}




