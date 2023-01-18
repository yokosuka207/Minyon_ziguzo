/*================================================================================
	
	�C���x���g���w�b�_�[[Inventory.h]
 		
												Author: ꎓ� ��o
												 Date : 2022/11/02
----------------------------------------------------------------------------------
Update:
	2022/11/01 Saito
	2022/11/02 Saito
	2022/11/04 Saito
	2022/11/16 Saito
================================================================================*/
#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "main.h"

//**************************************************
// �}�N����`
//**************************************************
#define INVENTORYBG_SIZE_X		(100)
#define INVENTORYBG_SIZE_Y		(SCREEN_HEIGHT)
#define INVENTORYBG_POS_X_REVESE		((SCREEN_WIDTH/2) +INVENTORYBG_SIZE_X / 2)
#define INVENTORYBG_POS_Y		(SCREEN_HEIGHT / 2)
#define INVENTORYBG_POS_X		(INVENTORYBG_SIZE_X / 2)


//**************************************************
// �\����
//**************************************************
typedef struct
{
	D3DXVECTOR2		pos;		// �\�����W
	D3DXVECTOR2		size;		// �\���T�C�Y
	D3DXCOLOR		color;		// �J���[
	float			texno;		// �e�N�X�`���C���f�b�N�X�ԍ�
}KEEP_PUZZLE_BG;

typedef struct
{
	int				PieNo;		// �s�[�X�ԍ�

	D3DXVECTOR2		pos;		// �\�����W
	D3DXVECTOR2		scpos;		// �\�����W
	D3DXVECTOR2		size;		// �\���T�C�Y
	D3DXCOLOR		color;		// �J���[
	float			texno;		// �e�N�X�`���C���f�b�N�X�ԍ�

	bool			IsIn;		// ���̃|�P�b�g�̒��ɂ��邩
	bool			IsCatch;	// �}�E�X�ɂ��܂�Ă��邩
	bool			IsUse;		// �g���Ă��邩
}KEEP_PUZZLE;


//**************************************************
// �v���g�^�C�v�錾
//**************************************************
HRESULT InitInventory();
void UninitInventory();
void UpdateInventory();
void DrawInventory();

void SetInventory(int PieNo);
KEEP_PUZZLE* GetInventory();
void DeleteInventory(int PieNo);
void DeleteInventoryMapCip(int PieNo);


#endif // !_INVENTORY_H_
