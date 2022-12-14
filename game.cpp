#include "game.h"
#include "main.h"
#include "renderer.h"
#include "polygon.h" 

#include "input.h"	//���͏���
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
#include "MoveBlock.h"
#include "switch.h"
#include "SwitchWall.h"
#include"player3D.h"
#include"camera.h"
#include "scene.h"
#include "pause.h"

static Time g_time;
static Score g_score;
static PLAYER3D g_Player3D;
static SCENE* p_Scene;
static bool* pause = GetPause();


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
		InitBroken();
		InitWarp();
		InitJumpStand();
		InitSheerFloors();
		InitPuzzleCip();
		InitPuzzle();
		InitInventory();			// �C���x���g���̏�����
		InitCursor();				// �J�[�\���̏�����
		InitThornBlock();
		InitHigh();
		InitSwitch();
		InitSwitchWall();
	}
	InitMapChip();
	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
	InitPlayer();
	g_score.InitScore();
	g_time.InitTime();
	g_time.SetTime(D3DXVECTOR2(TIME_POS_X, 30.0f), D3DXVECTOR2(50.0f, 50.0f));
	g_time.StartTime();
	g_Player3D.Init();

}
	//----------���[��
	//InitPolygon();//�|���S���̏�����
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
	InitInventory();			// �C���x���g���̏�����
	InitCursor();				// �J�[�\���̏�����
	InitThornBlock();
	InitMoveBlock();
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
	UninitCamera();
	//UninitPolygon();	//�|���S���̏I��
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
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
	UninitThornBlock();
	UninitMoveBlock();
	UninitHigh();
	UninitSwitch();
	UninitSwitchWall();
	UninitPause();
	g_score.UninitScore();
	g_time.UninitTime();
	g_Player3D.Uninit();
}

void UpdateGame()
{
	//�|�[�Y����
	if (GetKeyboardTrigger(DIK_TAB)) {
		//�|�[�Y�t���O��off
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
		//UpdatePolygon();	//�|���S���̍X�V
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
		UpdateMoveBlock();
		UpdateHigh();
		UpdateSwitch();
		UpdateSwitchWall();
		UpdateInventory();			// �C���x���g���̍X�V
		UpdateMapChip();
		UpdateGameMouse();
		UpdateCursor();				// �J�[�\���̍X�V

	}
	else {
		UpdatePause();
		UpdateGameMouse();
		UpdateCursor();				// �J�[�\���̍X�V
	}
}	
	UpdateGoal();
	UpdateBroken();
	UpdateWarp();
	UpdateJumpStand();
	UpdateSheerFloors();
	UpdateThornBlock();
	UpdateHigh();
	UpdateSwitch();
	UpdateSwitchWall();
	UpdateInventory();			// �C���x���g���̍X�V
	UpdateMapChip();
	
	UpdateCursor();				// �J�[�\���̍X�V
	g_Player3D.Update();
	UpdateCamera();
}	

void DrawGame()
{
	if (!(*pause)) {
		BgDraw();
		DrawSplitStage();			// ��؂�g�̕`��

		DrawPolygon();		//�|���S���̕`��
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
		DrawMoveBlock();
		DrawHigh();
		DrawSwitch();
		DrawSwitchwall();
		DrawGoal();
		DrawBroken();

		DrawThornBlock();
		DrawInventory();			// �C���x���g���̕`��
		g_time.DrawGameTime();
		//DrawCursor();				// �J�[�\���̕`��
	}
	else {
		BgDraw();
		//DrawCursor();				// �J�[�\���̕`��
		DrawPause();
	}
	DrawThornBlock();
	DrawInventory();			// �C���x���g���̕`��
	g_time.DrawGameTime();
	//DrawCursor();				// �J�[�\���̕`��
	g_Player3D.Draw();
	SetCamera();
}

void ResetGame()
{
	InitGame();
}
