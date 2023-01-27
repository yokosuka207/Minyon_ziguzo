#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

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
#include "Key.h"
#include "OpenKey.h"
#include "MoveBlock.h"
#include "switch.h"
#include "SwitchWall.h"
#include"player3D.h"
#include"camera.h"
#include "scene.h"
#include "pause.h"
#include "goal_key.h"
#include "doppelganger.h" //ドッペルゲンガー
#include "enemy.h"
#include "bullet.h"
#include"noizu.h"
#include "EffectSpark.h"	// ヒバナエフェクト
#include "PlayerLife.h"
#include "start.h"
#include "JumpStandExplain.h"
#include "spawnpoint.h"
#include"fallblock.h"
#include "StoryKey.h"
#include"KeyDisplay.h"
#include"lamp.h"
#include"lamp_switch.h"
#include "EffectLight.h"
#include "DoppelGangerLife.h"

static Time* pTime = pTime->GetTime();
static Score* pScore = pScore->GetScore();
static PLAYER3D g_Player3D;
static SCENE* p_Scene;
static bool* pause = GetPause();
static bool* pause2 = GetPauseMause();
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
		InitStart();
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
		InitKey();
		InitOpenKey();
		InitHigh();
		InitSwitch();
		InitSwitchWall();
		InitMoveBlock();
		InitFallBlock();
		InitNoizu();
		InitDoppelganger(); //ドッペルゲンガー
		//SetDoppelGanger(D3DXVECTOR2(50, 100),D3DXVECTOR2(DOPPELGANGER_SIZE_W,DOPPELGANGER_SIZE_H),1); //ドッペルゲンガー
		InitEnemy();
		InitPause();
		InitEffectSpark();		// ヒバナエフェクト
		InitEffectLight();
		InitBullet();
		InitPlayerLife();
		InitDoppelgangerLife();
		InitKeyDisplay();
		InitExplain();
		InitStoryKey();
		InitCollision();
		InitLamp();
		InitLampSwitch();
		InitSpawnPoint();
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
	UninitStart();
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
	UninitKey();
	UninitOpenKey();
	UninitMoveBlock();
	UninitFallBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitNoizu();
	UninitDoppelganger(); 	//ドッペルゲンガー
	UninitEnemy();
	UninitBullet();
	UninitPlayerLife();
	UninitDoppelgangerLife();
	UninitKeyDisplay();
	UninitExplain();
	UninitStoryKey();
	UninitCollision();
	UninitLamp();
	UninitLampSwitch();
	UninitSpawnPoint();

	UninitPause();
	pScore->UninitScore();
	pTime->UninitTime();
	g_Player3D.Uninit();
	UninitEffectSpark();		// ヒバナエフェクト
	UninitEffectLight();
}

void UpdateGame()
{
	//ポーズ処理
	if (Keyboard_IsKeyTrigger(KK_TAB) ||				// keyboard TAB
		IsButtonTriggered(0, XINPUT_GAMEPAD_START) ||	// GamePad START
		IsButtonTriggered(0, XINPUT_GAMEPAD_BACK)) {	// Gamepad BACK
		//ポーズフラグがoff
		if (!(*pause)) {
			(*pause) = true;
			pTime->PauseStartTime();
		}
	}	
	if(*pause2) {
		if ((*pause)) {
			(*pause) = false;
			(*pause2) = false;
			pTime->PauseEndTime();
			pTime->PauseElapsedTime();
		}
	}
	CAMERA* pCamera = GetCamera();
	if (!(*pause)) {
		//UpdatePolygon();	//ポリゴンの更新
		BgUpdate();
		UpdateNoizu();
		//PuzzleCollision();
		UpdatePlayer();
		UpdateDoppelganger();//ドッペルゲンガー
		UpdateCollision();
		PieceCollision();

		UpdateBlock();
		UpdateJoint();
		UpdatePuzzle();
		UpdatePuzzleCip();

		UpdateGoal();
		UpdateStart();
		UpdateGKey();
		UpdateBroken();
		UpdateWarp();
		UpdateJumpStand();
		UpdateSheerFloors();
		UpdateThornBlock();
		UpdateKey();
		UpdateOpenKey();
		UpdateMoveBlock();
		UpdateFallBlock();
		UpdateHigh();
		UpdateSwitch();
		UpdateSwitchWall();
		UpdateStoryKey();
		UpdateLamp();
		UpdateLampSwitch();

		UpdateEnemy();
		UpdateBullet();

		UpdateInventory();			// インベントリの更新
		UpdateMapChip();
		UpdateGameMouse();
		if (!pCamera->MoveFlag) {
			UpdateCursor();				// カーソルの更新
		}
		g_Player3D.Update();
		UpdateCamera();
		UpdateEffectSpark();	// ヒバナエフェクト
		UpdateEffectLight();

		UpdatePlayerLife();
		UpdateDoppelgangerLife();
		UpdateKeyDisplay();
		UpdateExplain();
	}
	else {
		UpdatePause();
		UpdateGameMouse();
		if (!pCamera->MoveFlag) {
			UpdateCursor();				// カーソルの更新
		}
	}
}	


void DrawGame()
{
	if (!(*pause)) {
		CAMERA* pCamera = GetCamera();
		SetCamera();

		BgDraw();
		DrawSplitStage();			// 区切り枠の描画

		DrawPolygon();		//ポリゴンの描画
		DrawPuzzle();
		DrawMapChip();

		//DrawJoint();				// （#^ω^）
		DrawBlock();

		DrawPuzzleCip();
		DrawStart();
		DrawLamp();
		DrawPlayer();
		DrawDoppelganger();//ドッペルゲンガー
		DrawGKey();
		DrawWarp();
		DrawJumpStand();
		DrawSheerFloors();
		DrawThornBlock();
		DrawKey();
		DrawOpenKey();
		DrawMoveBlock();
		DrawFallBlock();
		DrawHigh();
		DrawSwitch();
		DrawSwitchWall();
		DrawGoal();
		DrawBroken();		
		DrawThornBlock();
		DrawLampSwitch();

		DrawEnemy();
		DrawBullet();
		DrawNoizu();

		DrawPlayerLife();
		DrawDoppelgangerLife();
		DrawKeyDisplay();

		DrawInventory();			// インベントリの描画
		pTime->DrawGameTime();
		if (!pCamera->MoveFlag) {
			DrawCursor();				// カーソルの描画
		}
		g_Player3D.Draw();
		DrawEffectSpark();		// ヒバナエフェクト
		DrawEffectLight();
		SetCamera();
		DrawStoryKey();
		DrawExplain();
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
