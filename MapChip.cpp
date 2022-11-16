/*==============================================================================

   マップチップ管理 [MapChip.cpp]
														 Author : 伏木　伶
														 Date   : 2022/11/01
--------------------------------------------------------------------------------
 Update: 
 22/11/01 fusegi
 22/11/02 fusegi
 22/11/04 fusegi
==============================================================================*/

#include "MapChip.h"
#include "puzzle.h"
#include "puzzlecip.h"
#include "block.h"
#include "puzzlecip.h"
#include "warp.h"
#include "goal.h"
#include "texture.h"
#include "sprite.h"

//**************************************************
//　マクロ定義
//**************************************************

//**************************************************
// 構造体定義
//**************************************************
Piece g_PieceMapChip[PUZZLE_MAX];
//**************************************************
// プロトタイプ宣言
//**************************************************

//**************************************************
// グローバル変数:
//**************************************************

static	ID3D11Buffer* g_MapChipVertexBuffer = NULL;	//ポリゴン用
static ID3D11ShaderResourceView* g_MapChipTexture;	//画像一枚で一つの変数が必要

static char* g_MapChipTextureName = (char*)"data\\texture\\green.png";	//テクスチャファイルパス


HRESULT InitMapChip() {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		g_PieceMapChip[p].UseFlag = false;
		g_PieceMapChip[p].no = -1;
		g_PieceMapChip[p].TexNo = LoadTexture(g_MapChipTextureName);
		g_PieceMapChip[p].direction = 0;
		g_PieceMapChip[p].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_PieceMapChip[p].OldPos = g_PieceMapChip[p].pos;
		g_PieceMapChip[p].size = D3DXVECTOR2(PIECE_SIZE, PIECE_SIZE);
		for (int d = 0; d < BLOCK_CHIP_DIRECTION; d++) {
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					g_PieceMapChip[p].chip[d][i][j] = 0;
				}
			}
		}
	}

	FileLoad(0);	//あとでnoに変更する？fusegi
	SetPieceMapChip(D3DXVECTOR2(500.0f, 500.0f), 0);
	SetPieceMapChip(D3DXVECTOR2(200.0f, 500.0f), 1);

	return S_OK;
}
void UninitMapChip() {
	if (g_MapChipTexture) {
		g_MapChipTexture->Release();
		g_MapChipTexture = NULL;
	}
}
void UpdateMapChip() {

}
void DrawMapChip() {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (g_PieceMapChip[p].UseFlag) {
			SetWorldViewProjection2D();

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PieceMapChip[p].TexNo));

			SpriteDrawColorRotation(
				g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y,
				g_PieceMapChip[p].size.x, g_PieceMapChip[p].size.y, g_PieceMapChip[p].direction * 90, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1
			);
		}
	}
}

void SetMapChip(D3DXVECTOR2 pos, int no) {
	//p=ブロック最大数
		//i=y方向
	for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
		//j=x方向
		for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
			switch (g_PieceMapChip[no].chip[g_PieceMapChip[no].direction][i][j]) {
			case static_cast <int> (MAPCHIP_TYPE::TYPE_NONE) :	//0
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLOCK) :	//1
				SetBlock(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE),no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_CHIP) :	//2
				SetChipPuzzuleChip(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE));
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_WARP) :	//3
				SetWarp(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE));
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_GOAL) :	//4
				SetGoal(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE),no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLANK) :	//5				
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PUSH) :	//6

				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PULL) :	//7

				break;
			default:
				break;
			}
		}
	}
	g_PieceMapChip[no].UseFlag = true;
}

void FileLoad(int StageNo) {
	const char* filename;
	switch (StageNo)
	{
	case 0:
		filename = "MapData/map0.txt";
		break;
	case 1:
		filename = "MapData/map1.txt";
		break;
	}
	FILE* fp;
	//オープン
	fp = fopen(filename, "r");
	if (!fp) {
		exit(999);
	}
	//一ステージ分読み込み
	for (int p = 0; p < PUZZLE_MAX; p++) {
		for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
			for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
				fscanf(fp, "%d", &g_PieceMapChip[p].chip[0][i][j]);
			}
		}
	}
	//クローズ
	fclose(fp);
}
void RotateChipData() {
	//ステージp
	for (int p = 0; p < PUZZLE_MAX; p++) {
		//方向d
		for (int d = 0; d < BLOCK_CHIP_DIRECTION - 1; d++) {
			//i = x
			for (int i = 0; i < BLOCK_CHIP_SIZE; i++) {
				//j = y
				for (int j = 0; j < BLOCK_CHIP_SIZE; j++) {
					g_PieceMapChip[p].chip[d + 1][j][BLOCK_CHIP_SIZE - 1 - i] =
						g_PieceMapChip[p].chip[d][i][j];
				}
			}
		}
	}
}
Piece* GetPiece() {
	return g_PieceMapChip;
}
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo) {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (g_PieceMapChip[p].UseFlag) {
			g_PieceMapChip[p].pos = pos;
			g_PieceMapChip[p].no = PieceNo;
			SetMapChip(pos, PieceNo);

			g_PieceMapChip[p].UseFlag = true;
			break;
		}
	}
}

