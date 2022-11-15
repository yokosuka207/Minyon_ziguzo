/*==============================================================================

   当たり判定管理 [collision.h]
														 Author :新保翔麻
														 Date   :10/21
--------------------------------------------------------------------------------*/

#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_
#include"puzzle.h"

typedef enum
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	NUM

}DIRECSION;


//===============================
//プロトタイプ宣言
//===============================

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);//四角形が当たっているかあたっていないかを判定するだけ
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);//丸が当たっているかあたっていないかを判定するだけ


void UpdateCollision();	//当たり判定を行う

void PuzzleCollision();

bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);	//その方向のパズルが空いているか

bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);	//その方向のパズルが空いているか

bool fourCollision(PUZZLE puzzle, int index);			//四方向のパズルが空いているか



#endif // !COLLISION_H_
