#pragma once

#define JUMPSTAND_SIZE	(20)
#define JUMPSTAND_MAX (8)
typedef struct 
{
	D3DXVECTOR2 pos;	//�\�����W
	D3DXVECTOR2 size;	//�傫��
	D3DXVECTOR2 oldpos;
	D3DXVECTOR2 oldoldpos;
	D3DXVECTOR2 sp;		//�X�s�[�h

	float		rot;
	int			PieceIndex;
	int			NowPieceIndex;	//���̃s�[�X�̃C���f�b�N�X

	float JumpGravity;	//�d��
	float JumpPower;	//��ԗ�

	bool UseJumpStand;	//�W�����v�X�^���h�t���O
	bool JumpStandFlag;		//�W�����v�X�^���h�̃W�����v���t���O

	bool GetJumpStand;
	bool JumpStandNotMove;
	bool LookFlag;

	//�h�b�y���Q���K�[ver
	D3DXVECTOR2 spD;
	float JumpPowerD;
	bool JumpStandFlagD;		//�W�����v�X�^���h�̃W�����v���t���O


}JUMPSTAND;

HRESULT InitJumpStand();
void UninitJumpStand();
void UpdateJumpStand();
void DrawJumpStand();
void SetJumpStand(D3DXVECTOR2 p);
void SetJumpStand(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo);
void DeleteJumpStand(int PieceNo);

JUMPSTAND* GetJumpStand();

bool Collition_JumpStand();