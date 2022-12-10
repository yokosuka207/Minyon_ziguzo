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
#include "SplitStage.h"
#include "thorn_block.h"
#include "jump_stand.h"
#include "thorn_block.h"
#include "time.h"
#include "score.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "switch.h"
#include "SwitchWall.h"
#include "scene.h"

static Time g_time;
static Score g_score;
static SCENE* p_Scene;

void InitGame()
{
	p_Scene = GetScene();

	if ((int)p_Scene != SCENE_GAME) 
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
		InitWarp();
		InitJumpStand();
		InitSheerFloors();
		InitPuzzleCip();
		InitPuzzle();
		InitInventory();			// インベントリの初期化
		InitCursor();				// カーソルの初期化
		InitThornBlock();
		InitHigh();
		InitSwitch();
		InitSwitchWall();

		InitMapChip();
		SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
		InitPlayer();
		g_score.InitScore();
		g_time.InitTime();
		g_time.SetTime(D3DXVECTOR2(TIME_POS_X, 30.0f), D3DXVECTOR2(50.0f, 50.0f));
		g_time.StartTime();
	}
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
	UninitJumpStand();
	UninitSheerFloors();
	UninitInventory();			// インベントリの終了
	UninitMapChip();
	UninitCursor();				// カーソルの終了
	UninitThornBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	g_score.UninitScore();
	g_time.EndTime();
	g_time.UninitTime();
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
	UpdateSheerFloors();
	UpdateThornBlock();
	UpdateHigh();
	UpdateSwitch();
	UpdateSwitchWall();
	UpdateInventory();			// インベントリの更新
	UpdateMapChip();
	
	UpdateCursor();				// カーソルの更新
}	

void DrawGame()
{
	BgDraw();
	DrawSplitStage();			// 区切り枠の描画

	DrawPolygon();		//ポリゴンの描画
	DrawPuzzle();
	DrawMapChip();

	DrawJoint();
	DrawBlock();

	DrawPuzzleCip();
	DrawPlayer();
	DrawWarp();
	DrawJumpStand();
	DrawSheerFloors();
	DrawThornBlock();
	DrawHigh();
	DrawSwitch();
	DrawSwitchwall();
	DrawGoal();
	DrawBroken();

	DrawThornBlock();
	DrawInventory();			// インベントリの描画
	g_time.DrawGameTime();
	//DrawCursor();				// カーソルの描画
}

void ResetGame()
{
	InitGame();
}