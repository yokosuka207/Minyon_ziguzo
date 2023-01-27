
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "DoppelgangerLife.h"
#include "doppelganger.h"


static DOPPELGANGERLIFE gDoppelgangerLife[D_LIFE_MAX];
static DOPPELGANGER*	 pDoppelganger;

// JumpStand ヒント
static ID3D11ShaderResourceView* gLife_A;
static char* gLifeName = (char*)"data\\texture\\残機ある.png";
static int	  gDoppelgangerLifeNo = 0;

static ID3D11ShaderResourceView* gLife_B;
static char* gLifeName2 = (char*)"data\\texture\\残機ない.png";
static int	  gDoppelgangerLifeNo2 = 0;

HRESULT InitDoppelgangerLife()
{
	for (int i = 0; i < D_LIFE_MAX; i++)
	{
		gDoppelgangerLifeNo = LoadTexture(gLifeName);
		gDoppelgangerLifeNo2 = LoadTexture(gLifeName2);

		gDoppelgangerLife[i].pos = D3DXVECTOR2(1195.0f, 50.0f);
		gDoppelgangerLife[i].size = D3DXVECTOR2(D_LIFE_SIZE_X, D_LIFE_SIZE_Y);

		gDoppelgangerLife[i].bUse = true;
	}

	return S_OK;
}

void UninitDoppelgangerLife()
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

void UpdateDoppelgangerLife()
{
	pDoppelganger = GetDoppelganger();

	if (pDoppelganger->UseFlag)
	{
		if (pDoppelganger->hp == 2)
		{
			gDoppelgangerLife[2].bUse = false;
		}
		else if (pDoppelganger->hp == 1)
		{
			gDoppelgangerLife[1].bUse = false;
		}
		else if (pDoppelganger->hp == 0)
		{
			gDoppelgangerLife[0].bUse = false;
		}
	}
}

void DrawDoppelgangerLife()
{

	if (pDoppelganger->UseFlag)
	{
		for (int i = 0; i < D_LIFE_MAX; i++)
		{
			if (gDoppelgangerLife[i].bUse) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(gDoppelgangerLifeNo));
			}
			if (!gDoppelgangerLife[i].bUse) {
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(gDoppelgangerLifeNo2));
			}

			SpriteDrawColorRotation(gDoppelgangerLife[i].pos.x + 50.0f * i, gDoppelgangerLife[i].pos.y, 0.0f,
				gDoppelgangerLife[i].size.x, gDoppelgangerLife[i].size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1);
		}
	}
}