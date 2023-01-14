//=============================================================================
//
//	�X�e�[�W�Z���N�g�w�b�_�[[StageSelect.h]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

#include "main.h"
#include "renderer.h"

#define STAGE_MAX (27)
//#define STAGE_MAX (8)

#define SELECT_MAX (2)//2��

enum class STAGE_SELECT_TYPE
{
	TYPE_NG,
	TYPE_OK

};


typedef struct
{
	D3DXVECTOR2		pos;		// �\�����W
	D3DXVECTOR2		size;		// �\���T�C�Y
	D3DXCOLOR		color;		// �J���[
	float			texno;		// �e�N�X�`���C���f�b�N�X�ԍ�
}STAGESELECT_BG;
typedef struct
{
	D3DXVECTOR2		pos;		// �\�����W
	D3DXVECTOR2		size;		// �\���T�C�Y
	D3DXCOLOR		color;		// �J���[
	float			texno;		// �e�N�X�`���C���f�b�N�X�ԍ�

}STAGESELECT_STAIRS;

typedef struct
{
	D3DXVECTOR2		pos;		// �\�����W
	D3DXVECTOR2		size;		// �\���T�C�Y
	D3DXCOLOR		color;		// �J���[
	float			texno;		// �e�N�X�`���C���f�b�N�X�ԍ�

}STAGESELECT_BLOCK;



typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float		texno;
	int			StagePieceIndex;//�X�e�[�W�s�[�X�����ԖڂȂ̂�
	bool		StageUseFlag;	//�X�e�[�W�ɓ���邩�ǂ���
	STAGE_SELECT_TYPE type;//�X�e�[�W�ɓ���邩�ǂ���
	bool		UseFlag;		//�X�e�[�W�s�[�X(������)
}STAGESELECT;

HRESULT InitStageSelect();
void UninitStageSelect();
void UpdateStageSelect();
void DrawStageSelect();
void SetStageSelect(int a);
STAGESELECT* GetSelect();

int ReturnStageNo();


#endif // !_STAGESELECT_H_

