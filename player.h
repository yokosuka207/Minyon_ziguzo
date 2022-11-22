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

#define PLAYER_SIZE_W (30)
#define PLAYER_SIZE_H (30)

#define PLAYER_COOLTIME	(120)


struct PLAYER
{
	bool UseFlag;//�\���̗��p���t���O
	bool jump;//�W�����v��
	bool getjump;//�W�����v�̊J�n
	bool fall;//������
	bool getfall;//�����̊J�n
	bool WarpFlag;//���[�v������
	bool GetJumpStand;
	D3DXVECTOR2 size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 oldpos;//1�t���[���O�̍��W
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

};

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();
PLAYER* GetPlayer();//PLAYER�\���̂̐擪�|�C���^���擾