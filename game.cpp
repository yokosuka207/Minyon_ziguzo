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
#include"thorn_block.h"

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
	InitJumpStand();
	InitPuzzleCip();
	InitPuzzle();
	InitInventory();			// �C���x���g���̏�����
	InitMapChip();
	InitCursor();				// �J�[�\���̏�����
	InitThornBlock();
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
	UninitJumpStand();
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
	UninitCursor();				// �J�[�\���̏I��
	UninitThornBlock();
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
	UpdateThornBlock();
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

	DrawSplitStage();			// ��؂�g�̕`��
	DrawThornBlock();
	DrawInventory();			// �C���x���g���̕`��
	//DrawCursor();				// �J�[�\���̕`��
}

void ResetGame()
{
	InitGame();
}