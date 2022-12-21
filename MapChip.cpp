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
#include "joint.h"
#include "texture.h"
#include "sprite.h"
#include "jump_stand.h"
#include "SplitStage.h"
#include "Key.h"
#include "OpenKey.h"
#include "fallblock.h"
#include "thorn_block.h"
#include "switch.h"
#include "SwitchWall.h"
#include "StageSelect.h"
#include "SheerFloors.h"
#include "broken.h"
#include "high_broken.h"
#include"spawnpoint.h"

//**************************************************
//　マクロ定義
//**************************************************

//**************************************************
// 構造体定義
//**************************************************
Piece g_PieceMapChip[PUZZLE_MAX];
//**************************************************
// グローバル変数:
//**************************************************
static ID3D11ShaderResourceView* g_MapChipTexture;	//画像一枚で一つの変数が必要
static char* g_MapChipTextureName = (char*)"data\\texture\\black&white.jpg";	//テクスチャファイルパス

HRESULT InitMapChip() {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		g_PieceMapChip[p].UseFlag = false;
		g_PieceMapChip[p].no = -1;
		g_PieceMapChip[p].TexNo = LoadTexture(g_MapChipTextureName);
		g_PieceMapChip[p].direction = 2;
		g_PieceMapChip[p].pos = D3DXVECTOR2(0.0f,0.0f);
		g_PieceMapChip[p].OldMovePos = g_PieceMapChip[p].OldPos = g_PieceMapChip[p].pos;
		g_PieceMapChip[p].size = D3DXVECTOR2(PIECE_SIZE, PIECE_SIZE);
		g_PieceMapChip[p].MoveEndFlag = false;
		g_PieceMapChip[p].MoveFlag = false;
		for (int d = 0; d < BLOCK_CHIP_DIRECTION; d++) {
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					g_PieceMapChip[p].chip[d][i][j] = 0;
				}
			}
		}
	}

	STAGESELECT* pStageSelect = GetSelect();
	FileLoad(pStageSelect->StagePieceIndex);	//あとでnoに変更する？fusegi	yeah

	RotateChipData();

	SplitStage* pSplitStage = GetSplitStage();
	SetPieceMapChip(pSplitStage->Split3[0][0], 0);

	//SetPieceMapChip(pSplitStage->Split3[1][2], 2);

	//SetPieceMapChip(pSplitStage->Split3[1][0], 1);
	//SetPieceMapChip(pSplitStage->Split3[2][1], 2);

	return S_OK;
}
void UninitMapChip() {
	if (g_MapChipTexture != NULL) {
		g_MapChipTexture->Release();
		g_MapChipTexture = NULL;
	}
}
void UpdateMapChip() {

}
void DrawMapChip() {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (g_PieceMapChip[p].UseFlag) {
			//SetWorldViewProjection2D();

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PieceMapChip[p].TexNo));

			SpriteDrawColorRotation(
				g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y,0.0f,
				g_PieceMapChip[p].size.x, g_PieceMapChip[p].size.y, g_PieceMapChip[p].direction * 90, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
				1, 0.5f, 1.0f, 2
			);
		}
	}
}
void SetMapChip(D3DXVECTOR2 pos, int no, int Pin) {
	//p=ブロック最大数
		//i=y方向
	for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
		//j=x方向
		for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
			// 中心座標変数
			//D3DXVECTOR2 position = D3DXVECTOR2((pos.x - PUZZLE_SIZE / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - PUZZLE_SIZE / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2);
			D3DXVECTOR2 position = D3DXVECTOR2((pos.x + PUZZLE_SIZE / 2) - j * BLOCK_CHIP_SIZE - BLOCK_CHIP_SIZE / 2, (pos.y - PUZZLE_SIZE / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2);
			D3DXVECTOR2 DrawSize = D3DXVECTOR2(BLOCK_DRAW_SIZE, BLOCK_DRAW_SIZE);

			switch (g_PieceMapChip[no].chip[g_PieceMapChip[Pin].direction][i][j]) {
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLANK) :	//0				
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PUSH) :	//1
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_BUMP,Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PULL) :	//2
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_DIP,Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_NONE) :	//3
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLOCK) :	//4
				SetBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_CHIP) :	//5
				SetChipPuzzuleChip(position, DrawSize, no + 1);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_WARP) :	//6
				SetWarp(position, DrawSize);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_GOAL) :	//7
				SetGoal(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_JUMP) :	//8
				SetJumpStand(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SPIKE) :	//9
				SetThornBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_FALL) :	//10
				SetFallBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_KEY):	//11
				SetKey(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_DOOR):	//12
				SetOpenKey(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCH):	//13
				SetSwitch(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL3):	//14
				SetSwitchWall(position, DrawSize, no, 3);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL4):	//15
				SetSwitchWall(position, DrawSize, no, 4);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SHEET):	//16
				SetSheerFloors(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BROKEN):	//17
				SetBroken(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_HIGHBROKEN):	//18
				SetHigh(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_MIRROR):	//19
				//Set
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SPWANPOINT)://20
				SetSpawnPoint(position,DrawSize,no);
					break;
			default:
				break;
			}
		}
	}
}
void FileLoad(int StageNo) {
	const char* filename;
	switch (StageNo)
	{
	case 0:
		filename = "data/MapData/map0.txt";
		break;
	case 1:
		filename = "data/MapData/map.txt"; 
		break;
	case 2:
		filename = "data/MapData/Stage01.txt";
		break;
	case 3:
		filename = "data/MapData/Stage02.txt";
		break;
	case 4:
		filename = "data/MapData/Stage03.txt";
		break;
	case 5:
		filename = "data/MapData/Stage04.txt";
		break;
	case 6:
		filename = "data/MapData/Stage05.txt";
		break;
	case 7:
		filename = "data/MapData/Stage06.txt";
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
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				//j = y
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					g_PieceMapChip[p].chip[d + 1][j][BLOCK_CHIP_ARRAY - 1 - i] =
						g_PieceMapChip[p].chip[d][i][j];
				}
			}
		}
	}
}
//==================================================
// ピース回転（右）
//==================================================
void RotateMapChipR(int PieceNo) {
	// 方向の変数に +1
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_PieceMapChip[i].no == PieceNo)
		{
			g_PieceMapChip[i].direction++;
			// 0〜3の範囲から出ないようにする
			if (g_PieceMapChip[i].direction >= 4) {
				g_PieceMapChip[i].direction = 0;
			}

			// 各種デリート
			//deleteBlock(PieceNo);
			//DeleteJoint(PieceNo);
			DeleteMapChip(i);

			// ピース再構成
			SetPieceMapChip(g_PieceMapChip[i].pos, PieceNo);
			break;
		}
	}
}
//==================================================
// ピース回転（左）
//==================================================
void RotateMapChipL(int PieceNo) {
	// 方向の変数に -1
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_PieceMapChip[i].no == PieceNo)
		{

			g_PieceMapChip[i].direction--;
			// 0〜3の範囲から出ないようにする
			if (g_PieceMapChip[i].direction <= -1) {
				g_PieceMapChip[i].direction = 3;
			}

			// 各種デリート
			//deleteBlock(PieceNo);
			//DeleteJoint(PieceNo);
			DeleteMapChip(i);

			// ピース再構成
			SetPieceMapChip(g_PieceMapChip[i].pos, PieceNo);
			break;
		}
	}
}
//==================================================
//ピースの回転やインベントリから取り出すときに使うピースを消す関数
//==================================================
void DeleteMapChip(int PieceNo) {


	if (g_PieceMapChip[PieceNo].UseFlag) {
		g_PieceMapChip[PieceNo].UseFlag = false;
	}
	deleteBlock(g_PieceMapChip[PieceNo].no);
	DeleteJoint(g_PieceMapChip[PieceNo].no);
	DeleteJumpStand(g_PieceMapChip[PieceNo].no);
	DeleteChipPiece(g_PieceMapChip[PieceNo].no);
	DeleteThornBlock(g_PieceMapChip[PieceNo].no);
	DeleteSwitch(g_PieceMapChip[PieceNo].no);
	DeleteSwitchWall(g_PieceMapChip[PieceNo].no);
	DeleteKey(g_PieceMapChip[PieceNo].no);
	DeleteOpenKey(g_PieceMapChip[PieceNo].no);
	DeleteBroken(g_PieceMapChip[PieceNo].no);
	DeleteHigh(g_PieceMapChip[PieceNo].no);
	DeleteSheet(g_PieceMapChip[PieceNo].no);
	DeleteGoal(g_PieceMapChip[PieceNo].no);
	DeleteSpawnPoint(g_PieceMapChip[PieceNo].no);
	//Delete
}
Piece* GetPiece() {
	return g_PieceMapChip;
}
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo) {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (!g_PieceMapChip[p].UseFlag) {
			g_PieceMapChip[p].pos = pos;
			g_PieceMapChip[p].no = PieceNo;
			SetMapChip(pos, PieceNo, p);

			g_PieceMapChip[p].UseFlag = true;
			break;
		}
	}
}

