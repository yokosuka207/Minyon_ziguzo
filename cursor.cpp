/*================================================================================
	cursor.cpp
 
		カーソル
												Author: SaitoReito
												 Date : 2022/09/12
================================================================================*/
#include "cursor.h"		// 自身
#include "mouse.h"
#include "xmouse.h"
#include "puzzle.h"
#include"block.h"
#include"texture.h"
#include"sprite.h"
//#include"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include"player.h"
#include"MapChip.h"
#include"joint.h"
#include"puzzlecip.h"
#include"goal.h"
#include"thorn_block.h"
//#include"puzzlecip.h"
#include"jump_stand.h"
#include"spawnpoint.h"
#include "switch.h"
#include "SwitchWall.h"
#include"warp.h"
#include"broken.h"
#include"SheerFloors.h"
#include"goal_key.h"
#include "start.h"
//--------------------------------------------------
// マクロ定義
//--------------------------------------------------
#define CURSOR_SIZE_W	(50)		// カーソルのポリゴンの横のサイズ
#define CURSOR_SIZE_H	(50)		// カーソルのポリゴンの縦のサイズ

#define CURSOR_SPEED	(2)		// カーソルの移動速度

//--------------------------------------------------
// プロトタイプ宣言
//--------------------------------------------------

//--------------------------------------------------
// グローバル変数
//--------------------------------------------------
static CURSOR g_Cursor;
static char *g_CursorTextureName = (char*)"data\\texture\\cursor_default.png";
static char* g_CursorCatchTextureName = (char*)"data\\texture\\cursor_catch.png";
static int g_CursorTextureNo[2];

static bool oneFlag = false;	//マウスでパズルを一つ持っているか
static int g_CursorIndex = -1;	//マウスの掴んだパズルの番号入れ
static int NoIndex = -1;	//マウスで掴んだピース番号
static bool g_CursorFlag = false;	//マウスをクリックしているか

//==================================================
// カーソル初期化
//==================================================
HRESULT InitCursor()
{
	oneFlag = false;	//マウスでパズルを一つ持っているか
	g_CursorIndex = -1;	//マウスの掴んだパズルの番号入れ
	NoIndex = -1;	//マウスで掴んだピース番号
	 g_CursorFlag = false;	//マウスをクリックしているか


	// カーソルの初期化
	{
		g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
		g_Cursor.pos = g_Cursor.oldPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Cursor.sp = D3DXVECTOR2(1.0f, 1.0f);
		g_Cursor.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Cursor.texNo = LoadTexture(g_CursorTextureName);
		g_Cursor.RotIndex = 0;
		g_Cursor.pFlag = false;
		g_Cursor.useFlag = false;
		g_Cursor.type = 0;
	}
	g_CursorTextureNo[0] = LoadTexture(g_CursorTextureName);
	g_CursorTextureNo[1] = LoadTexture(g_CursorCatchTextureName);

	return S_OK;
}

//==================================================
// カーソル終了処理
//==================================================
void UninitCursor()
{

}

//==================================================
// カーソル更新処理
//==================================================
void UpdateCursor()
{
	//Mouse_GetState(&g_Mouse);

	PUZZLE* pPuzzle = GetPuzzle();
	BLOCK* pBlock = GetBlock();
	PLAYER* pPlayer = GetPlayer();
	Piece* pPiece = GetPiece();
	BLOCK* pCipBlock = GetChipBlock();
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
	GKey* pGkey = GetGKey();
	START* pStart = GetStart();
	//g_Cursor.useFlag = Mouse_IsLeftDown();

	// 絶対モード時 カーソル移動
	g_Cursor.pos.x = GetXMousePosX();
	g_Cursor.pos.y = GetXMousePosY();
	
	//g_Cursor.oldPos.x = g_Cursor.pos.x -= SCREEN_WIDTH / 2;
	//g_Cursor.pos.y = -g_Cursor.pos.y + SCREEN_HEIGHT / 2;

	if (Mouse_IsLeftDown()) {
		g_Cursor.oldPos = g_Cursor.pos;
		//[----------移動----------
		if (GetThumbRightX(0) < -0.2f || GetThumbRightX(0) > 0.2f) {				// 右スティック	左右
			g_Cursor.pos.x += GetThumbRightX(0) * 12;	// 左右移動
		}
		if (GetThumbRightY(0) < -0.2f || GetThumbRightY(0) > 0.2f) {				// 右スティック	上下
			g_Cursor.pos.y -= GetThumbRightY(0) * 12;	// 上下移動
		}
		//----------移動----------]

		//[----------壁判定 (壁の上下左右)----------
		// 上下
		if (g_Cursor.pos.y - g_Cursor.size.y / 2 < SCREEN_LIMIT_UP ||
			g_Cursor.pos.y + g_Cursor.size.y / 2 > SCREEN_LIMIT_DOWN) 
		{
			g_Cursor.pos.y = g_Cursor.oldPos.y;
		}
		// 左右
		if(	g_Cursor.pos.x - g_Cursor.size.x / 2 < SCREEN_LIMIT_LEFT ||
			g_Cursor.pos.x + g_Cursor.size.x / 2 > SCREEN_LIMIT_RIGHT) 
		{
			g_Cursor.pos.x = g_Cursor.oldPos.x;
		}
		//-----------------------------------------]

		if (Mouse_IsLeftDown())
		{
			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				//if (pPuzzle[i].UseFlag)
				//{
				//	pPuzzle[i].MoveEndFlag = false;
				//	if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 3 < g_Cursor.PosY&&
				//		pPuzzle[i].Position.y + pPuzzle[i].Size.y / 3 > g_Cursor.PosY&&
				//		pPuzzle[i].Position.x - pPuzzle[i].Size.x / 3 < g_Cursor.PosX&&
				//		pPuzzle[i].Position.x + pPuzzle[i].Size.x / 3 > g_Cursor.PosX&&
				//		!oneFlag)
				//	{
				//		if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y&&
				//			pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y&&
				//			pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x&&
				//			pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
				//			)
				//		{
				//		}
				//		else
				//		{
				//			oneFlag = true;
				//			g_CursorIndex = i;
				//			pPuzzle[i].oldPosition = pPuzzle[i].Position;
				//		}
				//	}
				//	else if (oneFlag && i == g_CursorIndex)
				//	{
				//		pPuzzle[g_CursorIndex].Position.x = g_Cursor.PosX;
				//		pPuzzle[g_CursorIndex].Position.y = g_Cursor.PosY;
				//		pPuzzle[g_CursorIndex].MoveFlag = true;
				//		if (GetKeyboardTrigger(DIK_A))	//aキーが押されたら
				//		{				//押されてる時の処理
				//			pPuzzle[g_CursorIndex].Rotation += 90.0f;
				//			pPuzzle[g_CursorIndex].RotNum++;
				//			if (pPuzzle[g_CursorIndex].RotNum >=4)
				//			{
				//				pPuzzle[g_CursorIndex].RotNum = 0;
				//			}
				//			if (pPuzzle[g_CursorIndex].Block_Type == TYPE_GRAND)
				//			{
				//				for (int j = 0; j < 4; j++)
				//				{
				//					if (pPuzzle[g_CursorIndex].blockIndex[j] != -1)
				//					{
				//						//pBlock[pPuzzle[g_CursorIndex].blockIndex[j]].Rotation += 90.0f;
				//					}
				//				}
				//			}
				//			PuzzleTypeShift(g_CursorIndex);
				//		}
				//	}
				//}

				if (pPiece[i].UseFlag)
				{

					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 3 < -g_Cursor.pos.y+SCREEN_HEIGHT/2 &&
						pPiece[i].pos.y + PUZZLE_HEIGHT / 3 > -g_Cursor.pos.y + SCREEN_HEIGHT / 2 &&
						pPiece[i].pos.x - PUZZLE_WIDHT / 3 < g_Cursor.pos.x - SCREEN_WIDTH / 2 &&
						pPiece[i].pos.x + PUZZLE_WIDHT / 3 > g_Cursor.pos.x - SCREEN_WIDTH / 2 &&
						!oneFlag)
					{
						//プレーヤーが持ったピースの中にいたら
						if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
							pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
							pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
							pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x
							)
						{
							g_Cursor.pFlag = true;
							pPlayer->OneOldpos = pPlayer->Position;
						}

						g_Cursor.RotIndex = 0;

						oneFlag = true;
						pPiece[i].MoveFlag = true;
						g_CursorIndex = i;
						NoIndex = pPiece[i].no;
						pPiece[i].OldMovePos = pPiece[i].pos;
						g_Cursor.type = 1;
					}
					else if (oneFlag && i == g_CursorIndex)
					{
						pPiece[g_CursorIndex].OldPos = pPiece[g_CursorIndex].pos;

						pPiece[g_CursorIndex].pos.x = g_Cursor.pos.x - SCREEN_WIDTH / 2;
						pPiece[g_CursorIndex].pos.y = -g_Cursor.pos.y + SCREEN_HEIGHT / 2;
						//pPiece[g_CursorIndex].MoveFlag = true;
						D3DXVECTOR2 temp = (pPiece[g_CursorIndex].pos - pPiece[g_CursorIndex].OldPos);

						for (int i = 0; i < BLOCK_CHIP_MAX; i++)
						{//ブロック動かす
							if (pCipBlock[i].UseFlag)
							{
								if (pCipBlock[i].PieceIndex == NoIndex)
								{
									pCipBlock[i].Position += temp;
								}

							}

						}
						for (int i = 0; i < BROKEN_MAX; i++)
						{//ブロック動かす
							if (pBroken[i].UseFlag)
							{
								if (pBroken[i].index == NoIndex)
								{
									pBroken[i].Postion += temp;
								}

							}

						}
						for (int i = 0; i < SHEERFLOORS_NUM; i++)
						{//ブロック動かす
							if (pSheerFloors[i].use)
							{
								if (pSheerFloors[i].index == NoIndex)
								{
									pSheerFloors[i].pos += temp;
								}

							}

						}
						for (int i = 0; i < JOINT_MAX; i++)
						{//凹凸
							if (pJoint[i].useFlag)
							{
								if (pJoint[i].pieNo == NoIndex)
								{
									pJoint[i].pos += temp;
								}

							}
						}
						for (int i = 0; i < PUZZLE_MAX; i++)
						{//ピースチップ
							if (pPuzzleCip[i].UseFlag)
							{
								if (pPuzzleCip[i].PieceIndex == NoIndex)
								{
									pPuzzleCip[i].Position += temp;
								}
							}
						}
						if (pGoal->UseFlag)
						{//ゴール
							if (pGoal->pieceIndex == NoIndex)
							{
								pGoal->Pos += temp;
							}
						}
						for (int i = 0; i < START_MAX; i++) {
							if (pStart[i].UseFlag) {
								if (pStart[i].PieceIndex == NoIndex) {
									pStart[i].pos += temp;
								}
							}
						}
						//if (pGkey->UseFlag)
						//{//ゴール
						//	if (pGkey-> == NoIndex)
						//	{
						//		pGkey->Pos += temp;
						//	}
						//}
						for (int i = 0; i < THORN_BLOCK_MAX; i++)
						{//とげ
							if (pThornBlock[i].UseFlag)
							{
								if (pThornBlock[i].PieceIndex == NoIndex)
								{
									pThornBlock[i].Postion += temp;
								}
							}

						}
						for (int i = 0; i < JUMPSTAND_MAX; i++)
						{//ジャンプスタンド
							if (pJumpStand[i].UseJumpStand)
							{
								if (pJumpStand[i].PieceIndex == NoIndex)
								{
									pJumpStand[i].pos += temp;
								}
							}
						}
						for (int i = 0; i < SPAWN_POINT_MAX; i++)
						{//スポーンポイント
							if (pSpawnPoint[i].UseFlag)
							{
								if (pSpawnPoint[i].PieceIndex == NoIndex)
								{
									pSpawnPoint[i].Position += temp;
								}

							}

						}
						for (int i = 0; i < SWITCH_MAX; i++)
						{//スイッチ
							if (pSwitch[i].UseFlag)
							{
								if (pSwitch[i].PieceIndex == NoIndex)
								{
									pSwitch[i].pos += temp;
								}

							}
						}
						for (int i = 0; i < SWITCHWALL_MAX; i++)
						{//スイッチ壁
							if (pSwitchWall[i].UseFlag)
							{
								if (pSwitchWall[i].PieceIndex == NoIndex)
								{
									pSwitchWall[i].pos += temp;
								}

							}
						}
						for (int i = 0; i < WARP_MAX; i++)
						{//ワープ
							if (pWarp[i].UseFlag)
							{
								if (pWarp[i].PieceIndex == NoIndex)
								{
									pWarp[i].Position += temp;
								}

							}
						}

						if (!g_Cursor.pFlag)
						{
							if (Keyboard_IsKeyTrigger(KK_A))	//aキーが押されたら
							{
								RotateMapChipR(NoIndex);
								g_Cursor.RotIndex += 1;

							}
						}
						else
						{
							pPlayer->Position += temp;
							pPlayer->oldpos = pPlayer->Position;
						}
					}
					else {
						g_Cursor.type = 0;
					}
				}
			}
		}
	}
	if (!Mouse_IsLeftDown())
	{
		if (g_CursorIndex != -1)
		{
			pPuzzle[g_CursorIndex].MoveFlag = false;
			pPuzzle[g_CursorIndex].MoveEndFlag = true;
			pPiece[g_CursorIndex].MoveEndFlag = true;
			pPiece[g_CursorIndex].MoveFlag = false;

			//g_Cursor.RotIndex = 0;
			g_Cursor.pFlag = false;
		}
		oneFlag = false;
		g_CursorIndex = -1;
		NoIndex = -1;
		g_Cursor.type = 0;
	}
}

//==================================================
// カーソル表示処理
//==================================================
void DrawCursor()
{
	SetWorldViewProjection2D();

	if (g_Cursor.useFlag) {
		// テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_CursorTextureNo[g_Cursor.type]));
		// ポリゴンの描画
		SpriteDrawColorRotation(g_Cursor.pos.x, g_Cursor.pos.y, 0.0f, g_Cursor.size.x, g_Cursor.size.y, 0.0f, g_Cursor.color, 1.0f, 1.0f, 1.0f, 1);
	}
}

//==================================================
// カーソルセット関数
// 引数：中心座標, サイズ
//==================================================
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Cursor.pos = g_Cursor.oldPos = pos;
	g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
	//g_Cursor.size = size;

	g_Cursor.useFlag = true;
}


//==================================================
// カーソルゲット関数
//==================================================
CURSOR* GetCurso()
{
	return &g_Cursor;
}

//==================================================
// カーソル削除関数
//==================================================
void DeleteCursor()
{
	g_Cursor.useFlag = false;
}
