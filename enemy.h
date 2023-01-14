//=============================================================================
//
//	エネミーヘッダー[enemy.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define ENEMY_MAX (1)
#define ENEMY_SIZE_W (10)
#define ENEMY_SIZE_H (30)

enum class ENEMY_DIRECTION {
	DIRECTION_LEFT = 0,
	DIRECTION_RIGHT,

	DIRECTION_MAX,
};

typedef struct {
	D3DXVECTOR2		pos;
	D3DXVECTOR2		size;
	D3DXVECTOR2		sp;
	D3DXCOLOR		color;
	int				index;
	int				texno;
	ENEMY_DIRECTION dir;

	bool			UseFlag;
	bool			AIFlag; //player ト　えねんみ　当たり判定
}ENEMY;

HRESULT InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();
void SetEnemy(D3DXVECTOR2 pos,D3DXVECTOR2 size,int index);
ENEMY* GetEnemy();
void DeleteEnemy(int index);

#endif // !_ENEMY_H_
