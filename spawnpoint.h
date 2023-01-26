//--------------------
//spawnpoint.h
// ����ҁF�V���Ė�
//--------------------
#pragma once
#ifndef SPAWN_POINT_H_
#define SPAWN_POINT_H_



#include"main.h"

#define SPAWN_POINT_MAX	16


typedef struct
{
	D3DXVECTOR2		Position;	//�|�W�V����
	D3DXVECTOR2		Size;	//�T�C�Y

	int				PieceIndex; //�s�[�X�̓Y�����i�[

	bool			UseFlag;	//�g�p�t���O

}SpawnPoint;

void InitSpawnPoint();
void UninitSpawnPoint();

void SetSpawnPoint(D3DXVECTOR2 p, D3DXVECTOR2 s,int index);

void DeleteSpawnPoint(int index);

SpawnPoint* GetSpawnPoint();

#endif // !SPAWN_POINT_H_
