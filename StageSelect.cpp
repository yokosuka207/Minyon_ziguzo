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
//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"

#include "cursor.h"
#include "MapChip.h"
#include "scene.h"
#include "player.h"
#include "fade.h"
//*****************************************************************************
//	マクロ定義
//*****************************************************************************

#define STAIRS_LEFT	75
#define STAIRS_RIGHT	285



//*****************************************************************************
//	グローバル変数
//*****************************************************************************
static STAGESELECT g_StageSelect[STAGE_MAX];
static STAGESELECT g_StageSelectBlack[STAGE_MAX];
static STAGESELECT_BG g_StageSelectBg;
static STAGESELECT_BG g_StageSelectfence[21];
static STAGESELECT_BLOCK g_StageSelectBlock[3];
static STAGESELECT_STAIRS g_StageSelectStairs[12];

static ID3D11ShaderResourceView* g_StageSelectTexture;	//画像一枚で一つの変数が必要
static char* g_StageSelectTextureName = (char*)"data\\texture\\ドア.png";	//テクスチャファイルパス
static ID3D11ShaderResourceView* g_StageSelect2Texture;	//画像一枚で一つの変数が必要
static char* g_StageSelect2TextureName = (char*)"data\\texture\\black.png";	//テクスチャファイルパス
static ID3D11ShaderResourceView* g_StageSelectTextureBg;	//画像一枚で一つの変数が必要
static char* g_StageSelectBgTextureName = (char*)"data\\texture\\スレージセレクト背景.png";	//テクスチャファイルパス
static ID3D11ShaderResourceView* g_StageSelectTextureBlock;	//画像一枚で一つの変数が必要
static char* g_StageSelectBlockTextureName = (char*)"data\\texture\\ステージ選択床.png";	//テクスチャファイルパス
static ID3D11ShaderResourceView* g_StageSelectTextureStairs;	//画像一枚で一つの変数が必要
static char* g_StageSelectStairsTextureName = (char*)"data\\texture\\jumpstand.png";	//テクスチャファイルパス
static ID3D11ShaderResourceView* g_StageSelectTexturefence;	//画像一枚で一つの変数が必要
static char* g_StageSelectfenceTextureName = (char*)"data\\texture\\柵.png";	//テクスチャファイルパス


static PLAYER ply;
static ID3D11ShaderResourceView* g_StageSelectTexturePly;	//画像一枚で一つの変数が必要

static char* g_TextureNamePly = (char*)"data\\texture\\プレイヤー.png";

static int TexNo;	//テクスチャ格納

int StageNo = 0;

static bool OneFlag =true;	//geゲームの最初かどうか



//-----------------------------------------------------------------------------
//	初期化
//-----------------------------------------------------------------------------
HRESULT InitStageSelect() {
	StageNo = 0;

	g_StageSelectBg.pos = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	g_StageSelectBg.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_StageSelectBg.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_StageSelectBg.texno = LoadTexture(g_StageSelectBgTextureName);

	int a = 0;
	int b = 0;

	for (int i = 0; i < 21; i++)
	{
		if (i % 7 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		g_StageSelectfence[i].pos = D3DXVECTOR2(250.0f+(170.0f*b), 220.0f + (250 * a));
		g_StageSelectfence[i].size = D3DXVECTOR2(170.0f, 110.0f);
		g_StageSelectfence[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectfence[i].texno = LoadTexture(g_StageSelectfenceTextureName);
		b++;
	}


	for (int i = 0; i < 3; i++)
	{
		g_StageSelectBlock[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 250.0f + (250 * i));
		g_StageSelectBlock[i].size = D3DXVECTOR2(SCREEN_WIDTH, 15.0f);
		g_StageSelectBlock[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectBlock[i].texno = LoadTexture(g_StageSelectBlockTextureName);

	}
	 a = 0;
	 b = 0;

	for (int i = 0; i < 12; i++)
	{
		if (i % 6 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		g_StageSelectStairs[i].pos = D3DXVECTOR2(90.0f+(b*25.0f), 270.0f+(b*40.0f) + (250 * a));
		g_StageSelectStairs[i].size = D3DXVECTOR2(30.0f, 40.0f);
		g_StageSelectStairs[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectStairs[i].texno = LoadTexture(g_StageSelectStairsTextureName);
		b++;


	}

	//g_Texturenumber = LoadTexture(g_StageSelectStairsTextureName);


	 a = 0;
	b = 0;


	if (OneFlag)
	{


		for (int i = 0; i < STAGE_MAX; i++)
		{
			if (i % 7 == 0 && i != 0)
			{
				a++;
				b = 0;
			}
			//ドア
			g_StageSelect[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (180.0f) + (250.0f * a));
			g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);
			g_StageSelect[i].UseFlag = true;
			g_StageSelect[i].StagePieceIndex = i;
			g_StageSelect[i].StageUseFlag = true;
			g_StageSelect[i].texno = LoadTexture(g_StageSelectTextureName);


			g_StageSelectBlack[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (175.0f) + (250.0f * a));
			g_StageSelectBlack[i].size = D3DXVECTOR2(120.0f, 150.0f);
			g_StageSelectBlack[i].texno = LoadTexture(g_StageSelect2TextureName);
			b++;
			if (i == 0)
			{
				g_StageSelect[i].StageUseFlag = true;
				g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);

			}

		}
		TexNo = LoadTexture(g_StageSelect2TextureName);

		OneFlag = false;
	}


	ply.Position = D3DXVECTOR2(30.0f, 30.0f);
	ply.OneOldpos = ply.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	ply.sp = D3DXVECTOR2(0.0f, 8.0f);
	ply.size = D3DXVECTOR2(100.0f, 117.0f);
	ply.col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
	ply.rot = 0.0f;
	ply.UseFlag = true;
	ply.jump = false;
	//ply.getjump = false;
	ply.GetJumpStand = false;		//ジャンプ台用
	ply.fall = false;
	ply.getfall = false;
	ply.WarpFlag = false;
	ply.isGround = true;
	ply.isSheerFloors = false;
	ply.isSheerFloorsUse = false;
	ply.isHigh = false;
	ply.isMoveBlock = false;
	ply.texno = LoadTexture(g_TextureNamePly);

	ply.PaternNo = 0;//パターン番号
	ply.uv_w = PLAYER_UV_W;//横サイズ
	ply.uv_h = PLAYER_UV_H;//縦サイズ
	ply.NumPatern = 4;//横枚数

	ply.hp = 3;
	ply.frame = 0;
	ply.CoolTime = PLAYER_COOLTIME;
	ply.PieceIndex = 0;



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

	if (ply.UseFlag == true)
	{
		if (ply.isGround)
		{


			//移動
			if (Keyboard_IsKeyDown(KK_RIGHT))//右キー
			{//押されているときの処理
				ply.sp.x = 2.0f;
				ply.PaternNo += 0.25f;
				if (ply.isHigh)
				{
					ply.sp.x = 3.0f;
					ply.sp.y = 4.0f;

				}

				// 向きを変える
				ply.dir = PLAYER_DIRECTION::RIGHT;
				ply.uv_w = PLAYER_UV_W;
			}
			else if (Keyboard_IsKeyDown(KK_LEFT))//左キー
			{//押されているときの処理
				ply.sp.x = -2.0f;
				ply.PaternNo -= 0.25f;
				if (ply.isHigh)
				{
					ply.sp.x = -3.0f;
					ply.sp.y = -3.5f;

				}

				// 向きを変える
				ply.dir = PLAYER_DIRECTION::LEFT;
				ply.uv_w = -PLAYER_UV_W;
			}
			else
			{
				if (ply.isHigh)
				{
					ply.sp.y = 0.0f;
				}
				ply.sp.x = 0;

			}
		}
		if (STAIRS_LEFT < ply.Position.x && ply.Position.x < STAIRS_RIGHT) {
			if (Keyboard_IsKeyDown(KK_DOWN))//右キー
			{

				if (ply.Position.y < SCREEN_HEIGHT - 110.0f)
				{
					ply.sp.x = 0;

					ply.sp.y = 5.0f;
					ply.isGround = false;

				}
			}
		}

		// アニメーションパターン番号を0～15の範囲内にする
		if (ply.PaternNo > 15) { ply.PaternNo -= 15; }
		if (ply.PaternNo < 0) { ply.PaternNo += 15; }

		ply.oldpos = ply.Position;
		ply.Position += ply.sp;




		for (int i = 0; i < 3; i++)
		{
			{
				//プレイヤー左・ブロック右
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.oldpos.x + ply.size.x / 2 <= g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2)
				{
					ply.Position.x = g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 - ply.size.x / 2;
				}
				//プレイヤー右・ブロック左
				if (ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.oldpos.x - ply.size.x / 2 >= g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 3 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 3 &&
					ply.Position.y - ply.size.y / 3 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 3)
				{
					ply.Position.x = g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 + ply.size.x / 2;
				}
				if (ply.isGround)
				{
					//プレイヤー上・ブロック下,着地する
					if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
						ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
						ply.Position.y + ply.size.y / 2 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 &&
						ply.oldpos.y + ply.size.y / 2 <= g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2)
					{
						ply.Position.y = g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 - ply.size.y / 2 - 0.02f;
						ply.jump = false;
						ply.fall = false;
						ply.WarpFlag = false;
						//ply.isGround = true;
						ply.sp.y = 0;
						ply.frame = 0;
						ply.isHigh = false;

					}
				}
				//プレイヤー下・ブロック上,落下する
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2 &&
					ply.oldpos.y + ply.size.y / 2 >= g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2)
				{
					ply.Position.y = g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 - ply.size.y / 2 - 0.02f;
					ply.isHigh = false;
					ply.sp.y = 0.0f;
					ply.fall = true;
					ply.getfall = true;
					ply.frame = 50;
				}
			}
		}
		for (int i = 0; i < 12; i++)
		{
			{
				//プレイヤー左・ブロック右
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.oldpos.x + ply.size.x / 2 <= g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2)
				{
					//ply.Position.x = g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 - ply.size.x / 2;
				}
				//プレイヤー右・ブロック左
				if (ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.oldpos.x - ply.size.x / 2 >= g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 3 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 3 &&
					ply.Position.y - ply.size.y / 3 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 3)
				{
					//ply.Position.x = g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 + ply.size.x / 2;
					//ply.sp = D3DXVECTOR2(0.0f,-4.0f);
					if (Keyboard_IsKeyDown(KK_UP))
					{
						ply.isHigh = true;	//上に上る

					}
				}

				//プレイヤー上・ブロック下,着地する
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 &&
					ply.oldpos.y + ply.size.y / 2 <= g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2)
				{
					ply.isGround = true;

					ply.Position.y = g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 - ply.size.y / 2 - 0.02f;
					ply.jump = false;
					ply.fall = false;
					ply.WarpFlag = false;
					//ply.isGround = true;
					ply.sp.y = 4.0f;
					ply.frame = 0;
				}
				//プレイヤー下・ブロック上,落下する
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2 &&
					ply.oldpos.y - ply.size.y / 2 >= g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2)
				{
					ply.fall = true;
					ply.getfall = true;
					ply.frame = 50;
				}
			}
		}


	}


	


	//ステージ選択

	for (int i = 0; i < STAGE_MAX; i++)
	{
		if (g_StageSelect[i].StageUseFlag)
		{
			if (ply.Position.x - ply.size.x / 2 > g_StageSelect[i].pos.x - g_StageSelect[i].size.x / 2 &&
				ply.Position.x + ply.size.x / 2 < g_StageSelect[i].pos.x + g_StageSelect[i].size.x / 2 &&
				ply.Position.y + ply.size.y / 2 > g_StageSelect[i].pos.y - g_StageSelect[i].size.y / 2 &&
				ply.Position.y - ply.size.y / 2 < g_StageSelect[i].pos.y + g_StageSelect[i].size.y / 2)
			{


				if (Keyboard_IsKeyTrigger(KK_A)) {
					StageNo = i;
					//SetScene(SCENE::SCENE_GAME);
					StartFade(FADE::FADE_OUT);
					break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	描画処理
//-----------------------------------------------------------------------------
void DrawStageSelect() {
	

	{	//背景ポリゴン表示
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBg.texno));
		SpriteDrawColorRotation(
			g_StageSelectBg.pos.x, g_StageSelectBg.pos.y, 0.5f, g_StageSelectBg.size.x, g_StageSelectBg.size.y
			, 0.0f, g_StageSelectBg.color, 0, 1.0f, 1.0f, 1);
	}
	for (int i = 0; i < 3; i++)
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBlock[i].texno));

		SpriteDrawColorRotation(
			g_StageSelectBlock[i].pos.x, g_StageSelectBlock[i].pos.y, 0.5f, g_StageSelectBlock[i].size.x, g_StageSelectBlock[i].size.y
			, 0.0f, g_StageSelectBlock[i].color, 0, 1.0f, 1.0f, 1);

	}

	//階段
	for (int i = 0; i < 12; i++)
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectStairs[i].texno));

		SpriteDrawColorRotation(
			g_StageSelectStairs[i].pos.x, g_StageSelectStairs[i].pos.y, 0.5f, g_StageSelectStairs[i].size.x+10, g_StageSelectStairs[i].size.y+10
			, 0.0f, g_StageSelectStairs[i].color, 0, 1.0f, 1.0f, 1);

	}

	

		for (int i = 0; i < STAGE_MAX; i++)
		{

		
		SetWorldViewProjection2D();
		if (g_StageSelect[i].StageUseFlag)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelect[i].texno));

		}
		else
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TexNo));

		}

		//g_StageSelect[i].pos.x = g_SelectDistance;

			SpriteDrawColorRotation(
				g_StageSelect[i].pos.x, g_StageSelect[i].pos.y - 10, 0.0f,
				g_StageSelect[i].size.x / 2, g_StageSelect[i].size.y,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,
				1.0f,
				1
			);
			//g_StageSelect[i].pos.x -= 30;
		
		}

		if (ply.UseFlag == true)
		{
			SetWorldViewProjection2D();

			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ply.texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(ply.Position.x, ply.Position.y, -0.0f, ply.size.x, ply.size.y, ply.rot, ply.col, ply.PaternNo, ply.uv_w, ply.uv_h, ply.NumPatern);
		}

		for (int i = 0; i < 21; i++)
		{

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectfence[i].texno));
			SpriteDrawColorRotation(
				g_StageSelectfence[i].pos.x, g_StageSelectfence[i].pos.y, 0.5f, g_StageSelectfence[i].size.x, g_StageSelectfence[i].size.y
				, 0.0f, g_StageSelectfence[i].color, 0, 1.0f, 1.0f, 1);

		}

	
}

//-----------------------------------------------------------------------------
//	ステージセット関数
//-----------------------------------------------------------------------------
void SetStageSelect(int a) {

	

}
//-----------------------------------------------------------------------------
//	ステージセレクトを外部で値を変えれるようにする関数
//-----------------------------------------------------------------------------
STAGESELECT* GetSelect() {
	return g_StageSelect;
}
int ReturnStageNo()
{
	return StageNo;
}

