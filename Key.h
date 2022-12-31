//=============================================================================
//
//�������J���錮
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
#define KEY_W (5)
#define KEY_H (5)
#define KEY_MAX (1)

typedef struct {

	bool GetKey; //������������ǂ����̔���
	bool OpenKey; //�����J���邩�ǂ����̔���
	D3DXVECTOR2 Size;//BOX�T�C�Y
	D3DXVECTOR2 Position;//�\�����W(���S���W)
	D3DXCOLOR col;//�F
	D3DXVECTOR2 oldpos;
	float rot;//��]�p�x
	float texno;//�e�N�X�`���C���f�b�N�X
	float PaternNo;//�p�^�[���ԍ�
	float uv_w;//���T�C�Y
	float uv_h;//�c�T�C�Y
	int NumPatern;//������

}KEY;
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

HRESULT InitKey();
void UninitKey();
void UpdateKey();
void DrawKey();

void SetKey(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void DeleteKey(int PieceNo);

KEY *GetKey();
