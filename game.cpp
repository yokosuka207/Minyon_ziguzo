#include "game.h"
#include"main.h"
#include"renderer.h"
#include"polygon.h" 

#include"input.h"	//入力処理
#include"bg.h"	//背景
#include"player.h"//プレイヤー
#include"collision.h"	//当たり判定]
#include"block.h"
#include"puzzle.h"
#include"mouse.h"
#include"goal.h"
#include"puzzlecip.h"
#include"broken.h"
#include"warp.h"
void InitGame()
{
	//----------げーむ
	//InitPolygon();//ポリゴンの初期化
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
	//UninitPolygon();	//ポリゴンの終了処理
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
	//UpdatePolygon();	//ポリゴンの更新
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
	DrawPolygon();		//ポリゴンの描画
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