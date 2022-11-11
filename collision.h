/*==============================================================================

   �����蔻��Ǘ� [collision.h]
														 Author :�V���Ė�
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
//�v���g�^�C�v�錾
//===============================

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);//�l�p�`���������Ă��邩�������Ă��Ȃ����𔻒肷�邾��
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);//�ۂ��������Ă��邩�������Ă��Ȃ����𔻒肷�邾��


void UpdateCollision();	//�����蔻����s��

void PuzzleCollision();

bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);	//���̕����̃p�Y�����󂢂Ă��邩

bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);	//���̕����̃p�Y�����󂢂Ă��邩

bool fourCollision(PUZZLE puzzle, int index);			//�l�����̃p�Y�����󂢂Ă��邩



#endif // !COLLISION_H_
