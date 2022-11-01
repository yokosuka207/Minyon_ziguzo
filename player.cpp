//=============================================================================
//
//プレイヤー処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//合体製作者：新保翔麻	制作更新日2022/10/24
//=============================================================================
#pragma once

#include "player.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "block.h"
#include "broken.h"
#include "warp.h"
//#include "piece.h"
#include"puzzlecip.h"
#include"game.h"
#include"puzzle.h"
#include"collision.h"
#include"mouse.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static PLAYER g_Player;
static char* g_TextureNameBroken = (char*)"data\\texture\\runningman001.png";



//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitPlayer()
{
	//プレイヤーの初期化
	g_Player.Position = D3DXVECTOR2(300.0f, 200.0f);
	g_Player.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Player.sp = D3DXVECTOR2(0,8);
	g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Player.col = D3DXCOLOR(0.0f, 1.0f, 0.0, 1.0f);
	g_Player.rot = 0.0f;
	g_Player.UseFlag = true;
	g_Player.jump = false;
	g_Player.getjump = false;
	g_Player.fall = false;
	g_Player.getfall = false;
	g_Player.WarpFlag = false;
	g_Player.texno = LoadTexture(g_TextureNameBroken);

	g_Player.PaternNo = 0;//パターン番号
	g_Player.uv_w = 1.0f / 5;//横サイズ
	g_Player.uv_h = 1.0f / 2;//縦サイズ
	g_Player.NumPatern = 5;//横枚数

	g_Player.hp = 30;
	g_Player.frame = 0;
	g_Player.CoolTime = PLAYER_COOLTIME;

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitPlayer()
{

}

//=============================================================================
//更新処理
//=============================================================================
void UpdatePlayer()
{
	MOUSE* pMouse = GetMouse();
	if (!pMouse->UseFlag)
	{


		if (g_Player.UseFlag == true)
		{





			//移動
			if (GetKeyboardPress(DIK_RIGHT))//右キー
			{//押されているときの処理
				g_Player.sp.x = 3.0f;
				g_Player.PaternNo++;
			}
			else if (GetKeyboardPress(DIK_LEFT))//左キー
			{//押されているときの処理
				g_Player.sp.x = -3.0f;
				g_Player.PaternNo++;
			}
			else
			{
				g_Player.sp.x = 0;

			}





			//ジャンプ
			g_Player.frame++;
			if (g_Player.jump == false && GetKeyboardPress(DIK_SPACE))
			{
				g_Player.jump = true;
				g_Player.getjump = true;
			}
			if (g_Player.jump == true && g_Player.frame < 50)
			{
				if (g_Player.getjump == true)//押した瞬間
				{
					g_Player.sp.y = -4.2f;
					g_Player.getjump = false;
				}
				else if (g_Player.sp.y <= 0)//減速
				{
					g_Player.sp.y += 0.1f;
				}
				else
				{
					//g_Player.sp.y = 0;//停止
				}
			}




			//落下
			if (g_Player.fall == false && g_Player.Position.y > g_Player.oldpos.y)
			{
				g_Player.fall = true;
				g_Player.getfall = true;
			}
			if (g_Player.fall == true)
			{
				if (g_Player.getfall == true)//落ちた瞬間
				{
					g_Player.sp.y = 0;
					g_Player.getfall = false;
				}
				else if (g_Player.sp.y <= 8)//落下,ジャンプした場合は50フレーム後から落下
				{
					g_Player.sp.y += 0.2;//加速
				}
				else
				{
					g_Player.sp.y = 8;//最大落下速度
				}
			}








			//反映
			g_Player.oldpos = g_Player.Position;
			g_Player.Position += g_Player.sp;









			//プレイヤー・ブロック　当たり判定
			for (int i = 0; i < BLOCK_MAX; i++)
			{
				BLOCK* block = GetBlock();

				if ((block + i)->UseFlag == true)
				{
					//プレイヤー左・ブロック右
					if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= (block + i)->Position.x - (block + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2)
					{
						g_Player.Position.x = (block + i)->Position.x - (block + i)->Size.x / 2 - g_Player.size.x / 2;
					}
					//プレイヤー右・ブロック左
					if (g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= (block + i)->Position.x + (block + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2)
					{
						g_Player.Position.x = (block + i)->Position.x + (block + i)->Size.x / 2 + g_Player.size.x / 2;
					}

					//プレイヤー上・ブロック下,着地する
					if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (block + i)->Position.y - (block + i)->Size.y / 2 &&
						g_Player.oldpos.y + g_Player.size.y / 2 <= (block + i)->Position.y - (block + i)->Size.y / 2)
					{
						g_Player.Position.y = (block + i)->Position.y - (block + i)->Size.y / 2 - g_Player.size.y / 2;
						g_Player.jump = false;
						g_Player.fall = false;
						g_Player.WarpFlag = false;
						g_Player.frame = 0;
					}
					//プレイヤー下・ブロック上,落下する
					if (g_Player.Position.x + g_Player.size.x / 2 > (block + i)->Position.x - (block + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (block + i)->Position.x + (block + i)->Size.x / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (block + i)->Position.y + (block + i)->Size.y / 2 &&
						g_Player.oldpos.y - g_Player.size.y / 2 >= (block + i)->Position.y + (block + i)->Size.y / 2)
					{
						g_Player.fall = true;
						g_Player.getfall = true;
						g_Player.frame = 50;
					}
				}
			}





			//プレイヤー・壊れるブロック　当たり判定
			for (int i = 0; i < BLOCK_MAX; i++)
			{
				BROKEN* broken = GetBroken();
				if ((broken + i)->UseFlag == true)
				{
					//プレイヤー左・壊れるブロック右
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						g_Player.Position.x = (broken + i)->Postion.x - (broken + i)->Size.x / 2 - g_Player.size.x / 2;
					}
					//プレイヤー右・壊れるブロック左
					if (g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						g_Player.Position.x = (broken + i)->Postion.x + (broken + i)->Size.x / 2 + g_Player.size.x / 2;
					}

					//プレイヤー上・壊れるブロック下
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
						g_Player.oldpos.y + g_Player.size.y / 2 <= (broken + i)->Postion.y - (broken + i)->Size.y / 2)
					{
						g_Player.Position.y = (broken + i)->Postion.y - (broken + i)->Size.y / 2 - g_Player.size.y / 2;
						g_Player.jump = false;
						g_Player.fall = false;
						g_Player.frame = 0;
					}
					//プレイヤー下・壊れるブロック上,壊れる
					if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
						g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2 &&
						g_Player.oldpos.y - g_Player.size.y / 2 >= (broken + i)->Postion.y + (broken + i)->Size.y / 2)
					{
						(broken + i)->UseFlag = false;
						g_Player.fall = true;
						g_Player.getfall = true;
						g_Player.frame = 50;
					}
				}
			}



			g_Player.CoolTime--;

			if (g_Player.CoolTime < 0)
			{
				g_Player.CoolTime = 0;

				//プレイヤー・ワープ　当たり判定
				for (int i = 0; i < BLOCK_MAX; i++)
				{
					WARP* warp = GetWarp();
					if ((warp + i)->UseFlag == true)
					{
						if (g_Player.Position.x + g_Player.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
							g_Player.Position.x - g_Player.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
							g_Player.Position.y + g_Player.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
						{
							if (i % 2 == 0)
							{
								if (!g_Player.WarpFlag)
								{
									g_Player.Position = (warp + i + 1)->Position;
									g_Player.CoolTime = PLAYER_COOLTIME;
									g_Player.WarpFlag = true;
								}

							}
							else if (i % 2 == 1)
							{
								if (!g_Player.WarpFlag)
								{
									g_Player.Position = (warp + i - 1)->Position;
									g_Player.CoolTime = PLAYER_COOLTIME;

									g_Player.WarpFlag = true;

								}
							}
						}
					}
				}
			}



			if (GetKeyboardTrigger(DIK_R))	//aキーが押されたら
			{
				ResetGame();
			}

			//プレイヤーとパズルの画面外判定

			PUZZLE* pPuzzle = GetPuzzle();

			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				if (pPuzzle[i].UseFlag)
				{
					bool hitflag = CollisionBB(g_Player.Position, pPuzzle[i].Position, g_Player.size, pPuzzle[i].Size);

					if (hitflag)
					{
						if (g_Player.Position.y < pPuzzle[i].Position.y - PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPuzzleOpen(pPuzzle[i], i, UP);

							if (!hitflag2)
							{
								g_Player.sp.y += 0.2;//加速
							}
							else
							{
								g_Player.fall = true;
								g_Player.sp.y = 0;
								//g_Player.getfall = true;
								g_Player.frame = 50;
								//g_Player.sp.y += 0.2;//加速
							}
						}
						if (g_Player.Position.x >= pPuzzle[i].Position.x + PUZZLE_WIDHT / 2)
						{

							bool hitflag2 = PlayerPuzzleOpen(pPuzzle[i], i, RIGHT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//加速
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						if (g_Player.Position.x <= pPuzzle[i].Position.x - PUZZLE_WIDHT / 2)
						{

							bool hitflag2 = PlayerPuzzleOpen(pPuzzle[i], i, LEFT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//加速
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}

					}
				}


			}


		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void DrawPlayer()
{
	if (g_Player.UseFlag == true)
	{
		//テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.texno));
		//スプライトを表示
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Player.Position.x, g_Player.Position.y, g_Player.size.x, g_Player.size.y, g_Player.rot, g_Player.col, g_Player.PaternNo, g_Player.uv_w, g_Player.uv_h, g_Player.NumPatern);
	}
}

//=============================================================================
//ゲット関数
//=============================================================================
PLAYER* GetPlayer()
{
	return &g_Player;
}