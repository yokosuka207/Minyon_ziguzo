//--------------------
//spawnpoint_d.h
// ����ҁF��t���l
//--------------------
#pragma once
#ifndef SPAWN_POINT_D_H_
#define SPAWN_POINT_D_H_



#include"main.h"

#define SPAWN_POINT_D_MAX	16


typedef struct
{
	D3DXVECTOR2		Position;	//�|�W�V����
	D3DXVECTOR2		Size;	//�T�C�Y

	int				PieceIndex; //�s�[�X�̓Y�����i�[

	bool			UseFlag;	//�g�p�t���O

}SpawnPointD;

void InitSpawnPointD();
void UninitSpawnPointD();
void UpdateSpawnPointD();


void SetSpawnPointD(D3DXVECTOR2 p, D3DXVECTOR2 s,int index);

void DeleteSpawnPointD(int index);

SpawnPointD* GetSpawnPointD();

#endif // !SPAWN_POINT_D_H_
