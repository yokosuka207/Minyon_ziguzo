#include "mouse.h"
#include "xmouse.h"
#include "puzzle.h"
#include"block.h"
#include"texture.h"
#include"sprite.h"
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

MOUSE Mouse;
static bool oneFlag = false;	//マウスでパズルを一つ持っているか
static int MouseIndex = -1;	//マウスの掴んだパズルの番号入れ
static int NoIndex = -1;	//マウスで掴んだピース番号
static bool MouseFlag = false;	//マウスをクリックしているか

long y,x;

static Mouse_State g_Mouse, g_OldMouse;

//新保翔麻
HRESULT InitGameMouse()
{
	bool oneFlag = false;
	 MouseIndex = -1;
	 NoIndex = -1;
	Mouse.PosX = GetMousePosX();
	Mouse.PosY = GetMousePosY();
	Mouse.oldPosX = GetMousePosX();
	Mouse.oldPosY = GetMousePosY();
	Mouse.RotIndex = 0;
	Mouse.UseFlag = false;
	Mouse.pFlag = false;

	return S_OK;
}

void UninitGameMouse()
{
}

void UpdateGameMouse()
{
	// マウスの状態構造体のポインタをもらう
	g_OldMouse = g_Mouse;
	Mouse_GetState(&g_Mouse);

	//PUZZLE* pPuzzle = GetPuzzle();
	//BLOCK* pBlock = GetBlock();
	//PLAYER* pPlayer = GetPlayer();
	//Piece* pPiece = GetPiece();
	//BLOCK* pCipBlock = GetChipBlock();
	//JOINT* pJoint = GetJoint();
	//PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	//GOAL* pGoal = GetGoal();
	//THORNBLOCK* pThornBlock = GetThornBlock();
	//JUMPSTAND* pJumpStand = GetJumpStand();
	//SpawnPoint* pSpawnPoint = GetSpawnPoint();
	//SWITCH* pSwitch = GetSwitch();
	//SWITCHWALL* pSwitchWall = GetSwitchWall();
	Mouse.oldPosX = Mouse.PosX;
	Mouse.oldPosY = Mouse.PosY;

	y = Mouse.PosY - Mouse.oldPosY;
	x = Mouse.PosX - Mouse.oldPosX;

	Mouse.PosX = GetMousePosX() - SCREEN_WIDTH / 2;
	Mouse.PosY = GetMousePosY() - SCREEN_HEIGHT / 2;

	Mouse.UseFlag = Mouse_IsLeftDown();
	Mouse.ScrollFlag = Mouse_IsMiddleDown();


	if (Mouse.UseFlag)
	{

		//for (int i = 0; i < PUZZLE_MAX; i++)

			//	{
			//			//if (pPuzzle[i].UseFlag)
			//			//{
			//			//	pPuzzle[i].MoveEndFlag = false;
			//			//	if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 3 < Mouse.PosY&&
			//			//		pPuzzle[i].Position.y + pPuzzle[i].Size.y / 3 > Mouse.PosY&&
			//			//		pPuzzle[i].Position.x - pPuzzle[i].Size.x / 3 < Mouse.PosX&&
			//			//		pPuzzle[i].Position.x + pPuzzle[i].Size.x / 3 > Mouse.PosX&&
			//			//		!oneFlag)
			//			//	{
			//			//		if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y&&
			//			//			pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y&&
			//			//			pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x&&
			//			//			pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
			//			//			)
			//			//		{
			//			//		}
			//			//		else
			//			//		{
			//			//			oneFlag = true;
			//			//			MouseIndex = i;
			//			//			pPuzzle[i].oldPosition = pPuzzle[i].Position;
			//			//		}
			//			//	}
			//			//	else if (oneFlag && i == MouseIndex)
			//			//	{
			//			//		pPuzzle[MouseIndex].Position.x = Mouse.PosX;
			//			//		pPuzzle[MouseIndex].Position.y = Mouse.PosY;
			//			//		pPuzzle[MouseIndex].MoveFlag = true;
			//			//		if (GetKeyboardTrigger(DIK_A))	//aキーが押されたら
			//			//		{				//押されてる時の処理
			//			//			pPuzzle[MouseIndex].Rotation += 90.0f;
			//			//			pPuzzle[MouseIndex].RotNum++;
			//			//			if (pPuzzle[MouseIndex].RotNum >=4)
			//			//			{
			//			//				pPuzzle[MouseIndex].RotNum = 0;
			//			//			}
			//			//			if (pPuzzle[MouseIndex].Block_Type == TYPE_GRAND)
			//			//			{
			//			//				for (int j = 0; j < 4; j++)
			//			//				{
			//			//					if (pPuzzle[MouseIndex].blockIndex[j] != -1)
			//			//					{
			//			//						//pBlock[pPuzzle[MouseIndex].blockIndex[j]].Rotation += 90.0f;
			//			//					}
			//			//				}
			//			//			}
			//			//			PuzzleTypeShift(MouseIndex);
			//			//		}
			//			//	}
			//			//}

	//		if (pPiece[i].UseFlag)
	//		{
	//			if (pPiece[i].pos.y - PUZZLE_HEIGHT / 3 < -Mouse.PosY &&
	//				pPiece[i].pos.y + PUZZLE_HEIGHT / 3 > -Mouse.PosY &&
	//				pPiece[i].pos.x - PUZZLE_WIDHT / 3 < Mouse.PosX &&
	//				pPiece[i].pos.x + PUZZLE_WIDHT / 3 > Mouse.PosX &&
	//				!oneFlag)
	//			{
	//				//プレーヤーが持ったピースの中にいたら
	//				if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
	//					pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
	//					pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
	//					pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x
	//					)
	//				{
	//					Mouse.pFlag = true;
	//					pPlayer->OneOldpos = pPlayer->Position;
	//				}

	//				Mouse.RotIndex = 0;

	//				oneFlag = true;
	//				pPiece[i].MoveFlag = true;
	//				MouseIndex = i;
	//				NoIndex = pPiece[i].no;
	//				pPiece[i].OldMovePos = pPiece[i].pos;

	//			}
	//			else if (oneFlag && i == MouseIndex)
	//			{
	//				pPiece[MouseIndex].OldPos = pPiece[MouseIndex].pos;

	//				pPiece[MouseIndex].pos.x = Mouse.PosX;
	//				pPiece[MouseIndex].pos.y = -Mouse.PosY;
	//				//pPiece[MouseIndex].MoveFlag = true;
	//				D3DXVECTOR2 temp = (pPiece[MouseIndex].pos - pPiece[MouseIndex].OldPos);

	//				for (int i = 0; i < BLOCK_CHIP_MAX; i++)
	//				{//ブロック動かす
	//					if (pCipBlock[i].UseFlag)
	//					{
	//						if (pCipBlock[i].PieceIndex == NoIndex)
	//						{
	//							pCipBlock[i].Position += temp;
	//						}

	//					}

	//				}
	//				for (int i = 0; i < JOINT_MAX; i++)
	//				{//凹凸
	//					if (pJoint[i].useFlag)
	//					{
	//						if (pJoint[i].pieNo == NoIndex)
	//						{
	//							pJoint[i].pos += temp;
	//						}

	//					}
	//				}
	//				for (int i = 0; i < PUZZLE_MAX; i++)
	//				{//ピースチップ
	//					if (pPuzzleCip[i].UseFlag)
	//					{
	//						if (pPuzzleCip[i].PieceIndex == NoIndex)
	//						{
	//							pPuzzleCip[i].Position += temp;
	//						}
	//					}
	//				}
	//				if (pGoal->UseFlag)
	//				{//ゴール
	//					if (pGoal->pieceIndex == NoIndex)
	//					{
	//						pGoal->Pos += temp;
	//					}
	//				}
	//				for (int i = 0; i < THORN_BLOCK_MAX; i++)
	//				{//とげ
	//					if (pThornBlock[i].UseFlag)
	//					{
	//						if (pThornBlock[i].PieceIndex == NoIndex)
	//						{
	//							pThornBlock[i].Postion += temp;
	//						}
	//					}

	//				}
	//				for (int i = 0; i < JUMPSTAND_MAX; i++)
	//				{//ジャンプスタンド
	//					if (pJumpStand[i].UseJumpStand)
	//					{
	//						if (pJumpStand[i].PieceIndex == NoIndex)
	//						{
	//							pJumpStand[i].pos += temp;
	//						}
	//					}
	//				}
	//				for (int i = 0; i < SPAWN_POINT_MAX; i++)
	//				{//スポーンポイント
	//					if (pSpawnPoint[i].UseFlag)
	//					{
	//						if (pSpawnPoint[i].PieceIndex == NoIndex)
	//						{
	//							pSpawnPoint[i].Position += temp;
	//						}

	//					}

	//				}
	//				for (int i = 0; i < SWITCH_MAX; i++)
	//				{//スイッチ
	//					if (pSwitch[i].UseFlag)
	//					{
	//						if (pSwitch[i].PieceIndex == NoIndex)
	//						{
	//							pSwitch[i].pos += temp;
	//						}

	//					}
	//				}
	//				for (int i = 0; i < SWITCHWALL_MAX; i++)
	//				{//スイッチ壁
	//					if (pSwitchWall[i].UseFlag)
	//					{
	//						if (pSwitchWall[i].PieceIndex == NoIndex)
	//						{
	//							pSwitchWall[i].pos += temp;
	//						}

	//					}
	//				}

	//				if (!Mouse.pFlag)
	//				{
	//					if (Keyboard_IsKeyTrigger(KK_A))	//aキーが押されたら
	//					{
	//						RotateMapChipR(NoIndex);
	//						Mouse.RotIndex += 1;

	//					}
	//				}
	//				else
	//				{
	//					pPlayer->Position += temp;
	//				}
	//			}



	//		}

	//}


	//

	//if (!Mouse.UseFlag)
	//{
	//	if (MouseIndex != -1)
	//	{
	//		pPuzzle[MouseIndex].MoveFlag = false;
	//		pPuzzle[MouseIndex].MoveEndFlag = true;
	//		pPiece[MouseIndex].MoveEndFlag = true;
	//		pPiece[MouseIndex].MoveFlag = false;

	//		//Mouse.RotIndex = 0;
	//		Mouse.pFlag = false;

	//	}

	//	oneFlag = false;
	//	MouseIndex = -1;
	//	NoIndex = -1;
	//}

	//for (int i = 0; i < PUZZLE_MAX; i++)
	//{

	//	if (pPiece[i].UseFlag)
	//	{

	//		if (pPiece[i].pos.y - pPiece[i].size.y / 3 < -Mouse.PosY &&
	//			pPiece[i].pos.y + pPiece[i].size.y / 3 > -Mouse.PosY &&
	//			pPiece[i].pos.x - pPiece[i].size.x / 3 < Mouse.PosX &&
	//			pPiece[i].pos.x + pPiece[i].size.x / 3 > Mouse.PosX &&
	//			!oneFlag) {

	//			if (Keyboard_IsKeyTrigger(KK_Y))
	//			{
	//				DeleteMapChip(i);
	//				SetPieceMapChip(pPiece[i].pos, pPiece[i].no);
	//			}


	//		}

	//	}
	//}
	}

}

MOUSE * GetMouse()
{
	return &Mouse;
}

int GetXMousePosX() 
{
	return g_Mouse.x;
}

int GetXMousePosY() 
{
	return g_Mouse.y;
}

bool Mouse_IsLeftDown()
{
	if (g_Mouse.leftButton) {
		return true;
	}
	return false;
}

bool Mouse_IsLeftUp()
{
	if (!g_Mouse.leftButton) {
		return true;
	}
	return false;
}

bool Mouse_IsLeftTrigger()
{
	if (g_Mouse.leftButton && 
		!g_OldMouse.leftButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsLeftRelease()
{
	if (!g_Mouse.leftButton && 
		g_OldMouse.leftButton) 
	{
		return  true;
	}
	return false;
}

bool Mouse_IsRightDown()
{
	if (g_Mouse.rightButton) {
		return true;
	}
	return false;
}

bool Mouse_IsRightUp()
{
	if (!g_Mouse.rightButton){
		return true;
	}
	return false;
}

bool Mouse_IsRightTrigger()
{
	if (g_Mouse.rightButton && 
		!g_OldMouse.rightButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsRightRelease()
{
	if (!g_Mouse.rightButton && 
		g_OldMouse.rightButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsMiddleDown()
{
	if (g_Mouse.middleButton) {
		return true;
	}
	return false;
}

bool Mouse_IsMiddleup()
{
	if (!g_Mouse.middleButton) {
		return true;
	}
	return false;
}

bool Mouse_IsMiddleTrigger()
{
	if (g_Mouse.middleButton && 
		!g_OldMouse.middleButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsMiddleRelease()
{
	if (!g_Mouse.middleButton && 
		g_OldMouse.middleButton) 
	{
		return true;
	}
	return false;
}