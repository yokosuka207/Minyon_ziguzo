#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

#include "input.h"	//入力処理
#include "bg.h"	//背景
#include "player.h"//プレイヤー
#include "collision.h"	//当たり判定]
#include "block.h"
#include "puzzle.h"
#include "mouse.h"
#include "goal.h"
#include "puzzlecip.h"
#include "broken.h"
#include "warp.h"
#include "MapChip.h"
#include "inventory.h"
#include "joint.h"
#include "cursor.h"
#include"SplitStage.h"

#include "jump_stand.h"

void InitGame()
{
	//----------げーむ
	//InitPolygon();//ポリゴンの初期化
	//-----------------------
	InitSplitStage();
	BgInit();
	InitBlock();
	InitJoint();
	InitGameMouse();
	InitGoal();
	InitBroken();
	InitPlayer();
	InitWarp();
	InintJumpStand();
	InitPuzzleCip();
	InitPuzzle();
	InitInventory();			// インベントリの初期化
	InitMapChip();
	InitCursor();				// カーソルの初期化

	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
}

void UninitGame()
{
	//UninitPolygon();	//ポリゴンの終了
	BgUninit();
	UninitBlock();
	UninitJoint();
	UninitPuzzle();
	UninitGameMouse();
	UninitGoal();
	UninitPuzzleCip();
	UninitBroken();
	UninitPlayer();
	UninitWarp();
	UninitJumoStand();
	UninitInventory();			// インベントリの終了
	UninitMapChip();
	UninitCursor();				// カーソルの終了
}

void UpdateGame()
{
	//UpdatePolygon();	//ポリゴンの更新
	BgUpdate();
	UpdatePlayer();

	UpdateGameMouse();
	//PuzzleCollision();
	UpdateCollision();
	PieceCollision();

	UpdateBlock();
	UpdateJoint();
	UpdatePuzzle();
	UpdatePuzzleCip();

	UpdateGoal();
	UpdateBroken();
	UpdateWarp();
	UpdateJumpStand();

	UpdateInventory();			// インベントリの更新
	UpdateMapChip();

	UpdateCursor();				// カーソルの更新
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//ポリゴンの描画
	DrawPuzzle();
	DrawMapChip();
	DrawBlock();
	DrawJoint();
	DrawPuzzleCip();
	DrawPlayer();
	DrawWarp();
	DrawJumpStand();
	DrawGoal();
	DrawBroken();

	DrawInventory();			// インベントリの描画
	//DrawCursor();				// カーソルの描画
}

void ResetGame()
{
	InitGame();
}