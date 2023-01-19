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
//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"

#include "block.h"
//#include "thorn_block.h"
#include "broken.h"
#include "warp.h"
#include "scene.h"
#include "pause.h"
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
#include "OpenKey.h"
#include "Key.h"
#include "fallblock.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "MoveBlock.h"
#include "goal_key.h"
#include "pause.h"
#include "goal_key.h"
#include"spawnpoint.h"
#include"cursor.h"
#include "sound.h"
#include "start.h"
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
static char* g_TextureNameBroken = (char*)"data\\texture\\プレイヤー.png";

static int g_PlayerSoundNo = 0;
static char g_PlayerSoundName[] = "data\\SoundData\\SE\\革靴で歩く.wav";

static Time		g_Time;

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitPlayer()
{
	Piece* pPiece = GetPiece();
	START* pStart = GetStart();
	//プレイヤーの初期化
	//g_Player.Position = D3DXVECTOR2(pPiece->pos.x+30.0f,pPiece->pos.y);
	g_Player.Position = D3DXVECTOR2(pStart[0].pos.x, pStart[0].pos.y);
	g_Player.OneOldpos = g_Player.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Player.sp = D3DXVECTOR2(0,-8);
	g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Player.Drawsize = D3DXVECTOR2(33.0f, 33.0f);
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
	g_Player.rot = 180.0f;
	g_Player.UseFlag = true;
	g_Player.jump = false;
	//g_Player.getjump = false;
	//g_Player.GetJumpStand = false;		//ジャンプ台用
	g_Player.fall = false;
	//g_Player.getfall = false;
	//g_Player.WarpFlag = false;
	g_Player.isGround = true;
	g_Player.isSheerFloors = false;
	g_Player.isSheerFloorsUse = false;
	//g_Player.isHigh = false;
	g_Player.isMoveBlock = false;
	g_Player.texno = LoadTexture(g_TextureNameBroken);

	g_Player.PaternNo = 0;//パターン番号
	g_Player.uv_w = PLAYER_UV_W;//横サイズ
	g_Player.uv_h = PLAYER_UV_H;//縦サイズ
	g_Player.NumPatern = 4;//横枚数

	g_Player.hp = 3;
	g_Player.frame = 0;
	g_Player.CoolTime = PLAYER_COOLTIME;
	g_Player.PieceIndex = 0;

	g_PlayerSoundNo = LoadSound(g_PlayerSoundName);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitPlayer()
{
	StopSound(g_PlayerSoundNo);
}

//=============================================================================
//更新処理
//=============================================================================
void UpdatePlayer()
{	//-------------------------------------------------
	//プレイヤーが関与している状態のギミックとの処理
	//-------------------------------------------------

	MOUSE* pMouse = GetMouse();
	if (!Mouse_IsLeftDown())
	{

		if (g_Player.UseFlag == true)
		{
			//移動
			if (GetThumbLeftX(0) > 0.3f ||					// GamePad	右スティック	右
				Keyboard_IsKeyDown(KK_RIGHT))				// Keyboard	右
			{//押されているときの処理
				g_Player.sp.x = 1.3f;
				g_Player.PaternNo -= 0.25f;

				// 向きを変える
				g_Player.dir = PLAYER_DIRECTION::RIGHT;
				g_Player.uv_w = -PLAYER_UV_W;
			}
			else if (GetThumbLeftX(0) < -0.3f ||			// GamePad	右スティック	左
				Keyboard_IsKeyDown(KK_LEFT))				// Keyboard	左
			{//押されているときの処理
				g_Player.sp.x = -1.3f;
				g_Player.PaternNo += 0.25f;

				// 向きを変える
				g_Player.dir = PLAYER_DIRECTION::LEFT;
				g_Player.uv_w = PLAYER_UV_W;
			}
			else
			{
				g_Player.sp.x = 0;
			}
			//fuck
			// アニメーションパターン番号を0～15の範囲内にする
			if (g_Player.PaternNo >= 15) { g_Player.PaternNo -= 15; }
			if (g_Player.PaternNo < 0) { g_Player.PaternNo += 15; }
			if (g_Player.PaternNo == 4.0f || g_Player.PaternNo == 12.0f) {
				PlaySound(g_PlayerSoundNo, 0);
				SetVolume(g_PlayerSoundNo, 0.5f);
			}

			if (g_Player.sp.x == 0)
			{
				g_Player.PaternNo = 17;

				if (g_Player.uv_w < 0)
				{
					g_Player.PaternNo = 18;

				}
			}
			if (g_Player.sp.y != 0)
			{
				g_Player.PaternNo = 16;
				if (g_Player.uv_w < 0)
				{
					g_Player.PaternNo = 19;

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
						if (CollisionBB(g_Player.Position, p_JumpStand[i].pos, g_Player.size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
							p_JumpStand[i].GetJumpStand = true;
						}
					}
					else
					{
						p_JumpStand[i].GetJumpStand = false;
					}
				}
			}

			//-------------
			//動く台の場合
			//-------------
			MOVEBLOCK* pMoveBlock = GetMoveBlock();

			for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
				if (pMoveBlock[i].bUse) {
					if (Keyboard_IsKeyDown(KK_N))
					{
						if (CollisionBB(g_Player.Position, pMoveBlock[i].pos, g_Player.size, pMoveBlock[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
							pMoveBlock[i].GetMoveBlock = true;
						}
					}
					else
					{
						pMoveBlock[i].GetMoveBlock = false;
					}
				}
			}

			//-------------------
			//基本ブロックの場合
			//-------------------
			BLOCK* block = GetChipBlock();
			SpawnPoint* pSpawnPoint = GetSpawnPoint();
			for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
				if (block[i].UseFlag)
				{
					// プレイヤーの下にブロックがあったら
					if ((g_Player.Position.y - g_Player.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
						(g_Player.Position.y + g_Player.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
						(g_Player.Position.x + g_Player.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
						(g_Player.Position.x - g_Player.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
					{	// 着地中にする
						if (!g_Player.isGround) {
							g_Player.sp.y = 0.0f;
							g_Player.isGround = true;
							g_Player.PieceIndex = block[i].PieceIndex;
							break;
						}
					}
					else {
						g_Player.isGround = false;
					}
				}
			}

			//---------------
			//透ける床の場合
			//---------------
			SHEERFLOORS* pSheerFloors = GetSheerFloors();
			for (int i = 0; i < SHEERFLOORS_NUM; i++)
			{
				if (g_Player.Position.x + g_Player.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
					g_Player.oldpos.x + g_Player.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
					g_Player.Position.y + g_Player.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
					g_Player.Position.y - g_Player.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
				{
					//g_Player.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Player.size.x / 2;
				}
				//プレイヤー右・ブロック左
				if (g_Player.Position.x - g_Player.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
					g_Player.oldpos.x - g_Player.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
					g_Player.Position.y + g_Player.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
					g_Player.Position.y - g_Player.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
				{
					//g_Player.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Player.size.x / 2;
				}

				//プレイヤー上・ブロック下,着地する
				if (!GetThumbLeftY(0) < -0.3f ||		// GamePad	左スティック	下
					!Keyboard_IsKeyDown(KK_DOWN))		// Keyboard 下
				{
					if ((g_Player.oldpos.y + g_Player.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
						CollisionBB(g_Player.Position, pSheerFloors[i].pos, g_Player.size, pSheerFloors[i].size))
					{
						g_Player.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Player.size.y / 2);
						g_Player.sp.y = 0.0f;
						p_JumpStand->JumpStandFlag = false;

						g_Player.isSheerFloors = true;
						g_Player.sp.y = 0.0f;


					}


				}
				//プレイヤー下・ブロック上,落下する
				if (g_Player.Position.x + g_Player.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
					g_Player.Position.x - g_Player.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
					g_Player.Position.y - g_Player.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
					g_Player.oldpos.y - g_Player.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
				{

				}
			}

			for (int i = 0; i < SHEERFLOORS_NUM; i++)
			{
				if (!GetThumbLeftY(0) < 0.3f ||					// GamePad	左スティック	下
					!Keyboard_IsKeyDown(KK_DOWN))				// Keyboard	下
				{
					// プレイヤーの下にブロックがあったら
					if ((g_Player.Position.y - g_Player.size.y / 2 - 0.05f > pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2) &&
						(g_Player.Position.y + g_Player.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
						(g_Player.Position.x + g_Player.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2) &&
						(g_Player.Position.x - g_Player.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2))
					{	// 着地中にする
						//g_Player.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 - g_Player.size.y / 2 - 0.02f;

						if (!g_Player.isSheerFloors) {
							g_Player.sp.y = 0.0f;
							g_Player.isSheerFloors = true;
							break;
						}
					}
					else {
						g_Player.isSheerFloors = false;
					}
				}
			}

			if (GetThumbLeftY(0) < -0.3f ||			// GamePad	左スティック	下
				Keyboard_IsKeyDown(KK_DOWN))		// Keyboard	下
			{
				g_Player.isSheerFloors = false;
			}

			// ジャンプ
			if ((g_Player.isGround || g_Player.isSheerFloors || g_Player.isHigh || g_Player.isMoveBlock) && g_Player.sp.y <= 0 && Keyboard_IsKeyDown(KK_SPACE))
			{

				g_Player.sp.y = 2.5f;			// スピードのyをマイナスにする

				if (g_Player.isGround) {
					g_Player.isGround = false;			// フラグをジャンプ中にする
				}
				if (g_Player.isSheerFloors) {
					g_Player.isSheerFloors = false;			// フラグをジャンプ中にする
				}
				if (g_Player.isHigh) {
					g_Player.isHigh = false;			// フラグをジャンプ中にする
				}
				if (g_Player.isMoveBlock) {
					g_Player.isMoveBlock = false;
				}
			}

			// 空中
			if (!g_Player.isGround && !g_Player.isHigh && !g_Player.isSheerFloors && !g_Player.isMoveBlock) {
				g_Player.sp.y -= 0.1f;			// スピードのyを増やす
			}
			{
				//{
				//	//ジャンプ
				//	g_Player.frame++;
				//	if (g_Player.jump == false && GetKeyboardPress(DIK_SPACE))
				//	{
				//		g_Player.jump = true;
				//		g_Player.getjump = true;
				//	}
				//	if (g_Player.jump == true && g_Player.frame < 50)
				//	{
				//		if (g_Player.getjump == true)//押した瞬間
				//		{
				//			g_Player.sp.y = -2.0f;
				//			g_Player.getjump = false;
				//		}
				//		else if (g_Player.sp.y <= 0)//減速
				//		{
				//			g_Player.sp.y += 0.1f;
				//		}
				//		else
				//		{
				//			//g_Player.sp.y = 0;//停止
				//		}
				//	}
				//	//落下
				//	if (g_Player.fall == false && g_Player.Position.y > g_Player.oldpos.y)
				//	{
				//		g_Player.fall = true;
				//		g_Player.getfall = true;
				//	}
				//	if (g_Player.fall == true)
				//	{
				//		if (g_Player.getfall == true)//落ちた瞬間
				//		{
				//			g_Player.sp.y = 0;
				//			g_Player.getfall = false;
				//		}
				//		else if (g_Player.sp.y <= 8)//落下,ジャンプした場合は50フレーム後から落下
				//		{
				//			g_Player.sp.y += 0.2;//加速
				//		}
				//		else
				//		{
				//			g_Player.sp.y = 8;//最大落下速度
				//		}
				//		g_Player.jump = true;
				//	}
				//}
			}
			//反映
			g_Player.oldpos = g_Player.Position;
			g_Player.Position += g_Player.sp;




			//透ける床処理
			//SHEERFLOORS* pSheerFloors = GetSheerFloors();


			//プレイヤーとチップブロック 当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < BLOCK_MAX; i++)
				//{
				//	BLOCK* block = GetBlock();
				//	BLOCK* cipblock = GetChipBlock();

				//	if ((cipblock + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・ブロック右
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 - g_Player.size.x / 2;
				//		}
				//		//プレイヤー右・ブロック左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 3 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 3 &&
				//			g_Player.Position.y - g_Player.size.y / 3 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 3)
				//		{
				//			g_Player.Position.x = (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 + g_Player.size.x / 2;
				//		}

				//		//プレイヤー上・ブロック下,着地する
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 + g_Player.size.y / 2 + 0.02f;
				//			g_Player.jump = false;
				//			g_Player.fall = false;
				//			g_Player.WarpFlag = false;
				//			//g_Player.isGround = true;
				//			g_Player.sp.y = 0;
				//			g_Player.frame = 0;
				//		}
				//		//プレイヤー下・ブロック上,落下する
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2)
				//		{
				//			g_Player.fall = true;
				//			g_Player.getfall = true;
				//			g_Player.frame = 50;
				//		}
				//	}
				//}
			}

			////プレイヤー・壊れるブロック　当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < BROKEN_MAX; i++)
				//{
				//	BROKEN* broken = GetBroken();
				//	if ((broken + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・壊れるブロック右
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (broken + i)->Postion.x - (broken + i)->Size.x / 2 - g_Player.size.x / 2;
				//		}
				//		//プレイヤー右・壊れるブロック左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (broken + i)->Postion.x + (broken + i)->Size.x / 2 + g_Player.size.x / 2;
				//		}

				//		//プレイヤー上・壊れるブロック下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (broken + i)->Postion.y + (broken + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (broken + i)->Postion.y + (broken + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (broken + i)->Postion.y - (broken + i)->Size.y / 2 - g_Player.size.y / 2;
				//			g_Player.jump = false;
				//			g_Player.fall = false;
				//			g_Player.frame = 0;
				//		}
				//		//プレイヤー下・壊れるブロック上,壊れる
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (broken + i)->Postion.x - (broken + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (broken + i)->Postion.x + (broken + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (broken + i)->Postion.y - (broken + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (broken + i)->Postion.y - (broken + i)->Size.y / 2)
				//		{
				//			(broken + i)->UseFlag = false;
				//			g_Player.fall = true;
				//			g_Player.getfall = true;
				//			g_Player.frame = 50;
				//		}
				//	}
				//}
			}

			////プレイヤー・動くブロック 当たり判定 collision.cppへ移動
			{
				//pMoveBlock = GetMoveBlock();

				//for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
				//	if (pMoveBlock[i].bUse)
				//	{
				//		if (g_Player.Position.x + g_Player.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				//		{
				//			pMoveBlock[i].sp = g_Player.sp;
				//			pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;

				//		}
				//		if (g_Player.Position.x - g_Player.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				//		{
				//			pMoveBlock[i].sp = g_Player.sp;
				//			pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
				//		}
				//		if (g_Player.Position.x + g_Player.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
				//		{
				//			g_Player.Position.y = pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 - g_Player.size.y / 2;
				//			// 着地中にする
				//			if (!g_Player.isMoveBlock) {
				//				g_Player.sp.y = 0.0f;
				//				g_Player.isMoveBlock = true;
				//				break;
				//			}
				//		}
				//		else {
				//			g_Player.isMoveBlock = false;
				//		}
				//		//プレイヤー下・ブロック上,落下する
				//		if (g_Player.Position.x + g_Player.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				//		{
				//			pMoveBlock[i].sp = g_Player.sp;
				//			pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
				//		}
				//	}
				//}
			}

			////トゲ・プレイヤー  当たり判定colision.cppへ移動
			{
				//プレイヤー・トゲブロック　当たり判定
				// 
				//for (int i = 0; i < THORN_BLOCK_MAX; i++)
				//{
				//	THORNBLOCK* thornblock = GetThornBlock();
				//	if ((thornblock + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・トゲブロック右
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 - g_Player.size.x / 2;
				//			//g_Player.UseFlag = false;//ゲームオーバーもしくはライフ-1
				//		}
				//		//プレイヤー右・トゲブロック左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 + g_Player.size.x / 2;
				//			//g_Player.UseFlag = false;//ゲームオーバーもしくはライフ-1
				//		}

				//		//プレイヤー上・トゲブロック下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (thornblock + i)->Postion.y - (thornblock + i)->Size.y / 2 - g_Player.size.y / 2;
				//			//g_Player.UseFlag = false;//ゲームオーバーもしくはライフ-1
				//			//(SCENE_RESULT);
				//		}
				//		//プレイヤー下・トゲブロック上,
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (thornblock + i)->Postion.x - (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (thornblock + i)->Postion.x + (thornblock + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (thornblock + i)->Postion.y + (thornblock + i)->Size.y / 2 + g_Player.size.y / 2;
				//			//g_Player.UseFlag = false;//ゲームオーバーもしくはライフ-1
				//		}
				//	}
				//}
			}

			////プレイヤー・高所落下壊れるブロック　当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < HIGH_MAX; i++)
				//{
				//	HIGH* high = GetHigh();
				//	if ((high + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・たかこわ右
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (high + i)->Postion.x - (high + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (high + i)->Postion.x - (high + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (high + i)->Postion.y - (high + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (high + i)->Postion.y + (high + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (high + i)->Postion.x - (high + i)->Size.x / 2 - g_Player.size.x / 2;
				//		}
				//		//プレイヤー右・たかこわ左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (high + i)->Postion.x + (high + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (high + i)->Postion.x + (high + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (high + i)->Postion.y - (high + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (high + i)->Postion.y + (high + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (high + i)->Postion.x + (high + i)->Size.x / 2 + g_Player.size.x / 2;
				//		}

				//		//プレイヤー上・たかこわ下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (high + i)->Postion.x - (high + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (high + i)->Postion.x + (high + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (high + i)->Postion.y + (high + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (high + i)->Postion.y + (high + i)->Size.y / 2)
				//		{
				//			if (g_Player.sp.y >= -10.0f)
				//			{
				//				//g_Player.isHigh = false;
				//				(high + i)->UseFlag = false;
				//				g_Player.frame = 50;
				//			}
				//			else
				//			{
				//				//g_Player.isHigh = true;
				//				g_Player.sp.y = 0.0f;
				//				g_Player.Position.y = (high + i)->Postion.y + (high + i)->Size.y / 2 + g_Player.size.y / 2;
				//			}

				//		}/*
				//		else
				//		{
				//			g_Player.isHigh = false;
				//		}*/
				//		//プレイヤー下・たかこわ上,
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (high + i)->Postion.x - (high + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (high + i)->Postion.x + (high + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (high + i)->Postion.y - (high + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (high + i)->Postion.y - (high + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (high + i)->Postion.y + (high + i)->Size.y / 2 + g_Player.size.y / 2;
				//		}

				//		// プレイヤーの下にブロックがあったら
				//		if ((g_Player.Position.y - g_Player.size.y / 2 - 0.05f < (high + i)->Postion.y + (high + i)->Size.y / 2) &&
				//			(g_Player.Position.y + g_Player.size.y / 2 > (high + i)->Postion.y - (high + i)->Size.y / 2) &&
				//			(g_Player.Position.x + g_Player.size.x / 2 > (high + i)->Postion.x - (high + i)->Size.x / 2) &&
				//			(g_Player.Position.x - g_Player.size.x / 2 < (high + i)->Postion.x + (high + i)->Size.x / 2))
				//		{	// 着地中にする
				//			if (!g_Player.isHigh) {
				//				g_Player.sp.y = 0.0f;
				//				g_Player.isHigh = true;
				//				break;
				//			}
				//		}
				//		else {
				//			g_Player.isHigh = false;
				//		}
				//	}
				//}
			}

			////落ちるブロック　当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < FALLBLOCK_MAX; i++)
				//{
				//	FALLBLOCK* FallBlock = GetFallBlock();
				//	if ((FallBlock + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・ブロック右判定
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 - g_Player.size.x / 2;
				//		}
				//		//プレイヤー右・落ちるブロック左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.x = (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 + g_Player.size.x / 2;
				//		}
				//		//プレイヤー上・落ちるブロック下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 - g_Player.size.y / 2;
				//			g_Player.getfall = false;
				//			g_Player.fall = false;
				//			g_Player.frame = 50;
				//			(FallBlock + i)->Position.y++;
				//		}
				//		//プレイヤー下・落ちるブロック
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
				//		{
				//			g_Player.Position.y = (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 - g_Player.size.y / 2;
				//		}
				//	}
				//}
			}

			////プレイヤー・鍵 当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < FALLBLOCK_MAX; i++)
				//{
				//	//PLAYER *player = GetPlayer();
				//	KEY* Key = GetKey();
				//	if (Key->GetKey == true)
				//	{
				//		//プレイヤー左・鍵取得　右側
				//		if (g_Player.Position.x + g_Player.size.x / 2 > Key->Position.x - Key->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= Key->Position.x - Key->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > Key->Position.y - Key->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < Key->Position.y + Key->Size.y / 2)
				//		{
				//			g_Player.HaveKey++;
				//			Key->GetKey = false;
				//		}
				//		//プレイヤー右・鍵取得　左側
				//		if (g_Player.Position.x - g_Player.size.x / 2 < Key->Position.x + Key->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= Key->Position.x + Key->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > Key->Position.y - Key->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < Key->Position.y + Key->Size.y / 2)
				//		{
				//			g_Player.HaveKey++;
				//			Key->GetKey = false;
				//		}
				//		//プレイヤー上・鍵取得　下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > Key->Position.x - Key->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < Key->Position.x + Key->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > Key->Position.y - Key->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= Key->Position.y - Key->Size.y / 2)
				//		{
				//			g_Player.HaveKey++;
				//			Key->GetKey = false;
				//		}
				//		//プレイヤー下・鍵取得　上
				//		if (g_Player.Position.x + g_Player.size.x / 2 > Key->Position.x - Key->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < Key->Position.x + Key->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < Key->Position.y + Key->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= Key->Position.y + Key->Size.y / 2)
				//		{
				//			g_Player.HaveKey++;
				//			Key->GetKey = false;
				//		}
				//	}
				//}
			}

			////鍵を取得したプレイヤー・鍵で開く扉　当たり判定 collision.cppへ移動
			{
				//for (int i = 0; i < OPEN_KEY_MAX; i++)
				//{
				//	OPENKEY* OpenKey = GetOpenKey();
				//	if ((OpenKey + i)->UseFlag == true)
				//	{
				//		//プレイヤー左・開く扉右
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 &&
				//			g_Player.oldpos.x + g_Player.size.x / 2 <= (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2)
				//		{
				//			if (g_Player.HaveKey > 0) {
				//				g_Player.Position.x = (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 - g_Player.size.x / 2;
				//				(OpenKey + i)->UseFlag = false;
				//			}
				//			else {
				//				g_Player.Position.x = (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 - g_Player.size.x / 2;
				//			}
				//		}
				//		//プレイヤー右・開く扉左
				//		if (g_Player.Position.x - g_Player.size.x / 2 < (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 &&
				//			g_Player.oldpos.x - g_Player.size.x / 2 >= (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2)
				//		{
				//			if (g_Player.HaveKey > 0) {
				//				g_Player.Position.x = (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 + g_Player.size.x / 2;
				//				(OpenKey + i)->UseFlag = false;
				//			}
				//			else {
				//				g_Player.Position.x = (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 + g_Player.size.x / 2;
				//			}
				//		}
				//		//プレイヤー上・開く扉下
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.y + g_Player.size.y / 2 > (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2 &&
				//			g_Player.oldpos.y + g_Player.size.y / 2 <= (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2)
				//		{
				//			/*if (g_Player.HaveKey > 0) {
				//				g_Player.Position.y = (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2 - g_Player.size.y / 2;
				//				(OpenKey + i)->UseFlag = false;
				//			}
				//			else {
				//				g_Player.Position.y = (OpenKey + i)->Position.y - (OpenKey + i)->Size.y / 2 - g_Player.size.y / 2;
				//			}*/
				//		}
				//		//プレイヤー下・開く扉上
				//		if (g_Player.Position.x + g_Player.size.x / 2 > (OpenKey + i)->Position.x - (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.x - g_Player.size.x / 2 < (OpenKey + i)->Position.x + (OpenKey + i)->Size.x / 2 &&
				//			g_Player.Position.y - g_Player.size.y / 2 < (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2 &&
				//			g_Player.oldpos.y - g_Player.size.y / 2 >= (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2)
				//		{
				//			/*if (g_Player.HaveKey > 0) {
				//				g_Player.Position.y = (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2 - g_Player.size.y / 2;
				//				(OpenKey + i)->UseFlag = false;
				//			}
				//			else {
				//				g_Player.Position.y = (OpenKey + i)->Position.y + (OpenKey + i)->Size.y / 2 - g_Player.size.y / 2;
				//			}*/
				//		}
				//	}
				//}
				//
			}

			//ゴール用鍵・プレイヤー 当たり判定 collision.cppへ移動
			{
				//GKey* GKey = GetGKey();
				//if (GKey->UseFlag == true)
				//{
				//	//プレイヤー左・鍵取得　右側
				//	if (g_Player.Position.x + g_Player.size.x / 2 > GKey->pos.x - GKey->size.x / 2 &&
				//		g_Player.oldpos.x + g_Player.size.x / 2 <= GKey->pos.x - GKey->size.x / 2 &&
				//		g_Player.Position.y + g_Player.size.y / 2 > GKey->pos.y - GKey->size.y / 2 &&
				//		g_Player.Position.y - g_Player.size.y / 2 < GKey->pos.y + GKey->size.y / 2)
				//	{
				//		GKey->UseFlag = false;
				//		GKey->GetGKey = true;
				//	}
				//	//プレイヤー右・鍵取得　左側
				//	if (g_Player.Position.x - g_Player.size.x / 2 < GKey->pos.x + GKey->size.x / 2 &&
				//		g_Player.oldpos.x - g_Player.size.x / 2 >= GKey->pos.x + GKey->size.x / 2 &&
				//		g_Player.Position.y + g_Player.size.y / 2 > GKey->pos.y - GKey->size.y / 2 &&
				//		g_Player.Position.y - g_Player.size.y / 2 < GKey->pos.y + GKey->size.y / 2)
				//	{
				//		GKey->UseFlag = false;
				//		GKey->GetGKey = true;

				//	}

				//	//プレイヤー上・鍵取得　下
				//	if (g_Player.Position.x + g_Player.size.x / 2 > GKey->pos.x - GKey->size.x / 2 &&
				//		g_Player.Position.x - g_Player.size.x / 2 < GKey->pos.x + GKey->size.x / 2 &&
				//		g_Player.Position.y + g_Player.size.y / 2 > GKey->pos.y - GKey->size.y / 2 &&
				//		g_Player.oldpos.y + g_Player.size.y / 2 <= GKey->pos.y - GKey->size.y / 2)
				//	{
				//		GKey->UseFlag = false;
				//		GKey->GetGKey = true;
				//	}
				//	//プレイヤー下・鍵取得　上
				//	if (g_Player.Position.x + g_Player.size.x / 2 > GKey->pos.x - GKey->size.x / 2 &&
				//		g_Player.Position.x - g_Player.size.x / 2 < GKey->pos.x + GKey->size.x / 2 &&
				//		g_Player.Position.y - g_Player.size.y / 2 < GKey->pos.y + GKey->size.y / 2 &&
				//		g_Player.oldpos.y - g_Player.size.y / 2 >= GKey->pos.y + GKey->size.y / 2)
				//	{
				//		GKey->UseFlag = false;
				//		GKey->GetGKey = true;

				//	}
				//}
			}

			//プレイヤー・ワープ 当たり判定 collision.cppへ移動
			{
				//g_Player.CoolTime--;

				//if (g_Player.CoolTime < 0)
				//{
				//	g_Player.CoolTime = 0;

				//	//プレイヤー・ワープ　当たり判定
				//	for (int i = 0; i < BLOCK_MAX; i++)
				//	{
				//		WARP* warp = GetWarp();
				//		if ((warp + i)->UseFlag == true)
				//		{
				//			if (g_Player.Position.x + g_Player.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
				//				g_Player.Position.x - g_Player.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
				//				g_Player.Position.y + g_Player.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
				//				g_Player.Position.y - g_Player.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
				//			{
				//				if (i % 2 == 0)
				//				{
				//					if (!g_Player.WarpFlag)
				//					{
				//						g_Player.Position = (warp + i + 1)->Position;
				//						g_Player.CoolTime = PLAYER_COOLTIME;
				//						g_Player.WarpFlag = true;
				//					}

				//				}
				//				else if (i % 2 == 1)
				//				{
				//					if (!g_Player.WarpFlag)
				//					{
				//						g_Player.Position = (warp + i - 1)->Position;
				//						g_Player.CoolTime = PLAYER_COOLTIME;

				//						g_Player.WarpFlag = true;

				//					}
				//				}
				//			}
				//		}
				//	}
				//}
				if (IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_THUMB) || 	// GamePad	Lタブ
					Keyboard_IsKeyTrigger(KK_R))						// Keyboard	R
				{
					ResetGame();
				}

				//プレイヤーとパズルの画面外判定
				Piece* pPiece = GetPiece();

				for (int i = 0; i < PUZZLE_MAX; i++)
				{
					if (pPiece[i].UseFlag)
					{
						bool hitflag = CollisionBB(g_Player.Position, pPiece[i].pos, g_Player.size, pPiece[i].size);

						if (hitflag)
						{
							if (g_Player.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, DOWN);

								if (!hitflag2)
								{
									g_Player.sp.y -= 0.2;//加速
								}
								else
								{//下に何もなく死亡する場合
									for (int i = 0; i < SPAWN_POINT_MAX; i++)
									{
										if (pSpawnPoint[i].UseFlag)
										{
											if (g_Player.PieceIndex == pSpawnPoint[i].PieceIndex)
											{
												g_Player.Position = pSpawnPoint[i].Position;
												g_Player.hp--;

											}


										}
									}

								}
							}
							else if (g_Player.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
							{

								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, RIGHT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{
									g_Player.Position.x = g_Player.oldpos.x;
								}


							}
							else if (g_Player.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, LEFT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{
									g_Player.Position.x = g_Player.oldpos.x;
								}


							}
							else if (g_Player.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, UP);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//加速
								}
								else
								{

									g_Player.fall = true;
									//g_Player.sp.y = 0;
									//g_Player.getfall = true;
									g_Player.frame = 50;
									//g_Player.sp.y += 0.2;//加速
								}

							}
						}
					}


				}


			}
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_THUMB) || 	// GamePad	Lタブ
				Keyboard_IsKeyTrigger(KK_R))						// Keyboard	R
			{
				ResetGame();
			}

			//プレイヤーとパズルの画面外判定
			Piece* pPiece = GetPiece();

			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				if (pPiece[i].UseFlag)
				{
					bool hitflag = CollisionBB(g_Player.Position, pPiece[i].pos, g_Player.size, pPiece[i].size);

					if (hitflag)
					{
						if (g_Player.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, DOWN);

							if (!hitflag2)
							{
								g_Player.sp.y -= 0.2;//加速
							}
							else
							{//下に何もなく死亡する場合
								for (int i = 0; i < SPAWN_POINT_MAX; i++)
								{
									if (pSpawnPoint[i].UseFlag)
									{
										if (g_Player.PieceIndex == pSpawnPoint[i].PieceIndex)
										{
											g_Player.Position = pSpawnPoint[i].Position;

										}


									}
								}

							}
						}
						else if (g_Player.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
						{

							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, RIGHT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//加速
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						else if (g_Player.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, LEFT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//加速
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						else if (g_Player.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, UP);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//加速
							}
							else
							{

								g_Player.fall = true;
								//g_Player.sp.y = 0;
								//g_Player.getfall = true;
								g_Player.frame = 50;
								//g_Player.sp.y += 0.2;//加速
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
		SpriteDrawColorRotation(g_Player.Position.x, g_Player.Position.y,-0.2f, g_Player.Drawsize.x, g_Player.Drawsize.y, g_Player.rot, g_Player.col, g_Player.PaternNo, g_Player.uv_w, g_Player.uv_h, g_Player.NumPatern);
	}
}

//=============================================================================
//ゲット関数
//=============================================================================
PLAYER* GetPlayer()
{
	return &g_Player;
}

void SetPlayerPosition(D3DXVECTOR2 pos)
{
	g_Player.Position = pos;
}
