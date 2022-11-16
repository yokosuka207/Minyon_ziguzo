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

void InitGame()
{
	//----------���[��
	//InitPolygon();//�|���S���̏�����
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
	InitInventory();			// �C���x���g���̏�����
	InitMapChip();
}

void UninitGame()
{
	//UninitPolygon();	//�|���S���̏I������
	BgUninit();
	UninitBlock();
	UninitPuzzle();
	UninitGameMouse();
	UninitGoal();
	UninitPuzzleCip();
	UninitBroken();
	UninitPlayer();
	UninitWarp();
	UninitInventory();			// �C���x���g���̏I��
	UninitMapChip();
}

void UpdateGame()
{
	//UpdatePolygon();	//�|���S���̍X�V
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

	UpdateInventory();			// �C���x���g���̍X�V
	UpdateMapChip();
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//�|���S���̕`��
	DrawPuzzle();
	DrawMapChip();
	DrawBlock();
	DrawPuzzleCip();
	DrawPlayer();
	DrawWarp();
	DrawGoal();
	DrawBroken();
	DrawInventory();			// �C���x���g���̕`��
}

void ResetGame()
{
	InitGame();
}