#include "game.h"
#include"main.h"
#include"renderer.h"
#include"polygon.h" 

#include"input.h"	//���͏���
#include"bg.h"	//�w�i
#include"player.h"//�v���C���[
#include"collision.h"	//�����蔻��]
#include"block.h"
#include"puzzle.h"
#include"mouse.h"
#include"goal.h"
#include"puzzlecip.h"
#include"broken.h"
#include"warp.h"
#include"MapChip.h"
#include"OperatePiece.h"
#include"inventory.h"

OperatePiece op;
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
	op.Init();
	InitInventory();			// �C���x���g���̏�����
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
	op.Uninit();
	UninitInventory();			// �C���x���g���̏I��
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
	op.Update();

	UpdateInventory();			// �C���x���g���̍X�V
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//�|���S���̕`��
	op.Draw();
	DrawPuzzle();
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