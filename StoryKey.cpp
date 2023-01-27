//=============================================================================
//ゴール用鍵
//
//制作者/座間研佑　
//=============================================================================

#include "main.h"
#include "renderer.h"
#include "StoryKey.h"
#include "sprite.h"
#include "texture.h"


//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================


static STORYKEY gStoryKey[STORYKEY_MAX];

static	ID3D11ShaderResourceView* g_StoryKeyTexture = NULL;//テクスチャ情報
static	char* g_StoryKeyTextureName = (char*)"data\\texture\\StoryKey.png";
int		StoryKeyTextureNo = 0;

float g_sub = 0;

HRESULT InitStoryKey()
{
	StoryKeyTextureNo = LoadTexture(g_StoryKeyTextureName);

	for (int i = 0; i < STORYKEY_MAX; i++) 
	{
		//-127, 150)
		gStoryKey[i].pos = D3DXVECTOR2(-127, 150);
		gStoryKey[i].size = D3DXVECTOR2(STORYKEY_SIZE, STORYKEY_SIZE);
		gStoryKey[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		gStoryKey[i].rot = 0.0f;

		gStoryKey[i].bUse = false;

		gStoryKey[i].no = -1;
	}

	g_sub = 0;

	return S_OK;

}


void UninitStoryKey()
{

}


void UpdateStoryKey()
{
	
}


void DrawStoryKey()
{
	//SetWorldViewProjection2D();

	for (int i = 0; i < STORYKEY_MAX; i++)
	{
		if (gStoryKey[i].bUse)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(StoryKeyTextureNo));

			SpriteDrawColorRotation(gStoryKey[i].pos.x, gStoryKey[i].pos.y, 0.0f, gStoryKey[i].size.x, gStoryKey[i].size.y,
				gStoryKey[i].rot, gStoryKey[i].col, 0, 1.0f, 1.0f, 1);
		}
	}
}


void SetStoryKey(D3DXVECTOR2 p, D3DXVECTOR2 s, int no, int direction, int tex)
{
	for (int i = 0; i < STORYKEY_MAX; i++) {
		switch (direction) {
		case 0:gStoryKey[i].rot = (direction + 2) * 90;
			break;
		case 1:gStoryKey[i].rot = direction * 90;
			break;
		case 2:gStoryKey[i].rot = (direction - 2) * 90;
			break;
		case 3:gStoryKey[i].rot = direction * 90;
			break;
		default:
			break;
		}

		if (!gStoryKey[i].bUse) {
			gStoryKey[i].pos = p;
			gStoryKey[i].size = s;

			gStoryKey[i].no = no;
			gStoryKey[i].bUse = true;
			break;
		}
	}
}


void DeleteStoryKey(int no)
{
	for (int i = 0; i < STORYKEY_MAX; i++) {
		if (gStoryKey[i].no == no) {
			gStoryKey[i].bUse = false;
		}
	}
}


STORYKEY* GetStoryKey()
{
	return gStoryKey;
}