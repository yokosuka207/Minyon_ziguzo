#pragma once

#include "SheerFloors.h"
#include "renderer.h"

#define SHEERFLOORS_NUM		70	//�����鏰�̍ő吔
#define SHEERFLOORS_SIZE_X	30	//�w�T�C�Y
#define SHEERFLOORS_SIZE_Y	5	//�x�T�C�Y	

typedef struct
{
	D3DXVECTOR2		pos;
	D3DXVECTOR2		size;
	float			rot;
	int				index;
	bool			use;

}SHEERFLOORS;

HRESULT InitSheerFloors();
void UninitSheerFloors();
void UpdateSheerFloors();
void DrawSheerFloors();

void SetSheerFloors(D3DXVECTOR2 p, D3DXVECTOR2 s,int direction, int index);
SHEERFLOORS* GetSheerFloors();

void DeleteSheet(int PieceNo);