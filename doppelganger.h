//=============================================================================
//
//�h�b�y���Q���K�[����(���v���C���[)
//
//�����/�e�n��@�����/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "goal_key.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define DOPPELGANGER_NUM (1)
#define DOPPELGANGER_SIZE_W (10)
#define DOPPELGANGER_SIZE_H (30)

#define DOPPELGANGER_COOLTIME	(120)

#define DOPPELGANGER_HP (5)
#define DOPPELGANGER_UV_W (1.0f / 4)
#define DOPPELGANGER_UV_H (1.0f / 4)

enum class DOPPELGANGER_DIRECTION
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

struct DOPPELGANGER
{
	
	bool UseFlag;//�\���̗��p���t���O
	//bool GetKey;

	bool jump;//�W�����v��
	//bool getjump;//�W�����v�̊J�n
	bool fall;//������
	bool getfall = false;//�����̊J�n
	
	//bool GetJumpStand;
	bool isGround;	// �n�ɑ������Ă���
	bool isSheerFloors;
	bool isSheerFloorsUse;
	bool isMoveBlock;
	bool isHigh;
	bool WarpFlag;

	D3DXVECTOR2 size;//BOX�T�C�Y
	D3DXVECTOR2 Drawsize;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 oldpos;//1�t���[���O�̍��W
	//D3DXVECTOR2 OneOldpos;//1�t���[���O�̍��W

	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������
	//int hp;
	int frame;
	int CoolTime;//�N�[���^�C��
	DOPPELGANGER_DIRECTION dir;			// ���v���C���[�̌���
	int PieceIndex;	//�����ł���s�[�X�̔ԍ�

};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitDoppelganger();
void UninitDoppelganger();
void UpdateDoppelganger();
void DrawDoppelganger();
DOPPELGANGER* GetDoppelganger();//DOPPELGANGER�\���̂̐擪�|�C���^���擾

void SetDoppelGanger(D3DXVECTOR2 position, D3DXVECTOR2 size, int index);
void DeleteDoppelGanger(int index);