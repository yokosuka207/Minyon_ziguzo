//=============================================================================
//�S�[���p��
//
//�����/���Ԍ��C�@
//=============================================================================

#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"

//==============================================================
//�}�N����`
//==============================================================
#define GKEY_W		(15)
#define GKEY_H		(15)
#define GKEY_MAX	(1)

typedef struct
{
	bool UseFlag;
	bool GetGKey;
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXCOLOR	col;
	float rot;
	float texno;
	float PaternNo;
	float uv_w;
	float uv_h;
	int NumPatern;
}GKEY;

//==============================================================
//�v���g�^�C�v�錾
//==============================================================

HRESULT InitGKey();
void UninitGKey();
void UpdateGKey();
void DrawGKey();

void SetGKey(D3DXVECTOR2 pos, D3DXVECTOR2 size);
void DeleteGKey(int PieceNo);

GKEY* GetGKey();
