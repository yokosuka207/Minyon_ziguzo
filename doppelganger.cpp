//=============================================================================
//
//ドッペルゲンガー(反プレイヤー)処理  こいつは敵だよなぁ！？
//
//制作者/菊地空　
//=============================================================================
#pragma once

#include "doppelganger.h"

#include "player.h"
#include "main.h"
//#include "polygon.h"
#include "sprite.h"
#include "texture.h"
//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"


#include "block.h"
#include "thorn_block.h"
#include "broken.h"
#include "bullet.h"

#include "scene.h"
//#include "pause.h"
//#include "piece.h"
#include"puzzlecip.h"
#include"game.h"
#include"puzzle.h"
#include"collision.h"
#include"mouse.h"
#include"jump_stand.h"		//ジャンプ台
#include"MapChip.h"
#include"thorn_block.h"
#include "time.h"
//#include "OpenKey.h"
//#include "Key.h"
#include "warp.h"
#include "fallblock.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "MoveBlock.h"
#include "goal_key.h"
//#include "pause.h"

#include"spawnpoint.h"

#include "fade.h"
#include "result.h"

 
//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static DOPPELGANGER g_Doppel;
static char* g_TextureNameBroken = (char*)"data\\texture\\ドッペルゲンガー.png";

static Time		g_Time;

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitDoppelganger()
{
	Piece* pPiece = GetPiece();

	
	g_Doppel.Position = D3DXVECTOR2(pPiece->pos.x - 30.0f, pPiece->pos.y);
	//g_Doppel.OneOldpos = g_Doppel.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Doppel.sp = D3DXVECTOR2(0, -8);
	g_Doppel.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Doppel.Drawsize = D3DXVECTOR2(33.0f, 33.0f);
	g_Doppel.col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
	g_Doppel.rot = 180.0f;
	g_Doppel.UseFlag = true;
	g_Doppel.jump = false;
	//g_Doppel.getjump = false;
	g_Doppel.GetJumpStand = false;		//ジャンプ台用
	g_Doppel.fall = false;
	//g_Doppel.getfall = false;
	g_Doppel.WarpFlag = false;
	g_Doppel.isGround = true;
	g_Doppel.isSheerFloors = false;
	g_Doppel.isSheerFloorsUse = false;
	g_Doppel.isHigh = false;
	g_Doppel.isMoveBlock = false;
	g_Doppel.texno = LoadTexture(g_TextureNameBroken);

	g_Doppel.PaternNo = 0;//パターン番号
	g_Doppel.uv_w = DOPPELGANGER_UV_W;//横サイズ
	g_Doppel.uv_h = DOPPELGANGER_UV_H;//縦サイズ
	g_Doppel.NumPatern = 4;//横枚数


	g_Doppel.frame = 0;
	g_Doppel.CoolTime = PLAYER_COOLTIME;
	g_Doppel.PieceIndex = 0;


	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitDoppelganger()
{

}

//=============================================================================
//更新処理
//=============================================================================

//ドッペルゲンガー 以下 反プレイヤー  と称す

void UpdateDoppelganger()
{	
	MOUSE* pMouse = GetMouse();
	if (!pMouse->UseFlag)
	{
		PLAYER* pPlayer = GetPlayer();
		//-------------------------------------------------
		//プレイヤーと反プレイヤーの移動処理
		//-------------------------------------------------

		if (pPlayer->UseFlag == true)
		{
			g_Doppel.sp.x = pPlayer->sp.x * -1;
			
			//pDoppel->sp == pPlayer->sp;
			//pDoppel->Position = pPlayer->Position;

			g_Doppel.UseFlag = true;

			if (g_Doppel.UseFlag == true)
			{


				//移動
				if (pPlayer->dir == PLAYER_DIRECTION::RIGHT)
				{
					//プレイヤーの速度がプラスされたら反プレイヤーも右に移動

					//g_Doppel.Position.x += g_Doppel.sp.x;
					if (g_Doppel.sp.x != 0) {
						g_Doppel.PaternNo += 0.25f;
					}


					// 向きを変える
					g_Doppel.dir = DOPPELGANGER_DIRECTION::RIGHT;
					g_Doppel.uv_w = -DOPPELGANGER_UV_W;
				}
				else if (pPlayer->dir == PLAYER_DIRECTION::LEFT)
				{
					//プレイヤーの速度がプラスされたら反プレイヤーも左に移動
					//g_Doppel.Position.x += g_Doppel.sp.x;
					if (g_Doppel.sp.x != 0) {
						g_Doppel.PaternNo += 0.25f;
					}


					// 向きを変える
					g_Doppel.dir = DOPPELGANGER_DIRECTION::LEFT;
					g_Doppel.uv_w = DOPPELGANGER_UV_W;
				}
				else
				{
					g_Doppel.sp.x = 0;
				}
				//fuck
				// アニメーションパターン番号を0～15の範囲内にする
				if (g_Doppel.PaternNo >= 16) { g_Doppel.PaternNo = 0; }
				//if (g_Doppel.PaternNo < 0) { g_Doppel.PaternNo = -17; }


				//ドッペルゲンガー弾発射
				//SetBullet(g_Doppel.Position, D3DXVECTOR2(BULLET_SIZE_H, BULLET_SIZE_W), 1);

			//}



			//-------------------
			//基本ブロックの場合
			//-------------------
				BLOCK* block = GetChipBlock();

				for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
					if (block[i].UseFlag)
					{
						// プレイヤーの下にブロックがあったら
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
						{	// 着地中にする
							if (!g_Doppel.isGround) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isGround = true;
								g_Doppel.PieceIndex = block[i].PieceIndex;
								break;
							}
						}
						else {
							g_Doppel.isGround = false;
						}
					}
				}

				//---------------
				//透ける床の場合
				//---------------
				SHEERFLOORS* pSheerFloors = GetSheerFloors();
				for (int i = 0; i < SHEERFLOORS_NUM; i++)
				{
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Doppel.size.x / 2;
					}
					//反プレイヤー右・ブロック左
					if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
						g_Doppel.Position.y - g_Doppel.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Doppel.size.x / 2;
					}

					////反プレイヤー上・ブロック下,着地する

					if ((g_Doppel.oldpos.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
						CollisionBB(g_Doppel.Position, pSheerFloors[i].pos, g_Doppel.size, pSheerFloors[i].size))
					{
						g_Doppel.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Doppel.size.y / 2);
						g_Doppel.sp.y = 0.0f;
						//p_JumpStand->JumpStandFlag = false;

						g_Doppel.isSheerFloors = true;
						g_Doppel.sp.y = 0.0f;


					}


					//反プレイヤー下・ブロック上,落下する
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
						g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
					{

					}
				}

				for (int i = 0; i < SHEERFLOORS_NUM; i++)
				{
					if (!GetThumbLeftY(0) < 0.3f ||					// GamePad	左スティック	下
						!Keyboard_IsKeyDown(KK_DOWN))				// Keyboard	下
					{
						// 反プレイヤーの下にブロックがあったら
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f > pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2))
						{	// 着地中にする
							//g_Doppel.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 - g_Doppel.size.y / 2 - 0.02f;

							if (!g_Doppel.isSheerFloors) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isSheerFloors = true;
								break;
							}
						}
						else {
							g_Doppel.isSheerFloors = false;
						}
					}
				}

				if (GetThumbLeftY(0) < -0.3f ||			// GamePad	左スティック	下
					Keyboard_IsKeyDown(KK_DOWN))		// Keyboard	下
				{
					g_Doppel.isSheerFloors = false;
				}

				// ジャンプ
				if ((g_Doppel.isGround || g_Doppel.isSheerFloors || g_Doppel.isHigh || g_Doppel.isMoveBlock) && g_Doppel.sp.y <=0 && Keyboard_IsKeyDown(KK_SPACE))//&& Keyboard_IsKeyDown(KK_SPACE
				{

					g_Doppel.sp.y = 2.5f;			// スピードのyをマイナスにする

					if (g_Doppel.isGround) {
						g_Doppel.isGround = false;			// フラグをジャンプ中にする
					}
					if (g_Doppel.isSheerFloors) {
						g_Doppel.isSheerFloors = false;			// フラグをジャンプ中にする
					}
					if (g_Doppel.isHigh) {
						g_Doppel.isHigh = false;			// フラグをジャンプ中にする
					}
					if (g_Doppel.isMoveBlock) {
						g_Doppel.isMoveBlock = false;
					}
				}

				// 空中
				if (!g_Doppel.isGround && !g_Doppel.isSheerFloors && !g_Doppel.isMoveBlock) {
					g_Doppel.sp.y -= 0.1f;			// スピードのyを増やす
				}

				//反映
				g_Doppel.oldpos = g_Doppel.Position;
				g_Doppel.Position += g_Doppel.sp;


				//反プレイヤーとチップブロック 当たり判定
				{
					for (int i = 0; i < BLOCK_MAX; i++)
					{
						BLOCK* block = GetBlock();
						BLOCK* cipblock = GetChipBlock();

						if ((cipblock + i)->UseFlag == true)
						{
							//プレイヤー左・ブロック右
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 - g_Doppel.size.x / 2;
							}
							//プレイヤー右・ブロック左
							if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 3 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 3 &&
								g_Doppel.Position.y - g_Doppel.size.y / 3 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 3)
							{
								g_Doppel.Position.x = (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 + g_Doppel.size.x / 2;
							}

							//プレイヤー上・ブロック下,着地する
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
								g_Doppel.jump = false;
								g_Doppel.fall = false;
								//g_Doppel.WarpFlag = false;
								//g_Doppel.isGround = true;
								g_Doppel.sp.y = 0;
								g_Doppel.frame = 0;
							}
							//プレイヤー下・ブロック上,落下する
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2)
							{
								g_Doppel.fall = true;
								g_Doppel.getfall = true;
								g_Doppel.frame = 50;
							}
						}
					}
				}



				//----------------
				//ジャンプ台の場合
				//----------------
				JUMPSTAND* p_JumpStand = GetJumpStand();

				for (int i = 0; i < JUMPSTAND_MAX; i++) {
					if (p_JumpStand[i].UseJumpStand) {
						if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad	B
							Keyboard_IsKeyDown(KK_B))						// Keyboard	B
						{
							if (CollisionBB(g_Doppel.Position, p_JumpStand[i].pos, g_Doppel.size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
								p_JumpStand[i].GetJumpStand = true;
							}
						}
						else
						{
							p_JumpStand[i].GetJumpStand = false;
						}
					}
				}

				////反プレイヤー・動くブロック 当たり判定
				{
					MOVEBLOCK* pMoveBlock = GetMoveBlock();

					for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
						if (pMoveBlock[i].bUse)
						{
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
								g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
							{
								pMoveBlock[i].sp = g_Doppel.sp;
								pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;

							}
							if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
								g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
							{
								pMoveBlock[i].sp = g_Doppel.sp;
								pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
							}
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
								g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
							{
								g_Doppel.Position.y = pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 - g_Doppel.size.y / 2;
								// 着地中にする
								if (!g_Doppel.isMoveBlock) {
									g_Doppel.sp.y = 0.0f;
									g_Doppel.isMoveBlock = true;
									break;
								}
							}
							else {
								g_Doppel.isMoveBlock = false;
							}
							//プレイヤー下・ブロック上,落下する
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
							{
								pMoveBlock[i].sp = g_Doppel.sp;
								pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
							}
						}
					}
				}


				//========================================================================
				//プレイヤー・ワープ　当たり判定(PlayerとWarpの当たり判定)
				//=========================================================================

				g_Doppel.CoolTime--;

				if (g_Doppel.CoolTime < 0)
				{
					g_Doppel.CoolTime = 0;

					//プレイヤー・ワープ　当たり判定
					for (int i = 0; i < BLOCK_MAX; i++)
					{
						WARP* warp = GetWarp();
						if ((warp + i)->UseFlag == true)
						{
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
							{
								if (i % 2 == 0)
								{
									if (!g_Doppel.WarpFlag)
									{
										g_Doppel.Position = (warp + i + 1)->Position;
										g_Doppel.CoolTime = PLAYER_COOLTIME;
										g_Doppel.WarpFlag = true;
									}

								}
								else if (i % 2 == 1)
								{
									if (!g_Doppel.WarpFlag)
									{
										g_Doppel.Position = (warp + i - 1)->Position;
										g_Doppel.CoolTime = PLAYER_COOLTIME;

										g_Doppel.WarpFlag = true;

									}
								}
							}
						}
					}
				}



				////トゲ・反プレイヤー  当たり判定
				{
					for (int i = 0; i < THORN_BLOCK_MAX; i++) {

						THORNBLOCK* pThornBlock = GetThornBlock();


						if (pThornBlock[i].UseFlag) {

							if (CollisionBB(pThornBlock[i].Postion, g_Doppel.Position, pThornBlock[i].Size, g_Doppel.size))
							{
								//GKey* pGkey = GetGKey();

								g_Doppel.UseFlag = false;

								/*pGKey->UseFlag = false;
								pGKey->GetGKey = true;*/

							}

						}
					}
				}

				//プレイヤーが落下死したら
				if (pPlayer->Position.y - pPlayer->size.y > SCREEN_HEIGHT)
				{
					g_Doppel.UseFlag = false;
				}



				//落ちるブロック　当たり判定 
				{
					for (int i = 0; i < FALLBLOCK_MAX; i++)
					{
						FALLBLOCK* FallBlock = GetFallBlock();
						if ((FallBlock + i)->UseFlag == true)
						{
							//プレイヤー左・ブロック右判定
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 - g_Doppel.size.x / 2;
							}
							//プレイヤー右・落ちるブロック左
							if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 + g_Doppel.size.x / 2;
							}
							//プレイヤー上・落ちるブロック下
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
								g_Doppel.getfall = false;
								g_Doppel.fall = false;
								g_Doppel.frame = 50;
								(FallBlock + i)->Position.y++;
							}
							//プレイヤー下・落ちるブロック
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
							}
						}
					}
				}

				//========================================================================
				//プレイヤー・壊れるブロック　当たり判定(PlayerとBrokenBlockの当たり判定)
				//=========================================================================

				for (int i = 0; i < BROKEN_MAX; i++)
				{

					BROKEN* pBroken = GetBroken();

					if ((pBroken + i)->UseFlag == true)
					{
						//プレイヤー左・壊れるブロック右
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							pPlayer->Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - pPlayer->size.x / 2;
						}
						//プレイヤー右・壊れるブロック左
						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + pPlayer->size.x / 2;
						}

						//プレイヤー上・壊れるブロック下
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							g_Doppel.Position.y = (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 - pPlayer->size.y / 2;
							g_Doppel.jump = false;
							g_Doppel.fall = false;
							g_Doppel.frame = 0;
						}
						//プレイヤー下・壊れるブロック上,壊れる
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
						{
							(pBroken + i)->UseFlag = false;
							g_Doppel.fall = true;
							g_Doppel.getfall = true;
							g_Doppel.frame = 50;
						}
					}
				}

				//====================================================================
				//プレイヤーと高所落下ブロックの当たり判定(PlayerとHighの当たり判定)
				//====================================================================

				for (int i = 0; i < HIGH_MAX; i++)
				{

					HIGH* pHigh = GetHigh();

					if ((pHigh + i)->UseFlag == true)
					{
						//プレイヤー左・高所落ちるブロック右
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - g_Doppel.size.x / 2;
						}
						//プレイヤー右・高所落ちるブロック左
						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + g_Doppel.size.x / 2;
						}

						//プレイヤー上・高所落ちるブロック下
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							if (g_Doppel.sp.y >= -10.0f)
							{
								//pPlayer->isHigh = false;
								(pHigh + i)->UseFlag = false;
								g_Doppel.frame = 50;
							}
							else
							{
								//pPlayer->isHigh = true;
								g_Doppel.sp.y = 0.0f;
								g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
							}

						}

						//プレイヤー下・高所落ちるブロック上,
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
						}

						// プレイヤーの下にブロックがあったら
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
						{	// 着地中にする
							if (!g_Doppel.isHigh) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isHigh = true;
								break;
							}
						}
						else {
							g_Doppel.isHigh = false;
						}
					}
				}


				////------------------------------------
				////ドッペルゲンガー弾用当たり判定
				////------------------------------------
				//	//DOPPELGANGER* pDoppel = GetDoppelganger();
				//	BULLET* pBullet = GetBullet();
				//	

				//	if (g_Doppel.UseFlag == true)
				//	{
				//		pBullet->use = true;

				//		if (pBullet->use == true)
				//		{
				//			if (pPlayer->UseFlag)
				//			{
				//				bool hit = CollisionBB(pBullet->pos, pPlayer->Position, D3DXVECTOR2(pBullet->w, pBullet->h), D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H));

				//				if (hit == true)//当たっている
				//				{
				//					if (pBullet->hit)
				//					{
				//						pPlayer->hp - (pBullet->Damage);
				//						if (pPlayer->hp <= 0)
				//						{
				//							pPlayer->UseFlag = false;
				//							StartFade(FADE::FADE_OUT);
				//							SetResultType(LOSE);
				//							/*pTime->EndTime();
				//							pTimeParam->EndFlag = true;*/
				//						}

				//					}
				//				}
				//				else//当っていない
				//				{

				//				}
				//			}
				//		}
				//	}


				Piece* pPiece = GetPiece();
				SpawnPoint* pSpawnPoint = GetSpawnPoint();

				for (int i = 0; i < PUZZLE_MAX; i++)
				{
					if (pPiece[i].UseFlag)
					{
						bool hitflag = CollisionBB(g_Doppel.Position, pPiece[i].pos, g_Doppel.size, pPiece[i].size);

						if (hitflag)
						{
							if (g_Doppel.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, DOWN);

								if (!hitflag2)
								{
									g_Doppel.sp.y -= 0.2;//加速
								}
								else
								{//下に何もなく死亡する場合
									for (int i = 0; i < SPAWN_POINT_MAX; i++)
									{
										if (pSpawnPoint[i].UseFlag)
										{
											if (g_Doppel.PieceIndex == pSpawnPoint[i].PieceIndex)
											{
												g_Doppel.Position = pSpawnPoint[i].Position;

											}


										}
									}

								}
							}
							else if (g_Doppel.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
							{

								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, RIGHT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{
									g_Doppel.Position.x = g_Doppel.oldpos.x;
								}


							}
							else if (g_Doppel.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, LEFT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{
									g_Doppel.Position.x = g_Doppel.oldpos.x;
								}


							}
							else if (g_Doppel.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, UP);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{

									g_Doppel.fall = true;
									//g_Player.sp.y = 0;
									//g_Player.getfall = true;
									g_Doppel.frame = 50;
									//g_Player.sp.y += 0.2;//加速
								}

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
void DrawDoppelganger()
{
	if (g_Doppel.UseFlag == true)
	{
		//テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Doppel.texno));
		//スプライトを表示
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Doppel.Position.x, g_Doppel.Position.y, -0.2f, g_Doppel.Drawsize.x, g_Doppel.Drawsize.y, g_Doppel.rot, g_Doppel.col, g_Doppel.PaternNo, g_Doppel.uv_w *-1, g_Doppel.uv_h, g_Doppel.NumPatern);
	}
}

void SetDoppelGanger(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	if (!g_Doppel.UseFlag)
	{
		g_Doppel.Position = pos;
		g_Doppel.size = size;
		g_Doppel.PieceIndex = index;
		g_Doppel.UseFlag = true;
	}
}
void DeleteDoppelGanger(int index) {
	if (g_Doppel.UseFlag && g_Doppel.PieceIndex == index) {
		g_Doppel.UseFlag = false;
	}
}