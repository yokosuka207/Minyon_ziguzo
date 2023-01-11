//collision.h
#include "collision.h"

#include <math.h>
#include "main.h"
		 

//����֘A
#include "mouse.h"
#include "inventory.h"

//�Q�[���֌W
#include "game.h"
#include "MapChip.h"
#include "player.h"
#include "result.h"
#include "scene.h"
#include "goal.h"

#include "button.h"
#include "time.h"
#include "spawnpoint.h"
#include "joint.h"
#include "SplitStage.h"
#include "fade.h"
//�M�~�b�N�֘A
#include "block.h"			//��{�u���b�N
#include "thorn_block.h"	//�g�Q�u���b�N
#include "broken.h"			//����u���b�N
#include "MoveBlock.h"		//�����u���b�N
#include "High_broken.h"	//���������痎���������u���b�N
#include "FallBlock.h"		//������u���b�N

#include "SheerFloors.h"	//�����鏰
#include "jump_stand.h"		//�W�����v�X�^���h
#include "switch.h"			//�X�C�b�`
#include "SwitchWall.h"		//�X�C�b�`�ŊJ����
#include "warp.h"			//���[�v
#include "Key.h"			//��
#include "OpenKey.h"		//���ŊJ����
#include "goal_key.h"		//�S�[����p��
#include "bullet.h"			//�h�b�y���Q���K�[���˒e
#include "doppelganger.h"   //�h�b�y���Q���K�[
#include "enemy.h"			//�G�l�~�[


/*==============================================================================

   �����蔻��Ǘ� [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

//==================================
//�v���g�^�C�v�錾
//=================================

bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);	//���̕����̃p�Y�����󂢂Ă��邩
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);	//��]��߂�
//void SetPosition(Piece p,int i);
bool SpritStageCollision(Piece p);

void UpdateCollision();
void PieceCollision();
void PuzzleCollision();
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);
bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion);
bool fourCollision(PUZZLE puzzle, int index);
void PositionPlas(D3DXVECTOR2 num, int pinNo);
bool PlayerPieceOpen(Piece p, int index, DIRECSION direcsion);
bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);
bool SpritStageCollision(Piece p);

int punum = 0;	//�p�Y���̔z��̓Y�����̊i�[

static Time* pTime = pTime->GetTime();
static TimeParam* pTimeParam = pTime->GetTimeParam();
DIRECSION Direcsion = NUM;	//�����̊m�F


//===============================
//�����蔻�菈��
//�����蔻�����C�ɍs��
//================================
void UpdateCollision()

{
	
	// �g�p�Q�b�g�ꗗ-----------------------------

	PLAYER* pPlayer = GetPlayer();
	MOUSE* pMouse = GetMouse();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();
	Piece* pPiece = GetPiece();
	ENEMY* pEnemy = GetEnemy();

	//BLOCK* pBlock = GetBlock();
	//BLOCK* pChipblock = GetChipBlock();
	//THORNBLOCK* pThornBlock = GetThornBlock();
	//MOVEBLOCK* pMoveBlock = GetMoveBlock();
	//BROKEN* pBroken = GetBroken();
	//FALLBLOCK* pFallBlock = GetFallBlock();
	//HIGH* pHigh = GetHigh();

	//SWITCH* pSwitch = GetSwitch();
	//SWITCHWALL* pSwitchWall = GetSwitchWall();

	//JUMPSTAND* p_JumpStand = GetJumpStand();

	//KEY* pKey = GetKey();
	//OPENKEY* pOpenKey = GetOpenKey();

	GKey* pGKey = GetGKey();
	//GOAL* pGoal = GetGoal();

	RESULT* pResult = GetResult();

	//-------------------------------------

	bool pFlag = false;	//�v���[���[���s�[�X�̒��ɂ��邩

	//�v���[���[�������Ă���s�[�X�̒��ɂ��邩

		for (int i = 0; i < PUZZLE_MAX; i++) {
			Piece* pPiece = GetPiece();
			if (pPiece[i].MoveFlag)
			{
				if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
					pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
					pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
					pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x
					)
				{
					//������
					pFlag = true;
					break;
				}
				break;
			}

		}


	//============================
	//�C���x���g���n
	//============================
	if (!pFlag)
	{
		// �s�[�X�ƃC���x���g���͈͂̓����蔻��
		for (int i = 0; i < PUZZLE_MAX; i++) {

			Piece* pPiece = GetPiece();

			// �s�[�X���C���x���g���ɂ��܂�
			if (pPiece[i].UseFlag && pPiece[i].pos.x < (-INVENTORYBG_POS_X_REVESE + INVENTORYBG_SIZE_X)) {
				DeleteMapChip(i);
				SetInventory(pPiece[i].no);
			}
		}
	}


	//=========================================
	//�v���[���[�ƃX�C�b�`�n(switch,SwitchWall)
	//=========================================


		for (int i = 0; i < SWITCH_MAX; i++) {

			SWITCH* pSwitch = GetSwitch();
			SWITCHWALL* pSwitchWall = GetSwitchWall();

			if (pSwitch[i].UseFlag) {
				//�X�C�b�`�̍����v���C���[�̉E�������ɂ���Ƃ��A
				//�X�C�b�`�̉E���v���C���[�̍������E�ɂ���Ƃ�
				//�X�C�b�`�̏オ
				if (
					pSwitch[i].pos.x - pSwitch[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
					pSwitch[i].pos.x + pSwitch[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
					pSwitch[i].pos.y - pSwitch[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
					pSwitch[i].pos.y + pSwitch[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
					)
				{
					pSwitch[i].PressFlag = true;//�����ꂽ��
					pSwitch[i].PaternNo += 0.25;
				}
				else {
					pSwitch[i].PressFlag = false;
					pSwitch[i].PaternNo = 0;
				}

				if (pSwitch[i].PressFlag) {
					//�v���P
					for (int j = 0; j < pSwitchWall[i].WallMax; j++) {
						if (pSwitch[i].SwitchIndex == pSwitchWall[j].SwitchIndex) {
							pSwitchWall[j].UseFlag = false;	//�����ꂽ��ǂ��Ȃ��Ȃ�
						}
					}
				}
				else {
					for (int j = 0; j < pSwitchWall[i].WallMax; j++) {
						pSwitchWall[j].UseFlag = true;		//�Ǐo��
					}
				}
			}
		}
		//�v���[���[�ƕǂ̔���
		for (int i = 0; i < SWITCHWALL_MAX; i++) {

			SWITCHWALL* pSwitchWall = GetSwitchWall();

			if (pSwitchWall[i].UseFlag) {
				if (
					pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
					pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
					pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
					pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2
					)
				{
					pPlayer->Position = pPlayer->oldpos;
				}
			}
		}
		//�X�C�b�`�Ɩؔ��̔���
		for (int i = 0; i < SWITCHWALL_MAX; i++) {

			SWITCHWALL* pSwitchWall = GetSwitchWall();

			if (pSwitchWall[i].UseFlag) {

			}
		}
	

	//=====================================
	//���S����i�g�Q�A������,thornBlock�j
	//=====================================
	
	if (!pMouse->UseFlag)
	{
		//�v���C���[�ƃg�Q�u���b�N�̔���
		for (int i = 0; i < THORN_BLOCK_MAX; i++) {

			THORNBLOCK* pThornBlock = GetThornBlock();

			if (pThornBlock[i].UseFlag) {

				if (CollisionBB(pThornBlock[i].Postion, pPlayer->Position, pThornBlock[i].Size, pPlayer->size))
				{

					pPlayer->hp--;

					if (pPlayer->hp <= 0) {
						SetResultType(LOSE);
						//SetScene(SCENE::SCENE_RESULT);
						StartFade(FADE::FADE_OUT);
						pTime->EndTime();
						pTimeParam->EndFlag = true;
					}
					else{//���ɉ����Ȃ����S����ꍇ
						for (int i = 0; i < SPAWN_POINT_MAX; i++)
						{
							if (pSpawnPoint[i].UseFlag)
							{
								if (pPlayer->PieceIndex == pSpawnPoint[i].PieceIndex)
								{
									pPlayer->Position = pSpawnPoint[i].Position;

								}


							}
						}

					}

				}
			}
		}

		//�v���C���[��������������
		if (pPlayer->Position.y - pPlayer->size.y > SCREEN_HEIGHT)
		{
			pResult[0].type = LOSE;
			pTime->EndTime();
			pTimeParam->EndFlag = true;
			//SetScene(SCENE::SCENE_RESULT);
			StartFade(FADE::FADE_OUT);
		}
	}


	//========================================================================
	//�v���C���[�E�`�b�v�u���b�N�@�����蔻��(Player��ChipBlock�̓����蔻��)
	//=========================================================================
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		BLOCK* pBlock = GetBlock();
		BLOCK* pChipblock = GetChipBlock();

		if ((pChipblock + i)->UseFlag == true)
		{
			//�v���C���[���E�u���b�N�E
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 - pPlayer->size.x / 2;
			}
			//�v���C���[�E�E�u���b�N��
			if (pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 + pPlayer->size.x / 2;
			}

			//�v���C���[��E�u���b�N��,���n����
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 &&
				pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 + pPlayer->size.y / 2 + 0.02f;
				pPlayer->jump = false;
				pPlayer->fall = false;
				pPlayer->WarpFlag = false;
				//pPlayer->isGround = true;
				pPlayer->sp.y = 0;
				pPlayer->frame = 0;
			}
			//�v���C���[���E�u���b�N��,��������
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 - pPlayer->size.y / 2 - 0.02f;

				pPlayer->fall = true;
				pPlayer->getfall = true;
				pPlayer->frame = 50;
			}
		}
	}


	//========================================================================
	//�v���C���[�E���[�v�@�����蔻��(Player��Warp�̓����蔻��)
	//=========================================================================
	
	pPlayer->CoolTime--;

	if (pPlayer->CoolTime < 0)
	{
		pPlayer->CoolTime = 0;

		//�v���C���[�E���[�v�@�����蔻��
		for (int i = 0; i < BLOCK_MAX; i++)
		{
			WARP* warp = GetWarp();
			if ((warp + i)->UseFlag == true)
			{
				if (pPlayer->Position.x + pPlayer->size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
					pPlayer->Position.x - pPlayer->size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
					pPlayer->Position.y + pPlayer->size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
					pPlayer->Position.y - pPlayer->size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
				{
					if (i % 2 == 0)
					{
						if (!pPlayer->WarpFlag)
						{
							pPlayer->Position = (warp + i + 1)->Position;
							pPlayer->CoolTime = PLAYER_COOLTIME;
							pPlayer->WarpFlag = true;
						}

					}
					else if (i % 2 == 1)
					{
						if (!pPlayer->WarpFlag)
						{
							pPlayer->Position = (warp + i - 1)->Position;
							pPlayer->CoolTime = PLAYER_COOLTIME;

							pPlayer->WarpFlag = true;

						}
					}
				}
			}
		}
	}



//-----------------------------------------------------
//�v���C���[�ƃW�����v�� �����蔻��(Player��Jumpstand)
//-----------------------------------------------------
	

	//for (int i = 0; i < JUMPSTAND_MAX; i++) {

	//	JUMPSTAND* p_JumpStand = GetJumpStand();

	//	if (p_JumpStand[i].UseJumpStand) {
	//		if (GetKeyboardPress(DIK_B))
	//		{
	//			if (CollisionBB(pPlayer->Position, p_JumpStand[i].pos, pPlayer->size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
	//				p_JumpStand[i].GetJumpStand = true;
	//			}
	//		}
	//		else
	//		{
	//			p_JumpStand[i].GetJumpStand = false;
	//		}
	//	}
	//}

	//========================================================================
	//�v���C���[�E����u���b�N�@�����蔻��(Player��BrokenBlock�̓����蔻��)
	//=========================================================================

	for (int i = 0; i < BROKEN_MAX; i++)
	{

		BROKEN* pBroken = GetBroken();

		if ((pBroken + i)->UseFlag == true)
		{
			//�v���C���[���E����u���b�N�E
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - pPlayer->size.x / 2;
			}
			//�v���C���[�E�E����u���b�N��
			if (pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + pPlayer->size.x / 2;
			}

			//�v���C���[��E����u���b�N��
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
				pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 - pPlayer->size.y / 2;
				pPlayer->jump = false;
				pPlayer->fall = false;
				pPlayer->frame = 0;
			}
			//�v���C���[���E����u���b�N��,����
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
			{
				(pBroken + i)->UseFlag = false;
				pPlayer->fall = true;
				pPlayer->getfall = true;
				pPlayer->frame = 50;
			}
		}
	}


	//====================================================================
	//�v���C���[�Ɠ����u���b�N�̓����蔻��(Player��MoveBlock�̓����蔻��)
	//====================================================================

	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {

		MOVEBLOCK* pMoveBlock = GetMoveBlock();

		if (pMoveBlock[i].bUse)
		{
			if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				pPlayer->oldpos.x + pPlayer->size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = pPlayer->sp;
				pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;

			}
			if (pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				pPlayer->oldpos.x - pPlayer->size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = pPlayer->sp;
				pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
			}
			if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				pPlayer->oldpos.y + pPlayer->size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
			{
				pPlayer->Position.y = pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 - pPlayer->size.y / 2;
				// ���n���ɂ���
				if (!pPlayer->isMoveBlock) {
					pPlayer->sp.y = 0.0f;
					pPlayer->isMoveBlock = true;
					break;
				}
			}
			else {
				pPlayer->isMoveBlock = false;
			}
			//�v���C���[���E�u���b�N��,��������
			if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
				pPlayer->oldpos.y - pPlayer->size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = pPlayer->sp;
				pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
			}
		}
	}


	//====================================================================
	//�v���C���[�Ɨ�����u���b�N�̓����蔻��(Player��FallBlock�̓����蔻��)
	//====================================================================
	
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{

		FALLBLOCK* pFallBlock = GetFallBlock();


		if ((pFallBlock + i)->UseFlag == true)
		{
			//�v���C���[���E�u���b�N�E����
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 - pPlayer->size.x / 2;
			}
			//�v���C���[�E�E������u���b�N��
			if (pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 + pPlayer->size.x / 2;
			}
			//�v���C���[��E������u���b�N��
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 - pPlayer->size.y / 2;
				pPlayer->getfall = false;
				pPlayer->fall = false;
				pPlayer->frame = 50;
				(pFallBlock + i)->Position.y++;
			}
			//�v���C���[���E������u���b�N
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 &&
				pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 - pPlayer->size.y / 2;
			}
		}
	}


	//====================================================================
	//�v���C���[�ƍ��������u���b�N�̓����蔻��(Player��High�̓����蔻��)
	//====================================================================

	for (int i = 0; i < HIGH_MAX; i++)
	{

		HIGH* pHigh = GetHigh();

		if ((pHigh + i)->UseFlag == true)
		{
			//�v���C���[���E����������u���b�N�E
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - pPlayer->size.x / 2;
			}
			//�v���C���[�E�E����������u���b�N��
			if (pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				pPlayer->oldpos.x - pPlayer->size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				pPlayer->Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + pPlayer->size.x / 2;
			}

			//�v���C���[��E����������u���b�N��
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
				pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				if (pPlayer->sp.y >= -10.0f)
				{
					//pPlayer->isHigh = false;
					(pHigh + i)->UseFlag = false;
					pPlayer->frame = 50;
				}
				else
				{
					//pPlayer->isHigh = true;
					pPlayer->sp.y = 0.0f;
					pPlayer->Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + pPlayer->size.y / 2;
				}

			}/*
			else
			{
				pPlayer->isHigh = false;
			}*/
			//�v���C���[���E����������u���b�N��,
			if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
			{
				pPlayer->Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + pPlayer->size.y / 2;
			}

			// �v���C���[�̉��Ƀu���b�N����������
			if ((pPlayer->Position.y - pPlayer->size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
				(pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
				(pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
				(pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
			{	// ���n���ɂ���
				if (!pPlayer->isHigh) {
					pPlayer->sp.y = 0.0f;
					pPlayer->isHigh = true;
					break;
				}
			}
			else {
				pPlayer->isHigh = false;
			}
		}
	}


	//-----------------------------------------------------
	//�v���C���[�ƌ��̓����蔻��(Player��Key)
	//-----------------------------------------------------

	for (int i = 0; i < KEY_MAX; i++)
	{

		KEY* pKey = GetKey();
		if (pKey->GetKey == true)
		{
			if (CollisionBB(pKey[i].Position, pPlayer->Position, pKey[i].Size, pPlayer->size))
			{

				pPlayer->HaveKey++;
				pKey->GetKey = false;
			}

		}
	}


	//-----------------------------------------------------------------
	//�ʏ팮�擾�v���C���[�ƌ��ŊJ�����̓����蔻��(Player��OpenKey)
	//-----------------------------------------------------------------

	for (int i = 0; i < OPEN_KEY_MAX; i++)
	{
		OPENKEY* pOpenKey = GetOpenKey();
		KEY* pKey = GetKey();
		if ((pOpenKey + i)->UseFlag == true)
		{

			if (CollisionBB(pOpenKey[i].Position, pKey->Position, pOpenKey[i].Size, pKey->Size))
			{

				if (pPlayer->HaveKey > 0)
				{
					//pPlayer->Position.x = (pOpenKey + i)->Position.x - (pOpenKey + i)->Size.x / 2 - pPlayer->size.x / 2;
					(pOpenKey + i)->UseFlag = false;
					
					//SetScene();
					
				}
				/*else 
				{
					pPlayer->Position.x = (pOpenKey + i)->Position.x - (pOpenKey + i)->Size.x / 2 - pPlayer->size.x / 2;
				}*/
				
			}
		}

	}


	//------------------------------------------------------------------
	//�S�[����p���ƃv���C���[�̓����蔻��(GKey��Player)
	//------------------------------------------------------------------

	//GKey* pGKey = GetGKey();
	if (pGKey->UseFlag == true)
	{
		if (CollisionBB(pGKey->pos, pPlayer->Position, pGKey->size, pPlayer->size))
		{
			pGKey->UseFlag = false;
			pGKey->GetGKey = true;
		}
	}

	//-------------------------------------------------------------------
	//�S�[����p���擾�v���C���[�ƌ��ŊJ�����̓����蔻��(Player��Goal)
	//-------------------------------------------------------------------

		GOAL* pGoal = GetGoal();
		//GKey* pGKey = GetGKey();
		if (pGoal->UseFlag == true)
		{

			if (GetGoal()->UseFlag)
			{
				
				
				if (!pMouse->UseFlag && pGKey->GetGKey)
				{

					if (CollisionBB(GetGoal()->Pos, pPlayer->Position, GetGoal()->Size, pPlayer->size))
					{
						GetGoal()->UseFlag = false;
						SetResultType(WIN);
						//SetScene(SCENE_RESULT);
						StartFade(FADE::FADE_OUT);
						pTime->EndTime();
						pTimeParam->EndFlag = true;
					}
				}
			}

			
		}

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (pEnemy[i].UseFlag == true)
			{
				if (CollisionBB(pEnemy[i].pos, pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x * 1000, pEnemy[i].size.y), pPlayer->size))
				{
					pEnemy[i].AIFlag = true;
				}
			}
		}
		//------------------------------------
		//�h�b�y���Q���K�[�e�p�����蔻��
		//------------------------------------
		//DOPPELGANGER* pDoppel = GetDoppelganger();
		//BULLET* pBullet = GetBullet();

		//���v���C���[�e �� �G�L����
		//if(pDoppel->UseFlag == true)
		//{ 
		//	pBullet->use = true;

		//	if (pBullet->use == true)
		//	{
		//		if (pPlayer->UseFlag)
		//		{
		//			bool hit = CollisionBB(pBullet->pos, pPlayer->Position, D3DXVECTOR2(pBullet->w, pBullet->h), D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H));

		//			if (hit == true)//�������Ă���
		//			{
		//				if (pBullet->hit)
		//				{
		//					pPlayer->hp - (pBullet->Damage);
		//					if (pPlayer->hp <= 0)
		//					{
		//						pPlayer->UseFlag = false;
		//						StartFade(FADE::FADE_OUT);
		//						SetResultType(LOSE);
		//						pTime->EndTime();
		//						pTimeParam->EndFlag = true;
		//					}
		//					
		//				}
		//			}
		//			else//�����Ă��Ȃ�
		//			{

		//			}
		//		}
		//	}
		//}
		
}
//----------------------------------------------------------------------------------------------------------




//==========================
//�p�Y���s�[�X�����蔻��
//==========================
void PieceCollision()
{
	
	SplitStage* pSplitStage = GetSplitStage();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();

	Piece* pPiece = GetPiece();
	JOINT* pJoint = GetJoint();
	PLAYER* pPlayer = GetPlayer();
	bool colFlag = false;//�������ē�������
	bool colFlag2 = false;//�������ē�������
	bool pFlag =false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (pPiece[i].MoveEndFlag)	//�����I�������
			{

				pPiece[i].MoveEndFlag = false;

				if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
					pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
					pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
					pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x
					)
				{
					pFlag = true;
				}

				if (!SpritStageCollision(pPiece[i]))
				{
					//pPiece[i].pos = pPiece[i].OldMovePos;
					Rotreturn(pPiece[i].no);
					colFlag2 = true;
					D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
					PositionPlas(temp, pPiece[i].no);
					pPiece[i].pos = pPiece[i].OldMovePos;
					if (pFlag)
					{
						pPlayer->Position = pPlayer->OneOldpos;
					}

					break;
				}


				for (int j = 0; j < JOINT_MAX; j++)
				{
					if (pJoint[j].pieNo == pPiece[i].no)	//�����I������s�[�X�̒��ɂ�������
					{
						for (int k = 0; k < JOINT_MAX; k++)
						{
							if (pJoint[j].pieNo != pJoint[k].pieNo)//�s�[�X�ԍ����������
							{

								//�W���C���g���d�Ȃ��Ă�����
								colFlag = CollisionBB(pJoint[j].pos, pJoint[k].pos, pJoint[j].size, pJoint[k].size);

								if (colFlag)
								{

									//���ʂ������Ă�����
									if (pJoint[j].type == JOINT_TYPE::TYPE_BUMP && pJoint[k].type == JOINT_TYPE::TYPE_DIP ||
										pJoint[k].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP)
									{
										colFlag2 = true;

										//�W���C���g���E��������
										if (pPiece[i].pos.x + pPiece[i].size.x / 3 < pJoint[j].pos.x)
										{


											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, pPiece[i].no);
												pPiece[i].OldMovePos = pPiece[i].pos;
												if (pFlag)
												{
													pPlayer->Position += temp;
												}

											}
											else
											{
												Rotreturn(pPiece[i].no);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, pPiece[i].no);
												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}


										}
										//�W���C���g������������
										else if (pPiece[i].pos.x - pPiece[i].size.x / 3 > pJoint[j].pos.x)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_SIZE, pPiece[pJoint[k].indexno].pos.y);

											if (fourPieceCollision(pPiece[i], i))
											{
												pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_SIZE, pPiece[pJoint[k].indexno].pos.y);

												PositionPlas(temp, pPiece[i].no);
												pPiece[i].OldMovePos = pPiece[i].pos;
												if (pFlag)
												{
													pPlayer->Position += temp;
												}
												pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);

											}
											else
											{
												Rotreturn(pPiece[i].no);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, pPiece[i].no);

												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}
										//�W���C���g���ゾ������
										else if (pPiece[i].pos.y - pPiece[i].size.y / 3 > pJoint[j].pos.y)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, pPiece[i].no);
												pPiece[i].OldMovePos = pPiece[i].pos;
												if (pFlag)
												{
													pPlayer->Position += temp;
												}

											}
											else
											{
												Rotreturn(pPiece[i].no);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
												PositionPlas(temp, pPiece[i].no);

												pPiece[i].pos = pPiece[i].OldMovePos;
												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}
										//�W���C���g������������
										else if (pPiece[i].pos.y + pPiece[i].size.y / 3 < pJoint[j].pos.y)
										{
											D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT) - pPiece[i].pos;

											pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT);

											if (fourPieceCollision(pPiece[i], i))
											{
												PositionPlas(temp, pPiece[i].no);
												pPiece[i].OldMovePos = pPiece[i].pos;
												if (pFlag)
												{
													pPlayer->Position += temp;
												}

											}
											else
											{
												Rotreturn(pPiece[i].no);
												colFlag2 = true;
												temp = pPiece[i].OldMovePos - pPiece[i].pos;
												PositionPlas(temp, pPiece[i].no);

												pPiece[i].pos = pPiece[i].OldMovePos;

												if (pFlag)
												{
													pPlayer->Position = pPlayer->OneOldpos;
												}

											}

										}

										break;
									}
									break;
								}


							}
						}
					}


				}
				if (!colFlag2)
				{

					if (fourNomalPieceCollision(pPiece[i], i))
					{

					}
					else
					{
						Rotreturn(pPiece[i].no);

						colFlag2 = true;
						D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
						PositionPlas(temp, pPiece[i].no);
						pPiece[i].pos = pPiece[i].OldMovePos;
						pPiece[i].OldPos = pPiece[i].pos;
						if (pFlag)
						{
							pPlayer->Position = pPlayer->OneOldpos;
						}

					}


					for (int m = 0; m < 3; m++)
					{
						if (!colFlag2)
						{

							for (int n = 0; n < 4; n++)
							{

								if (pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) - pSplitStage->size.y / 2 < pPiece[i].pos.y &&
									pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) + pSplitStage->size.y / 2 > pPiece[i].pos.y &&
									pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) - pSplitStage->size.x / 2 < pPiece[i].pos.x &&
									pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) + pSplitStage->size.x / 2 > pPiece[i].pos.x)
								{
									pPiece[i].pos = pSplitStage->Split34[n][m];

									if (fourNomalPieceCollision(pPiece[i], i))
									{
										D3DXVECTOR2 temp = pPiece[i].pos - pPiece[i].OldPos;

										PositionPlas(temp, pPiece[i].no);
										if (pFlag)
										{
											pPlayer->Position += temp;
										}

									}
									else
									{
										colFlag2 = true;
										D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
										PositionPlas(temp, pPiece[i].no);
										pPiece[i].pos = pPiece[i].OldMovePos;
										Rotreturn(pPiece[i].no);
										if (pFlag)
										{
											pPlayer->Position = pPlayer->OneOldpos;
										}

									}

									break;
								}
							}
						}
					}

				}

			}
		}
	}

}

//---------------------------------
//�p�Y���̓����蔻��
//���������邩�ǂ���
//---------------------------------
void PuzzleCollision()
{
	punum = -1;
	bool colFlag = false;//�������ē�������
	bool pFlag = false;
	PUZZLE* pPuzzle = GetPuzzle();
	PLAYER* pPlayer = GetPlayer();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{

			if (pPuzzle[i].MoveEndFlag)
			{
				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					pPuzzle[j].OneOldPosition = pPuzzle[j].Position;

				}

				pPuzzle[i].MoveEndFlag = false;

				if (pPuzzle[i].Position.y - pPuzzle[i].Size.y / 2 < pPlayer->Position.y &&
					pPuzzle[i].Position.y + pPuzzle[i].Size.y / 2 > pPlayer->Position.y &&
					pPuzzle[i].Position.x - pPuzzle[i].Size.x / 2 < pPlayer->Position.x &&
					pPuzzle[i].Position.x + pPuzzle[i].Size.x / 2 > pPlayer->Position.x
					)
				{
					pFlag = true;
				}


				for (int j = 0; j < PUZZLE_MAX; j++)
				{
					if (j != i)
					{
						//�������I������p�Y���ƍ��̃p�Y�����d�Ȃ��Ă��邩
						bool hitFlag = CollisionBB(pPuzzle[i].Position, pPuzzle[j].Position, pPuzzle[i].Size, D3DXVECTOR2(pPuzzle[j].Size.x, pPuzzle[j].Size.y));

						if (hitFlag)	//�d�Ȃ��Ă�����
						{
							//�|�W�V�����̍���
							float x = pPuzzle[i].Position.x - pPuzzle[j].Position.x;
							float y = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//��Βl�̎擾
							x = fabsf(x);
							y = fabsf(y);
							//x = x / 1.5f;
							//�p�Y�������̂ق��ɗL������
							if (x >= y)
							{
								//�������Ă���p�Y�����E�ɂ�������
								if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
								{
									//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);
										//�E���J���Ă��邩
										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_SIZE, pPuzzle[j].Position.y);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�L���Ă�����g�D���[
												colFlag = true;

											}
											else
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									else
									{
										//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��Ȃ�������

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}
								}
								//�������Ă���p�Y�������ɂ�������
								if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
								{

									//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
									{
										hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);
										//�����J���Ă��邩

										if (hitFlag) {
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_SIZE, pPuzzle[j].Position.y);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�L���Ă�����g�D���[
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��Ȃ�������
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}
							//�p�Y�����c�̂ق��ɗL������
							else if (y > x)
							{
								//�������Ă���p�Y������ɂ�������

								if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
								{
									//�p�Y���̃`�b�v�̉��Əオ�L���Ă��邩
									if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
									{
										//�オ�J���Ă��邩
										hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_SIZE);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�

												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}
											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;
											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̉��Əオ�L���Ă��Ȃ�������

										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}
								//�������Ă���p�Y�������ɂ�������
								if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
								{
									//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��邩

									if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
										(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
									{
										//�����J���Ă��邩
										hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

										if (hitFlag)
										{
											//�󂢂Ă�����|�W�V�������ړ�����
											pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_SIZE);
											//�l�����̃p�Y���ɍ�����
											if (fourCollision(pPuzzle[i], i))
											{
												//�����Ă�����g�D���[
												colFlag = true;

											}
											else
											{
												//�����Ă��Ȃ������猳�̖߂�
												pPuzzle[i].Position = pPuzzle[i].oldPosition;

											}

											pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

											pPuzzle[i].oldPosition = pPuzzle[i].Position;

											break;
										}
										else if (!hitFlag)
										{
											//�J���Ă��Ȃ������猳�ɖ߂�

											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									else
									{
										//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��Ȃ������猳�ɖ߂�
										pPuzzle[i].Position = pPuzzle[i].oldPosition;
										break;
									}

								}

							}


							//hitFlag = CollisionBB(pPuzzle[i].Position,D3DXVECTOR2( pPuzzle[j].Position.x
							//	pPuzzle[i].Size, pPuzzle[j].Size);
						}
						else
						{
							//�|�W�V�����̍���
							float abx = (pPuzzle[i].Position.x) - pPuzzle[j].Position.x;
							float aby = pPuzzle[i].Position.y - pPuzzle[j].Position.y;

							//��Βl�̎擾
							abx = fabsf(abx);
							aby = fabsf(aby);
							//�t�������p�Y���̋߂��ɂ��邩
							if ((abx < 20.0f && aby < 200.0f) || (abx < 200.0f && aby < 20.0f))
							{

								//�p�Y�������̂ق��ɗL������

								if (abx >= aby)
								{
									//�������Ă���p�Y�����E�ɂ�������
									if (pPuzzle[i].Position.x > pPuzzle[j].Position.x)
									{
										//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩

										if ((pPuzzle[i].Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeRight == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeRight == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeLeft == STEAT_NUM && pPuzzle[j].Puzzle_TypeRight == STEAT_NUM))
										{
											//�E���J���Ă��邩

											hitFlag = PuzzleOpen(pPuzzle[j], i, RIGHT);

											if (hitFlag)
											{
												//�󂢂Ă�����|�W�V�������ړ�����
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x + PUZZLE_SIZE, pPuzzle[j].Position.y);
												//�l�����̃p�Y���ɍ�����

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}
										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}
									}
									//�������Ă���p�Y�������ɂ�������
									if (pPuzzle[i].Position.x < pPuzzle[j].Position.x)
									{

										if ((pPuzzle[i].Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeLeft == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeRight == STEAT_NUM && pPuzzle[j].Puzzle_TypeLeft == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, LEFT);

											if (hitFlag) {
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x - PUZZLE_SIZE, pPuzzle[j].Position.y);
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}

								}
								else if (aby > abx)
								{
									//�������Ă���p�Y������ɂ�������

									if (pPuzzle[i].Position.y < pPuzzle[j].Position.y)
									{

										if ((pPuzzle[i].Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeUp == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeUp == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeDown == STEAT_NUM && pPuzzle[j].Puzzle_TypeUp == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, UP);

											if (hitFlag)
											{
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y - PUZZLE_SIZE);
												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;
												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}
									//�������Ă���p�Y�������ɂ�������
									if (pPuzzle[i].Position.y > pPuzzle[j].Position.y)
									{

										if ((pPuzzle[i].Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[j].Puzzle_TypeDown == STEAT_DEPPARI) ||
											(pPuzzle[i].Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[j].Puzzle_TypeDown == STEAT_HIKKOMI) ||
											(pPuzzle[i].Puzzle_TypeUp == STEAT_NUM && pPuzzle[j].Puzzle_TypeDown == STEAT_NUM))
										{
											hitFlag = PuzzleOpen(pPuzzle[j], i, DOWN);

											if (hitFlag)
											{
												pPuzzle[i].Position = D3DXVECTOR2(pPuzzle[j].Position.x, pPuzzle[j].Position.y + PUZZLE_SIZE);

												if (fourCollision(pPuzzle[i], i))
												{
													colFlag = true;

												}
												else
												{
													pPuzzle[i].Position = pPuzzle[i].oldPosition;

												}
												pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

												pPuzzle[i].oldPosition = pPuzzle[i].Position;

												break;
											}
											else if (!hitFlag)
											{
												pPuzzle[i].Position = pPuzzle[i].oldPosition;
												break;
											}

										}
										else
										{
											pPuzzle[i].Position = pPuzzle[i].oldPosition;
											break;
										}

									}

								}

							}

						}
					}

				}
				if (!colFlag)
				{
					//�����������Ǔ����Ă��Ȃ�������
					float pPx = pPuzzle[i].Position.x - pPuzzle[i].oldPosition.x;
					float pPy = pPuzzle[i].Position.y - pPuzzle[i].oldPosition.y;
					pPx = fabsf(pPx);
					pPy = fabsf(pPy);
					//�O��Ƃقڈʒu���ς���Ă��Ȃ�������
					if (pPx + pPy < 10)
					{
						//pPuzzle[i].Position.x += (20.0f);
						pPuzzle[i].Position.y -= (20.0f);

					}
					pPuzzle[i].OneOldPosition = pPuzzle[i].oldPosition;

					pPuzzle[i].oldPosition = pPuzzle[i].Position;

					pPuzzle[i].Position = pPuzzle[i].oldPosition;

				}
				if (pFlag) {

					MOUSE* pMouse = GetMouse();

					pPlayer->Position = pPuzzle[i].Position - pMouse->PlPos;
				}


			}
		}

	}


}
//===========================================
//�l�p�`���m���������Ă��邩�������Ă��Ȃ����𔻒肷�邾��
//����: �������W�P�A�������W�Q�A�T�C�Y�P�A�T�C�Y�Q
//�߂�l�F true�������Ă���:false�����Ă��Ȃ�
//================================================
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2	min1, min2;	//�l�p�`�̍ŏ����W�i����j
	D3DXVECTOR2 max1, max2;	//�l�p�`�̍ő���W(�E��)

	//�l�p�`�P����
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;
	//�l�p�`�P�E��
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;
	//�l�p�`�Q����
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;
	//�l�p�`�Q�E��
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//�Փ˔���

	if (max1.x < min2.x)//����1
	{
		return false;
	}
	if (max2.x < min1.x)//����2
	{
		return false;
	}
	if (max1.y < min2.y)//����3
	{
		return false;
	}
	if (max2.y < min1.y)//����4
	{
		return false;
	}
	return true;


	//if (max1.x > min2.x)//����1
	//{
	//	return true;
	//}
	//if (max2.x > min1.x)//����2
	//{
	//	return true;
	//}
	//if (max1.y > min2.y)//����3
	//{
	//	return true;
	//}
	//if (max2.y > min1.y)//����4
	//{
	//	return true;
	//}
	//return false;

}
//=================================================
//�~���m���������Ă��邩�������Ă��Ȃ����𔻒肷�邾��
//����: �������W�P�A�������W�Q�A���a�P�A���a�Q
//�߂�l�F true�������Ă���:false�����Ă��Ȃ�
//================================================
bool CollisionCircle(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	D3DXVECTOR2 vDisitance = pos1 - pos2;

	float Lenght;
	Lenght = D3DXVec2LengthSq(&vDisitance);	//���[�g���g��Ȃ���
	//Length = D3DXVec2Length(&vDisitance);	//���[�g���g����(���m�Ȓ���)

	//���a�̑��a

	float size = (size1 + size2) * (size1 + size2);
	//float size = (size1+size2);	���[�g��

	//�Փ˔���
	if (size > Lenght)
	{
		return	true;
	}

	return false;
}
//--------------------------------------------
//�p�Y���̈ړ��悪�󂢂Ă��邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{

				switch (direcsion)
				{
				case UP:

					//puzzle�̏�ɕʂ̃p�Y�������邩
					if (puzzle.Position.y - PUZZLE_SIZE - (PUZZLE_SIZE / 2) < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_SIZE + (PUZZLE_SIZE / 2) > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.x)
					{

						punum = i;
						return false;
					}

					break;
				case DOWN:
					//if (puzzle.Position.y + PUZZLE_SIZE == pPuzzle[i].Position.y)	return false;
										//puzzle�̉��ɕʂ̃p�Y�������邩

					if (puzzle.Position.y + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (puzzle.Position.x - PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;
										//puzzle�̍��ɕʂ̃p�Y�������邩

					if (puzzle.Position.y - PUZZLE_SIZE / 3 <= pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 3 >= pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (puzzle.Position.x + PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;
					//puzzle�̉E�ɕʂ̃p�Y�������邩
					if (puzzle.Position.y - PUZZLE_SIZE / 3 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 3 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPuzzle[i].Position.x)
					{
						punum = i;

						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//�v���C���[�̈ړ���Ƀp�Y�������邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PlayerPuzzleOpen(PUZZLE puzzle, int index, DIRECSION direcsion)
{
	PUZZLE* pPuzzle = GetPuzzle();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzle[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzle�̏�ɕʂ̃p�Y�������邩
					if (puzzle.Position.y - PUZZLE_SIZE == pPuzzle[i].Position.y)return false;

					if (puzzle.Position.y - PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y - PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 2 > pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 2 < pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//puzzle�̉��ɕʂ̃p�Y�������邩
					if (puzzle.Position.y + PUZZLE_SIZE == pPuzzle[i].Position.y)	return false;

					if (puzzle.Position.y + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//puzzle�̍��ɕʂ̃p�Y�������邩
					if (puzzle.Position.x - PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x - PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x - PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//puzzle�̉E�ɕʂ̃p�Y�������邩
					if (puzzle.Position.x + PUZZLE_SIZE == pPuzzle[i].Position.x)	return false;

					if (puzzle.Position.y - PUZZLE_SIZE / 2 < pPuzzle[i].Position.y &&
						puzzle.Position.y + PUZZLE_SIZE / 2 > pPuzzle[i].Position.y &&
						puzzle.Position.x + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPuzzle[i].Position.x &&
						puzzle.Position.x + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPuzzle[i].Position.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//4�����Ƀp�Y�������邩��������s�[�X�̏o�����肪�L���Ă��邩
//----------------------------------------------
bool fourCollision(PUZZLE puzzle, int index)
{
	PUZZLE* pPuzzle = GetPuzzle();
	punum = -1;

	bool hitFlag;

	hitFlag = PuzzleOpen(puzzle, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
		if ((puzzle.Puzzle_TypeRight == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeRight == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeLeft == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeRight == STEAT_NUM && pPuzzle[punum].Puzzle_TypeLeft == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}

	//�����J���Ă��Ȃ�������
	hitFlag = PuzzleOpen(puzzle, index, LEFT);

	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		if ((puzzle.Puzzle_TypeLeft == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeRight == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeRight == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeLeft == STEAT_NUM && pPuzzle[punum].Puzzle_TypeRight == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}
	hitFlag = PuzzleOpen(puzzle, index, UP);


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������

		//�p�Y���̃`�b�v�̏�Ɖ����L���Ă��邩
		if ((puzzle.Puzzle_TypeUp == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeDown == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeUp == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeDown == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeUp == STEAT_NUM && pPuzzle[punum].Puzzle_TypeDown == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}

	hitFlag = PuzzleOpen(puzzle, index, DOWN);


	if (!hitFlag)
	{
		//�����J���Ă��Ȃ�������

		//�p�Y���̃`�b�v�̉��Əオ�L���Ă��邩
		if ((puzzle.Puzzle_TypeDown == STEAT_HIKKOMI && pPuzzle[punum].Puzzle_TypeUp == STEAT_DEPPARI) ||
			(puzzle.Puzzle_TypeDown == STEAT_DEPPARI && pPuzzle[punum].Puzzle_TypeUp == STEAT_HIKKOMI) ||
			(puzzle.Puzzle_TypeDown == STEAT_NUM && pPuzzle[punum].Puzzle_TypeUp == STEAT_NUM))
		{
			//�����Ă����牽�����Ȃ�
		}
		else
		{
			//�����Ă��Ȃ�������
			return false;
		}
	}


	return true;

}
//--------------------------------------
//�s�[�X�̒��̂��̂��ړ�������
//�����F�ړ������������̃|�W�V�����A���̃s�[�X�ԍ�
//--------------------------------------
void PositionPlas(D3DXVECTOR2 num,int pinNo)
{
	BLOCK* pBlock = GetChipBlock();
	JOINT* pJoint = GetJoint();
	PUZZLE_CIP* pPuzzleCip = GetPuzzleCip();
	GOAL* pGoal = GetGoal();
	THORNBLOCK* pThornBlock = GetThornBlock();
	JUMPSTAND* pJumpStand = GetJumpStand();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();


	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (pBlock[i].UseFlag)
		{

			if (pBlock[i].PieceIndex == pinNo)
			{

				pBlock[i].Position += num;

			}

		}

	}
	for (int i = 0; i < JOINT_MAX; i++)
	{
		if (pJoint[i].useFlag)
		{
			if (pJoint[i].pieNo == pinNo)
			{
				pJoint[i].pos += num;
			}

		}

	}
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPuzzleCip[i].UseFlag)
		{
			if (pPuzzleCip[i].PieceIndex == pinNo)
			{
				pPuzzleCip[i].Position += num;
			}
		}
	}
	if (pGoal->UseFlag)
	{
		if (pGoal->pieceIndex == pinNo)
		{
			pGoal->Pos += num;
		}
	}
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{//�Ƃ�
		if (pThornBlock[i].UseFlag)
		{
			if (pThornBlock[i].PieceIndex == pinNo)
			{
				pThornBlock[i].Postion += num;
			}
		}

	}
	for (int i = 0; i < JUMPSTAND_MAX; i++)
	{
		if (pJumpStand[i].UseJumpStand)
		{
			if (pJumpStand[i].PieceIndex == pinNo)
			{
				pJumpStand[i].pos += num;
			}
		}
	}
	for (int i = 0; i < SPAWN_POINT_MAX; i++)
	{
			if (pSpawnPoint[i].UseFlag)
			{
				if (pSpawnPoint[i].PieceIndex == pinNo)
				{
					pSpawnPoint[i].Position += num;
				}

			}

		

	}

}
//--------------------------------------------
//�v���C���[�̈ړ���Ƀs�[�X�����邩
//�����F���̃s�[�X�A�ړ��������s�[�X�̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PlayerPieceOpen(Piece p, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();


	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				switch (direcsion)
				{
				case UP:
					//puzzle�̏�ɕʂ̃p�Y�������邩
					if (p.pos.y - PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)return false;

					if (p.pos.y - PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y - PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 > pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 < pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case DOWN:
					//p�̉��ɕʂ̃p�Y�������邩
					if (p.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)	return false;

					if (p.pos.y + PUZZLE_HEIGHT - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case LEFT:
					//p�̍��ɕʂ̃p�Y�������邩
					if (p.pos.x - PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x - PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x - PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}

					break;
				case RIGHT:
					//p�̉E�ɕʂ̃p�Y�������邩

   					if (p.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x&& p.pos.y == pPiece[i].pos.y)	return false;

					if (p.pos.y - PUZZLE_HEIGHT / 2 < pPiece[i].pos.y &&
						p.pos.y + PUZZLE_HEIGHT / 2 > pPiece[i].pos.y &&
						p.pos.x + PUZZLE_WIDHT - PUZZLE_WIDHT / 2 < pPiece[i].pos.x &&
						p.pos.x + PUZZLE_WIDHT + PUZZLE_WIDHT / 2 > pPiece[i].pos.x)
					{
						//return false;
					}


					break;

				}

			}

		}
	}
	return true;

}//--------------------------------------------
//4�����Ƀp�Y�������邩��������s�[�X�̏o�����肪�L���Ă��邩
//----------------------------------------------
bool fourPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{
				if (piece.pos == pPiece[i].pos)
				{
					return false;
				}
			}
		}
	}

	hitFlag = PieceOpen(piece, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.x + piece.size.x / 3 < pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo ==pPiece[punum].no)
						{
							if (pPiece[punum].pos.x - pPiece[punum].size.x / 3 > pJoint[j].pos.x)
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}


	}
	JointFlag = false;

	//�����J���Ă��Ȃ�������
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.x - piece.size.x / 3 > pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.x + pPiece[punum].size.x / 3 < pJoint[j].pos.x)
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}

	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y - piece.size.y / 3 > pJoint[i].pos.y)	//�W���C���g���s�[�X�̏ゾ������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{

							if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[j].pos.y)	//��
							{
								JointFlag = true;

								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
									
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;


		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		//�����J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y + piece.size.y / 3 < pJoint[i].pos.y)	//�W���C���g���s�[�X�̏ゾ������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[j].pos.y)	//��
							{
								JointFlag = true;
								//�p�Y���̃`�b�v�̉E�ƍ����L���Ă��邩
								if ((pJoint[i].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP) ||
									(pJoint[i].type == JOINT_TYPE::TYPE_DIP && pJoint[j].type == JOINT_TYPE::TYPE_BUMP))
								{
									//�����Ă����牽�����Ȃ�
								}
								else
								{
									//�����Ă��Ȃ�������
									return false;
								}


							}


						}

					}

				}
			}
		}
		if (!JointFlag)
		{
			return false;
		}
	}


	return true;

}
//--------------------------------------------
//�p�Y���̈ړ��悪�󂢂Ă��邩
//�����F���̃p�Y���A�ړ��������p�Y���̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool PieceOpen(Piece piece, int index, DIRECSION direcsion)
{
	Piece* pPiece = GetPiece();

	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (i != index)
			{

				switch (direcsion)
				{
				case UP:

					//piece�̏�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PUZZLE_SIZE - (PUZZLE_SIZE / 2) < pPiece[i].pos.y &&
						piece.pos.y - PUZZLE_SIZE + (PUZZLE_SIZE / 2) > pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_SIZE / 3 >= pPiece[i].pos.x)
					{

						punum = i;
						return false;
					}

					break;
				case DOWN:
					//if (piece.pos.y + PUZZLE_SIZE == pPiece[i].pos.y)	return false;
										//piece�̉��ɕʂ̃p�Y�������邩

					if (piece.pos.y + PUZZLE_SIZE - PUZZLE_SIZE / 2 < pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_SIZE + PUZZLE_SIZE / 2 > pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_SIZE / 3 >= pPiece[i].pos.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (piece.pos.x - PUZZLE_SIZE == pPiece[i].pos.x)	return false;
										//piece�̍��ɕʂ̃p�Y�������邩

					if (piece.pos.y - PUZZLE_SIZE / 3 <= pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_SIZE / 3 >= pPiece[i].pos.y &&
						piece.pos.x - PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x - PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (piece.pos.x + PUZZLE_SIZE == pPiece[i].pos.x)	return false;
					//piece�̉E�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PUZZLE_SIZE / 3 < pPiece[i].pos.y &&
						piece.pos.y + PUZZLE_SIZE / 3 > pPiece[i].pos.y &&
						piece.pos.x + PUZZLE_SIZE - PUZZLE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x + PUZZLE_SIZE + PUZZLE_SIZE / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}


					break;

				}

			}

		}
	}
	return true;

}
//--------------------------------------------
//4�����Ƀp�Y�������邩��������s�[�X�̃m�[�}����
//----------------------------------------------
bool fourNomalPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{


			if (i != index)
			{
				if (piece.pos == pPiece[i].pos)
				{
					return false;
				}
			}
		}

	}


	hitFlag = PieceOpen(piece, index, RIGHT);
	//�E���J���Ă��Ȃ�������
	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo ==  piece.no)
			{
				if (pJoint[j].pos.x>piece.pos.x+piece.size.x/3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)	//���̃s�[�X�̃W���C���g��������
			{
				//�W���C���g���Ȃ�������
				if (pPiece[punum].pos.x - pPiece[punum].size.x / 3 > pJoint[i].pos.x)
				{
					//�����Ă��Ȃ�������
					return false;
				}	
			}
		}
	}
	JointFlag = false;

	//�����J���Ă��Ȃ�������
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.x < piece.pos.x - piece.size.x / 3)
				{
					return false;
				}
			}
		}

		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{				//�W���C���g���Ȃ�������

				if (pPiece[punum].pos.x + pPiece[punum].size.x / 3 < pJoint[i].pos.x)
				{
					//�����Ă��Ȃ�������
					return false;
				}
			}
		}
	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.y < piece.pos.y - piece.size.y / 3)
				{
					return false;
				}
			}
		}

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{
				//�W���C���g���Ȃ�������

				if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[i].pos.y)	//��
				{
					{
						//�����Ă��Ȃ�������
						return false;
					}


				}


			}

		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;


	if (!hitFlag)
	{
		for (int j = 0; j < JOINT_MAX; j++)
		{
			if (pJoint[j].pieNo == piece.no)
			{
				if (pJoint[j].pos.y > piece.pos.y + piece.size.y / 3)
				{
					return false;
				}
			}
		}

		//�����J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == pPiece[punum].no)
			{
				//�W���C���g���Ȃ�������
				if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[i].pos.y)	//��
				{
					//�����Ă��Ȃ�������
					return false;

				}


			}

		}

	}


	return true;

}
//--------------------------------
//��]�����ɖ߂�
//�����F�p�Y���̓Y����
//--------------------------------
void Rotreturn(int index)
{
	MOUSE* pMouse = GetMouse();

	for (int i = 0; i < pMouse->RotIndex; i++)
	{
		RotateMapChipL(index);

	}

}
//------------------------------
//�X�v���b�g�X�e�[�W�̊O�ɏo�Ă邩
//
//------------------------------
bool SpritStageCollision(Piece p)
{
	SplitStage* pSprit = GetSplitStage();

	D3DXVECTOR2 up = pSprit->Split3[0][0];
	D3DXVECTOR2 down = pSprit->Split3[0][2];
	D3DXVECTOR2 right = pSprit->Split3[2][0];
	D3DXVECTOR2 left = pSprit->Split3[0][1];

	float x = p.pos.x;

	//��̔���
	if (p.pos.y > up.y + SPLIT_SIZE / 2)
	{
		return false;
	}
	//��
	if (p.pos.y < down.y - SPLIT_SIZE / 2)
	{
		return false;
	}
	//�E
	if (p.pos.x > right.x + SPLIT_SIZE/2)
	{
		return false;
	}
	//��


	if (x < left.x - SPLIT_SIZE / 2);
	{
		if (p.pos.x < left.x - SPLIT_SIZE / 2)
		{
			return false;

		}
	}

	return true;
}


