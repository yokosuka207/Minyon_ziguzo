
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "PlayerLife.h"
#include "player.h"


static PLAYERLIFE gPlayerLife[LIFE_MAX];
static PLAYER*	 pPlayer;

// JumpStand �q���g
static ID3D11ShaderResourceView* gLife_A;
static char* gLifeName = (char*)"data\\texture\\Life_A.png";
static int	  gPlayerLifeNo = 0;

static ID3D11ShaderResourceView* gLife_B;
static char* gLifeName2 = (char*)"data\\texture\\Life_B.png";
static int	  gPlayerLifeNo2 = 0;

HRESULT InitPlayerLife()
{
	for (int i = 0; i < LIFE_MAX; i++)
	{
		gPlayerLifeNo = LoadTexture(gLifeName);
		gPlayerLifeNo2 = LoadTexture(gLifeName2);

		gPlayerLife[i].pos = D3DXVECTOR2(50.0f, 20.0f);
		gPlayerLife[i].size = D3DXVECTOR2(LIFE_SIZE_X, LIFE_SIZE_Y);

		gPlayerLife[i].bUse = true;
	}

	return S_OK;
}

void UninitPlayerLife()
{
	if (gLife_A)
	{
		gLife_A->Release();
		gLife_A = NULL;
	}

	if (gLife_B)
	{
		gLife_B->Release();
		gLife_B = NULL;
	}
}

void UpdatePlayerLife()
{
	pPlayer = GetPlayer();

	if (pPlayer->hp == 2)
	{
		gPlayerLife[2].bUse = false;
	}
	else if (pPlayer->hp == 1)
	{
		gPlayerLife[1].bUse = false;
	}
	else if (pPlayer->hp == 0)
	{
		gPlayerLife[0].bUse = false;
	}
}

void DrawPlayerLife()
{

	for (int i = 0; i < LIFE_MAX; i++)
	{
		if (gPlayerLife[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(gPlayerLifeNo));
		}
		if (!gPlayerLife[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(gPlayerLifeNo2));
		}

		SpriteDrawColorRotation(gPlayerLife[i].pos.x + 50.0f * i, gPlayerLife[i].pos.y, 0.0f,
			gPlayerLife[i].size.x, gPlayerLife[i].size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0, 1.0f, 1.0f, 1);
	}

}