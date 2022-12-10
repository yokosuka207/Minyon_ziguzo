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
	UninitSheerFloors();
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
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
	//UpdatePolygon();	//�|���S���̍X�V
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
	UpdateInventory();			// �C���x���g���̍X�V
	UpdateMapChip();
	
	UpdateCursor();				// �J�[�\���̍X�V
}	

void DrawGame()
{
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

void ResetGame()
{
	InitGame();
}