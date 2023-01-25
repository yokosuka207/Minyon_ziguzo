//------------------------------------------
//�S�[���Ǘ�[goal.h]
//����X�V��10/21
//����ҁF�V���Ė�
//------------------------------------------

#pragma once
#ifndef GOAL_H_
#define GOAL_H_

#include"main.h"

#define	GOAL_MAX	10

#define GOAL_SIEZX	20
#define GOAL_SIZEY	20
#define GOAL_UV_W 1.0f / 4
#define GOAL_UV_H 1.0f / 4
typedef struct
{
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	D3DXCOLOR		Col;	//�F
	float			texno;	//�e�N�X�`���C���f�b�N�X
	float			Rotation;	//�p�x
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

	int pieceIndex;	//�s�[�X�̓Y�����i�[

	bool UseFlag;
	bool GetFlag;

}GOAL;


HRESULT InitGoal();
void UninitGoal();
void UpdateGoal();
void DrawGoal();

void SetGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index);
void DeleteGoal(int index);
GOAL* GetGoal();

#endif // !GOAL_H_


