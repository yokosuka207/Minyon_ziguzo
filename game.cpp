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
#include "pause.h"

static Time g_time;
static Score g_score;
static bool* pause = GetPause();


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
	InitPause();
	InitMapChip();
	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
	InitPlayer();
	g_score.InitScore();
	g_time.InitTime();
	g_time.SetTime(D3DXVECTOR2(TIME_POS_X, 30.0f), D3DXVECTOR2(50.0f, 50.0f));
	//g_time.GetTime();
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
	//UninitSheerFloors();
	UninitInventory();			// インベントリの終了
	UninitMapChip();
	UninitCursor();				// カーソルの終了
	UninitThornBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitPause();
	g_score.UninitScore();
	g_time.UninitTime();
}

void UpdateGame()
{
	//ポーズ処理
	if (GetKeyboardTrigger(DIK_TAB)) {
		//ポーズフラグがoff
		if (!(*pause)) {
			(*pause) = true;
			g_time.PuaseStartTime();
		}
		else {
			(*pause) = false;
			g_time.PuaseEndTime();
		}
	}
	
	if (!(*pause)) {
		//UpdatePolygon();	//ポリゴンの更新
		BgUpdate();
		UpdatePlayer();

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
		UpdateGameMouse();
		UpdateCursor();				// カーソルの更新

	}
	else {
		UpdatePause();
		UpdateGameMouse();
		UpdateCursor();				// カーソルの更新
	}
}	

void DrawGame()
{
	if (!(*pause)) {
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
	else {
		BgDraw();
		//DrawCursor();				// カーソルの描画
		DrawPause();
	}
}

void ResetGame()
{
	InitGame();
}
