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
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define OPEN_KEY_MAX (9)


typedef struct {
	bool		UseFlag;//�\���̗��p���t���O
	bool		KeyOpen;
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXVECTOR2 sp;
	float		rot;//��]�p�x
	float		texno;//�e�N�X�`���C���f�b�N�X
	D3DXCOLOR	col;//�F
	int			index;
	float		PaternNo;//�p�^�[���ԍ�
	float		uv_w;//���T�C�Y
	float		uv_h;//�c�T�C�Y
	int			NumPatern;//������
}OPENKEY;

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitOpenKey();
void UninitOpenKey();
void UpdateOpenKey();
void DrawOpenKey();
OPENKEY *GetOpenKey();
void SetOpenKey(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int index);
void DeleteOpenKey(int PieceNo);


//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
