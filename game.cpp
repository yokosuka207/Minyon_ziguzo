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
#include"SplitStage.h"

#include "jump_stand.h"

void InitGame()
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
	InitPlayer();
	InitWarp();
	InintJumpStand();
	InitPuzzleCip();
	InitPuzzle();
	InitInventory();			// �C���x���g���̏�����
	InitMapChip();
	InitCursor();				// �J�[�\���̏�����

	SetCursor(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), D3DXVECTOR2(100, 100));
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
	UninitJumoStand();
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
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

	UpdateInventory();			// �C���x���g���̍X�V
	UpdateMapChip();

	UpdateCursor();				// �J�[�\���̍X�V
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//�|���S���̕`��
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

	DrawInventory();			// �C���x���g���̕`��
	//DrawCursor();				// �J�[�\���̕`��
}

void ResetGame()
{
	InitGame();
}