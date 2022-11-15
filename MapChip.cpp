/*==============================================================================

   �}�b�v�`�b�v�Ǘ� [MapChip.cpp]
														 Author : ���؁@��
														 Date   : 2022/11/01
--------------------------------------------------------------------------------
 Update: 
 22/11/01 fusegi
 22/11/02 fusegi
 22/11/04 fusegi
==============================================================================*/

#include "MapChip.h"
#include "puzzle.h"
#include "puzzlecip.h"
#include "block.h"
#include "puzzlecip.h"
#include "warp.h"
#include "goal.h"

//**************************************************
//�@�}�N����`
//**************************************************

//**************************************************
// �\���̒�`
//**************************************************
Piece g_PieceMapChip[PUZZLE_MAX];
//**************************************************
// �v���g�^�C�v�錾
//**************************************************

//**************************************************
// �O���[�o���ϐ�:
//**************************************************

void SetMapChip(D3DXVECTOR2 pos, int no) {
	//p=�u���b�N�ő吔
		//i=y����
	for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
		//j=x����
		for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
			switch (g_PieceMapChip[no].chip[g_PieceMapChip[no].direction][i][j]) {
			case static_cast <int> (MAPCHIP_TYPE::TYPE_NONE) :	//0
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLOCK) :	//1
				SetBlock(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE),no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_CHIP) :	//2
				SetChipPuzzuleChip(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE));
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_WARP) :	//3
				SetWarp(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE));
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_GOAL) :	//4
				SetGoal(D3DXVECTOR2((pos.x - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - BLOCK_CHIP_SIZE * BLOCK_CHIP_ARRAY / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2), D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE));
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLANK) :	//5				
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PUSH) :	//6

				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PULL) :	//7

				break;
			default:
				break;
			}
		}
	}
	g_PieceMapChip[no].UseFlag = true;
}

void FileLoad(int StageNo) {
	const char* filename;
	switch (StageNo)
	{
	case 0:
		filename = "MapData/map0.txt";
		break;
	case 1:
		filename = "MapData/map1.txt";
		break;
	}
	FILE* fp;
	//�I�[�v��
	fp = fopen(filename, "r");
	if (!fp) {
		exit(999);
	}
	//��X�e�[�W���ǂݍ���
	for (int p = 0; p < PUZZLE_MAX; p++) {
		for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
			for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
				fscanf(fp, "%d", &g_PieceMapChip[p].chip[0][i][j]);
			}
		}
	}
	//�N���[�Y
	fclose(fp);
}
void RotateChipData() {
	//�X�e�[�Wp
	for (int p = 0; p < PUZZLE_MAX; p++) {
		//����d
		for (int d = 0; d < BLOCK_CHIP_DIRECTION - 1; d++) {
			//i = x
			for (int i = 0; i < BLOCK_CHIP_SIZE; i++) {
				//j = y
				for (int j = 0; j < BLOCK_CHIP_SIZE; j++) {
					g_PieceMapChip[p].chip[d + 1][j][BLOCK_CHIP_SIZE - 1 - i] =
						g_PieceMapChip[p].chip[d][i][j];
				}
			}
		}
	}
}
Piece* GetPiece() {
	return g_PieceMapChip;
}
