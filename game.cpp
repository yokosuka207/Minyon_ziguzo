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
}	

void DrawGame()
{
	BgDraw();
	DrawPolygon();		//�|���S���̕`��
	DrawPuzzle();
	DrawBlock();
	DrawPuzzleCip();
	DrawPlayer();
	DrawWarp();
	DrawGoal();
	DrawBroken();

}

void ResetGame()
{
	InitGame();
}