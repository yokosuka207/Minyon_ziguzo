//--------------------------------------
//パズルのチップ[puzzlecip.h]
//制作更新日10/21
//製作者：新保翔麻
//--------------------------------------
#pragma once

#ifndef PUZZLE_CIP_H_
#define PUZZLE_CIP_H_

#include"main.h"

#define CIP_MAX	(20)
#define	CIP_SIZE_X	(20)
#define	CIP_SIZE_Y	(20)

typedef enum
{
	CIP_NOMAL =0,	//普通のパズルチップ
	CIP_GOAL,		//ゴールチップ
	CIP_NONE		//何もない
}CIP_TYPE;

typedef enum
{
	CREATE_GRAND = 0,
	CREATE_HARFGRAND,
	CREATE_CENTER,
	CREATE_T,
	CREATE_SQUARE,
	CREATE_ZYUUZI,
	CREATE_TATE,
	CREATE_BOX,
	CREATE_COVER,
	CREATE_GOAL,
	CREATE_NUM


}CREATE_CIP_TYPE;


typedef struct
{
	D3DXVECTOR2	Position;	//チップの位置
	D3DXVECTOR2	Size;	//大きさ
	D3DXCOLOR		Col;	//色
	float			texno;	//テクスチャインデックス
	float			Rotation;	//角度

	CIP_TYPE	Type;	//チップの種類
	CREATE_CIP_TYPE		Num_type;//今のタイプ
	int houkou[4];	//方向パズル出っ張ているかひっこんでいるか
	//CREATE_CIP_TYPE		Next_Type;//次のチップのタイプ
	bool GoalFlag;	//ゴールのチップか
	bool UseFlag;		//使用フラグ

}PUZZLE_CIP;

HRESULT InitPuzzleCip();
void UninitPuzzleCip();
void UpdatePuzzleCip();
void DrawPuzzleCip();

int SetPuzzleCip(D3DXVECTOR2 pos,D3DXVECTOR2 size,CIP_TYPE type);
PUZZLE_CIP* GetPuzzleCip();


#endif // !PUZZLE_CIP_H_

