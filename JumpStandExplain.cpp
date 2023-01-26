
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "collision.h"
#include "JumpStandExplain.h"

static EXPLAIN g_Explain[EXPLAIN_MAX];

// ヒント表示オブジェクト
static ID3D11ShaderResourceView* g_ExplainBlock;
static char* g_ExplainBlockName = (char*)"data\\texture\\ヒントブロック.png";
static int	  g_ExplainBlockNo = 0;

// Piace ヒント
static ID3D11ShaderResourceView* g_PiaceExplain;
static char* g_PiaceExplainName = (char*)"data\\texture\\PiaceExplain.png";
static int	  g_PiaceExplainNo = 0;
// Piace2 ヒント
static ID3D11ShaderResourceView* g_Piace2Explain;
static char* g_Piace2ExplainName = (char*)"data\\texture\\Piace2Explain.png";
static int	  g_Piace2ExplainNo = 0;
// Piace3 ヒント
static ID3D11ShaderResourceView* g_Piace3Explain;
static char* g_Piace3ExplainName = (char*)"data\\texture\\Piace3Explain.png";
static int	  g_Piace3ExplainNo = 0;
// Block ヒント
static ID3D11ShaderResourceView* g_BlockExplain;
static char* g_BlockExplainName = (char*)"data\\texture\\BlockExplain.png";
static int	  g_BlockExplainNo = 0;
// Enemy ヒント
static ID3D11ShaderResourceView* g_EnemyExplain;
static char* g_EnemyExplainName = (char*)"data\\texture\\EnemyExplain.png";
static int	  g_EnemyExplainNo = 0;
// BrokenBlock ヒント
static ID3D11ShaderResourceView* g_BrokenExplain;
static char* g_BrokenExplainName = (char*)"data\\texture\\BrokenExplain.png";
static int	  g_BrokenExplainNo = 0;
// MoveBlock ヒント
static ID3D11ShaderResourceView* g_MoveExplain;
static char* g_MoveExplainName = (char*)"data\\texture\\MoveExplain.png";
static int	  g_MoveExplainNo = 0;
// SheerBlock ヒント
static ID3D11ShaderResourceView* g_SheerExplain;
static char* g_SheerExplainName = (char*)"data\\texture\\SheerExplain.png";
static int	  g_SheerExplainNo = 0;


HRESULT InitExplain()
{
	//ヒント表示ブロック初期化
	g_ExplainBlockNo = LoadTexture(g_ExplainBlockName);

	g_PiaceExplainNo = LoadTexture(g_PiaceExplainName);
	g_Piace2ExplainNo = LoadTexture(g_Piace2ExplainName);
	g_Piace3ExplainNo = LoadTexture(g_Piace3ExplainName);
	g_BlockExplainNo = LoadTexture(g_BlockExplainName);
	g_EnemyExplainNo = LoadTexture(g_EnemyExplainName);
	g_BrokenExplainNo = LoadTexture(g_BrokenExplainName);
	g_MoveExplainNo = LoadTexture(g_MoveExplainName);
	g_SheerExplainNo = LoadTexture(g_SheerExplainName);

	for (int i = 0; i < EXPLAIN_MAX; i++) {
		g_Explain[i].pos = D3DXVECTOR2(-127, 150);
		g_Explain[i].size = D3DXVECTOR2(EXPLAIN_SIZE, EXPLAIN_SIZE);
		g_Explain[i].rot = 0.0f;
		g_Explain[i].PieceIndex = -1;
		g_Explain[i].bUse = false;
	}

	return S_OK;
}

void UninitExplain()
{
	if (g_ExplainBlock)
	{
		g_ExplainBlock->Release();
		g_ExplainBlock = NULL;
	}

	if (g_PiaceExplain)
	{
		g_PiaceExplain->Release();
		g_PiaceExplain = NULL;
	}
	if (g_Piace2Explain)
	{
		g_Piace2Explain->Release();
		g_Piace2Explain = NULL;
	}
	if (g_Piace3Explain)
	{
		g_Piace3Explain->Release();
		g_Piace3Explain = NULL;
	}

	if (g_BlockExplain)
	{	  
		g_BlockExplain->Release();
		g_BlockExplain = NULL;
	}
	if (g_EnemyExplain)
	{	  
		g_EnemyExplain->Release();
		g_EnemyExplain = NULL;
	}
	if (g_BrokenExplain)
	{	  
		g_BrokenExplain->Release();
		g_BrokenExplain = NULL;
	}
	if (g_MoveExplain)
	{	  
		g_MoveExplain->Release();
		g_MoveExplain = NULL;
	}
	if (g_SheerExplain)
	{	  
		g_SheerExplain->Release();
		g_SheerExplain = NULL;
	}

}

void UpdateExplain()
{
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].CollisionUse)
		{
			if (Keyboard_IsKeyDown(KK_B) ||					// keyboard B
				IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {	// GamePad B
				if (g_Explain[i].No == 0) {
					g_Explain[i].HintUse = true;
					g_Explain[i].No++;
				}
				else if (g_Explain[i].No == 1) {
					g_Explain[i].HintUse = false;
					g_Explain[i].No--;
				}
			}
		}
		else if (!g_Explain[i].CollisionUse) {
			g_Explain[i].HintUse = false;
		}
	}

}

void DrawExplain()
{
	//SetWorldViewProjection2D();

	//ヒントブロック
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].bUse)
		{
			//ブロック表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ExplainBlockNo));

			SpriteDrawColorRotation(g_Explain[i].pos.x, g_Explain[i].pos.y, 0.0f,
				g_Explain[i].size.x, g_Explain[i].size.y, g_Explain[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1);


			//ヒント表示
			if (g_Explain[i].HintUse)
			{
				SetWorldViewProjection2D();

				switch (g_Explain[i].tex) {
				case 26:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PiaceExplainNo));
					break;
				case 27:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace2ExplainNo));
					break;
				case 28:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace3ExplainNo));
					break;
				case 29:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BlockExplainNo));
					break;
				case 30:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EnemyExplainNo));
					break;
				case 31:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BrokenExplainNo));
					break;
				case 32:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BlockExplainNo));
					break;
				case 33:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SheerExplainNo));
					break;
				}
				SpriteDrawColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f,
					HINT_SIZE_X, HINT_SIZE_Y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					0, 1.0f, 1.0f, 1);
			}
		}
	}
}


void SetExplain(D3DXVECTOR2 pos, D3DXVECTOR2 size, int no, int direction, int q)
{
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (!g_Explain[i].bUse)
		{
			switch (direction) {
			case 0:g_Explain[i].rot = direction * 90;
				break;
			case 1:g_Explain[i].rot = (direction + 2) * 90;
				break;
			case 2:g_Explain[i].rot = direction * 90;
				break;
			case 3:g_Explain[i].rot = (direction - 2) * 90;
				break;
			default:
				break;
			}

			g_Explain[i].pos = pos;
			g_Explain[i].size = size;
			g_Explain[i].bUse = true;

			g_Explain[i].tex = q;
		}
	}
}

EXPLAIN* GetExplain()
{
	return &g_Explain[0];
}

void DeleteExplain(int PieceNo)
{
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].bUse) {
			if(g_Explain[i].PieceIndex == PieceNo)
			g_Explain[i].bUse = false;
		}
	}
}
