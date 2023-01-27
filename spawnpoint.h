//--------------------
//spawnpoint.h
// 製作者：新保翔麻
//--------------------
#pragma once
#ifndef SPAWN_POINT_H_
#define SPAWN_POINT_H_



#include"main.h"

#define SPAWN_POINT_MAX	16


typedef struct
{
	D3DXVECTOR2		Position;	//ポジション
	D3DXVECTOR2		Size;	//サイズ

	int				PieceIndex; //ピースの添え字格納

	bool			UseFlag;	//使用フラグ

}SpawnPoint;

void InitSpawnPoint();
void UninitSpawnPoint();

void SetSpawnPoint(D3DXVECTOR2 p, D3DXVECTOR2 s,int index);

void DeleteSpawnPoint(int index);

SpawnPoint* GetSpawnPoint();

#endif // !SPAWN_POINT_H_
