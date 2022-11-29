//------------------------------------------
//ゴール管理[goal.h]
//制作更新日10/21
//製作者：新保翔麻
//------------------------------------------

#pragma once
#ifndef GOAL_H_
#define GOAL_H_

#include"main.h"

#define	GOAL_MAX	10

#define GOAL_SIEZX	20
#define GOAL_SIZEY	20
typedef struct
{
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	D3DXCOLOR		Col;	//色
	float			texno;	//テクスチャインデックス
	float			Rotation;	//角度

	int pieceIndex;	//ピースの添え字格納

	bool UseFlag;

}GOAL;


HRESULT InitGoal();
void UninitGoal();
void UpdateGoal();
void DrawGoal();

void SetGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index);
void DeleteGoal(int index);
GOAL* GetGoal();

#endif // !GOAL_H_


