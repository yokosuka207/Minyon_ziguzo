//=============================================================================
//
//���ŊJ������
//
//�����/�e�n ��@
//=============================================================================
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define OPEN_KEY_W (500)
#define OPEN_KEY_H (700)


typedef struct {
	bool UseFlag;//�\���̗��p���t���O
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR col;//�F
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������
}OPENKEY;

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitOpenKey();
void UninitOpenKey();
void UpdateOpenKey();
void DrawOpenKey();
OPENKEY *OpenKey();
void SetOpenKey(D3DXVECTOR2 size, D3DXVECTOR2 pos);


//=============================================================================
//�O���[�o���ϐ�
//=============================================================================