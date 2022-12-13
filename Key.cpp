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
static KEY g_Key[KEY_MAX];
static ID3D11ShaderResourceView	*g_textureKey;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameKey = (char*)"data\\texture\\key-1.png";



HRESULT InitKey()
{
	for (int i = 0; i < KEY_MAX; i++) {
		g_Key[i].Size = D3DXVECTOR2(KEY_W, KEY_H);
		g_Key[i].Position = D3DXVECTOR2(200, 200);
		g_Key[i].texno = LoadTexture(g_TextureNameKey);
		g_Key[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Key[i].GetKey = false;
		//g_Key.OpenKey = false;
		return S_OK;
	}

}

void UninitKey()
{
	for (int i = 0; i < KEY_MAX; i++)
	{

	}
}

void UpdateKey()
{
	
}

void DrawKey()
{
	for (int i = 0; i < KEY_MAX; i++){
		if (g_Key[i].GetKey)
		{
			//SetWorldViewProjection2D();

			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Key[i].texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_Key[i].Position.x, g_Key[i].Position.y,-0.1f, g_Key[i].Size.x, g_Key[i].Size.y,
				g_Key[i].rot, g_Key[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
	
}

void SetKey(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{

	for (int i = 0; i < KEY_MAX; i++) {
		if (!g_Key[i].GetKey)
		{
			g_Key[i].Position = pos;
			g_Key[i].Size = size;
			g_Key[i].GetKey = true;
		}
	}
	
}

void DeleteKey(int PieceNo) {
	for (int i = 0; i < KEY_MAX; i++) {
		if (g_Key[i].GetKey) {
			g_Key[i].GetKey = false;
		}
	}
}

KEY *GetKey()
{
	return g_Key;
}
