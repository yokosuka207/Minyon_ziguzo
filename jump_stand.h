#pragma once

#define JUMPSTAND_SIZE	(20)
#define JUMPSTAND_MAX (1)
typedef struct 
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��
	D3DXVECTOR2 oldpos;	
	D3DXVECTOR2 sp;		//�X�s�[�h

	int			PieceIndex;

	float JumpGravity;	//�d��
	float JumpPower;	//��ԗ�

	bool UseJumpStand;	//�W�����v�X�^���h�t���O
	bool JumpStandFlag;		//�W�����v�X�^���h�̃W�����v���t���O

}JUMPSTAND;

HRESULT InitJumpStand();
void UninitJumpStand();
void UpdateJumpStand();
void DrawJumpStand();
void SetJumpStand(D3DXVECTOR2 p);
void SetJumpStand(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo);
void DeleteJumpStand(int PieceNo);

JUMPSTAND* GetJumpStand();

bool Collition_JumpStand();