#include "goal.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "puzzle.h"
#include "scene.h"
#include "player.h"
#include "mouse.h"
#include "result.h"
#include "time.h"

GOAL g_Goal;
static ID3D11ShaderResourceView	*g_textureGoal;	//画像一枚で一つの変数が必要
static char *g_textureName_Goal = (char*)"data\\texture\\yello.jpg";	//テクスチャファイルパス
static Time* pTime = new(Time);
static TimeParam* pTimeParam = pTime->GetTimeParam();
HRESULT InitGoal(){
	g_Goal.texno = LoadTexture(g_textureName_Goal);
	g_Goal.Pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Goal.Size = D3DXVECTOR2(GOAL_SIEZX, GOAL_SIZEY);
	g_Goal.Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Goal.Rotation = 180.0f;
	g_Goal.pieceIndex = -1;
	g_Goal.UseFlag = false;
	return S_OK;
}

void UninitGoal()
{
	if (g_textureGoal){
		g_textureGoal->Release();
		g_textureGoal = NULL;
	}

}

void UpdateGoal()
{
	if (g_Goal.UseFlag)
	{
		PLAYER* pPlayer = GetPlayer();
		MOUSE* pMouse = GetMouse();
		RESULT* pResult = GetResult();
		if (!pMouse->UseFlag)
		{

			if (g_Goal.Pos.x + g_Goal.Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2
				&& g_Goal.Pos.x - g_Goal.Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2
				&& g_Goal.Pos.y + g_Goal.Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
				&& g_Goal.Pos.y - g_Goal.Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2)
			{
				g_Goal.UseFlag = false;
				SetResultType(WIN);
				SetScene(SCENE_RESULT);	
				pTimeParam->EndFlag = true;
			}
		}
	}
}

void DrawGoal()
{
	if (g_Goal.UseFlag){
		//SetWorldViewProjection2D();


		//四角形の描画
		//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Goal.texno));

		SpriteDrawColorRotation(g_Goal.Pos.x, g_Goal.Pos.y,-0.2f,
			g_Goal.Size.x, g_Goal.Size.y, g_Goal.Rotation, g_Goal.Col,
			0, 1.0f, 1.0f, 1);
	}

}

void SetGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index)
{
		if (!g_Goal.UseFlag)
		{
			g_Goal.Pos = pos;
			g_Goal.Size = size;
			g_Goal.pieceIndex = index;
			g_Goal.UseFlag = true;
		}
	

}

void DeleteGoal(int index)
{
	if (g_Goal.pieceIndex == index)
	{
		g_Goal.UseFlag = false;
	}

}

GOAL * GetGoal(){
	return &g_Goal;
}
