/*==============================================================================

   パズル管理 [puzzle.h]
														 Author :新保翔麻
														 Date   :10/18
--------------------------------------------------------------------------------*/

#pragma once

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include "main.h"
#include "renderer.h"
#include"block.h"
//#include"puzzlecip.h"
#define	PUZZLE_MAX	16

#define PUZZLE_WIDHT	180
#define PUZZLE_HEIGHT	180
#define	NUM_PUZZLE_VERTEX	(64)		//パズル用頂点数

typedef enum
{
	STEAT_NUM = 0,
	STEAT_DEPPARI,
	STEAT_HIKKOMI,
}PUZZLE_STEAT;

typedef enum
{
	TYPE_NOMAL =0,
	TYPE_GOAL,
	TYPE_NONE

}PUZZLE_TYPE;



typedef struct
{
	D3DXVECTOR2		Position;	//ポジション
	D3DXVECTOR2		oldPosition;	//1フレーム前のポジション
	D3DXVECTOR2		OneOldPosition;//ひとつ前のパズルの位置に戻す

	D3DXVECTOR2		Size;	//サイズ
	D3DXCOLOR		Col;	//色
	float			texno;	//テクスチャインデックス
	float			Rotation;	//角度
	float			oldRotation;//1フレーム前の角度

	PUZZLE_STEAT		InitPuzzle_TypeUp;	//最初の上引っ込みタイプ
	PUZZLE_STEAT		InitPuzzle_TypeDown;	//最初の下引っ込みタイプ
	PUZZLE_STEAT		InitPuzzle_TypeLeft;	//最初の左引っ込みタイプ
	PUZZLE_STEAT		InitPuzzle_TypeRight;	//最初の右引っ込みタイプ

	PUZZLE_STEAT		Puzzle_TypeUp;	//上引っ込みタイプ
	PUZZLE_STEAT		Puzzle_TypeDown;	//下引っ込みタイプ
	PUZZLE_STEAT		Puzzle_TypeLeft;	//左引っ込みタイプ
	PUZZLE_STEAT		Puzzle_TypeRight;	//右引っ込みタイプ

	PUZZLE_TYPE			Puzzle_type;	//パズルのピースの種類

	BLOCK_TYPE			Block_Type;	//パズル内のブロックのタイプ

	int				blockIndex[4];	//blockの添え字
	int				CipIndex;	//チップのインデックス
	int				BrokenIndex;//壊れるブロックのインデックス
	int				WarpIndex[2];	//ワープのインデックス
	int				RotNum;	//回転した数
	bool			MoveFlag;	//動いているか
	bool			MoveEndFlag;	//動き終わったか
	bool			UseFlag;	//使用フラグ

}PUZZLE;

HRESULT InitPuzzle();
void UninitPuzzle();
void UpdatePuzzle();
void DrawPuzzle();

PUZZLE* GetPuzzle();
void SetPuzzle(D3DXVECTOR2 pos, D3DXVECTOR2 size, PUZZLE_STEAT PTUp, PUZZLE_STEAT PTDown, PUZZLE_STEAT PTLeft, PUZZLE_STEAT PTRigft,
	GRAND_TYPE gtype,PUZZLE_TYPE ptype,CIP_TYPE cType,BLOCK_TYPE btype,bool Wflag);

void	SpriteDrawColorRotationPuzzle(D3DXVECTOR2, D3DXVECTOR2, float, D3DXCOLOR,
	PUZZLE_STEAT, PUZZLE_STEAT, PUZZLE_STEAT, PUZZLE_STEAT);	//三角形用頂点格納処理
void PuzzleTypeShift(int index);	//90度上下左右のパズルを入れ替える


void PuzzleBlockUpdate(PUZZLE puzzle);//パズルのブロックの更新


#endif // !BLOCK_H_
