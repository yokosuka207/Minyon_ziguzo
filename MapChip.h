/*==============================================================================

   マップチップヘッダー [MapChip.h]
														 Author : 伏木　伶
														 Date   : 2022/11/01
--------------------------------------------------------------------------------
 Update: 
 22/11/01 fusegi
 22/11/02 fusegi
 22/11/04 fusegi
==============================================================================*/

#ifndef _MAPCHIP_H_
#define _MAPCHIP_H_

#include "main.h"
#include "renderer.h"

//**************************************************
//　マクロ定義
//**************************************************
#define BLOCK_CHIP_ARRAY (16)	// 配列の最小単位
#define BLOCK_CHIP_SIZE (15.0f)	//マップチップブロックのサイズ
#define BLOCK_DRAW_SIZE (15.0f)	//マップチップブロックの表示サイズ
#define BLOCK_CHIP_MAX (12 * 12 * 10)//マップチップの中のブロック最大数
#define BLOCK_CHIP_WARP_MAX (2)	//1ステージワープの個数
#define BLOCK_CHIP_DIRECTION (4)//チップの回転4方向分

#define PUZZLE_SIZE (BLOCK_CHIP_ARRAY * BLOCK_CHIP_SIZE)	//16 * 15 (180 + 60) 
#define PIECE_SIZE (180)
//**************************************************
// 構造体定義
//**************************************************
enum class MAPCHIP_TYPE{
	TYPE_BLANK = 0,	// 0	外側の空白
	TYPE_PUSH,		// 1	凸
	TYPE_PULL,		// 2	凹
	TYPE_NONE,		// 3
	TYPE_BLOCK,		// 4
	TYPE_CHIP,		// 5
	TYPE_WARP,		// 6
	TYPE_GOAL,		// 7
	TYPE_JUMP,		// 8
	TYPE_SPIKE,		// 9

	TYPE_NUM,		
};

typedef struct {
	int			no;		//現在のピース番号
	D3DXVECTOR2 pos;	//パズルの座標
	D3DXVECTOR2 OldPos;	//移動用oldpos
	D3DXVECTOR2 OldMovePos;//動く前の座標
	D3DXVECTOR2 size;	//パズルのサイズ
	int			chip[BLOCK_CHIP_DIRECTION][BLOCK_CHIP_ARRAY][BLOCK_CHIP_ARRAY];	//パズルの中のブロックの個数
	float		TexNo;
	int			direction;	//パズルの方向
	bool		MoveEndFlag;//動き終わった瞬間
	bool		UseFlag;//パズルが出現しているか否か

}Piece;

//**************************************************
// プロトタイプ宣言
//**************************************************

//**************************************************
// グローバル変数:
//**************************************************

HRESULT InitMapChip();
void UninitMapChip();
void UpdateMapChip();
void DrawMapChip();

//-----enum別にセット-----
void SetMapChip(D3DXVECTOR2 pos, int no);
//-----ファイル一括管理-----
void FileLoad(int StageNo);

//-----ピースの回転------
void RotateChipData();
void RotateMapChipR(int PieceNo);
void RotateMapChipL(int PieceNo);

Piece* GetPiece();
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo);

#endif // !_MAPCHIP_H_
