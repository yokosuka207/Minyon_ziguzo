#pragma once
//====================
//�}�N����`
//=====================
typedef enum
{
	WIN =0,
	LOSE,
}RESULT_TYPE;


typedef	struct
{
	D3DXVECTOR3		Position;	//�\�����W
	D3DXVECTOR2		Size;		//�T�C�Y
	D3DXCOLOR		Color;		//�F
	float			Rotate;		//�p�x
	RESULT_TYPE type;
}RESULT;

//======================
//�v���g�^�C�v�錾
//======================
void	InitResult();
void	UninitResult();
void	UpdateResult();
void	DrawResult();
void SetResultType(RESULT_TYPE ty);
RESULT* GetResult();