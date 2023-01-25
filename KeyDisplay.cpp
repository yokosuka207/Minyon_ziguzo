
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "KeyDisplay.h"
#include "key.h"
#include "player.h"


static KEYDISPLAY pKeyDisplay[KEY_MAX];
static KEY* pKey;
static PLAYER* pPlayer;

// JumpStand ƒqƒ“ƒg
static ID3D11ShaderResourceView* gDisplay;
static char* gKeyDisplayName = (char*)"data\\texture\\Œ®.png";
static int	  pKeyDisplayNo = 0;

HRESULT InitKeyDisplay()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		pKeyDisplayNo = LoadTexture(gKeyDisplayName);

		pKeyDisplay[i].pos = D3DXVECTOR2(130.0f, 150.0f);
		pKeyDisplay[i].size = D3DXVECTOR2(KEYDISPLAY_SIZE_X, KEYDISPLAY_SIZE_Y);

		pKeyDisplay[i].bUse = true;
	}

	return S_OK;
}

void UninitKeyDisplay()
{
	if (gDisplay)
	{
		gDisplay->Release();
		gDisplay = NULL;
	}
}

void UpdateKeyDisplay()
{

}

void DrawKeyDisplay()
{
	pKey = GetKey();
	pPlayer = GetPlayer();
	int n = 0;



	for (int i = 0; i < pPlayer->HaveKey; i++)
	{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(pKeyDisplayNo));
	SpriteDrawColorRotation(pKeyDisplay[i].pos.x + 50.0f * i, pKeyDisplay[i].pos.y, 0.0f,
		pKeyDisplay[i].size.x, pKeyDisplay[i].size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		0, 1.0f, 1.0f, 1);

	}
	

}