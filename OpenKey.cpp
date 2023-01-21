//=============================================================================
//
//���ŊJ������
//
//�����/�e�n ��@
//=============================================================================
#include "OpenKey.h"
#include "Key.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"


//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static OPENKEY g_OpenKey[OPEN_KEY_MAX];
static ID3D11ShaderResourceView	*g_OpenKeytexture;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_OpenKeyTextureName = (char*)"data\\texture\\���t���h�A.png";
static int g_OpenKeyTextureNo = 0;


HRESULT InitOpenKey()
{
	for (int i = 0; i < OPEN_KEY_MAX; i++)
	{
		g_OpenKey[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_OpenKey[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_OpenKey[i].rot = 0.0f;
		g_OpenKey[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OpenKey[i].index = -1;
		g_OpenKey[i].PaternNo = 0.0f;
		g_OpenKey[i].KeyOpen = false;
		g_OpenKey[i].UseFlag = false;
		
	}
	g_OpenKeyTextureNo = LoadTexture(g_OpenKeyTextureName);
	return S_OK;
}

void UninitOpenKey(){
	if (g_OpenKeytexture != NULL) {
		g_OpenKeytexture->Release();
		g_OpenKeytexture = NULL;
	}
}

void UpdateOpenKey()
{
}

void DrawOpenKey()
{
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_OpenKeyTextureNo));

	//�e�N�X�`���̐ݒ�
	//�X�v���C�g��\��

	for (int i = 0; i < OPEN_KEY_MAX; i++) {

		if (g_OpenKey[i].UseFlag)
		{
			g_OpenKey[i].PaternNo = i;

			SpriteDrawColorRotation(
				g_OpenKey[i].Position.x,
				g_OpenKey[i].Position.y,
				-0.1f,
				g_OpenKey[i].Size.x,
				-g_OpenKey[i].Size.y,
				g_OpenKey[i].rot,
				g_OpenKey[i].col,
				g_OpenKey[i].PaternNo,
				1.0f / 1.0f,
				1.0f / 3.0f,
				1);
		}
	}
	
}


void SetOpenKey(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int index){
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (!g_OpenKey[i].KeyOpen) {
			if (!g_OpenKey[i].UseFlag) {

				switch (direction)
				{
				case 0:
					g_OpenKey[i].Position = D3DXVECTOR2(pos.x, pos.y + i * size.y);
					g_OpenKey[i].rot = (direction + 2) * 90;
					break;
				case 1:
					g_OpenKey[i].Position = D3DXVECTOR2(pos.x + i * size.x, pos.y);
					g_OpenKey[i].rot = direction * 90;
					break;
				case 2:
					g_OpenKey[i].Position = D3DXVECTOR2(pos.x, pos.y - i * size.y);
					g_OpenKey[i].rot = (direction - 2) * 90;
					break;
				case 3:
					g_OpenKey[i].Position = D3DXVECTOR2(pos.x - i * size.x, pos.y);
					g_OpenKey[i].rot = direction * 90;
					break;
				default:
					break;
				}
				g_OpenKey[i].Size = size;
				g_OpenKey[i].index = index;
				g_OpenKey[i].UseFlag = true;
				if (i % 3 == 0) break;
			}
		}
		
	}
}

void DeleteOpenKey(int PieceNo) {
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (g_OpenKey[i].index == PieceNo) {
			if (g_OpenKey[i].UseFlag) {
				g_OpenKey[i].UseFlag = false;
			}
		}
	}
}

OPENKEY* GetOpenKey()
{
	return g_OpenKey;
}
