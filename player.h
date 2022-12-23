//=============================================================================
//
//�v���C���[����
//
//�����/��t���l�@�����/2022/06/27
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//=============================================================================
//�}�N����`
//=============================================================================

#define PLAYER_SIZE_W (25)
#define PLAYER_SIZE_H (30)

#define PLAYER_COOLTIME	(120)

#define PLAYER_HP (3)

enum class PLAYER_DIRECTION
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT
};

struct PLAYER
{
	bool UseFlag;//�\���̗��p���t���O
	bool jump;//�W�����v��
	//bool getjump;//�W�����v�̊J�n
	bool fall;//������
	bool getfall = false;//�����̊J�n
	bool WarpFlag = false;//���[�v������
	bool GetJumpStand;
	bool isGround;	// �n�ɑ������Ă���
	bool isSheerFloors;
	bool isSheerFloorsUse;
	bool isHigh;
	bool isMoveBlock;
	int	HaveKey; //��������
	int GHaveKey;
	//int Hp;

	D3DXVECTOR2 size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 oldpos;//1�t���[���O�̍��W
	D3DXVECTOR2 OneOldpos;//1�t���[���O�̍��W

	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������
	int hp;
	int frame;
	int CoolTime;//�N�[���^�C��
	PLAYER_DIRECTION dir;			// �v���C���[�̌���
	int PieceIndex;	//�����ł���s�[�X�̔ԍ�

};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER* GetPlayer();//PLAYER�\���̂̐擪�|�C���^���擾
