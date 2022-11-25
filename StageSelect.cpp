//=============================================================================
//
//	ステージセレクト処理[StageSelect.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================

#include "texture.h"
#include "sprite.h"
#include "StageSelect.h"
#include "input.h"
#include "cursor.h"
#include "MapChip.h"
#include "scene.h"

//*****************************************************************************
//	マクロ定義
//*****************************************************************************

//*****************************************************************************
//	グローバル変数
//*****************************************************************************
static STAGESELECT g_StageSelect;

static ID3D11Buffer* g_StageSelectVertexBuffer = NULL;	//ポリゴン用
static ID3D11ShaderResourceView* g_StageSelectTexture;	//画像一枚で一つの変数が必要
static char* g_StageSelectTextureName = (char*)"data\\texture\\Ground.png";	//テクスチャファイルパス

//-----------------------------------------------------------------------------
//	初期化
//-----------------------------------------------------------------------------
HRESULT InitStageSelect() {
	g_StageSelect.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_StageSelect.size = D3DXVECTOR2(0.0f, 0.0f);
	g_StageSelect.UseFlag = false;
	g_StageSelect.StagePieceIndex = 0;
	g_StageSelect.StageUseFlag = false;
	g_StageSelect.texno = LoadTexture(g_StageSelectTextureName);
	return S_OK;
}

//-----------------------------------------------------------------------------
//	終了処理
//-----------------------------------------------------------------------------
void UninitStageSelect() {
	if (g_StageSelectTexture) {
		g_StageSelectTexture->Release();
		g_StageSelectTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
//	更新処理
//-----------------------------------------------------------------------------
void UpdateStageSelect() {

	//ステージ選択
	if (GetKeyboardTrigger(DIK_RIGHT)) {
		g_StageSelect.StagePieceIndex++;
		if (g_StageSelect.StagePieceIndex > STAGE_MAX - 1) {
			g_StageSelect.StagePieceIndex = 0;
		}
	}
	if (GetKeyboardTrigger(DIK_LEFT)) {
		g_StageSelect.StagePieceIndex--;
		if (g_StageSelect.StagePieceIndex < 0) {
			g_StageSelect.StagePieceIndex = STAGE_MAX - 1;
		}
	}

	if (GetKeyboardTrigger(DIK_F5)) {
		SetScene(SCENE::SCENE_GAME);
	}
}

//-----------------------------------------------------------------------------
//	描画処理
//-----------------------------------------------------------------------------
void DrawStageSelect() {
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelect.texno));

		SpriteDrawColorRotation(
			g_StageSelect.pos.x, g_StageSelect.pos.y,
			g_StageSelect.size.x, g_StageSelect.size.y,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1,
			1.0f / 1.0f,
			1.0f / 1.0f,
			1
		);
	}
}

//-----------------------------------------------------------------------------
//	ステージセット関数
//-----------------------------------------------------------------------------
void SetStageSelect() {

}
//-----------------------------------------------------------------------------
//	ステージセレクトを外部で値を変えれるようにする関数
//-----------------------------------------------------------------------------
STAGESELECT* GetSelect() {
	return &g_StageSelect;
}
