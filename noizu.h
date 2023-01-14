#pragma once
#include "main.h"
#include "renderer.h"

#define NOIZU_UV_W (1.0f / 2)
#define NOIZU_UV_H (1.0f / 2)


typedef struct
{
	//���̎l������Ύ�芸�����\���ł���
	D3DXVECTOR2		Position;	//�\�����W
	D3DXCOLOR		Color;		//�\���F
	float			Rotation;	//�p�x
	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
		//float w, h;	//�{�b�N�X�T�C�Y
	float texno;	//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

	bool UseFlag;	//�g�p�t���O

}NOIZU;

HRESULT InitNoizu();
void UninitNoizu();
void UpdateNoizu();
void DrawNoizu();

