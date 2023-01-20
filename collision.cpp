/*==============================================================================

   当たり判定管理 [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//collision.h
#include "collision.h"

#include <math.h>
#include "main.h"	 

//操作関連
#include "mouse.h"
#include "inventory.h"

//ゲーム関係
#include "game.h"
#include "MapChip.h"
#include "player.h"
#include "result.h"
#include "scene.h"
#include "goal.h"
#include "start.h"

#include "button.h"
#include "time.h"
#include "spawnpoint.h"
#include "joint.h"
#include "SplitStage.h"
#include "fade.h"
//ギミック関連
#include "block.h"			//基本ブロック
#include "thorn_block.h"	//トゲブロック
#include "broken.h"			//壊れるブロック
#include "MoveBlock.h"		//動くブロック
#include "High_broken.h"	//高い所から落ちたら壊れるブロック
#include "FallBlock.h"		//落ちるブロック

#include "SheerFloors.h"	//透ける床
#include "jump_stand.h"		//ジャンプスタンド
#include "switch.h"			//スイッチ
#include "SwitchWall.h"		//スイッチで開く壁
#include "warp.h"			//ワープ
#include "Key.h"			//鍵
#include "OpenKey.h"		//鍵で開く扉
#include "goal_key.h"		//ゴール専用鍵
#include "bullet.h"			//ドッペルゲンガー発射弾
#include "doppelganger.h"   //ドッペルゲンガー
#include "enemy.h"			//エネミー

#include "JumpStandExplain.h"		

#include "EffectSpark.h"	// ヒバナエフェクト
#include"switch.h"	//スイッチ
#include"SwitchWall.h"//switchの壁
#include"cursor.h"

#include"sound.h"

//==================================
//プロトタイプ宣言
//=================================

bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);	//その方向のパズルが空いているか
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);	//回転を戻す
//void SetPosition(Piece p,int i);
bool SpritStageCollision(Piece p);

void UpdateCollision();
void PieceCollision();
void PuzzleCollision();

bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);
bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);
bool fourCollision(PUZZLE puzzle, int index);
void PositionPlas(D3DXVECTOR2 num, int pinNo);
bool PlayerPieceOpen(Piece p, int index, DIRECSION direcsion);

bool DoppelPieceOpen(Piece pi, int index, DIRECSION direcsion);

bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);
bool SpritStageCollision(Piece p);

int punum = 0;	//パズルの配列の添え字の格納

static Time* pTime = pTime->GetTime();
static TimeParam* pTimeParam = pTime->GetTimeParam();
DIRECSION Direcsion = NUM;	//方向の確認
static bool InventoryFlag = false;

////効果音
////壊れるブロック
//static int g_BrokenSoundNo = 0;
//static char g_BrokenSoundName[] = "data\\SoundData\\SE\\タイプライター.wav";
//
////スイッチ
//static int g_SwitchSoundNo = 0;
//static char g_SwitchSoundName[] = "data\\SoundData\\SE\\タイプライター.wav";
////ワープ
//static int g_WarpSoundNo = 0;
//static char g_WarpSoundName[] = "data\\SoundData\\SE\\タイプライター.wav";
////高いとこから請われる床
//static int g_HighSoundNo = 0;
//static char g_HighSoundName[] = "data\\SoundData\\SE\\タイプライター..wav";
////鍵
//static int g_KeySoundNo = 0;
//static char g_KeySoundName[] = "data\\SoundData\\SE\\タイプライター..wav";
////鍵扉
//static int g_OpenKeySoundNo = 0;
//static char g_OpenKeySoundName[] = "data\\SoundData\\SE\\タイプライター..wav";





//===============================
//初期化処理
//================================
void InitCollision()
{
	/*g_BrokenSoundNo = LoadSound(g_BrokenSoundName);
	g_WarpSoundNo = LoadSound(g_WarpSoundName);
	g_HighSoundNo = LoadSound(g_HighSoundName);
	g_SwitchSoundNo = LoadSound(g_SwitchSoundName);
	g_KeySoundNo = LoadSound(g_KeySoundName);
	g_OpenKeySoundNo = LoadSound(g_OpenKeySoundName);*/
}


//===============================
//更新処理
//================================
void UninitCollision()
{
	/*StopSound(g_BrokenSoundNo);
	StopSound(g_SwitchSoundNo);
	StopSound(g_WarpSoundNo);
	StopSound(g_HighSoundNo);
	StopSound(g_KeySoundNo);
	StopSound(g_OpenKeySoundNo);*/
}



//===============================
//当たり判定処理
//当たり判定を一気に行う
//================================
void UpdateCollision(){
	// 使用ゲット一覧-----------------------------
	PLAYER* pPlayer = GetPlayer();
	MOUSE* pMouse = GetMouse();
	ENEMY* pEnemy = GetEnemy();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();

	WARP* pWarp = GetWarp();

	BLOCK* pBlock = GetBlock();
	BLOCK* pChipblock = GetChipBlock();
	MOVEBLOCK* pMoveBlock = GetMoveBlock();
	FALLBLOCK* pFallBlock = GetFallBlock();
	THORNBLOCK* pThornBlock = GetThornBlock();

	BROKEN* pBroken = GetBroken();
	HIGH* pHigh = GetHigh();
	SWITCH* pSwitch = GetSwitch();
	SWITCHWALL* pSwitchWall = GetSwitchWall();
	JUMPSTAND* pJumpStand = GetJumpStand();
	KEY* pKey = GetKey();
	OPENKEY* pOpenKey = GetOpenKey();
	GKey* pGKey = GetGKey();
	EXPLAIN* p_Explain = GetExplain();

	GOAL* pGoal = GetGoal();
	START* pStart = GetStart();
	RESULT* pResult = GetResult();

	Piece* pPiece = GetPiece();

	//-------------------------------------

	bool pFlag = false;	//プレーヤーがピースの中にいるか
	InventoryFlag = false;
	//プレーヤーが動いているピースの中にいるか
	for (int i = 0; i < PUZZLE_MAX; i++) {
		//Piece* pPiece = GetPiece();
		if (pPiece[i].MoveFlag){
			if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
				pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
				pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
				pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x)
			{
				//いたら
				pFlag = true;
				break;
			}
			//break;
		}
	}

	//============================
	//インベントリ系
	//============================
	if (!pFlag) {
		// ピースとインベントリ範囲の当たり判定
		for (int i = 0; i < PUZZLE_MAX; i++) {
			// ピースをインベントリにしまう
			if (!pPiece[i].InventoryFlag&&pPiece[i].UseFlag && pPiece[i].pos.x < (-INVENTORYBG_POS_X_REVESE + INVENTORYBG_SIZE_X*1.5f)) {
				DeleteMapChip(i);
				SetInventory(pPiece[i].no);
				InventoryFlag = true;

				break;
			}
		}

		//=========================================
		//プレーヤーとヒント表示
		//=========================================
		//ジャンプ台ヒント
		
		if (p_Explain->bUse) {
			if (CollisionBB(pPlayer->Position, p_Explain->pos, pPlayer->size * 2, p_Explain->size * 2))
			{
				p_Explain->CollisionUse = true;
			}
			else {
				p_Explain->CollisionUse = false;
			}
		}
		
		//動く台ヒント
		//for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		//	if (pMoveBlock[i].bUse) {
		//		if (CollisionBB(pPlayer->Position, pMoveBlock[i].pos, pPlayer->size * 2, pMoveBlock[i].size * 2)) 
		//		{
		//			
		//		}
		//		else
		//		{
		//			pExplain->bUse = false;
		//		}
		//	}
		//}

		//=========================================
		//プレーヤーとスイッチ系(switch,SwitchWall)
		//=========================================
		for (int i = 0; i < SWITCH_MAX; i++) {
			if (pSwitch[i].UseFlag) {
				//スイッチの左がプレイヤーの右よりも左にあるとき、
				//スイッチの右がプレイヤーの左よりも右にあるとき
				//スイッチの上が
				if (pSwitch[i].pos.x - pSwitch[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
					pSwitch[i].pos.x + pSwitch[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
					pSwitch[i].pos.y - pSwitch[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
					pSwitch[i].pos.y + pSwitch[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2)
				{
					pSwitch[i].PressFlag = true;//押されたら
					pSwitch[i].PaternNo = 1;
					//SetVolume(g_BrokenSoundNo, 0.5f);
					//PlaySound(g_SwitchSoundNo, 0);
				}
				else {
					pSwitch[i].PressFlag = false;
					pSwitch[i].PaternNo = 0;
				}
				if (pSwitch[i].PressFlag) {
					for (int j = 0; j < pSwitchWall[i].WallMax; j++) {
						//  switch index 0,1			switch wall	index 0,3
						if (pSwitch[i].SwitchIndex == pSwitchWall[i + j].SwitchIndex) {
							pSwitchWall[i + j].UseFlag = false;	//押されたら壁がなくなる
						}
					}
				}
				else {
					for (int j = 0; j < pSwitchWall[i].WallMax; j++) {
						pSwitchWall[j].UseFlag = true;		//壁出現
					}
				}
			}
		}
		//プレーヤーと壁の判定
		for (int i = 0; i < SWITCHWALL_MAX; i++) {
			if (pSwitchWall[i].UseFlag) {
				if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
					pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
					pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
					pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2)
				{
					if (pSwitchWall[i].rot == 0.0f) {
						pPlayer->Position.x = pPlayer->oldpos.x;
						pPlayer->Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2;
					}
					else if (pSwitchWall[i].rot == 90.0f) {
						pPlayer->Position = pPlayer->oldpos;
						pPlayer->Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2;
					}
					else if (pSwitchWall[i].rot == 180.0f) {
						pPlayer->Position = pPlayer->oldpos;
						pPlayer->Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2;
					}
					else if (pSwitchWall[i].rot == 270.0f) {
						pPlayer->Position = pPlayer->oldpos;
						pPlayer->Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2;
					}
				}

			}
		}
		//スイッチと木箱の判定
		for (int i = 0; i < SWITCHWALL_MAX; i++) {
			if (pSwitchWall[i].UseFlag) {

			}
		}
		//=====================================
		// start
		//=====================================
		for (int i = 0; i < START_MAX; i++) {
			if (pStart[i].UseFlag) {
				if (pStart[i].GoalFlag) {
					if (CollisionBB(pPlayer->Position, pStart[i].pos, pPlayer->size, pStart[i].size)) {
						SetResultType(WIN);
						StartFade(FADE::FADE_OUT);
						pTime->EndTime();
						pTimeParam->EndFlag = true;
					}
				}
			}
		}

		//=====================================
		//死亡判定（トゲ、落下死,thornBlock）
		//=====================================
		if (!Mouse_IsLeftDown())
		{
			//プレイヤーとトゲブロックの判定
			for (int i = 0; i < THORN_BLOCK_MAX; i++) {
				if (pThornBlock[i].UseFlag) {
					if (CollisionBB(pThornBlock[i].Postion, pPlayer->Position, pThornBlock[i].Size, pPlayer->size)) {
						
						pPlayer->hp--;

						if (pPlayer->hp <= 0) {
							SetResultType(LOSE);
							StartFade(FADE::FADE_OUT);
							pTime->EndTime();
							pTimeParam->EndFlag = true;
						}
						else {//下に何もなく死亡する場合
							for (int i = 0; i < SPAWN_POINT_MAX; i++) {
								if (pSpawnPoint[i].UseFlag) {
									if (pPlayer->PieceIndex == pSpawnPoint[i].PieceIndex) {
										pPlayer->Position = pSpawnPoint[i].Position;
									}
								}
							}
						}
					}
				}
			}
		}
		//プレイヤーが落下死したら
		if (pPlayer->Position.y - pPlayer->size.y < -SCREEN_HEIGHT / 2) {
			pPlayer->hp--;
			pResult[0].type = LOSE;
			pTime->EndTime();
			pTimeParam->EndFlag = true;
			StartFade(FADE::FADE_ALPHA_OUT);
		}

		//========================================================================
		//プレイヤー・チップブロック　当たり判定(PlayerとChipBlockの当たり判定)
		//=========================================================================
		for (int i = 0; i < BLOCK_MAX; i++) {
			if ((pChipblock + i)->UseFlag) {
				//プレイヤー左・ブロック右
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
					pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 - pPlayer->size.x / 2;
				}
				//プレイヤー右・ブロック左
				if (pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
					pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 + pPlayer->size.x / 2;
				}
				//プレイヤー上・ブロック下,着地する
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 &&
					pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 + pPlayer->size.y / 2 + 0.02f;
					pPlayer->jump = false;
					pPlayer->fall = false;
					pPlayer->WarpFlag = false;
					//pPlayer->isGround = true;
					pPlayer->sp.y = 0;
					pPlayer->frame = 0;
				}
				//プレイヤー下・ブロック上,落下する
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
					pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 - pPlayer->size.y / 2 - 0.02f;
					pPlayer->sp.y = 0;
					for (int i = 0; i < JUMPSTAND_MAX; i++)
					{
						pJumpStand[i].JumpStandFlag = false;

					}

					pPlayer->fall = true;
					pPlayer->getfall = true;
					pPlayer->frame = 50;
				}
			}
		}
		//========================================================================
		//プレイヤー・ワープ　当たり判定(PlayerとWarpの当たり判定)
		//========================================================================	
		pPlayer->CoolTime--;
		if (pPlayer->CoolTime < 0) {
			pPlayer->CoolTime = 0;
			//プレイヤー・ワープ　当たり判定
			for (int i = 0; i < WARP_MAX; i++) {
				if ((pWarp + i)->UseFlag) {
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pWarp + i)->Position.x - (pWarp + i)->Size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < (pWarp + i)->Position.x + (pWarp + i)->Size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > (pWarp + i)->Position.y - (pWarp + i)->Size.y / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < (pWarp + i)->Position.y + (pWarp + i)->Size.y / 2)
					{
						if (i % 2 == 0)
						{
							if (pWarp[i + 1].UseFlag)
							{
								if (!pWarp[i + 1].InventoryFlag)
								{
									if (!pPlayer->WarpFlag)
									{
										pPlayer->Position = (pWarp + i + 1)->Position;
										pPlayer->CoolTime = PLAYER_COOLTIME;
										//SetVolume(g_WarpSoundNo, 0.5f);
										//PlaySound(g_WarpSoundNo, 0);
										pPlayer->WarpFlag = true;
									}
								}
							}

						}
						else if (i % 2 == 1)
						{
							if (pWarp[i - 1].UseFlag)
							{
								if (!pWarp[i - 1].InventoryFlag)
								{
									if (!pPlayer->WarpFlag)
									{
										pPlayer->Position = (pWarp + i - 1)->Position;
										pPlayer->CoolTime = PLAYER_COOLTIME;
										//SetVolume(g_WarpSoundNo, 0.5f);
										//PlaySound(g_WarpSoundNo, 0);
										pPlayer->WarpFlag = true;

									}
								}
							}
						}
					}
				}
			}
		}
		//-----------------------------------------------------
		//プレイヤーとジャンプ台 当たり判定(PlayerとJumpstand)
		//-----------------------------------------------------
		//for (int i = 0; i < JUMPSTAND_MAX; i++) {

		//	JUMPSTAND* p_JumpStand = GetJumpStand();

		//	if (p_JumpStand[i].UseJumpStand) {
		//		if (GetKeyboardPress(DIK_B))
		//		{
		//			if (CollisionBB(pPlayer->Position, p_JumpStand[i].pos, pPlayer->size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
		//				p_JumpStand[i].GetJumpStand = true;
		//			}
		//		}
		//		else
		//		{
		//			p_JumpStand[i].GetJumpStand = false;
		//		}
		//	}
		//}
		//========================================================================
		//プレイヤー・壊れるブロック　当たり判定(PlayerとBrokenBlockの当たり判定)
		//=========================================================================
		for (int i = 0; i < BROKEN_MAX; i++) {
			if ((pBroken + i)->UseFlag) {
				//プレイヤー左・壊れるブロック右
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
					pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - pPlayer->size.x / 2;
				}
				//プレイヤー右・壊れるブロック左
				if (pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
					pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + pPlayer->size.x / 2;
				}
				//プレイヤー上・壊れるブロック下
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
					pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 + pPlayer->size.y / 2;
					pPlayer->jump = false;
					pPlayer->fall = false;
					pPlayer->frame = 0;
				}
				//プレイヤー下・壊れるブロック上,壊れる
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
					pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
				{
					(pBroken + i)->breakFlag = true;
					//SetVolume(g_BrokenSoundNo, 0.5f);
					//PlaySound(g_BrokenSoundNo, 0);
					(pBroken + i)->UseFlag = false;
					pPlayer->fall = true;
					pPlayer->getfall = true;
					pPlayer->frame = 50;
				}
			}
		}
		//====================================================================
		//プレイヤーと動くブロックの当たり判定(PlayerとMoveBlockの当たり判定)
		//====================================================================
		for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
			if (pMoveBlock[i].bUse) {
				if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
					pPlayer->oldpos.x + pPlayer->size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				{
					pMoveBlock[i].sp = pPlayer->sp;
					pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
				}
				if (pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
					pPlayer->oldpos.x - pPlayer->size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				{
					pMoveBlock[i].sp = pPlayer->sp;
					pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
				}
				if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
					pPlayer->oldpos.y + pPlayer->size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
				{
					pPlayer->Position.y = pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 + pPlayer->size.y / 2;
					// 着地中にする
					if (!pPlayer->isMoveBlock) {
						pPlayer->sp.y = 0.0f;
						pPlayer->isMoveBlock = true;
						break;
					}
				}
				else {
					pPlayer->isMoveBlock = false;
				}
				//プレイヤー下・ブロック上,落下する
				if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
					pPlayer->oldpos.y - pPlayer->size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
				{
					pMoveBlock[i].sp = pPlayer->sp;
					pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
				}
			}
		}
		//====================================================================
		//プレイヤーと落ちるブロックの当たり判定(PlayerとFallBlockの当たり判定)
		//====================================================================
		for (int i = 0; i < FALLBLOCK_MAX; i++) {
			if ((pFallBlock + i)->UseFlag) {
				//プレイヤー左・ブロック右判定
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
					pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 - pPlayer->size.x / 2;
				}
				//プレイヤー右・落ちるブロック左
				if (pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
					pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 + pPlayer->size.x / 2;
				}
				//プレイヤー上・落ちるブロック下
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
					pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pFallBlock + i)->Position.y +(pFallBlock + i)->Size.y / 2 + pPlayer->size.y / 2;
					pPlayer->getfall = false;
					pPlayer->fall = false;
					pPlayer->frame = 50;
					(pFallBlock + i)->Position.y++;
				}
				//プレイヤー下・落ちるブロック
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 &&
					pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 - pPlayer->size.y / 2;
				}
			}
		}
		//====================================================================
		//プレイヤーと高所落下ブロックの当たり判定(PlayerとHighの当たり判定)
		//====================================================================
		for (int i = 0; i < HIGH_MAX; i++) {
			if ((pHigh + i)->UseFlag) {
				//プレイヤー左・高所落ちるブロック右
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
					pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - pPlayer->size.x / 2;
				}
				//プレイヤー右・高所落ちるブロック左
				if (pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
					pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
				{
					pPlayer->Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + pPlayer->size.x / 2;
				}
				//プレイヤー上・高所落ちるブロック下
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
					pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
				{
					if (pPlayer->sp.y >= 5.0f) {
						//pPlayer->isHigh = false;
						(pHigh + i)->UseFlag = false;
						//SetVolume(g_HighSoundNo, 0.5f);
						//PlaySound(g_HighSoundNo, 0);
						pPlayer->frame = 50;
					}
					else {
						//pPlayer->isHigh = true;
						pPlayer->sp.y = 0.0f;
						pPlayer->Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + pPlayer->size.y / 2;
					}

				}/*
				else
				{
					pPlayer->isHigh = false;
				}*/
				//プレイヤー下・高所落ちるブロック上,
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
					pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
				{
					pPlayer->Position.y = (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 - pPlayer->size.y / 2;
				}
				// プレイヤーの下にブロックがあったら
				if ((pPlayer->Position.y - pPlayer->size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
					(pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
					(pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
					(pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
				{
					// 着地中にする
					if (!pPlayer->isHigh) {
						pPlayer->sp.y = 0.0f;
						pPlayer->isHigh = true;
						break;
					}
				}
				else {
					pPlayer->isHigh = false;
				}
			}
		}
		//-----------------------------------------------------
		//プレイヤーと鍵の当たり判定(PlayerとKey)
		//-----------------------------------------------------
		for (int i = 0; i < KEY_MAX; i++) {
			if (pKey->GetKey) {
				if (CollisionBB(pKey[i].Position, pPlayer->Position, pKey[i].Size, pPlayer->size)) {
					pPlayer->HaveKey++;
					pKey->GetKey = false;
					//SetVolume(g_BrokenSoundNo, 0.5f);
					//PlaySound(g_KeySoundNo, 0);
				}
			}
		}
		//-----------------------------------------------------------------
		//通常鍵取得プレイヤーと鍵で開く扉の当たり判定(PlayerとOpenKey)
		//-----------------------------------------------------------------
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			if ((pOpenKey + i)->UseFlag) {
				if (CollisionBB(pOpenKey[i].Position, pKey->Position, pOpenKey[i].Size, pKey->Size)) {
					if (pPlayer->HaveKey > 0) {
						//pPlayer->Position.x = (pOpenKey + i)->Position.x - (pOpenKey + i)->Size.x / 2 - pPlayer->size.x / 2;
						(pOpenKey + i)->UseFlag = false;
						//SetVolume(g_OpenKeySoundNo, 0.5f);
						//PlaySound(g_OpenKeySoundNo, 0);
					}
					/*else
					{
						pPlayer->Position.x = (pOpenKey + i)->Position.x - (pOpenKey + i)->Size.x / 2 - pPlayer->size.x / 2;
					}*/

				}
			}

		}
		//------------------------------------------------------------------
		//ゴール専用鍵とプレイヤーの当たり判定(GKeyとPlayer)
		//------------------------------------------------------------------
		if (pGKey->UseFlag) {
			if (CollisionBB(pGKey->pos, pPlayer->Position, pGKey->size, pPlayer->size)) {
				pGKey->UseFlag = false;
				pGKey->GetGKey = true;
			}
		}
		//-------------------------------------------------------------------
		//ゴール専用鍵取得プレイヤーと鍵で開く扉の当たり判定(PlayerとGoal)
		//-------------------------------------------------------------------

		if (pGoal->UseFlag) {
			if (!pMouse->UseFlag && pGKey->GetGKey) {
				if (CollisionBB(pGoal->Pos, pPlayer->Position, pGoal->Size, pPlayer->size)) {
					pGoal->UseFlag = false;
					//
					for (int i = 0; i < START_MAX; i++) {
						pStart[i].GoalFlag = true;
					}
					//
					//SetResultType(WIN);
					//StartFade(FADE::FADE_OUT);
					//pTime->EndTime();
					//pTimeParam->EndFlag = true;
				}
			}
		}
		//------------------------------------
		//敵の目の前とプレイヤー当たり判定
		//------------------------------------
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (pEnemy[i].UseFlag) {
				pEnemy[i].AIFlag = false;
				if (CollisionBB(pEnemy[i].pos, pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x * 1000, pEnemy[i].size.y), pPlayer->size)) {
					pEnemy[i].AIFlag = true;
				}
			}
		}
		//------------------------------------
		//動くブロックとバネ当たり判定
		//-----------------------------------
		for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pMoveBlock[i].pos, pJumpStand[j].pos, pMoveBlock[i].size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
		}
		//------------------------------------
		//バネと下からこわすっブロッコ当たり判定
		//-----------------------------------
		for (int i = 0; i < THORN_BLOCK_MAX; i++) {
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pThornBlock[i].Postion, pJumpStand[j].pos, pThornBlock[i].Size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
		}
		//------------------------------------
		//バネと鍵付き扉当たり判定
		//-----------------------------------
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pOpenKey[i].Position, pJumpStand[j].pos, pOpenKey[j].Size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
		}
		//------------------------------------
		//バネとトゲブロック当たり判定
		//-----------------------------------
		for (int i = 0; i < BROKEN_MAX; i++) {
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pBroken[i].Postion, pJumpStand[j].pos, pBroken[j].Size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
		}
		//------------------------------------
		//バネとトゲブロック当たり判定
		//-----------------------------------
		for (int i = 0; i < HIGH_MAX; i++) {
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pHigh[i].Postion, pJumpStand[j].pos, pHigh[i].Size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
		}
		//------------------------------------
		//動くブロックと鍵付き扉当たり判定
		//-----------------------------------
		for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
			for (int j = 0; j < OPEN_KEY_MAX; j++) {
				if (CollisionBB(pMoveBlock[i].pos, pOpenKey[j].Position, pMoveBlock[i].size, pOpenKey[j].Size)) {
					pMoveBlock[i].pos = pMoveBlock[i].oldpos;
				}
			}
		}
		//------------------------------------
		//動くブロックjとジャンプで壊すブロックi当たり判定
		//-----------------------------------
		for (int i = 0; i < BROKEN_MAX; i++) {
			for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
				if (CollisionBB(pMoveBlock[j].pos, pBroken[i].Postion, pMoveBlock[j].size, pBroken[i].Size)) {
					pMoveBlock[j].pos = pMoveBlock[j].oldpos;
				}
			}
		}
		//------------------------------------
		//動くブロックjとトゲブロックi当たり判定
		//-----------------------------------
		for (int i = 0; i < THORN_BLOCK_MAX; i++) {
			for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
				if (CollisionBB(pMoveBlock[j].pos, pThornBlock[i].Postion, pMoveBlock[j].size, pThornBlock[i].Size)) {
					pMoveBlock[j].pos = pMoveBlock[j].oldpos;
				}
			}
		}
	}
	//------------------------------------
	//ドッペルゲンガー弾用当たり判定
	//------------------------------------
	//DOPPELGANGER* pDoppel = GetDoppelganger();
	//BULLET* pBullet = GetBullet();

	//反プレイヤー弾 と 敵キャラ
	//if(pDoppel->UseFlag == true)
	//{ 
	//	pBullet->use = true;

	//	if (pBullet->use == true)
	//	{
	//		if (pPlayer->UseFlag)
	//		{
	//			bool hit = CollisionBB(pBullet->pos, pPlayer->Position, D3DXVECTOR2(pBullet->w, pBullet->h), D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H));

	//			if (hit == true)//当たっている
	//			{
	//				if (pBullet->hit)
	//				{
	//					pPlayer->hp - (pBullet->Damage);
	//					if (pPlayer->hp <= 0)
	//					{
	//						pPlayer->UseFlag = false;
	//						StartFade(FADE::FADE_OUT);
	//						SetResultType(LOSE);
	//						pTime->EndTime();
	//						pTimeParam->EndFlag = true;
	//					}
	//					
	//				}
	//			}
	//			else//当っていない
	//			{

	//			}
	//		}
	//	}
	//}
	
}
//----------------------------------------------------------------------------------------------------------




//==========================
//パズルピース当たり判定
//==========================
void PieceCollision()
{
	
	SplitStage* pSplitStage = GetSplitStage();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();

	Piece* pPiece = GetPiece();
	JOINT* pJoint = GetJoint();
	PLAYER* pPlayer = GetPlayer();
	bool colFlag = false;//当たって入ったか
	bool colFlag2 = false;//当たって入ったか
	bool pFlag =false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (pPiece[i].MoveEndFlag)	//動き終わったら
			{
				if (!pPiece[i].InventoryFlag)
				{



					pPiece[i].MoveEndFlag = false;

					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
						pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
						pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
						pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x &&
						pPiece[i].no == pPlayer->PieceIndex)
					{
						pFlag = true;
					}

					if (!SpritStageCollision(pPiece[i]))
					{
						//pPiece[i].pos = pPiece[i].OldMovePos;
						Rotreturn(pPiece[i].no);
						colFlag2 = true;
						D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
						PositionPlas(temp, pPiece[i].no);
						pPiece[i].pos = pPiece[i].OldMovePos;
						if (pFlag)
						{
							pPlayer->Position = pPlayer->OneOldpos;
							pPlayer->oldpos = pPlayer->Position;

							pPlayer->hp--;
						}

						break;
					}


					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[i].no)	//動き終わったピースの中にあったら
						{
							for (int k = 0; k < JOINT_MAX; k++)
							{
								if (pJoint[k].useFlag)
								{

								
									if (pJoint[j].pieNo != pJoint[k].pieNo)//ピース番号が違ったら
									{


										//ジョイントが重なっていたら
										colFlag = CollisionBB(pJoint[j].pos, pJoint[k].pos, pJoint[j].size, pJoint[k].size);

										if (colFlag)
										{

											//凹凸が合っていたら
											if (pJoint[j].type == JOINT_TYPE::TYPE_BUMP && pJoint[k].type == JOINT_TYPE::TYPE_DIP ||
												pJoint[k].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP)
											{
												colFlag2 = true;

												//ジョイントが右だったら
												if (pPiece[i].pos.x + pPiece[i].size.x / 3 < pJoint[j].pos.x)
												{


													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);

													if (fourPieceCollision(pPiece[i], i))
													{
														PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;
														}
														// ヒバナエフェクト
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// ピースのアニメーション
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
													}
													else
													{
														Rotreturn(pPiece[i].no);
														colFlag2 = true;
														temp = pPiece[i].OldMovePos - pPiece[i].pos;
														PositionPlas(temp, pPiece[i].no);
														pPiece[i].pos = pPiece[i].OldMovePos;
														if (pFlag)
														{
															pPlayer->Position = pPlayer->OneOldpos;
														}
													}
												}
												//ジョイントが左だったら
												else if (pPiece[i].pos.x - pPiece[i].size.x / 3 > pJoint[j].pos.x)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_SIZE, pPiece[pJoint[k].indexno].pos.y);

													if (fourPieceCollision(pPiece[i], i))
													{

														PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;

														}
														pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);
														// ヒバナエフェクト
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// ピースのアニメーション
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
													}
													else
													{
														Rotreturn(pPiece[i].no);
														colFlag2 = true;
														temp = pPiece[i].OldMovePos - pPiece[i].pos;
														PositionPlas(temp, pPiece[i].no);

														pPiece[i].pos = pPiece[i].OldMovePos;
														if (pFlag)
														{
															pPlayer->Position = pPlayer->OneOldpos;
														}
													}
												}
												//ジョイントが上だったら
												else if (pPiece[i].pos.y - pPiece[i].size.y / 3 > pJoint[j].pos.y)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT);

													if (fourPieceCollision(pPiece[i], i))
													{
														PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;

														}
														// ヒバナエフェクト
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// ピースのアニメーション
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
													}
													else
													{
														Rotreturn(pPiece[i].no);
														colFlag2 = true;
														temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
														PositionPlas(temp, pPiece[i].no);

														pPiece[i].pos = pPiece[i].OldMovePos;
														if (pFlag)
														{
															pPlayer->Position = pPlayer->OneOldpos;
														}

													}

												}
												//ジョイントが下だったら
												else if (pPiece[i].pos.y + pPiece[i].size.y / 3 < pJoint[j].pos.y)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT);

													if (fourPieceCollision(pPiece[i], i))
													{
														PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;

														}
														// ヒバナエフェクト
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// ピースのアニメーション
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
													}
													else
													{
														Rotreturn(pPiece[i].no);
														colFlag2 = true;
														temp = pPiece[i].OldMovePos - pPiece[i].pos;
														PositionPlas(temp, pPiece[i].no);

														pPiece[i].pos = pPiece[i].OldMovePos;

														if (pFlag)
														{
															pPlayer->Position = pPlayer->OneOldpos;
														}

													}

												}

												break;
											}
											break;
										}
									}

								}
							}
						}


					}
					if (!colFlag2)
					{

						if (fourNomalPieceCollision(pPiece[i], i))
						{

						}
						else
						{
							Rotreturn(pPiece[i].no);

							colFlag2 = true;
							D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
							PositionPlas(temp, pPiece[i].no);
							pPiece[i].pos = pPiece[i].OldMovePos;
							pPiece[i].OldPos = pPiece[i].pos;
							if (pFlag)
							{
								pPlayer->Position = pPlayer->OneOldpos;
								pPlayer->oldpos = pPlayer->Position;
							}

						}


						for (int m = 0; m < 3; m++)
						{
							if (!colFlag2)
							{

								for (int n = 0; n < 4; n++)
								{

									if (pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) - pSplitStage->size.y / 2 < pPiece[i].pos.y &&
										pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) + pSplitStage->size.y / 2 > pPiece[i].pos.y &&
										pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) - pSplitStage->size.x / 2 < pPiece[i].pos.x &&
										pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) + pSplitStage->size.x / 2 > pPiece[i].pos.x)
									{
										pPiece[i].pos = pSplitStage->Split34[n][m];

										if (fourNomalPieceCollision(pPiece[i], i))
										{
											D3DXVECTOR2 temp = pPiece[i].pos - pPiece[i].OldPos;

											PositionPlas(temp, pPiece[i].no);
											if (pFlag)
											{
												pPlayer->Position += temp;
												pPlayer->oldpos = pPlayer->Position;

											}

										}
										else
										{
											colFlag2 = true;
											D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
											PositionPlas(temp, pPiece[i].no);
											pPiece[i].pos = pPiece[i].OldMovePos;
											Rotreturn(pPiece[i].no);
											if (pFlag)
											{
												pPlayer->Position = pPlayer->OneOldpos;
											}

										}

										break;
									}
								}
							}
						}

					}
				}

			}
		}
	}

}

//---------------------------------
//パズルの当たり判定
//くっつくけるかどうか
//---------------------------------
void PuzzleCollision()
{
	punum = -1;
	bool colFlag = false;//当たって入ったか
	bool pFlag = false;
	PUZZLE* pPuzzle = GetPuzzle();
	PLAYER* pPlayer = GetPlayer();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{

			if (pPuzzle[i].MoveEndFlag)
			{
				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					pPuzzle[j].OneOldPosition = pPuzzle[j].Position;

				}

				pPuzzle[i].MoveEndFlag = false;

				if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y &&
					pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y &&
					pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x &&
					pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
					)
				{
					pFlag = true;
				}


				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					if (j != i)
					{
						//動かし終わったパズルと今のパズルが重なっているか
						bool hitFlag = CollisionBB(pPuzzle[i].Position, pPuzzle[j].Position, pPuzzle[i].Size, D3DXVECTOR2(pPuzzle[j].Size.x, pPuzzle[j].Size.y));

						if (hitFlag)	//重なっていたら
						{
							//ポジションの差分
							float x = pPuzzle[i].Position.x - pPuzzle[j].Position.x;
							float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//絶対値の取得
							x = fabsf(x);
							y = fabsf(y);
							//x = x / 1.5f;
							//パズルが横のほうに有ったら
							if (x >= y)
							{
								//動かしているパズルが右にあったら
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{
									//パズルのチップの左と右が有っているか
									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);
										//右が開いているか
										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_SIZE, pPuzzle[j].Position.y);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//有っていたらトゥルー
												colFlag = true;

											}
											else
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										//パズルのチップの右と左が有っていなかったら

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//動かしているパズルが左にあったら
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									//パズルのチップの右と左が有っているか
									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);
										//左が開いているか

										if (hitFlag) {
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_SIZE, pPuzzle[j].Position.y);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//有っていたらトゥルー
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの右と左が有っていなかったら
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							//パズルが縦のほうに有ったら
							else if (y > x)
							{
								//動かしているパズルが上にあったら

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{
									//パズルのチップの下と上が有っているか
									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										//上が開いているか
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_SIZE);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの下と上が有っていなかったら

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//動かしているパズルが下にあったら
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{
									//パズルのチップの上と下が有っているか

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										//下が開いているか
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											//空いていたらポジションを移動する
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_SIZE);
											//四方向のパズルに合うか
											if (fourCollision(pPuzzle[i], i))
											{
												//合っていたらトゥルー
												colFlag = true;

											}
											else
											{
												//合っていなかったら元の戻す
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//開いていなかったら元に戻す

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//パズルのチップの上と下が有っていなかったら元に戻す
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}


							//hitFlag = CollisionBB(pPuzzle[i].Position,D3DXVECTOR2( pPuzzle[j].Position.x
							//	pPuzzle[i].Size, pPuzzle[j].Size);
						}
						else
						{
							//ポジションの差分
							float abx = (pPuzzle[i].Position.x) - pPuzzle[j].Position.x;
							float aby = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//絶対値の取得
							abx = fabsf(abx);
							aby = fabsf(aby);
							//付けたいパズルの近くにいるか
							if ((abx < 20.0f && aby < 200.0f) || (abx < 200.0f && aby < 20.0f))
							{

								//パズルが横のほうに有ったら

								if (abx >= aby)
								{
									//動かしているパズルが右にあったら
									if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
									{
										//パズルのチップの左と右が有っているか

										if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
										{
											//右が開いているか

											hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

											if (hitFlag)
											{
												//空いていたらポジションを移動する
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_SIZE, pPuzzle[j].Position.y);
												//四方向のパズルに合うか

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}
										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									//動かしているパズルが左にあったら
									if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
									{

										if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);

											if (hitFlag) {
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_SIZE, pPuzzle[j].Position.y);
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}

								}
								else if (aby > abx)
								{
									//動かしているパズルが上にあったら

									if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
									{

										if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

											if (hitFlag)
											{
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_SIZE);
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;
												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									//動かしているパズルが下にあったら
									if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
									{

										if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

											if (hitFlag)
											{
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_SIZE);

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;
												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}

								}

							}

						}
					}

				}
				if (!colFlag)
				{
					//当たったけど入っていなかったら
					float pPx = pPuzzle[i].Position.x - pPuzzle[i].oldPosition.x;
					float pPy = pPuzzle[i].Position.y - pPuzzle[i].oldPosition.y;
					pPx = fabsf(pPx);
					pPy = fabsf(pPy);
					//前回とほぼ位置が変わっていなかったら
					if (pPx + pPy < 10)
					{
						//pPuzzle[i].Position.x += (20.0f);
						pPuzzle[i].Position.y -= (20.0f);

					}
					pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

					pPuzzle[i].oldPosition = pPuzzle[i].Position;

					pPuzzle[i].Position = pPuzzle[i].oldPosition;

				}
				if (pFlag) {

					MOUSE* pMouse = GetMouse();

					pPlayer->Position = pPuzzle[i].Position - pMouse->PlPos;
				}


			}
		}

	}


}
//===========================================
//四角形同士が当たっているかあたっていないかを判定するだけ
//引数: 中央座標１、中央座標２、サイズ１、サイズ２
//戻り値： true当たっている:false当っていない
//================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2	min1, min2;	//四角形の最小座標（左上）
	D3DXVECTOR2 max1, max2;	//四角形の最大座標(右下)

	//四角形１左上
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//四角形１右下
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//四角形２左上
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//四角形２右下
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//衝突判定

	if (max1.x < min2.x)//判定1
	{
		return false;
	}
	if (max2.x < min1.x)//判定2
	{
		return false;
	}
	if (max1.y < min2.y)//判定3
	{
		return false;
	}
	if (max2.y < min1.y)//判定4
	{
		return false;
	}
	return true;


	//if (max1.x > min2.x)//判定1
	//{
	//	return true;
	//}
	//if (max2.x > min1.x)//判定2
	//{
	//	return true;
	//}
	//if (max1.y > min2.y)//判定3
	//{
	//	return true;
	//}
	//if (max2.y > min1.y)//判定4
	//{
	//	return true;
	//}
	//return false;

}
//=================================================
//円同士が当たっているかあたっていないかを判定するだけ
//引数: 中央座標１、中央座標２、半径１、半径２
//戻り値： true当たっている:false当っていない
//================================================
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	D3DXVECTOR2 vDisitance = pos1 - pos2;

	float Lenght;
	Lenght = D3DXVec2LengthSq(&vDisitance);	//ルートを使わない版
	//Length = D3DXVec2Length(&vDisitance);	//ルートを使う版(正確な長さ)

	//半径の総和

	float size = (size1 + size2) * (size1 + size2);
	//float size = (size1+size2);	ルート版

	//衝突判定
	if (size > Lenght)
	{
		return	true;
	}

	return false;
}
//--------------------------------------------
//パズルの移動先が空いているか
//引数：元のパズル、移動したいパズルの添え字、移動したい場所
//----------------------------------------------
bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{

				switch (direcsion)
				{
				case UP:

					//puzzleの上に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_SIZE - (PUZZLE_SIZE / 2) < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_SIZE + (PUZZLE_SIZE / 2) > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.x)
					{

						punum = i;
						return false;
					}

					break;
				case DOWN:
					//if (puzzle.Position.y + PUZZLE_SIZE == pPuzzle[i].Position.y)	return false;
										//puzzleの下に別のパズルがあるか

					if (puzzle.Position.y + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (puzzle.Position.x - PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;
										//puzzleの左に別のパズルがあるか

					if (puzzle.Position.y - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (puzzle.Position.x + PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;
					//puzzleの右に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_SIZE / 3 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 3 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//プレイヤーの移動先にパズルがあるか
//引数：元のパズル、移動したいパズルの添え字、移動したい場所
//----------------------------------------------
bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzleの上に別のパズルがあるか
					if (puzzle.Position.y - PUZZLE_SIZE == pPuzzle[i].Position.y)return false;

					if (puzzle.Position.y - PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 2 > pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 2 < pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//puzzleの下に別のパズルがあるか
					if (puzzle.Position.y + PUZZLE_SIZE == pPuzzle[i].Position.y)	return false;

					if (puzzle.Position.y + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//puzzleの左に別のパズルがあるか
					if (puzzle.Position.x - PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//puzzleの右に別のパズルがあるか
					if (puzzle.Position.x + PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}



//--------------------------------------------
//4方向にパズルがあるかあったらピースの出っ張りが有っているか
//----------------------------------------------
bool fourCollision(PUZZLE puzzle, int index)
{
	PUZZLE* pPuzzle = GetPuzzle();
	punum = -1;

	bool hitFlag;

	hitFlag = PuzzleOpen(puzzle, index, RIGHT);
	//右が開いていなかったら
	if (!hitFlag)
	{
		//パズルのチップの右と左が有っているか
		if ((puzzle.Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeRight == STEAT_NUM && pPuzzle[punum].Puzzle_TypeLeft == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}

	//左が開いていなかったら
	hitFlag = PuzzleOpen(puzzle, index, LEFT);

	if (!hitFlag)
	{
		//パズルのチップの左と右が有っているか
		if ((puzzle.Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeRight == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeRight == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_NUM && pPuzzle[punum].Puzzle_TypeRight == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}
	hitFlag = PuzzleOpen(puzzle, index, UP);


	if (!hitFlag)
	{	//上が開いていなかったら

		//パズルのチップの上と下が有っているか
		if ((puzzle.Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeDown == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeDown == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeUp == STEAT_NUM && pPuzzle[punum].Puzzle_TypeDown == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}

	hitFlag = PuzzleOpen(puzzle, index, DOWN);


	if (!hitFlag)
	{
		//下が開いていなかったら

		//パズルのチップの下と上が有っているか
		if ((puzzle.Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeUp == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeUp == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeDown == STEAT_NUM && pPuzzle[punum].Puzzle_TypeUp == STEAT_NUM))
		{
			//合っていたら何もしない
		}
		else
		{
			//合っていなかったら
			return false;
		}
	}


	return true;

}
//--------------------------------------
//ピースの中のものを移動させる
//引数：移動させたい分のポジション、そのピース番号
//--------------------------------------
void PositionPlas(D3DXVECTOR2 num,int pinNo)
{
	BLOCK* pBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	GOAL* pGoal = GetGoal();
	THORNBLOCK* pThornBlock = GetThornBlock();
	JUMPSTAND* pJumpStand = GetJumpStand();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();
	SWITCH* pSwitch = GetSwitch();
	SWITCHWALL* pSwitchWall = GetSwitchWall();
	WARP* pWarp = GetWarp();
	BROKEN* pBroken = GetBroken();
	SHEERFLOORS* pSheerFloors = GetSheerFloors();
	START* pStart = GetStart();
	HIGH* pHigh = GetHigh();
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (pBlock[i].UseFlag)
		{

			if (pBlock[i].PieceIndex == pinNo)
			{

				pBlock[i].Position += num;

			}

		}

	}
	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (pBroken[i].UseFlag)
		{

			if (pBroken[i].index == pinNo)
			{

				pBroken[i].Postion += num;

			}

		}

	}
	for (int i = 0; i < HIGH_MAX; i++)
	{//ブロック動かす
		if (pHigh[i].UseFlag)
		{
			if (pHigh[i].index == pinNo)
			{
				pHigh[i].Postion += num;
			}

		}

	}

	for (int i = 0; i < SHEERFLOORS_NUM; i++)
	{//ブロック動かす
		if (pSheerFloors[i].use)
		{
			if (pSheerFloors[i].index == pinNo)
			{
				pSheerFloors[i].pos += num;
			}

		}

	}
	for (int i = 0; i < START_MAX; i++) {
		if (pStart[i].UseFlag) {
			if (pStart[i].PieceIndex == pinNo) {
				pStart[i].pos += num;
			}
		}
	}

	for (int i = 0; i < JOINT_MAX; i++)
	{
		if (pJoint[i].useFlag)
		{
			if (pJoint[i].pieNo == pinNo)
			{
				pJoint[i].pos += num;
			}

		}

	}
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzleCip[i].UseFlag)
		{
			if (pPuzzleCip[i].PieceIndex == pinNo)
			{
				pPuzzleCip[i].Position += num;
			}
		}
	}
	if (pGoal->UseFlag)
	{
		if (pGoal->pieceIndex == pinNo)
		{
			pGoal->Pos += num;
		}
	}
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{//とげ
		if (pThornBlock[i].UseFlag)
		{
			if (pThornBlock[i].PieceIndex == pinNo)
			{
				pThornBlock[i].Postion += num;
			}
		}

	}
	for (int i = 0; i < JUMPSTAND_MAX; i++)
	{
		if (pJumpStand[i].UseJumpStand)
		{
			if (pJumpStand[i].NowPieceIndex == pinNo)
			{
				pJumpStand[i].pos += num;
			}
		}
	}
	for (int i = 0; i < SPAWN_POINT_MAX; i++)
	{
			if (pSpawnPoint[i].UseFlag)
			{
				if (pSpawnPoint[i].PieceIndex == pinNo)
				{
					pSpawnPoint[i].Position += num;
				}

			}

		

	}
	for (int i = 0; i < SWITCH_MAX; i++)
	{
		if (pSwitch[i].UseFlag)
		{
			if (pSwitch[i].PieceIndex == pinNo)
			{
				pSwitch[i].pos += num;
			}

		}
	}
	for (int i = 0; i < SWITCHWALL_MAX; i++)
	{
		if (pSwitchWall[i].UseFlag)
		{
			if (pSwitchWall[i].PieceIndex == pinNo)
			{
				pSwitchWall[i].pos += num;
			}

		}
	}
	//ワープ
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (pWarp[i].UseFlag)
		{
			if (pWarp[i].PieceIndex == pinNo)
			{
				pWarp[i].Position += num;
			}

		}
	}

}
//--------------------------------------------
//プレイヤーの移動先にピースがあるか
//引数：元のピース、移動したいピースの添え字、移動したい場所
//----------------------------------------------
bool PlayerPieceOpen(Piece p, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzleの上に別のパズルがあるか
					if (p.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)return false;

					if (p.pos.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 > pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 < pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//pの下に別のパズルがあるか
					if (p.pos.y - PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)	return false;

					if (p.pos.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//pの左に別のパズルがあるか
					if (p.pos.x - PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//pの右に別のパズルがあるか

   					if (p.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x&& p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}

//--------------------------------------------
//ドッペルゲンガーの移動先にピースがあるか
//引数：元のピース、移動したいピースの添え字、移動したい場所
//----------------------------------------------
bool DoppelPieceOpen(Piece p, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzleの上に別のパズルがあるか
					if (p.pos.y - PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)return false;

					if (p.pos.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 > pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 < pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//pの下に別のパズルがあるか
					if (p.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)	return false;

					if (p.pos.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//pの左に別のパズルがあるか
					if (p.pos.x - PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//pの右に別のパズルがあるか

					if (p.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//4方向にパズルがあるかあったらピースの出っ張りが有っているか
//----------------------------------------------
bool fourPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				if (piece.pos == pPiece[i].pos)
				{
					return false;
				}
			}
		}
	}

	hitFlag = PieceOpen(piece, index, RIGHT);
	//右が開いていなかったら
	if (!hitFlag)
	{
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//元のピースのジョイントだったら
			{
				if (piece.pos.x + PIECE_SIZE / 3 < pJoint[i].pos.x)	//ジョイントがピースの右だったら
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo ==pPiece[punum].no)
						{
							if (pPiece[punum].pos.x - PIECE_SIZE / 3 > pJoint[j].pos.x)
							{
								JointFlag = true;

								//パズルのチップの右と左が有っているか
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//合っていたら何もしない
								}
								else
								{
									//合っていなかったら
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}


	}
	JointFlag = false;

	//左が開いていなかったら
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		//パズルのチップの左と右が有っているか
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//元のピースのジョイントだったら
			{
				if (piece.pos.x - PIECE_SIZE / 3 > pJoint[i].pos.x)	//ジョイントがピースの右だったら
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.x + PIECE_SIZE / 3 < pJoint[j].pos.x)
							{
								JointFlag = true;

								//パズルのチップの右と左が有っているか
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//合っていたら何もしない
								}
								else
								{
									//合っていなかったら
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}

	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//上が開いていなかったら

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//元のピースのジョイントだったら
			{
				if (piece.pos.y + PIECE_SIZE / 3 < pJoint[i].pos.y)	//ジョイントがピースの上だったら
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{

							if (pPiece[punum].pos.y - PIECE_SIZE / 3 > pJoint[j].pos.y)	//下
							{
								JointFlag = true;

								//パズルのチップの右と左が有っているか
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//合っていたら何もしない
									
								}
								else
								{
									//合っていなかったら
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;


		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		//下が開いていなかったら

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//元のピースのジョイントだったら
			{
				if (piece.pos.y - PIECE_SIZE / 3 > pJoint[i].pos.y)	//ジョイントがピースの下だったら
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.y + PIECE_SIZE / 3 < pJoint[j].pos.y)	//下
							{
								JointFlag = true;
								//パズルのチップの右と左が有っているか
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//合っていたら何もしない
								}
								else
								{
									//合っていなかったら
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}
	}


	return true;

}
//--------------------------------------------
//パズルの移動先が空いているか
//引数：元のパズル、移動したいパズルの添え字、移動したい場所
//----------------------------------------------
bool PieceOpen(Piece piece, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{

				switch (direcsion)
				{
				case DOWN:

					//pieceの上に別のパズルがあるか
					if (piece.pos.y - PIECE_SIZE - (PIECE_SIZE / 2) < pPiece[i].pos.y &&
						piece.pos.y - PIECE_SIZE + (PIECE_SIZE / 2) > pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE / 3 >= pPiece[i].pos.x)
					{

						punum = i;
						return false;
					}

					break;
				case UP:
					//if (piece.pos.y + PUZZLE_SIZE == pPiece[i].pos.y)	return false;
										//pieceの下に別のパズルがあるか

					if (piece.pos.y + PIECE_SIZE - PIECE_SIZE / 2 < pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE + PIECE_SIZE / 2 > pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE / 3 >= pPiece[i].pos.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (piece.pos.x - PUZZLE_SIZE == pPiece[i].pos.x)	return false;
										//pieceの左に別のパズルがあるか

					if (piece.pos.y - PIECE_SIZE / 3 <= pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE / 3 >= pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE - PIECE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x - PIECE_SIZE + PIECE_SIZE / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (piece.pos.x + PUZZLE_SIZE == pPiece[i].pos.x)	return false;
					//pieceの右に別のパズルがあるか
					if (piece.pos.y - PIECE_SIZE / 3 < pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE / 3 > pPiece[i].pos.y &&
						piece.pos.x + PIECE_SIZE - PIECE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE + PIECE_SIZE / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//4方向にパズルがあるかあったらピースのノーマルか
//----------------------------------------------
bool fourNomalPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{


			if (i != index)
			{
				if (piece.pos == pPiece[i].pos)
				{
					return false;
				}
			}
		}

	}


	hitFlag = PieceOpen(piece, index, RIGHT);
	//右が開いていなかったら
	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo ==  piece.no)
			{
				if (pJoint[j].pos.x>piece.pos.x+piece.size.x/3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)	//元のピースのジョイントだったら
			{
				//ジョイントがなかったら
				if (pPiece[punum].pos.x - pPiece[punum].size.x / 3 > pJoint[i].pos.x)
				{
					//合っていなかったら
					return false;
				}	
			}
		}
	}
	JointFlag = false;

	//左が開いていなかったら
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.x < piece.pos.x - piece.size.x / 3)
				{
					return false;
				}
			}
		}

		//パズルのチップの左と右が有っているか
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{				//ジョイントがなかったら

				if (pPiece[punum].pos.x + pPiece[punum].size.x / 3 < pJoint[i].pos.x)
				{
					//合っていなかったら
					return false;
				}
			}
		}
	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//上が開いていなかったら
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.y < piece.pos.y - piece.size.y / 3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{
				//ジョイントがなかったら

				if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[i].pos.y)	//下
				{
					{
						//合っていなかったら
						return false;
					}


				}


			}

		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.y > piece.pos.y + piece.size.y / 3)
				{
					return false;
				}
			}
		}

		//下が開いていなかったら

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{
				//ジョイントがなかったら
				if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[i].pos.y)	//下
				{
					//合っていなかったら
					return false;

				}


			}

		}

	}


	return true;

}
//--------------------------------
//回転を元に戻す
//引数：パズルの添え字
//--------------------------------
void Rotreturn(int index)
{
	MOUSE* pMouse = GetMouse();
	CURSOR* pCursor = GetCurso();
	for (int i = 0; i < pCursor->RotIndex; i++)
	{
		RotateMapChipL(index);

	}

}
//------------------------------
//スプリットステージの外に出てるか
//
//------------------------------
bool SpritStageCollision(Piece p)
{
	SplitStage* pSprit = GetSplitStage();

	D3DXVECTOR2 up = pSprit->Split34[0][0];
	D3DXVECTOR2 down = pSprit->Split34[0][2];
	D3DXVECTOR2 right = pSprit->Split34[3][0];
	D3DXVECTOR2 left = pSprit->Split34[0][1];

	float x = p.pos.x;

	//上の判定
	if (p.pos.y > up.y + SPLIT_SIZE / 2)
	{
		return false;
	}
	//下
	if (p.pos.y < down.y - SPLIT_SIZE / 2)
	{
		return false;
	}
	//右
	if (p.pos.x > right.x + SPLIT_SIZE/2)
	{
		return false;
	}
	//左


	if (x < left.x - 240 / 2);
	{
		if (p.pos.x < left.x - 240 / 2)
		{
			return false;

		}
	}

	return true;
}


