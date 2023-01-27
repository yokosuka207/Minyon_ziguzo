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
#include "sound.h"
#include "story.h"
#include "collision.h"
//*****************************************************************************
//	マクロ定義
//*****************************************************************************

#define STAIRS_LEFT	65
#define STAIRS_RIGHT	245

#define DOOR_SPACE	1050 / 7


//*****************************************************************************
//	グローバル変数
//*****************************************************************************
static STAGESELECT g_StageSelect[STAGE_MAX];
static STAGESELECT g_StageSelectBlack[STAGE_MAX];
static STAGESELECT_BG g_StageSelectBg;
static STAGESELECT_BG g_StageSelectfence[24];
static STAGESELECT_BLOCK g_StageSelectBlock[3];
static STAGESELECT_STAIRS g_StageSelectStairs[12];

static ID3D11ShaderResourceView* g_StageSelectTexture;	//画像一枚で一つの変数が必要
static char* g_StageSelectTextureName = (char*)"data\\texture\\ドア3.png";	//テクスチャファイルパス

static ID3D11ShaderResourceView* g_StageSelect2Texture;	//画像一枚で一つの変数が必要
static char* g_StageSelect2TextureName = (char*)"data\\texture\\black.png";	//テクスチャファイルパス

static ID3D11ShaderResourceView* g_StageSelectTextureBg;	//画像一枚で一つの変数が必要
static char* g_StageSelectBgTextureName = (char*)"data\\texture\\ステージセレクト背景.png";	//テクスチャファイルパス

static ID3D11ShaderResourceView* g_StageSelectTextureBlock;	//画像一枚で一つの変数が必要
static char* g_StageSelectBlockTextureName = (char*)"data\\texture\\ステージ選択床.png";	//テクスチャファイルパス

static ID3D11ShaderResourceView* g_StageSelectTextureStairs;	//画像一枚で一つの変数が必要
static char* g_StageSelectStairsTextureName = (char*)"data\\texture\\階段6.png";	//テクスチャファイルパス
static char* g_StageSelectStairsTextureName2 = (char*)"data\\texture\\階段2.png";	//テクスチャファイルパス
static int g_StageSelectStairsTexNo = 0;
static int g_StageSelectStairsTexNo2 = 0;

static ID3D11ShaderResourceView* g_StageSelectTexturefence;	//画像一枚で一つの変数が必要
static char* g_StageSelectfenceTextureName = (char*)"data\\texture\\新柵1.png";	//テクスチャファイルパス


static PLAYER ply;
static ID3D11ShaderResourceView* g_StageSelectTexturePly;	//画像一枚で一つの変数が必要

STORY* pStory;

static char* g_TextureNamePly = (char*)"data\\texture\\プレイヤー.png";

static int TexNo;	//テクスチャ格納

int StageNo = -1;
int q = 0;

static bool OneFlag =true;	//geゲームの最初かどうか

//プレイヤーSE
static int g_StageSelectPlayerRightSoundNo = 0;
static char g_StageSelectPlayerRightSoundName[] = "data\\SoundData\\SE\\革靴で歩く右.wav";
static int g_StageSelectPlayerLeftSoundNo = 0;
static char g_StageSelectPlayerLeftSoundName[] = "data\\SoundData\\SE\\革靴で歩く左.wav";

//ステージセレクトドアSE
static int g_StageSelectSoundNo = 0;
static char g_StageSelectSoundName[] = "data\\SoundData\\SE\\ドアを開ける音(無料効果音で遊ぼう！).wav";
static int g_ClearStageNum = 0;

//-----------------------------------------------------------------------------
//	初期化
//-----------------------------------------------------------------------------
HRESULT InitStageSelect() {
	//StageNo = 0;

	g_StageSelectBg.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_StageSelectBg.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_StageSelectBg.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_StageSelectBg.texno = LoadTexture(g_StageSelectBgTextureName);
	

	int a = 0;
	int b = 0;
	//=============================================
	//フェンス
	//=============================================
	for (int i = 0; i < 24; i++)
	{
		if (i % 8 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		//g_StageSelectfence[i].pos = D3DXVECTOR2(300.0f + (170.0f * b), 190.0f + (250 * a));
		g_StageSelectfence[i].pos = D3DXVECTOR2(420.0f + (170.0f * b), 190.0f + (250 * a));
		g_StageSelectfence[i].size = D3DXVECTOR2(170.0f, 110.0f);
		g_StageSelectfence[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectfence[i].texno = LoadTexture(g_StageSelectfenceTextureName);
		b++;
	}

	//=============================================
	// ブロック
	//=============================================
	for (int i = 0; i < 3; i++)
	{
		g_StageSelectBlock[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 250.0f + (250 * i));
		g_StageSelectBlock[i].size = D3DXVECTOR2(SCREEN_WIDTH, 15.0f);
		g_StageSelectBlock[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectBlock[i].texno = LoadTexture(g_StageSelectBlockTextureName);

	}
	//=============================================
	// 階段
	//=============================================
	a = 0;
	b = 0;

	for (int i = 0; i < 12; i++)
	{
		if (i % 6 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		//g_StageSelectStairs[i].pos = D3DXVECTOR2(90.0f+ (b * 28.0f), 270.0f+(b * 40.0f) + (250 * a));
		//g_StageSelectStairs[i].pos = D3DXVECTOR2(90.0f + (b * 23.0f), 267.0f + (b * 40.0f) + (250 * a));
		g_StageSelectStairs[i].pos = D3DXVECTOR2(140.0f + (b * 23.0f), 267.0f + (b * 40.0f) + (250 * a));
		g_StageSelectStairs[i].size = D3DXVECTOR2(30.0f, 40.0f);
		g_StageSelectStairs[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		b++;
	}
	g_StageSelectStairsTexNo = LoadTexture(g_StageSelectStairsTextureName);
	g_StageSelectStairsTexNo2 = LoadTexture(g_StageSelectStairsTextureName2);

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
			//g_StageSelect[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (180.0f) + (250.0f * a));
			//g_StageSelect[i].pos = D3DXVECTOR2((300.0f) + (DOOR_SPACE * b), (180.0f) + (250.0f * a));
			g_StageSelect[i].pos = D3DXVECTOR2((420.0f) + (DOOR_SPACE * b), (180.0f) + (250.0f * a));
			g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);
			g_StageSelect[i].UseFlag = true;
			g_StageSelect[i].StagePieceIndex = i;
			g_StageSelect[i].StageUseFlag = false;		// true : 全ステージ開放チート	false : 通常
			g_StageSelect[i].texno = LoadTexture(g_StageSelectTextureName);
			//ドアSE
			g_StageSelectSoundNo = LoadSound(g_StageSelectSoundName);

			g_StageSelectBlack[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (175.0f) + (250.0f * a));
			g_StageSelectBlack[i].size = D3DXVECTOR2(120.0f, 150.0f);
			g_StageSelectBlack[i].texno = LoadTexture(g_StageSelect2TextureName);
			b++;
			if (i == 0)
			{
				g_StageSelect[i].StageUseFlag = true;
				g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);
			}
			// クリアステージ数分解放する
			else if (i <= g_ClearStageNum) {
				g_StageSelect[i].StageUseFlag = true;
			}
		}
		TexNo = LoadTexture(g_StageSelect2TextureName);

		OneFlag = false;
	}

	if (StageNo < 0)
	{
		ply.Position = D3DXVECTOR2(110, 180);
	}
	else {
		q = StageNo;
		ply.Position = D3DXVECTOR2(g_StageSelect[q].pos.x, g_StageSelect[q].pos.y);
	}
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
	ply.SoundRightFlag = false;
	ply.SoundLeftFlag = false;
	ply.texno = LoadTexture(g_TextureNamePly);

	ply.PaternNo = 0;//パターン番号
	ply.uv_w = PLAYER_UV_W;//横サイズ
	ply.uv_h = PLAYER_UV_H;//縦サイズ
	ply.NumPatern = 4;//横枚数

	ply.hp = 3;
	ply.frame = 0;
	ply.CoolTime = PLAYER_COOLTIME;
	ply.PieceIndex = 0;

	g_StageSelectPlayerRightSoundNo = LoadSound(g_StageSelectPlayerRightSoundName);
	g_StageSelectPlayerLeftSoundNo = LoadSound(g_StageSelectPlayerLeftSoundName);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	終了処理
//-----------------------------------------------------------------------------
void UninitStageSelect() {
	if (g_StageSelectTexture) {
		g_StageSelectTexture->Release();
		g_StageSelectTexture = NULL;

		StopSound(g_StageSelectSoundNo);
	}
}

//-----------------------------------------------------------------------------
//	更新処理
//-----------------------------------------------------------------------------
void UpdateStageSelect() {

	pStory = GetStory();

	if (!pStory->KeyUse)
	{
		if (ply.UseFlag == true)
		{
			if (ply.isGround)
			{


				//移動
				if (GetThumbLeftX(0) > 0.3f ||					// GamePad	右スティック	右
					Keyboard_IsKeyDown(KK_D))				// Keyboard	D
				{//押されているときの処理
					ply.sp.x = 3.0f;
					ply.PaternNo += 0.25f;
					if (ply.isHigh)
					{
						ply.sp.x = 2.0f;
						ply.sp.y = 5.0f;

					}

					// 向きを変える
					ply.dir = PLAYER_DIRECTION::RIGHT;
					ply.uv_w = PLAYER_UV_W;
				}
				else if (GetThumbLeftX(0) < -0.3f ||			// GamePad	右スティック	左
					Keyboard_IsKeyDown(KK_A))				// Keyboard	A
				{//押されているときの処理
					ply.sp.x = -3.0f;
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
						//ply.sp.y = 0.0f;
					}
					ply.sp.x = 0;

				}
			}
			if (STAIRS_LEFT < ply.Position.x && ply.Position.x < STAIRS_RIGHT) {
				if (GetThumbLeftY(0) < -0.3f ||		// GamePad 左スティック 下
					Keyboard_IsKeyDown(KK_S))		// keyboard S
				{

					if (ply.Position.y < SCREEN_HEIGHT - 100.0f)
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
			if (!ply.SoundRightFlag) {
				if (ply.PaternNo == 9.0f) {
					PlaySound(g_StageSelectPlayerRightSoundNo, 0);
					SetVolume(g_StageSelectPlayerRightSoundNo, 1.5f);
					ply.SoundRightFlag = true;
				}
			}
			else {
				if (ply.PaternNo != 9.0f) {
					ply.SoundRightFlag = false;
				}
			}
			if (!ply.SoundLeftFlag) {
				if (ply.PaternNo == 1.0f) {
					PlaySound(g_StageSelectPlayerLeftSoundNo, 0);
					SetVolume(g_StageSelectPlayerLeftSoundNo, 1.5f);
					ply.SoundLeftFlag = true;
				}
			}
			else {
				if (ply.PaternNo != 1.0f) {
					ply.SoundLeftFlag = false;
				}
			}

		if (ply.sp.x == 0)
		{
			ply.PaternNo = 17;

			if (ply.uv_w < 0)
			{
				ply.PaternNo = 18;

			}
		}

		ply.oldpos = ply.Position;
		ply.Position += ply.sp;

		if (ply.Position.y > SCREEN_HEIGHT)
		{
			ply.jump = false;
			ply.fall = false;
			ply.WarpFlag = false;
			//ply.isGround = true;
			ply.sp.y = 0;
			ply.frame = 0;
			ply.isHigh = false;
			ply.isGround = true;
			ply.Position = D3DXVECTOR2(30.0f, 0.0f);
		}
		if (ply.Position.x > SCREEN_WIDTH)
		{
			ply.Position.x = SCREEN_WIDTH;
		}
		if (ply.Position.x < 0)
		{
			ply.Position.x = 0;
		}


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
						if (GetThumbLeftY(0) > 0.3f ||			// GamePad 左スティック 上
							Keyboard_IsKeyDown(KK_W))			// keyboard W
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
						ply.sp.y = 5.0f;
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
					if (Keyboard_IsKeyTrigger(KK_LEFTCONTROL) ||					// keyboard Ctrl 左
						Keyboard_IsKeyTrigger(KK_C) ||								// keyboard C
						IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {					// GamePad B
						SetVolume(g_StageSelectSoundNo, 0.5f);
						PlaySound(g_StageSelectSoundNo, 0);
						StageNo = i;
						//SetScene(SCENE::SCENE_GAME);
						StartFade(FADE::FADE_OUT);
						break;
					}
				}
			}
		}
	}

		//ストーリー
		if (pStory->bUse) {
			if (CollisionBB(ply.Position, pStory->pos, ply.size, pStory->size))
			{
				if (Keyboard_IsKeyTrigger(KK_LEFTCONTROL) ||	// keyboard Ctrl 左
					Keyboard_IsKeyTrigger(KK_C)) {				// keyboard C
					if (pStory->KeyUse) pStory->KeyUse = false;
					else pStory->KeyUse = true;
				}
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {			// GamePad B
					pStory->KeyUse = true;
				}
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_A)) {			// GamePad A
					pStory->KeyUse = false;
				}
			}
		}
	
	
}

//-----------------------------------------------------------------------------
//	描画処理
//-----------------------------------------------------------------------------
void DrawStageSelect() {

	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);

	if (pStory->KeyUse) {
		color = D3DXCOLOR(0, 0, 0, 0.5);
	}
	else {
		color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	{	//背景ポリゴン表示
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBg.texno));
		SpriteDrawColorRotation(
			g_StageSelectBg.pos.x, g_StageSelectBg.pos.y, 0.5f, g_StageSelectBg.size.x, g_StageSelectBg.size.y
			, 0.0f, D3DXCOLOR(0.7f, 0.7f, 0.76f, 1.0f), 0, 1.0f, 1.0f, 1);
	}
	for (int i = 0; i < 3; i++)
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBlock[i].texno));

		SpriteDrawColorRotation(
			g_StageSelectBlock[i].pos.x, g_StageSelectBlock[i].pos.y, 0.5f, g_StageSelectBlock[i].size.x, g_StageSelectBlock[i].size.y
			, 0.0f, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), 0, 1.0f, 1.0f, 1);

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
			color,
			0,
			1.0f,
			1.0f,
			1
		);
		//g_StageSelect[i].pos.x -= 30;
	}
	if (!pStory->KeyUse)
	{
		DrawStory();
	}
	//===========================================
	// プレイヤー
	//===========================================
	if (ply.UseFlag == true)
	{
		SetWorldViewProjection2D();

		//テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ply.texno));
		//スプライトを表示
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(ply.Position.x, ply.Position.y, -0.0f, ply.size.x, ply.size.y, ply.rot, color, ply.PaternNo, ply.uv_w, ply.uv_h, ply.NumPatern);
	}

	//===========================================
	//階段
	//===========================================
	for (int i = 0; i < 12; i += 6)
	{
		SetWorldViewProjection2D();
		if (i == 0 || i == 6) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectStairsTexNo));

			SpriteDrawColorRotation(
				g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x * 2,
				g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y * 2,
				0.5f,
				g_StageSelectStairs[i].size.x * 8,
				g_StageSelectStairs[i].size.y * 8,
				0.0f,
				D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),
				0,
				1.0f,
				1.0f,
				1
			);
		}
		//else if (i == 3 || i == 9) {
		//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectStairsTexNo2));
		//	SpriteDrawColorRotation(
		//		g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x + 24.0f,
		//		g_StageSelectStairs[i].pos.y + 4.0f,
		//		0.5f,
		//		g_StageSelectStairs[i].size.x * 5,
		//		g_StageSelectStairs[i].size.y * 5,
		//		0.0f,
		//		color,
		//		0,
		//		1.0f,
		//		1.0f,
		//		1
		//	);
		//}
		//SpriteDrawColorRotation(
		//	g_StageSelectStairs[i].pos.x, g_StageSelectStairs[i].pos.y, 0.5f, g_StageSelectStairs[i].size.x * 2, g_StageSelectStairs[i].size.y * 2,
		//	0.0f, color, 0, 1.0f, 1.0f, 1);
	}


	//===========================================================
	// フェンス
	//===========================================================
	for (int i = 0; i < 24; i++)
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectfence[i].texno));
		SpriteDrawColorRotation(
			g_StageSelectfence[i].pos.x, 
			g_StageSelectfence[i].pos.y,
			0.5f,
			g_StageSelectfence[i].size.x,
			g_StageSelectfence[i].size.y,
			0.0f,
			D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f),
			0,
			1.0f,
			1.0f,
			1
		);

	}
	if (pStory->KeyUse)
	{
		DrawStory();
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

//-----------------------------------------------------------------------------
//	クリアステージ数のゲット関数
//-----------------------------------------------------------------------------
int GetClearStageNum()
{
	g_ClearStageNum = 0;
	for (STAGESELECT& ss : g_StageSelect) {
		if (ss.StageUseFlag){
			g_ClearStageNum++;
		}
	}
		return g_ClearStageNum;
}
//-----------------------------------------------------------------------------
//　クリアステージ数のセット関数
//-----------------------------------------------------------------------------
void SetClearStageNum(int num)
{
	g_ClearStageNum = num;
}

//-----------------------------------------------------------------------------
//	ステージセレクトのプレイヤーのゲット関数
//-----------------------------------------------------------------------------
PLAYER* GetSelectPlayer()
{
	return &ply;
}
