//=============================================================================
//
//	�X�e�[�W�Z���N�g�w�b�_�[[StageSelect.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGE_SELECT_H_

#include "main.h"
#include "renderer.h"

//#define STAGE_MAX (28)
#define STAGE_MAX (8)

#define SELECT_MAX (2)//2��

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float		texno;
	int			StagePieceIndex;//�X�e�[�W�s�[�X�����ԖڂȂ̂�
	bool		StageUseFlag;	//�X�e�[�W�ɓ���邩�ǂ���

	bool		UseFlag;		//�X�e�[�W�s�[�X(������)
}STAGESELECT;

HRESULT InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();
void SetStageSelect();
STAGESELECT* GetSelect();
#endif // !_STAGESELECT_H_

