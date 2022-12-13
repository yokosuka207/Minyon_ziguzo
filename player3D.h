//-----------------------------
//	player.h[�v���C���[�Ǘ�]
//-----------------------------
#pragma once

#include<d3dx9.h>
#include"renderer.h"
//#include"model.h"

//--------------------
//�}�N����`
//--------------------
#define		ROTAION_SPEED	(2.0f)	//��]���x
#define		MOVE_SPEED		(1.0f)	//�������x



//--------------------
//�\���̐錾
//--------------------
struct PLAYER3D
{
	bool UseFlag;//�g�p���t���O

	//DX11_MODEL Model;	//���f���\����

	//�A�b�v�f�[�g�ōX�V������
	D3DXVECTOR3	Position;	//�\�����W
	D3DXVECTOR3 Rotation;	//��]�p�x
	D3DXVECTOR3 Scaling;	//�傫��

	D3DXVECTOR3 MoveSpeed;	//�ړ�����X�s�[�h
		
	//�\������Ƃ��ɍ쐬�������
	D3DXMATRIX	WorldMatrix;//�\���p�ŏI�s��
	D3DXMATRIX	RotationMatrix;//��]�s��
	D3DXMATRIX	TranslationMatrix;//���s�ړ��s��
	D3DXMATRIX	ScalingMatrix;//�傫���s��

	//�����o�ϐ��̃A�N�Z�X
	void SetPosition(D3DXVECTOR3 vec) { Position = vec; };
	void SetRotation(D3DXVECTOR3 rot) { Rotation = rot; };
	void SetScaling(D3DXVECTOR3 scl) { Scaling = scl; };
	void SetMoveSpeed(D3DXVECTOR3 spd) { MoveSpeed = spd; };


	D3DXVECTOR3 GetPosition() { return Position; };
	D3DXVECTOR3 GetRotation() { return Rotation; };
	D3DXVECTOR3 GetScaling() { return Scaling; };
	D3DXVECTOR3 GetMoveSpeed() { return MoveSpeed; };

	//��{�֐�
	void Init();	//������
	void Uninit();	//�I������
	void Update();	//�X�V����
	void Draw();	//�\��

	void SetUse(bool use) { UseFlag = use; };
	bool GetUseFlag() { return UseFlag; };//�g�p�����ǂ���
};


//--------------------
//�v���g�^�C�v�錾
//--------------------

