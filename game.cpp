#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

#include "xinput.h"
#include "xkeyboard.h"

#include "bg.h"	//�w�i
#include "player.h"//�v���C���[
#include "collision.h"	//�����蔻��]
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
#include "doppelganger.h" //�h�b�y���Q���K�[
#include "enemy.h"
#include "bullet.h"
#include"noizu.h"
#include "EffectSpark.h"	// �q�o�i�G�t�F�N�g
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
		//----------���[��
		//InitPolygon();//�|���S���̏�����
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
		InitInventory();			// �C���x���g���̏�����
		InitCursor();				// �J�[�\���̏�����
		InitThornBlock();
		InitKey();
		InitOpenKey();
		InitHigh();
		InitSwitch();
		InitSwitchWall();
		InitMoveBlock();
		InitFallBlock();
		InitNoizu();
		InitDoppelganger(); //�h�b�y���Q���K�[
		//SetDoppelGanger(D3DXVECTOR2(50, 100),D3DXVECTOR2(DOPPELGANGER_SIZE_W,DOPPELGANGER_SIZE_H),1); //�h�b�y���Q���K�[
		InitEnemy();
		InitPause();
		InitEffectSpark();		// �q�o�i�G�t�F�N�g
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
	//UninitPolygon();	//�|���S���̏I��
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
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
	UninitThornBlock();
	UninitKey();
	UninitOpenKey();
	UninitMoveBlock();
	UninitFallBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitNoizu();
	UninitDoppelganger(); 	//�h�b�y���Q���K�[
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
	UninitEffectSpark();		// �q�o�i�G�t�F�N�g
	UninitEffectLight();
}

void UpdateGame()
{
	//�|�[�Y����
	if (Keyboard_IsKeyTrigger(KK_TAB) ||				// keyboard TAB
		IsButtonTriggered(0, XINPUT_GAMEPAD_START) ||	// GamePad START
		IsButtonTriggered(0, XINPUT_GAMEPAD_BACK)) {	// Gamepad BACK
		//�|�[�Y�t���O��off
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
		//UpdatePolygon();	//�|���S���̍X�V
		BgUpdate();
		UpdateNoizu();
		//PuzzleCollision();
		UpdatePlayer();
		UpdateDoppelganger();//�h�b�y���Q���K�[
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

		UpdateInventory();			// �C���x���g���̍X�V
		UpdateMapChip();
		UpdateGameMouse();
		if (!pCamera->MoveFlag) {
			UpdateCursor();				// �J�[�\���̍X�V
		}
		g_Player3D.Update();
		UpdateCamera();
		UpdateEffectSpark();	// �q�o�i�G�t�F�N�g
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
			UpdateCursor();				// �J�[�\���̍X�V
		}
	}
}	


void DrawGame()
{
	if (!(*pause)) {
		CAMERA* pCamera = GetCamera();
		SetCamera();

		BgDraw();
		DrawSplitStage();			// ��؂�g�̕`��

		DrawPolygon();		//�|���S���̕`��
		DrawPuzzle();
		DrawMapChip();

		//DrawJoint();				// �i#^��^�j
		DrawBlock();

		DrawPuzzleCip();
		DrawStart();
		DrawLamp();
		DrawPlayer();
		DrawDoppelganger();//�h�b�y���Q���K�[
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

		DrawInventory();			// �C���x���g���̕`��
		pTime->DrawGameTime();
		if (!pCamera->MoveFlag) {
			DrawCursor();				// �J�[�\���̕`��
		}
		g_Player3D.Draw();
		DrawEffectSpark();		// �q�o�i�G�t�F�N�g
		DrawEffectLight();
		SetCamera();
		DrawStoryKey();
		DrawExplain();
	}
	else {
		BgDraw();
		//DrawCursor();				// �J�[�\���̕`��
		DrawPause();
	}
}

void ResetGame()
{
	InitGame();
}
