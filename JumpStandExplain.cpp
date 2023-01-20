
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "collision.h"
#include "JumpStandExplain.h"

static EXPLAIN g_Explain;

// ヒント表示オブジェクト
static ID3D11ShaderResourceView* g_ExplainBlock;
static char* g_ExplainBlockName = (char*)"data\\texture\\ヒントブロック.jpg";
static int	  g_ExplainBlockNo = 0;

// JumpStand ヒント
static ID3D11ShaderResourceView* g_JumpExplain;
static char* g_JumpExplainName = (char*)"data\\texture\\ヒント.jpg";
static int	  g_JumpExplainNo = 0;

HRESULT InitExplain()
{
	//ヒント表示ブロック初期化
	g_ExplainBlockNo = LoadTexture(g_ExplainBlockName);
	g_JumpExplainNo = LoadTexture(g_JumpExplainName);

	g_Explain.pos = D3DXVECTOR2(-127,150);
	g_Explain.size = D3DXVECTOR2(EXPLAIN_SIZE, EXPLAIN_SIZE);

	g_Explain.bUse = false;

	return S_OK;
}

void UninitExplain()
{
	if (g_ExplainBlock)
	{
		g_ExplainBlock->Release();
		g_ExplainBlock = NULL;
	}

	if (g_JumpExplain)
	{
		g_JumpExplain->Release();
		g_JumpExplain = NULL;
	}

}

void UpdateExplain()
{
	if (g_Explain.CollisionUse)
	{
		if (Keyboard_IsKeyDown(KK_B)) {
			if (g_Explain.No == 0) {
				g_Explain.HintUse = true;
				g_Explain.No++;
			}
			else if (g_Explain.No == 1) {
				g_Explain.HintUse = false;
				g_Explain.No--;
			}
		}
	}
	else if (!g_Explain.CollisionUse) {
		g_Explain.HintUse = false;
	}

}

void DrawExplain()
{
	//SetWorldViewProjection2D();

	//ヒントブロック
	if (g_Explain.bUse)
	{
		//ブロック表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ExplainBlockNo));

		SpriteDrawColorRotation(g_Explain.pos.x, g_Explain.pos.y, 0.0f,
			g_Explain.size.x, g_Explain.size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0, 1.0f, 1.0f, 1);


		//ヒント表示
		if (g_Explain.HintUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_JumpExplainNo));

			SpriteDrawColorRotation(0, 0, 0.0f,
				HINT_SIZE_X, HINT_SIZE_Y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1);
		}
	}
}


void SetExplain(D3DXVECTOR2 pos)
{
	if (!g_Explain.bUse)
	{
		g_Explain.pos = pos;
		g_Explain.bUse = true;
	}
}

EXPLAIN* GetExplain()
{
	return &g_Explain;
}
