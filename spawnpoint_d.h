//--------------------
//spawnpoint_d.h
// 製作者：稲葉陸斗
//--------------------
#pragma once
#ifndef SPAWN_POINT_D_H_
#define SPAWN_POINT_D_H_



#include"main.h"

#define SPAWN_POINT_D_MAX	16


typedef struct
{
	D3DXVECTOR2		Position;	//ポジション
	D3DXVECTOR2		Size;	//サイズ

	int				PieceIndex; //ピースの添え字格納

	bool			UseFlag;	//使用フラグ

}SpawnPointD;

void InitSpawnPointD();
void UninitSpawnPointD();
void UpdateSpawnPointD();


void SetSpawnPointD(D3DXVECTOR2 p, D3DXVECTOR2 s,int index);

void DeleteSpawnPointD(int index);

SpawnPointD* GetSpawnPointD();

#endif // !SPAWN_POINT_D_H_
