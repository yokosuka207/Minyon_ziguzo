#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

//#include "input.h"	//入力処理
#include "xinput.h"
#include "xkeyboard.h"

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
#include "MoveBlock.h"
#include "switch.h"
#include "SwitchWall.h"
#include"player3D.h"
#include"camera.h"
#include "scene.h"
#include "pause.h"
#include "goal_key.h"

static Time* pTime = pTime->GetTime();
static Score* pScore = pScore->GetScore();
static PLAYER3D g_Player3D;
static SCENE* p_Scene;
static bool* pause = GetPause();
static TimeParam* pTimeParam = pTime->GetTimeParam();

void InitGame()
{
	p_Scene = GetScene();

	if ((int)p_Scene != SCENE_GAME)
	{
		InitCamera();
		//----------げーむ
		//InitPolygon();//ポリゴンの初期化
		//-----------------------
		InitSplitStage();
		BgInit();
		InitBlock();
		InitJoint();
		InitGameMouse();
		InitGoal();
		InitGKey();
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
		InitMoveBlock();
		InitPause();

	}
	InitMapChip();
	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
	InitPlayer();
	pScore->InitScore();
	g_Player3D.Init();
	if (!pTimeParam->UseFlag) {
		pTime->InitTime();
		pTime->SetTime(D3DXVECTOR2(TIME_POS_X, 30.0f), D3DXVECTOR2(50.0f, 50.0f));
		pTime->StartTime();
	}
}


void UninitGame()
{
	UninitCamera();
	//UninitPolygon();	//ポリゴンの終了
	BgUninit();
	UninitBlock();
	UninitJoint();
	UninitPuzzle();
	UninitGameMouse();
	UninitGoal();
	UninitGKey();
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
	UninitMoveBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitPause();
	pScore->UninitScore();
	pTime->UninitTime();
	g_Player3D.Uninit();
}

void UpdateGame()
{
	//ポーズ処理
	if (Keyboard_IsKeyTrigger(KK_TAB)) {
		//ポーズフラグがoff
		if (!(*pause)) {
			(*pause) = true;
			pTime->PauseStartTime();
		}
	}	
	if(Keyboard_IsKeyTrigger(KK_Z)) {
		if ((*pause)) {
			(*pause) = false;
			pTime->PauseEndTime();
			pTime->PauseElapsedTime();
		}
	}
	if (Keyboard_IsKeyTrigger(KK_R)) {
		ResetGame();
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
		UpdateGKey();
		UpdateBroken();
		UpdateWarp();
		UpdateJumpStand();
		UpdateSheerFloors();
		UpdateThornBlock();
		UpdateMoveBlock();
		UpdateHigh();
		UpdateSwitch();
		UpdateSwitchWall();
		UpdateInventory();			// インベントリの更新
		UpdateMapChip();
		UpdateGameMouse();
		UpdateCursor();				// カーソルの更新
		g_Player3D.Update();
		UpdateCamera();

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
		SetCamera();

		BgDraw();
		DrawSplitStage();			// 区切り枠の描画

		DrawPolygon();		//ポリゴンの描画
		DrawPuzzle();
		DrawMapChip();

		DrawJoint();
		DrawBlock();

		DrawPuzzleCip();
		DrawPlayer();
		DrawGKey();
		DrawWarp();
		DrawJumpStand();
		DrawSheerFloors();
		DrawThornBlock();
		DrawMoveBlock();
		DrawHigh();
		DrawSwitch();
		DrawSwitchwall();
		DrawGoal();
		DrawBroken();

		DrawThornBlock();
		DrawInventory();			// インベントリの描画
		pTime->DrawGameTime();
		//DrawCursor();				// カーソルの描画
		g_Player3D.Draw();
		SetCamera();

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
