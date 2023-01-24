/*================================================================================
	cursor.cpp
 
		�J�[�\��
												Author: SaitoReito
												 Date : 2022/09/12
================================================================================*/
#include "cursor.h"		// ���g
#include "mouse.h"
#include "xmouse.h"
#include "puzzle.h"
#include"block.h"
#include"texture.h"
#include"sprite.h"
//#include"input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include"player.h"
#include"doppelganger.h"
#include"MapChip.h"
#include"joint.h"
#include"puzzlecip.h"
#include"goal.h"
#include"thorn_block.h"
//#include"puzzlecip.h"
#include"jump_stand.h"
#include"spawnpoint.h"
#include "Key.h"
#include "OpenKey.h"
#include "MoveBlock.h"
#include "switch.h"
#include "SwitchWall.h"
#include"warp.h"
#include"broken.h"
#include"SheerFloors.h"
#include"goal_key.h"
#include "start.h"
#include"high_broken.h"
#include "sound.h"
#include"MoveBlock.h"
#include"fallblock.h"
#include"enemy.h"
#include "JumpStandExplain.h"
#include "StoryKey.h"
//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
#define CURSOR_SIZE_W	(50)		// �J�[�\���̃|���S���̉��̃T�C�Y
#define CURSOR_SIZE_H	(50)		// �J�[�\���̃|���S���̏c�̃T�C�Y

#define CURSOR_SPEED	(2)		// �J�[�\���̈ړ����x

//--------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------

//--------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------
static CURSOR g_Cursor;
static char *g_CursorTextureName = (char*)"data\\texture\\cursor_default.png";
static char* g_CursorCatchTextureName = (char*)"data\\texture\\cursor_catch.png";
static int g_CursorTextureNo[2];

static bool oneFlag = false;	//�}�E�X�Ńp�Y����������Ă��邩
static int NoIndex = -1;	//�}�E�X�Œ͂񂾃s�[�X�ԍ�
static bool g_CursorFlag = false;	//�}�E�X���N���b�N���Ă��邩

//�}�E�X�N���b�NSE
static int g_CursorSoundNo = 0;
static char g_CursorSoundName[] = "data\\SoundData\\SE\\�s�[�X��͂މ�(���ʉ����{).wav";


//==================================================
// �J�[�\��������
//==================================================
HRESULT InitCursor()
{
	oneFlag = false;	//�}�E�X�Ńp�Y����������Ă��邩
	g_Cursor.PieceIndex = -1;	//�}�E�X�̒͂񂾃p�Y���̔ԍ�����
	NoIndex = -1;	//�}�E�X�Œ͂񂾃s�[�X�ԍ�
	g_CursorFlag = false;	//�}�E�X���N���b�N���Ă��邩


	// �J�[�\���̏�����
	{
		g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
		g_Cursor.pos = g_Cursor.oldPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Cursor.sp = D3DXVECTOR2(1.0f, 1.0f);
		g_Cursor.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Cursor.texNo = LoadTexture(g_CursorTextureName);
		g_Cursor.RotIndex = 0;
		g_Cursor.pFlag = false;
		g_Cursor.useFlag = false;
		g_Cursor.type = 0;
		g_Cursor.PieceIndex = -1;
		g_Cursor.bHave = false;
	}
	g_CursorTextureNo[0] = LoadTexture(g_CursorTextureName);
	g_CursorTextureNo[1] = LoadTexture(g_CursorCatchTextureName);
	g_CursorSoundNo = LoadSound(g_CursorSoundName);

	return S_OK;
}

//==================================================
// �J�[�\���I������
//==================================================
void UninitCursor()
{
	StopSound(g_CursorSoundNo);
}

//==================================================
// �J�[�\���X�V����
//==================================================
void UpdateCursor()
{
	//Mouse_GetState(&g_Mouse);

	PUZZLE* pPuzzle = GetPuzzle();
	BLOCK* pBlock = GetBlock();
	PLAYER* pPlayer = GetPlayer();
	DOPPELGANGER* pDoppel = GetDoppelganger();
	Piece* pPiece = GetPiece();
	BLOCK* pCipBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	GOAL* pGoal = GetGoal();
	KEY* pKey = GetKey();
	OPENKEY* pOpenKey = GetOpenKey();
	MOVEBLOCK* pMoveBlock = GetMoveBlock();
	THORNBLOCK* pThornBlock = GetThornBlock();
	JUMPSTAND* pJumpStand = GetJumpStand();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();
	SWITCH* pSwitch = GetSwitch();
	SWITCHWALL* pSwitchWall = GetSwitchWall();
	WARP* pWarp = GetWarp();
	BROKEN* pBroken = GetBroken();
	SHEERFLOORS* pSheerFloors = GetSheerFloors();
	GKey* pGkey = GetGKey();
	START* pStart = GetStart();
	HIGH* pHigh = GetHigh();
	FALLBLOCK* pFallBlock = GetFallBlock();
	ENEMY* pEnemy = GetEnemy();
	EXPLAIN* pExplain = GetExplain();
	STORYKEY* pStoryKey = GetStoryKey();
	//g_Cursor.useFlag = Mouse_IsLeftDown();

	static float MouseOldPosX = GetMousePosX();
	static float MouseOldPosY = GetMousePosY();

	if (MouseOldPosX != GetMousePosX() || MouseOldPosY != GetMousePosY()) {
		// ��΃��[�h�� �J�[�\���ړ�
		g_Cursor.pos.x = GetXMousePosX();
		g_Cursor.pos.y = GetXMousePosY();
	}

	//g_Cursor.oldPos.x = g_Cursor.pos.x -= SCREEN_WIDTH / 2;
	//g_Cursor.pos.y = -g_Cursor.pos.y + SCREEN_HEIGHT / 2;

	g_Cursor.oldPos = g_Cursor.pos;
	//[----------�ړ�----------
	if (GetThumbRightX(0) < -0.2f || GetThumbRightX(0) > 0.2f) {				// �E�X�e�B�b�N	���E
		g_Cursor.pos.x += GetThumbRightX(0) * 12;	// ���E�ړ�
	}
	if (GetThumbRightY(0) < -0.2f || GetThumbRightY(0) > 0.2f) {				// �E�X�e�B�b�N	�㉺
		g_Cursor.pos.y -= GetThumbRightY(0) * 12;	// �㉺�ړ�
	}
	//----------�ړ�----------]

	//[----------�ǔ��� (�ǂ̏㉺���E)----------
	// �㉺
	if (g_Cursor.pos.y - g_Cursor.size.y / 2 < SCREEN_LIMIT_UP ||
		g_Cursor.pos.y + g_Cursor.size.y / 2 > SCREEN_LIMIT_DOWN) 
	{
		g_Cursor.pos.y = g_Cursor.oldPos.y;
	}
	// ���E
	if(	g_Cursor.pos.x - g_Cursor.size.x / 2 < SCREEN_LIMIT_LEFT ||
		g_Cursor.pos.x + g_Cursor.size.x / 2 > SCREEN_LIMIT_RIGHT) 
	{
		g_Cursor.pos.x = g_Cursor.oldPos.x;
	}
	//-----------------------------------------]

	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {		// GamePad B
		if (!g_Cursor.bHave) {
			g_Cursor.bHave = true;
		}
		else {
			g_Cursor.bHave = false;
		}
	}

	if (Mouse_IsLeftRelease()) {		// moues ��
		g_Cursor.bHave = false;
	}

	if (Mouse_IsLeftDown() ||						// mouse ��
		g_Cursor.bHave)
	{
		for (int i = 0; i < PUZZLE_MAX; i++)
		{
			if (pPiece[i].UseFlag)
			{
				if (pPiece[i].pos.y - PUZZLE_HEIGHT / 3 < -g_Cursor.pos.y + SCREEN_HEIGHT / 2 &&
					pPiece[i].pos.y + PUZZLE_HEIGHT / 3 > -g_Cursor.pos.y + SCREEN_HEIGHT / 2 &&
					pPiece[i].pos.x - PUZZLE_WIDHT / 3 < g_Cursor.pos.x - SCREEN_WIDTH / 2 &&
					pPiece[i].pos.x + PUZZLE_WIDHT / 3 > g_Cursor.pos.x - SCREEN_WIDTH / 2 &&
					!oneFlag)
				{
					//�������s�[�X�̒��Ƀv���[���[��������
					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
						pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
						pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
						pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x
						)
					{
						g_Cursor.pFlag = true;
						
						pPlayer->OneOldpos = pPlayer->Position;
					}

					g_Cursor.RotIndex = 0;

					oneFlag = true;
					if (oneFlag == true)
					{
						//SetVolume(g_CursorSoundNo, 0.5f);
						PlaySound(g_CursorSoundNo, 0);
					}
					pPiece[i].MoveFlag = true;
					g_Cursor.PieceIndex = i;
					NoIndex = pPiece[i].no;
					pPiece[i].OldMovePos = pPiece[i].pos;
					g_Cursor.type = 1;
					g_Cursor.bHave = true;
					break;
				}
				else if (oneFlag && i == g_Cursor.PieceIndex)
				{
					g_Cursor.type = 1;
					g_Cursor.bHave = true;

					pPiece[g_Cursor.PieceIndex].OldPos = pPiece[g_Cursor.PieceIndex].pos;

					pPiece[g_Cursor.PieceIndex].pos.x = g_Cursor.pos.x - SCREEN_WIDTH / 2;
					pPiece[g_Cursor.PieceIndex].pos.y = -g_Cursor.pos.y + SCREEN_HEIGHT / 2;
					//pPiece[g_Cursor.PieceIndex].MoveFlag = true;
					D3DXVECTOR2 temp = (pPiece[g_Cursor.PieceIndex].pos - pPiece[g_Cursor.PieceIndex].OldPos);


					//�u���b�N������
					if (pDoppel->UseFlag)
					{
						if (pDoppel->PieceIndex == NoIndex)
						{
							pDoppel->Position += temp;
						}

					}

					for (int i = 0; i < BLOCK_CHIP_MAX; i++)
					{//�u���b�N������
						if (pCipBlock[i].UseFlag)
						{
							if (pCipBlock[i].PieceIndex == NoIndex)
							{
								pCipBlock[i].Position += temp;
							}

						}

					}
					for (int i = 0; i < BROKEN_MAX; i++)
					{//�u���b�N������
						if (pBroken[i].UseFlag)
						{
							if (pBroken[i].index == NoIndex)
							{
								pBroken[i].Postion += temp;
							}

						}

					}
					for (int i = 0; i < HIGH_MAX; i++)
					{//�u���b�N������
						if (pHigh[i].UseFlag)
						{
							if (pHigh[i].index == NoIndex)
							{
								pHigh[i].Postion += temp;
							}

						}

					}
					for (int i = 0; i < SHEERFLOORS_NUM; i++)
					{//�u���b�N������
						if (pSheerFloors[i].use)
						{
							if (pSheerFloors[i].index == NoIndex)
							{
								pSheerFloors[i].pos += temp;
							}

						}

					}
					for (int i = 0; i < MOVE_BLOCK_MAX; i++)
					{
						if (pMoveBlock[i].bUse)
						{
							if (pMoveBlock[i].NowPieceIndex == NoIndex)
							{
								pMoveBlock[i].pos += temp;
							}

						}

					}
					for (int i = 0; i < FALLBLOCK_MAX; i++)
					{
						if (pFallBlock[i].UseFlag)
						{
							if (pFallBlock[i].PieceIndex == NoIndex)
							{
								pFallBlock[i].Position += temp;
							}
						}
					}
					for (int i = 0; i < JOINT_MAX; i++)
					{//����
						if (pJoint[i].useFlag)
						{
							if (pJoint[i].pieNo == NoIndex)
							{
								pJoint[i].pos += temp;
							}

						}
					}
					for (int i = 0; i < PUZZLE_MAX; i++)
					{//�s�[�X�`�b�v
						if (pPuzzleCip[i].UseFlag)
						{
							if (pPuzzleCip[i].PieceIndex == NoIndex)
							{
								pPuzzleCip[i].Position += temp;
							}
						}
					}
					if (pGoal->UseFlag)
					{//�S�[��
						if (pGoal->pieceIndex == NoIndex)
						{
							pGoal->Pos += temp;
						}
					}
					for (int i = 0; i < START_MAX; i++) {
						if (pStart[i].UseFlag) {
							if (pStart[i].PieceIndex == NoIndex) {
								pStart[i].pos += temp;
							}
						}
					}
					for (int i = 0; i < EXPLAIN_MAX; i++) {
						if (pExplain[i].bUse) {
							if (pExplain[i].PieceIndex == NoIndex) {
								pExplain[i].pos += temp;
							}
						}
					}
					//if (pGkey->UseFlag)
					//{//�S�[��
					//	if (pGkey-> == NoIndex)
					//	{
					//		pGkey->Pos += temp;
					//	}
					//}
					for (int i = 0; i < KEY_MAX; i++) {
						if (pKey[i].UseFlag) {
							if (pKey[i].index == NoIndex) {
								pKey[i].Position += temp;
							}
						}
					}
					
					for (int i = 0; i < OPEN_KEY_MAX * STAGE_OPEN_KEY_MAX; i++) {
						if ((pOpenKey + i)->UseFlag) {
							if ((pOpenKey + i)->index == NoIndex) {
								(pOpenKey + i)->Position += temp;
							}
						}
					}
					
					for (int i = 0; i < THORN_BLOCK_MAX; i++)
					{//�Ƃ�
						if (pThornBlock[i].UseFlag)
						{
							if (pThornBlock[i].PieceIndex == NoIndex)
							{
								pThornBlock[i].Postion += temp;
							}
						}

					}
					for (int i = 0; i < JUMPSTAND_MAX; i++)
					{//�W�����v�X�^���h
						if (pJumpStand[i].UseJumpStand)
						{
							if (pJumpStand[i].NowPieceIndex == NoIndex)
							{
								pJumpStand[i].pos += temp;
							}
						}
					}
					for (int i = 0; i < SPAWN_POINT_MAX; i++)
					{//�X�|�[���|�C���g
						if (pSpawnPoint[i].UseFlag)
						{
							if (pSpawnPoint[i].PieceIndex == NoIndex)
							{
								pSpawnPoint[i].Position += temp;
							}

						}

					}
					for (int i = 0; i < SWITCH_MAX; i++)
					{//�X�C�b�`
						if (pSwitch[i].UseFlag)
						{
							if (pSwitch[i].PieceIndex == NoIndex)
							{
								pSwitch[i].pos += temp;
							}

						}
					}
					for (int i = 0; i < SWITCHWALL_MAX; i++)
					{//�X�C�b�`��
						if (pSwitchWall[i].UseFlag)
						{
							if (pSwitchWall[i].PieceIndex == NoIndex)
							{
								pSwitchWall[i].pos += temp;
							}

						}
					}
					for (int i = 0; i < WARP_MAX; i++)
					{//���[�v
						if (pWarp[i].UseFlag)
						{
							if (pWarp[i].PieceIndex == NoIndex)
							{
								pWarp[i].Position += temp;
							}
						}
					}
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						if (pEnemy[i].UseFlag)
						{
							if (pEnemy[i].index == NoIndex)
							{
								pEnemy[i].pos += temp;
							}
						}
					}
					for (int i = 0; i < STORYKEY_MAX; i++) {
						if (pStoryKey[i].bUse) {
							if (pStoryKey[i].no == NoIndex) {
								pStoryKey[i].pos += temp;
							}
						}
					}
					// �s�[�X�̒��Ƀv���C���[�����Ȃ�
					if (!g_Cursor.pFlag)
					{
						// ��]
						if (Keyboard_IsKeyTrigger(KK_E) ||								// keyboard E
							IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER))			// GamePad R
						{
							RotateMapChipR(NoIndex);
							g_Cursor.RotIndex++;
						}
						else if (Keyboard_IsKeyTrigger(KK_Q) ||					// keyboard Q
							IsButtonTriggered(0, XINPUT_GAMEPAD_LEFT_SHOULDER)) {	// GamePad L
							RotateMapChipL(NoIndex);
							g_Cursor.RotIndex--;
						}
					}
					else
					{
						pPlayer->Position += temp;
						pPlayer->oldpos = pPlayer->Position;
					}
					break;
				}
				else {
					g_Cursor.type = 0;
					g_Cursor.bHave = false;
				}
			}
		}
	}
	
	if (!Mouse_IsLeftDown() &&						// mouse ��
		!g_Cursor.bHave)
	{
		if (g_Cursor.PieceIndex != -1)
		{
			pPuzzle[g_Cursor.PieceIndex].MoveFlag = false;
			pPuzzle[g_Cursor.PieceIndex].MoveEndFlag = true;
			pPiece[g_Cursor.PieceIndex].MoveEndFlag = true;
			pPiece[g_Cursor.PieceIndex].MoveFlag = false;

			//g_Cursor.RotIndex = 0;
		}
		g_Cursor.pFlag = false;

		oneFlag = false;
		g_Cursor.PieceIndex = -1;
		NoIndex = -1;
		g_Cursor.type = 0;
	}

	MouseOldPosX = GetMousePosX();
	MouseOldPosY = GetMousePosY();
}

//==================================================
// �J�[�\���\������
//==================================================
void DrawCursor()
{
	SetWorldViewProjection2D();

	if (g_Cursor.useFlag) {
		// �e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_CursorTextureNo[g_Cursor.type]));
		// �|���S���̕`��
		SpriteDrawColorRotation(g_Cursor.pos.x, g_Cursor.pos.y, 0.0f, g_Cursor.size.x, g_Cursor.size.y, 0.0f, g_Cursor.color, 1.0f, 1.0f, 1.0f, 1);
	}
}

//==================================================
// �J�[�\���Z�b�g�֐�
// �����F���S���W, �T�C�Y
//==================================================
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Cursor.pos = g_Cursor.oldPos = pos;
	g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
	//g_Cursor.size = size;

	g_Cursor.useFlag = true;
}


//==================================================
// �J�[�\���Q�b�g�֐�
//==================================================
CURSOR* GetCurso()
{
	return &g_Cursor;
}

//==================================================
// �J�[�\���폜�֐�
//==================================================
void DeleteCursor()
{
	g_Cursor.useFlag = false;
}
