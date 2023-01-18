
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "MapChip.h"

#include "SheerFloors.h"
#include "player.h"


SHEERFLOORS gSheerFloors[SHEERFLOORS_NUM];
PLAYER* pPlayer;

static ID3D11Buffer* gSheerFloorsVertexBuffer = NULL;	//ポリゴン用
static ID3D11ShaderResourceView* gSheerFloorsTexture;	//画像一枚で一つの変数が必要
static char* gSheerFloorsTextureName = (char*)"data\\texture\\透ける床.png";	//テクスチャファイルパス

int gSheerFloorsNo;		//テクスチャナンバ


HRESULT InitSheerFloors()
{
	for (int i = 0; i < SHEERFLOORS_NUM; i++)
	{
		gSheerFloors[i].pos = D3DXVECTOR2(SCREEN_HEIGHT / 2 + 160, 220);

		gSheerFloors[i].size = D3DXVECTOR2(SHEERFLOORS_SIZE_X, SHEERFLOORS_SIZE_Y);

		gSheerFloors[i].index = -1;

		gSheerFloors[i].use = false;

		gSheerFloorsNo = LoadTexture(gSheerFloorsTextureName);
	}

	return S_OK;
}
void UninitSheerFloors()
{
	if (gSheerFloorsTexture)
	{
		gSheerFloorsTexture->Release();
		gSheerFloorsTexture = NULL;
	}
}
void UpdateSheerFloors()
{

}
void DrawSheerFloors()
{
	//SetWorldViewProjection2D();

	for (int i = 0; i < SHEERFLOORS_NUM; i++)
	{
		if (gSheerFloors[i].use)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(gSheerFloorsNo));

			SpriteDrawColorRotation(
				gSheerFloors[i].pos.x, gSheerFloors[i].pos.y,-0.1f,
				gSheerFloors[i].size.x, gSheerFloors[i].size.y,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f / 10.0f,
				1.0f / 1.0f,
				1
			);
		}
	}
}

void SetSheerFloors(D3DXVECTOR2 p, D3DXVECTOR2 s,int index)
{
	for (int i = 0; i < SHEERFLOORS_NUM; i++) {
		if (!gSheerFloors[i].use)
		{
			gSheerFloors[i].pos = p + D3DXVECTOR2(0.0f, BLOCK_CHIP_SIZE / 2);
			gSheerFloors[i].size = s;
			gSheerFloors[i].index = index;
			gSheerFloors[i].use = true;
			break;
		}
	}
}

SHEERFLOORS* GetSheerFloors()
{
	return &gSheerFloors[0];
}

void DeleteSheet(int PieceNo)
{
	for (int i = 0; i < SHEERFLOORS_NUM; i++) {
		if (gSheerFloors[i].index == PieceNo) {
			if (gSheerFloors[i].use) {
				gSheerFloors[i].use = false;
			}
		}
	}

}
