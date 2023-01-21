#include "goal.h"
#include "goal_key.h"
#include "texture.h"
#include "sprite.h"
#include "puzzle.h"
#include "scene.h"
#include "player.h"
#include "mouse.h"
#include "result.h"
#include "time.h"
#include "fade.h"
#include"StageSelect.h"
#include "start.h"
#include "save.h"

GOAL g_Goal;
GKey g_GKey;
static ID3D11ShaderResourceView	*g_textureGoal;	//画像一枚で一つの変数が必要
static char *g_textureName_Goal = (char*)"data\\texture\\ピース取得アイテム.png";	//テクスチャファイルパス
static Time* pTime = pTime->GetTime();
static TimeParam* pTimeParam = pTime->GetTimeParam();
HRESULT InitGoal(){
	g_Goal.texno = LoadTexture(g_textureName_Goal);
	g_Goal.Pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Goal.Size = D3DXVECTOR2(GOAL_SIEZX, GOAL_SIZEY);
	g_Goal.Col = D3DXCOLOR(0.7f, 1.0f, 0.7f, 1.0f);
	g_Goal.Rotation = 0.0f;
	g_Goal.pieceIndex = -1;

	g_Goal.NumPatern = 4;
	g_Goal.PaternNo = 0;
	g_Goal.uv_w = CIP_UV_W;
	g_Goal.uv_h = CIP_UV_H;

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
		GKey* pGKey = GetGKey();
		MOUSE* pMouse = GetMouse();
		RESULT* pResult = GetResult();
		START* pStart = GetStart();
		if (!pMouse->UseFlag)// && pGKey->GetGKey)
		{
			g_Goal.PaternNo += 0.25f;
			if (g_Goal.PaternNo > 16.0f)
			{
				g_Goal.PaternNo = 0;
			}


			if (g_Goal.Pos.x + g_Goal.Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2
				&& g_Goal.Pos.x - g_Goal.Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2
				&& g_Goal.Pos.y + g_Goal.Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
				&& g_Goal.Pos.y - g_Goal.Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2)
			{
				STAGESELECT* pStageSelect = GetSelect();

				if (ReturnStageNo() != STAGE_MAX)
				{
					pStageSelect[ReturnStageNo() + 1].StageUseFlag = true;
					pStageSelect[ReturnStageNo() + 1].size = D3DXVECTOR2(120.0f, 140.f);
				}
				else {		// 最後のステージだったら
					SetStageAllClear(true);
				}
				for (int i = 0; i < START_MAX; i++) {
					if (pStart[i].UseFlag) {
						g_Goal.UseFlag = false;
						pStart[i].GoalFlag = true;
						//SetResultType(WIN);
						//StartFade(FADE::FADE_ALPHA_OUT);
						//pTime->EndTime();
						//pTimeParam->EndFlag = true;
					}
				}
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

		SpriteDrawColorRotation(g_Goal.Pos.x, g_Goal.Pos.y,-0.1f,
			g_Goal.Size.x + 10.0f, g_Goal.Size.y + 10.0f, g_Goal.Rotation, g_Goal.Col,
			g_Goal.PaternNo, g_Goal.uv_w, g_Goal.uv_h, g_Goal.NumPatern);
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
