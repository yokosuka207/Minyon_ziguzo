//=============================================================================
//
//�������J���錮
//
//�����/�e�n ��@
//=============================================================================
#include "Key.h"
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

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static KEY g_Key;
static ID3D11ShaderResourceView	*g_textureKey;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameKey = (char*)"data\\texture\\key-1.png";



HRESULT InitKey()
{
	g_Key.Size = D3DXVECTOR2(KEY_W, KEY_H);
	g_Key.Position = D3DXVECTOR2(200, 200);
	g_Key.texno = LoadTexture(g_TextureNameKey);
	g_Key.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Key.GetKey = true;
	//g_Key.OpenKey = false;
	return S_OK;
}

void UninitKey()
{
}

void UpdateKey()
{
	
}

void DrawKey()
{
	if (g_Key.GetKey)
	{
		SetWorldViewProjection2D();

		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Key.texno));
		//�X�v���C�g��\��
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Key.Position.x, g_Key.Position.y, g_Key.Size.x, g_Key.Size.y,
			g_Key.rot, g_Key.col, 0, 1.0f, 1.0f, 1);

	}
}

void SetKey(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	if(!g_Key.GetKey)
	{

		g_Key.Position = pos;
		g_Key.Size = size;
		g_Key.GetKey = false;
	

	}
}

KEY *GetKey()
{
	return &g_Key;
}
