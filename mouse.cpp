#include "mouse.h"
#include "xmouse.h"
#include "puzzle.h"
#include"block.h"
#include"texture.h"
#include"sprite.h"
#include"player.h"
#include"MapChip.h"
#include"joint.h"
#include"puzzlecip.h"
#include"goal.h"
#include"thorn_block.h"
//#include"puzzlecip.h"
#include"jump_stand.h"
#include"spawnpoint.h"
#include "switch.h"
#include "SwitchWall.h"

MOUSE Mouse;
static bool oneFlag = false;	//マウスでパズルを一つ持っているか
static int MouseIndex = -1;	//マウスの掴んだパズルの番号入れ
static int NoIndex = -1;	//マウスで掴んだピース番号
static bool MouseFlag = false;	//マウスをクリックしているか

long y,x;

static Mouse_State g_Mouse, g_OldMouse;

//新保翔麻
HRESULT InitGameMouse()
{
	bool oneFlag = false;
	 MouseIndex = -1;
	 NoIndex = -1;
	Mouse.PosX = GetMousePosX();
	Mouse.PosY = GetMousePosY();
	Mouse.oldPosX = GetMousePosX();
	Mouse.oldPosY = GetMousePosY();
	Mouse.RotIndex = 0;
	Mouse.UseFlag = false;
	Mouse.pFlag = false;

	return S_OK;
}

void UninitGameMouse()
{
}

void UpdateGameMouse()
{
	// マウスの状態構造体のポインタをもらう
	g_OldMouse = g_Mouse;
	Mouse_GetState(&g_Mouse);

	//PUZZLE* pPuzzle = GetPuzzle();
	//BLOCK* pBlock = GetBlock();
	//PLAYER* pPlayer = GetPlayer();
	//Piece* pPiece = GetPiece();
	//BLOCK* pCipBlock = GetChipBlock();
	//JOINT* pJoint = GetJoint();
	//PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	//GOAL* pGoal = GetGoal();
	//THORNBLOCK* pThornBlock = GetThornBlock();
	//JUMPSTAND* pJumpStand = GetJumpStand();
	//SpawnPoint* pSpawnPoint = GetSpawnPoint();
	//SWITCH* pSwitch = GetSwitch();
	//SWITCHWALL* pSwitchWall = GetSwitchWall();
	Mouse.oldPosX = Mouse.PosX;
	Mouse.oldPosY = Mouse.PosY;

	y = Mouse.PosY - Mouse.oldPosY;
	x = Mouse.PosX - Mouse.oldPosX;

	Mouse.PosX = GetMousePosX() - SCREEN_WIDTH / 2;
	Mouse.PosY = GetMousePosY() - SCREEN_HEIGHT / 2;

	Mouse.UseFlag = Mouse_IsLeftDown();
	Mouse.ScrollFlag = Mouse_IsMiddleDown();


	if (Mouse.UseFlag)
	{
	}

}

MOUSE * GetMouse()
{
	return &Mouse;
}

int GetXMousePosX() 
{
	return g_Mouse.x;
}

int GetXMousePosY() 
{
	return g_Mouse.y;
}

bool Mouse_IsLeftDown()
{
	if (g_Mouse.leftButton) {
		return true;
	}
	return false;
}

bool Mouse_IsLeftUp()
{
	if (!g_Mouse.leftButton) {
		return true;
	}
	return false;
}

bool Mouse_IsLeftTrigger()
{
	if (g_Mouse.leftButton && 
		!g_OldMouse.leftButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsLeftRelease()
{
	if (!g_Mouse.leftButton && 
		g_OldMouse.leftButton) 
	{
		return  true;
	}
	return false;
}

bool Mouse_IsRightDown()
{
	if (g_Mouse.rightButton) {
		return true;
	}
	return false;
}

bool Mouse_IsRightUp()
{
	if (!g_Mouse.rightButton){
		return true;
	}
	return false;
}

bool Mouse_IsRightTrigger()
{
	if (g_Mouse.rightButton && 
		!g_OldMouse.rightButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsRightRelease()
{
	if (!g_Mouse.rightButton && 
		g_OldMouse.rightButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsMiddleDown()
{
	if (g_Mouse.middleButton) {
		return true;
	}
	return false;
}

bool Mouse_IsMiddleup()
{
	if (!g_Mouse.middleButton) {
		return true;
	}
	return false;
}

bool Mouse_IsMiddleTrigger()
{
	if (g_Mouse.middleButton && 
		!g_OldMouse.middleButton) 
	{
		return true;
	}
	return false;
}

bool Mouse_IsMiddleRelease()
{
	if (!g_Mouse.middleButton && 
		g_OldMouse.middleButton) 
	{
		return true;
	}
	return false;
}