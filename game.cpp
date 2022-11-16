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

void InitGame()
{
	//----------げーむ
	//InitPolygon();//ポリゴンの初期化
	//-----------------------
	BgInit();
	InitBlock();
	InitGameMouse();
	InitGoal();
	InitBroken();
	InitPlayer();
	InitWarp();
	InitPuzzleCip();
	InitPuzzle();
	InitInventory();			// インベントリの初期化
	InitMapChip();
}

void UninitGame()
{
	//UninitPolygon();	//ポリゴンの終了処理
	BgUninit();
	UninitBlock();
	UninitPuzzle();
	UninitGameMouse();
	UninitGoal();
	UninitPuzzleCip();
	UninitBroken();
	UninitPlayer();
	UninitWarp();
	UninitInventory();			// インベントリの終了
	UninitMapChip();
}

void UpdateGame()
{
	//UpdatePolygon();	//ポリゴンの更新
	BgUpdate();
	UpdatePlayer();

	UpdateGameMouse();
	PuzzleCollision();
	UpdateCollision();

	UpdateBlock();
	UpdatePuzzle();
	UpdatePuzzleCip();

	UpdateGoal();
	UpdateBroken();
	UpdateWarp();

	UpdateInventory();			// インベントリの更新
	UpdateMapChip();
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//ポリゴンの描画
	DrawPuzzle();
	DrawMapChip();
	DrawBlock();
	DrawPuzzleCip();
	DrawPlayer();
	DrawWarp();
	DrawGoal();
	DrawBroken();
	DrawInventory();			// インベントリの描画
}

void ResetGame()
{
	InitGame();
}