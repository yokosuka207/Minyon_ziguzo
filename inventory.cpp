/*================================================================================
	
	パズル保存処理[inventory.cpp]
		
												Author: 齊藤 零登
												 Date : 2022/11/02
----------------------------------------------------------------------------------
Update:
	2022/11/01 Saito
	2022/11/02 Saito
	2022/11/04 Saito
	2022/11/16 Saito
================================================================================*/
#include "inventory.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "puzzle.h"

//**************************************************
// マクロ定義
//**************************************************
#define INVENTORY_MAX			(4)
#define INVENTORY_SIZE_X		(60)
#define INVENTORY_SIZE_Y		(60)
#define INVENTORY_BIGSIZE_X		(80)
#define INVENTORY_BIGSIZE_Y		(80)


#define INVENTORYBG_SIZE_X		(100)
#define INVENTORYBG_SIZE_Y		(SCREEN_HEIGHT)
#define INVENTORYBG_POS_X		(INVENTORYBG_SIZE_X / 2)
#define INVENTORYBG_POS_Y		(SCREEN_HEIGHT / 2)

#define INVENTORY_BOX_SIZE_Y	(INVENTORYBG_SIZE_Y / INVENTORY_MAX)
#define INVENTORY_POS_X			(INVENTORYBG_POS_X)
#define INVENTORY_POS_Y			INVENTORY_BOX_SIZE_Y + INVENTORY_BOX_SIZE_Y / 2		// 何番目かをこの値に掛ける


//**************************************************
// プロトタイプ宣言
//**************************************************
//**************************************************
// グローバル変数
//**************************************************
static KEEP_PUZZLE_BG	g_InventoryBG;
static KEEP_PUZZLE		g_Inventory[INVENTORY_MAX];

// テクスチャの名前
static char* g_InventoryBGTextureName = (char*)"data\\texture\\white.jpg";
static char* g_InventoryTextureName = (char*)"data\\texture\\blue.png";



//==================================================
// 初期化
//==================================================
HRESULT InitInventory() 
{
	// 各テクスチャのロード
	float BGTexNo = LoadTexture(g_InventoryBGTextureName);
	float TexNo = LoadTexture(g_InventoryTextureName);

	// 背景の初期化
	g_InventoryBG.pos = D3DXVECTOR2(INVENTORYBG_POS_X, INVENTORYBG_POS_Y);
	g_InventoryBG.size = D3DXVECTOR2(INVENTORYBG_SIZE_X, INVENTORYBG_SIZE_Y);
	g_InventoryBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	g_InventoryBG.texno = BGTexNo;

	// インベントリ内のパズルの初期化
	for (int i = 0; i < INVENTORY_MAX; i++) {
		g_Inventory[i].PieNo = 0.0f;

		g_Inventory[i].pos = D3DXVECTOR2(0.0f, INVENTORY_POS_Y);
		g_Inventory[i].size = D3DXVECTOR2(INVENTORY_SIZE_X, INVENTORY_SIZE_Y);
		g_Inventory[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Inventory[i].texno = TexNo;
		
		g_Inventory[i].IsIn = true;
		g_Inventory[i].IsCatch = false;
		g_Inventory[i].IsUse = false;
	}

	// デバッグ用
	SetInventory(0);
	SetInventory(0);
	SetInventory(0);
	SetInventory(0);

	return S_OK;
}

//==================================================
// 終了処理
//==================================================
void UninitInventory()
{

}

//==================================================
// 更新処理
//==================================================
void UpdateInventory()
{
	D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

	for (int i = 0; i < INVENTORY_MAX; i++) {
		if (g_Inventory[i].IsUse) {
			// 当たり判定用座標
			D3DXVECTOR2 min, max;		// min左上, max右下
			min = D3DXVECTOR2(g_Inventory[i].pos.x - g_Inventory[i].size.x / 2, g_Inventory[i].pos.y - g_Inventory[i].size.y / 2);
			max = D3DXVECTOR2(g_Inventory[i].pos.x + g_Inventory[i].size.x / 2, g_Inventory[i].pos.y + g_Inventory[i].size.y / 2);

			// マウスと所持パズルの当たり判定
			if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y) {
				// ちょっとでかくする
				g_Inventory[i].size = D3DXVECTOR2(INVENTORY_BIGSIZE_X, INVENTORY_BIGSIZE_Y);
			}
			else {
				// 元のサイズに戻す
				g_Inventory[i].size = D3DXVECTOR2(INVENTORY_SIZE_X, INVENTORY_SIZE_Y);
			}

			// 左に置くバージョン
			float bgmax_x = INVENTORYBG_POS_X + INVENTORYBG_SIZE_X / 2;
			// 所持パズルとUI範囲の当たり判定
			// 所持パズルが上に出たら
			if (g_Inventory[i].pos.x > bgmax_x) {
				// 外に出たよ
				// パズル出す
				PUZZLE_CIP* pPiece = GetPuzzleCip();
				if (!pPiece[i].UseFlag) {
					// ここでパズル出現
				}

				// 透明にする
				g_Inventory[i].color.a = 0.5f;
			}
			else {
				// 不透明にする
				g_Inventory[i].color.a = 1.0f;
			}

			// 入力(マウス左Press)
			if (IsMouseLeftPressed()) {
				//----------Trigger挙動----------
				if (!g_Inventory[i].IsCatch) {
					// マウスと所持パズルが当たっていたら
					if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y) {
						// 所持ピースを全部調べて誰もつかまれていなかったら自分がつかまる
						for (int j = 0; j < INVENTORY_MAX; j++) {
							if (g_Inventory[j].IsCatch == true) {
								break;
							}
							if (j == INVENTORY_MAX - 1) {
								// つかまった!!!!
								g_Inventory[i].IsCatch = true;
							}
						}
					}
				}
				//--------------------------------

				//----------Press挙動----------
				// つかまれていたら
				if (g_Inventory[i].IsCatch) {
					// パズルをマウスの位置に移動
					g_Inventory[i].pos = MousePos;
				}
				//-----------------------------
			}
			else {
				//----------Release挙動----------
				if (g_Inventory[i].IsCatch) {
					// 初期位置に戻る
					//g_Inventory[i].pos = D3DXVECTOR2(i * INVENTORY_POS_X, INVENTORY_POS_Y);		// 下ver
					g_Inventory[i].pos = D3DXVECTOR2(INVENTORY_POS_X, i * INVENTORY_POS_Y);			// 左ver
					// 逃れた!!!!
					g_Inventory[i].IsCatch = false;
				}
				//-------------------------------
			}
		}
	}
}

//==================================================
// 描画処理
//==================================================
void DrawInventory()
{
	// 背景の描画
	// テクスチャの設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_InventoryBG.texno));
	// ブレンド
	SetBlendState(BLEND_MODE_SUBTRACT);
	// 四角形の描画
	SpriteDrawColorRotation(g_InventoryBG.pos.x, g_InventoryBG.pos.y, g_InventoryBG.size.x, g_InventoryBG.size.y, 0.0f, g_InventoryBG.color, 1.0f, 1.0f, 1.0f, 1);
	// ブレンドをデフォに戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// インベントリ内のパズルの描画
	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		if (g_Inventory[i].IsUse) {
			// テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Inventory[i].texno));
			// 四角形の描画
			SpriteDrawColorRotation(g_Inventory[i].pos.x, g_Inventory[i].pos.y, g_Inventory[i].size.x, g_Inventory[i].size.y, 0.0f, g_Inventory[i].color, 1.0f, 1.0f, 1.0f, 1);
		}
	}
}

//==================================================
// セット関数
//==================================================
void SetInventory(float PieNo)
{
	// 保持するパズル配列の中を確認
	for (int i = 0; i < INVENTORY_MAX; i++) {
		// 使っていなかったら
		if (!g_Inventory[i].IsUse) {
			g_Inventory[i].PieNo = PieNo;
			
			g_Inventory[i].pos = D3DXVECTOR2(INVENTORY_POS_X, i * INVENTORY_POS_Y);
			
			g_Inventory[i].IsUse = true;

			break;
		}
	}
}

//==================================================
// ゲット関数
//==================================================
KEEP_PUZZLE * GetInventory()
{
	return g_Inventory;
}

