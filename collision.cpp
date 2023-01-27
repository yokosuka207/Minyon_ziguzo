/*==============================================================================

   �����蔻��Ǘ� [collsion.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

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
#include "start.h"
#include"xkeyboard.h"
#include "xinput.h"
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
#include "StoryKey.h"		//�X�g�[���[�p��
#include "bullet.h"			//�h�b�y���Q���K�[���˒e
#include "doppelganger.h"   //�h�b�y���Q���K�[
#include"lamp.h"
#include"lamp_switch.h"
#include "spawnpoint_d.h"
#include "enemy.h"			//�G�l�~�[

#include "JumpStandExplain.h"		

#include "EffectSpark.h"	// �q�o�i�G�t�F�N�g
#include"switch.h"	//�X�C�b�`
#include"SwitchWall.h"//switch�̕�
#include"cursor.h"

#include"sound.h"
#include"bullet.h"

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

bool DoppelPieceOpen(Piece pi, int index, DIRECSION direcsion);

bool fourPieceCollision(Piece piece, int index);
bool PieceOpen(Piece piece, int index, DIRECSION direcsion);
bool fourNomalPieceCollision(Piece piece, int index);
void Rotreturn(int index);
bool SpritStageCollision(Piece p);

int punum = 0;	//�p�Y���̔z��̓Y�����̊i�[

static Time* pTime = pTime->GetTime();
static TimeParam* pTimeParam = pTime->GetTimeParam();
DIRECSION Direcsion = NUM;	//�����̊m�F
static bool InventoryFlag = false;

//���ʉ�
//����u���b�N
static int g_BrokenSoundNo = 0;
static char g_BrokenSoundName[] = "data\\SoundData\\SE\\�ؔ�������(������).wav";
//�X�C�b�`
static int g_SwitchSoundNo = 0;
static char g_SwitchSoundName[] = "data\\SoundData\\SE\\�X�C�b�`(�j�R�j�E�R�����Y).wav";
//���[�v
static int g_WarpSoundNo = 0;
static char g_WarpSoundName[] = "data\\SoundData\\SE\\���[�v(�������ʉ��ŗV�ڂ��I).wav";
//�����Ƃ�������鏰
static int g_HighSoundNo = 0;
static char g_HighSoundName[] = "data\\SoundData\\SE\\�^�C�v���C�^�[.wav";
//��
static int g_KeySoundNo = 0;
static char g_KeySoundName[] = "data\\SoundData\\SE\\������.wav";
//����
static int g_OpenKeySoundNo = 0;
static char g_OpenKeySoundName[] = "data\\SoundData\\SE\\�����J����(�������ʉ��ŗV�ڂ��I).wav";
//�s�[�X�̍���
static int g_MatchPieceSoundNo = 0;
static char g_MatchPieceSoundName[] = "data\\SoundData\\SE\\�s�[�X�͂ߍ��މ�(�������ʉ��ŗV�ڂ��I).wav";
//�낤����
static int g_CandleSoundNo = 0;
static char g_CandleSoundName[] = "data\\SoundData\\SE\\�낤����(���ʉ����{).wav";
//�X�^�[�g
static int g_GoalSoundNo = 0;
static char g_GoalSoundName[] = "data\\SoundData\\SE\\�h�A���J���鉹(�������ʉ��ŗV�ڂ��I).wav";
//�G���S
static int g_EnemySoundNo = 0;
static char g_EnemySoundName[] = "data\\SoundData\\SE\\�낤����(���ʉ����{).wav";





//===============================
//����������
//================================
void InitCollision()
{
	g_BrokenSoundNo = LoadSound(g_BrokenSoundName);
	g_SwitchSoundNo = LoadSound(g_SwitchSoundName);
	g_WarpSoundNo = LoadSound(g_WarpSoundName);
	g_HighSoundNo = LoadSound(g_HighSoundName);
	g_KeySoundNo = LoadSound(g_KeySoundName);
	g_OpenKeySoundNo = LoadSound(g_OpenKeySoundName);
	g_MatchPieceSoundNo = LoadSound(g_MatchPieceSoundName);
	g_CandleSoundNo = LoadSound(g_CandleSoundName);
	g_GoalSoundNo = LoadSound(g_GoalSoundName);
	g_EnemySoundNo = LoadSound(g_EnemySoundName);
}


//===============================
//�X�V����
//================================
void UninitCollision()
{
	StopSound(g_BrokenSoundNo);
	StopSound(g_SwitchSoundNo);
	StopSound(g_WarpSoundNo);
	StopSound(g_HighSoundNo);
	StopSound(g_KeySoundNo);
	StopSound(g_OpenKeySoundNo);
	StopSound(g_MatchPieceSoundNo);
	StopSound(g_CandleSoundNo);
	//StopSound(g_GoalSoundNo);
	StopSound(g_EnemySoundNo);
}



//===============================
//�����蔻�菈��
//�����蔻�����C�ɍs��
//================================
void UpdateCollision(){
	// �g�p�Q�b�g�ꗗ-----------------------------
	PLAYER* pPlayer = GetPlayer();
	MOUSE* pMouse = GetMouse();
	ENEMY* pEnemy = GetEnemy();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();

	WARP* pWarp = GetWarp();

	BLOCK* pBlock = GetBlock();
	BLOCK* pChipblock = GetChipBlock();
	MOVEBLOCK* pMoveBlock = GetMoveBlock();
	FALLBLOCK* pFallBlock = GetFallBlock();
	THORNBLOCK* pThornBlock = GetThornBlock();

	BROKEN* pBroken = GetBroken();
	HIGH* pHigh = GetHigh();
	SWITCH* pSwitch = GetSwitch();
	SWITCHWALL* pSwitchWall = GetSwitchWall();
	JUMPSTAND* pJumpStand = GetJumpStand();
	KEY* pKey = GetKey();
	STORYKEY* pSKey = GetStoryKey();
	OPENKEY* pOpenKey = GetOpenKey();
	GKey* pGKey = GetGKey();
	EXPLAIN* p_Explain = GetExplain();
	LAMP* p_Lamp = GetLamp();
	LAMP_SWITCH* p_LampSwitch = GetLampSwitch();
	DOPPELGANGER* pDoppel = GetDoppelganger();

	GOAL* pGoal = GetGoal();
	START* pStart = GetStart();
	RESULT* pResult = GetResult();

	Piece* pPiece = GetPiece();
	BULLET* pBullet = GetBullet();
	CURSOR* pCursor = GetCurso();
	//-------------------------------------

	bool pFlag = false;	//�v���[���[���s�[�X�̒��ɂ��邩
	bool dFlag = false;	//�h�b�y���Q���K�[���s�[�X�̒��ɂ��邩
	InventoryFlag = false;
	//�v���[���[�������Ă���s�[�X�̒��ɂ��邩
	for (int i = 0; i < PUZZLE_MAX; i++) {
		//Piece* pPiece = GetPiece();
		if (pPiece[i].MoveFlag){
			if (pPiece[i].pos.y - pPiece[i].size.y / 2 < pPlayer->Position.y &&
				pPiece[i].pos.y + pPiece[i].size.y / 2 > pPlayer->Position.y &&
				pPiece[i].pos.x - pPiece[i].size.x / 2 < pPlayer->Position.x &&
				pPiece[i].pos.x + pPiece[i].size.x / 2 > pPlayer->Position.x)
			{
				//������
				pFlag = true;
				break;
			}
			//break;
		}
	}

	for (int i = 0; i < PUZZLE_MAX; i++) {
		if (pPiece[i].MoveFlag) {

			if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pDoppel->Position.y &&
				pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pDoppel->Position.y &&
				pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pDoppel->Position.x &&
				pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pDoppel->Position.x &&
				pDoppel->UseFlag == true)
			{
				dFlag = true;
				break;
			}
		}
	}

	//============================
	//�C���x���g���n
	//============================
	if (!pFlag&&!dFlag) {
		// �s�[�X�ƃC���x���g���͈͂̓����蔻��
		for (int i = 0; i < PUZZLE_MAX; i++) {
			if (pPiece[i].UseFlag)
			{
				if (pPlayer->PieceIndex != pPiece[i].no&& pDoppel->PieceIndex != pPiece[i].no)
				{
					// �s�[�X���C���x���g���ɂ��܂�
					if (!pPiece[i].InventoryFlag && pPiece[i].UseFlag && pPiece[i].pos.x < -INVENTORYBG_POS_X_REVESE + INVENTORYBG_SIZE_X * 2.3f) {
						DeleteMapChip(i);
						SetInventory(pPiece[i].no);
						pPiece[i].InventoryFlag = true;

						break;
					}
				}

				
			}
		}

		//=========================================
		//�v���[���[�ƃq���g�\��
		//=========================================
		//�W�����v��q���g
		
		if (p_Explain->bUse) {
			if (CollisionBB(pPlayer->Position, p_Explain->pos, pPlayer->size * 2, p_Explain->size * 2))
			{
				p_Explain->CollisionUse = true;
			}
			else {
				p_Explain->CollisionUse = false;
			}
		}
		
		//������q���g
		//for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		//	if (pMoveBlock[i].bUse) {
		//		if (CollisionBB(pPlayer->Position, pMoveBlock[i].pos, pPlayer->size * 2, pMoveBlock[i].size * 2)) 
		//		{
		//			
		//		}
		//		else
		//		{
		//			pExplain->bUse = false;
		//		}
		//	}
		//}

		//=========================================
		//�X�C�b�`�n(switch,SwitchWall)
		//=========================================
		for (int i = 0; i < SWITCH_MAX; i++) {
			//�X�C�b�`�ƃv���C���[�̓����蔻��
			if (pSwitch[i].UseFlag) {
				if (pSwitch[i].pos.x - pSwitch[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
					pSwitch[i].pos.x + pSwitch[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
					pSwitch[i].pos.y - pSwitch[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
					pSwitch[i].pos.y + pSwitch[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2)
				{
					pSwitch[i].PressFlag = true;//�����ꂽ��
					pSwitch[i].PaternNo = 1;
					if (pSwitch[i].NotPressed)
					{
						SetVolume(g_SwitchSoundNo, 0.5f);
						PlaySound(g_SwitchSoundNo, 0);
						pSwitch[i].NotPressed = false;
					}
				}
				else {
					pSwitch[i].PressFlag = false;
					pSwitch[i].PaternNo = 0;
					pSwitch[i].NotPressed = true;
				}

				//�X�C�b�`�Ɩؔ��̓����蔻��
				for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
					if(CollisionBB(pSwitch[i].pos,pMoveBlock[j].pos,pSwitch[i].size,pMoveBlock[j].size)){
						pSwitch[i].PressFlag = true;//�����ꂽ��
						pSwitch[i].PaternNo = 1;
						if (pSwitch[i].NotPressed == true)
						{
							SetVolume(g_SwitchSoundNo, 0.5f);
							PlaySound(g_SwitchSoundNo, 0);
							pSwitch[i].NotPressed = false;
						}
					}
					//else {
					//	pSwitch[i].PressFlag = false;
					//	pSwitch[i].PaternNo = 0;
					//	pSwitch[i].NotPressed = true;
					//}
				}

				if (CollisionBB(pSwitch[i].pos, pDoppel->Position, pSwitch[i].size, pDoppel->size)) {
					pSwitch[i].PressFlag = true;//�����ꂽ��
					pSwitch[i].PaternNo = 1;
					if (pSwitch[i].NotPressed == true)
					{
						SetVolume(g_SwitchSoundNo, 0.5f);
						PlaySound(g_SwitchSoundNo, 0);
						pSwitch[i].NotPressed = false;
					}
				}

			
				if (pSwitch[i].PressFlag) {
					for (int j = 0; j < SWITCHWALL_MAX * SWITCHWALL_LIMIT; j++) {
						if (pSwitch[i].SwitchIndex == pSwitchWall[j].SwitchIndex) {
							pSwitchWall[j].PressFlag = true;	//�����ꂽ��ǂ��Ȃ��Ȃ�
						}
					}
				}
				else {
					for (int j = 0; j < SWITCHWALL_MAX * SWITCHWALL_LIMIT; j++) {
						if (pSwitch[i].SwitchIndex == pSwitchWall[j].SwitchIndex) {
							pSwitchWall[j].PressFlag = false;		//�Ǐo��
						}
					}
				}
			}
		}
		bool SwitchWallFlag = false;
		for (int i = 0; i < SWITCHWALL_MAX * SWITCHWALL_LIMIT; i++) {
			if (pSwitchWall[i].UseFlag)
			{
				if (!pSwitchWall[i].PressFlag) {
					//�v���[���[�ƕǂ̔���
					//�ǂ̍��ƃv���C���[�̉E
					if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 >= pPlayer->oldpos.x + pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 3 &&
						pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 3)
					{
						pPlayer->Position.x = pPlayer->oldpos.x;
					}
					//�ǂ̉E�ƃv���C���[�̍�
					if (pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 <= pPlayer->oldpos.x - pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
						pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2)
					{
						pPlayer->Position.x = pPlayer->oldpos.x;
					}
					//�ǂ́��ƃv���C���[�̏�
					if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < pPlayer->Position.y - pPlayer->size.y / 2 &&
						pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 >= pPlayer->oldpos.y - pPlayer->size.y / 2)
					{
						pPlayer->Position = pPlayer->oldpos;
					}
					//�ǂ́��ƃv���C���[�́�
					if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
						pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2 &&
						pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 <= pPlayer->oldpos.y - pPlayer->size.y / 2)
					{
						if (!pPlayer->isSwithWall)
						{
							pPlayer->Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 + pPlayer->size.y / 2;
							pPlayer->jump = false;
							pPlayer->fall = false;
							pPlayer->WarpFlag = false;
							pPlayer->isSwithWall = true;
							pPlayer->sp.y = 0;
							pPlayer->frame = 0;
							SwitchWallFlag = true;

						}
						else {
							pPlayer->isSwithWall = false;

						}
					}
					else if (!SwitchWallFlag) {
						pPlayer->isSwithWall = false;

					}

					//�ǂ�jumpstand�̔���
					for (int j = 0; j < JUMPSTAND_MAX; j++) {
						if (CollisionBB(pSwitchWall[i].pos, pJumpStand[j].pos, pSwitchWall[i].size, pJumpStand[j].size)) {
							pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
						}
					}
					//�ǂƓ����u���b�N�̔���
					for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
						if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < pMoveBlock[j].pos.x + pMoveBlock[j].size.x / 2 &&
							pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > pMoveBlock[j].pos.x - pMoveBlock[j].size.x / 2 &&
							pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > pMoveBlock[j].pos.y - pMoveBlock[j].size.y / 2 &&
							pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 <=pMoveBlock[j].oldpos.y - pMoveBlock[j].size.y / 2)
						{
							pMoveBlock[j].pos.y = pMoveBlock[j].oldpos.y;
						}
					}
				}
			}
		}




		//=====================================
		// start
		//=====================================
		for (int i = 0; i < START_MAX; i++) {
			if (pStart[i].UseFlag) {
				if (pStart[i].GoalFlag) {
					if (CollisionBB(pPlayer->Position, pStart[i].pos, pPlayer->size, pStart[i].size)) {
						SetResultType(WIN);
						StartFade(FADE::FADE_ALPHA_OUT);
						pTime->EndTime();
						pTimeParam->EndFlag = true;
					}
				}
			}
		}

		//=====================================
		//���S����i�g�Q�A������,thornBlock�j
		//=====================================
		if (!Mouse_IsLeftDown() &&
			!pCursor->bHave)
		{
			//�v���C���[�ƃg�Q�u���b�N�̔���(�v���C���[���g�Q��)
			for (int i = 0; i < THORN_BLOCK_MAX; i++) {
				if (pThornBlock[i].UseFlag) {
					if (CollisionBB(pThornBlock[i].Postion, pPlayer->Position, pThornBlock[i].Size, pPlayer->size)) {

						pPlayer->hp--;
						SetVolume(g_CandleSoundNo, 0.8f);
						PlaySound(g_CandleSoundNo, 0);
						for (int j = 0; j < SPAWN_POINT_MAX; j++) {//���X�|��������HP�����葱���Ă���
							if (pSpawnPoint[j].UseFlag) {
								if (pPlayer->PieceIndex == pSpawnPoint[j].PieceIndex) {
									pPlayer->Position = pSpawnPoint[j].Position;
									pPlayer->oldpos = pSpawnPoint[j].Position;
									pPlayer->sp.y -= 1.0f;
									break;
								}
							}
							else if (j == SPAWN_POINT_MAX - 1) {
								pPlayer->Position = pSpawnPoint[0].Position;
								pPlayer->oldpos = pSpawnPoint[0].Position;
								pPlayer->sp.y -= 1.0f;
								break;
							}
						}
					}
				}
			}

			//�v���C���[��������
			if (pPlayer->Position.y - pPlayer->size.y < -SCREEN_HEIGHT / 2) {
				pPlayer->hp--;
				SetVolume(g_CandleSoundNo, 0.8f);
				PlaySound(g_CandleSoundNo, 0);
				for (int j = 0; j < SPAWN_POINT_MAX; j++) {//���X�|��������HP�����葱���Ă���
					if (pSpawnPoint[j].UseFlag) {
						if (pPlayer->PieceIndex == pSpawnPoint[j].PieceIndex - 1) {
							pPlayer->Position = pSpawnPoint[j].Position;
							pPlayer->oldpos = pSpawnPoint[j].Position;
							pPlayer->sp.y -= 1.0f;
							break;
						}
					}
					else if (j == SPAWN_POINT_MAX - 1) {
						pPlayer->Position = pSpawnPoint[0].Position;
						pPlayer->oldpos = pSpawnPoint[0].Position;
						pPlayer->sp.y -= 1.0f;
						break;
					}
				}
			}
			//�v���C���[�c�@�[��
			if (pPlayer->hp <= 0) {
				pPlayer->UseFlag = false;
				SetResultType(LOSE);
				StartFade(FADE::FADE_ALPHA_OUT);
				pTime->EndTime();
				pTimeParam->EndFlag = true;
			}

			//========================================================================
			//�v���C���[�E�`�b�v�u���b�N�@�����蔻��(Player��ChipBlock�̓����蔻��)
			//=========================================================================
			for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
				if ((pChipblock + i)->UseFlag) {
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
						pPlayer->sp.y = 0;
						for (int i = 0; i < JUMPSTAND_MAX; i++)
						{
							pJumpStand[i].JumpStandFlag = false;

						}
						pPlayer->isHigh = false;

						pPlayer->fall = true;
						pPlayer->getfall = true;
						pPlayer->frame = 50;
					}
				}
			}
			//========================================================================
			//�v���C���[�E���[�v�@�����蔻��(Player��Warp�̓����蔻��)
			//========================================================================	
			pPlayer->CoolTime--;
			if (pPlayer->CoolTime < 0) {
				pPlayer->CoolTime = 0;
				//�v���C���[�E���[�v�@�����蔻��
				for (int i = 0; i < WARP_MAX; i++) {
					if ((pWarp + i)->UseFlag) {
						if (pPlayer->Position.x + pPlayer->size.x / 2 > (pWarp + i)->Position.x - (pWarp + i)->Size.x / 2 &&
							pPlayer->Position.x - pPlayer->size.x / 2 < (pWarp + i)->Position.x + (pWarp + i)->Size.x / 2 &&
							pPlayer->Position.y + pPlayer->size.y / 2 > (pWarp + i)->Position.y - (pWarp + i)->Size.y / 2 &&
							pPlayer->Position.y - pPlayer->size.y / 2 < (pWarp + i)->Position.y + (pWarp + i)->Size.y / 2)
						{
							if (i % 2 == 0)
							{
								if (pWarp[i + 1].UseFlag)
								{
									if (!pWarp[i + 1].InventoryFlag)
									{
										if (!pPlayer->WarpFlag)
										{
											pPlayer->Position = (pWarp + i + 1)->Position;
											pPlayer->oldpos = pPlayer->Position;
											pPlayer->CoolTime = PLAYER_COOLTIME;
											SetVolume(g_WarpSoundNo, 0.5f);
											PlaySound(g_WarpSoundNo, 0);
											pPlayer->WarpFlag = true;
										}
									}
								}

							}
							else if (i % 2 == 1)
							{
								if (pWarp[i - 1].UseFlag)
								{
									if (!pWarp[i - 1].InventoryFlag)
									{
										if (!pPlayer->WarpFlag)
										{
											pPlayer->Position = (pWarp + i - 1)->Position;
											pPlayer->oldpos = pPlayer->Position;

											pPlayer->CoolTime = PLAYER_COOLTIME;
											//SetVolume(g_WarpSoundNo, 0.5f);
											PlaySound(g_WarpSoundNo, 0);
											pPlayer->WarpFlag = true;

										}
									}
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
			bool BrokenFlag = false;
			for (int i = 0; i < BROKEN_MAX; i++) {
				if ((pBroken + i)->UseFlag) {
					//�v���C���[���E����u���b�N�E
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
						pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 3 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 3)
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
						for (int j = 0; j < JUMPSTAND_MAX; j++)
						{
							pJumpStand[j].JumpStandFlag = false;

						}
						pPlayer->PieceIndex = pBroken[i].index;
						pPlayer->Position.y = (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 + pPlayer->size.y / 2;
						pPlayer->jump = false;
						pPlayer->fall = false;
						pPlayer->frame = 0;
						pPlayer->isBrokenBlock = true;
						pPlayer->sp.y = 0.0f;
						BrokenFlag = true;
					}
					else if (!BrokenFlag)
					{
						pPlayer->isBrokenBlock = false;

					}
					//�v���C���[���E����u���b�N��,����
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
						pPlayer->oldpos.y + pPlayer->size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
					{
						(pBroken + i)->breakFlag = true;
						SetVolume(g_BrokenSoundNo, 0.5f);
						PlaySound(g_BrokenSoundNo, 0);
						(pBroken + i)->UseFlag = false;
						SetBrokenAnime(D3DXVECTOR2(pBroken[i].Postion.x, pBroken[i].Postion.y + 8), D3DXVECTOR2(pBroken[i].Size.x*2, pBroken[i].Size.y*2), pBroken[i].index);
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
				if (pMoveBlock[i].bUse) {
					if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
						pPlayer->oldpos.x + pPlayer->size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
					{
						//pMoveBlock[i].sp = pPlayer->sp;
						//pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
						pPlayer->Position = pPlayer->oldpos;
					}
					if (pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
						pPlayer->oldpos.x - pPlayer->size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
					{
						//pMoveBlock[i].sp = pPlayer->sp;
						//pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
						pPlayer->Position = pPlayer->oldpos;
					}
					if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
						pPlayer->oldpos.y + pPlayer->size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
					{
						//pMoveBlock[i].sp = pPlayer->sp;
						//pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
						pPlayer->Position = pPlayer->oldpos;

					}
					//�v���C���[���E�u���b�N��,��������
					if (pPlayer->Position.x + pPlayer->size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
						pPlayer->oldpos.y - pPlayer->size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
					{
						pPlayer->Position.y = pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 + pPlayer->size.y / 2;
						pMoveBlock[i].MoveFlag = true;
						// ���n���ɂ���
						if (!pPlayer->isMoveBlock) {
							pPlayer->sp.y = 0.0f;
							pPlayer->isMoveBlock = true;
							break;
						}

					}
					else {
						pMoveBlock[i].MoveFlag = false;

						pPlayer->isMoveBlock = false;
					}


				}
			}
			//====================================================================
			//�v���C���[�Ɨ�����u���b�N�̓����蔻��(Player��FallBlock�̓����蔻��)
			//====================================================================
			bool FallFlag = false;
			for (int i = 0; i < FALLBLOCK_MAX; i++) {
				if ((pFallBlock + i)->UseFlag) {
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

					}
					//�v���C���[���E������u���b�N
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 &&
						pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
					{
						pPlayer->PieceIndex = pFallBlock[i].PieceIndex;

						pPlayer->Position.y = (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 + pPlayer->size.y / 2;
						pPlayer->getfall = false;
						pPlayer->jump = false;
						pPlayer->fall = false;
						pPlayer->frame = 50;
						//pPlayer->sp.y = -0.4f;
						pPlayer->isFallBlock = true;
						(pFallBlock + i)->oldpos = (pFallBlock + i)->Position;
						(pFallBlock + i)->Position.y -= 3.0f;
						FallFlag = true;
					}
					else if (!FallFlag)
					{
						pPlayer->isFallBlock = false;
					}

					for (int j = 0; j < BLOCK_CHIP_MAX; j++)
					{
						if (pChipblock[j].UseFlag)
						{
							if (pFallBlock[i].Position.x + pFallBlock[i].Size.x / 3 > (pChipblock + j)->Position.x - (pChipblock + j)->Size.x / 2 &&
								pFallBlock[i].Position.x - pFallBlock[i].Size.x / 3 < (pChipblock + j)->Position.x + (pChipblock + j)->Size.x / 2 &&
								pFallBlock[i].Position.y - pFallBlock[i].Size.y / 2 < (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2 &&
								pFallBlock[i].oldpos.y - pFallBlock[i].Size.y / 2 >= (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2)
							{
								pFallBlock[i].Position.y = (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2 + pFallBlock[i].Size.y / 2;
							}

						}
					}

				}
			}
			//====================================================================
			//�v���C���[�ƍ��������u���b�N�̓����蔻��(Player��High�̓����蔻��)
			//====================================================================
			for (int i = 0; i < HIGH_MAX; i++) {
				if ((pHigh + i)->UseFlag)
				{
					//�v���C���[���E����������u���b�N�E
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
						pPlayer->oldpos.x + pPlayer->size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
						pPlayer->Position.y + pPlayer->size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 3 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 3)
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
						pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 3 &&
						pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 3)
					{
						pPlayer->PieceIndex = pHigh[i].index;

						if (pPlayer->sp.y <= -5.0f) {
							//pPlayer->isHigh = false;
							(pHigh + i)->UseFlag = false;
							pHigh[i].breakFlag = true;
							SetVolume(g_BrokenSoundNo, 0.5f);
							PlaySound(g_BrokenSoundNo, 0);
							SetHighAnime(D3DXVECTOR2(pHigh[i].Postion.x, pHigh[i].Postion.y + 8), D3DXVECTOR2(pHigh[i].Size.x * 2, pHigh[i].Size.y * 2), pHigh[i].index);

							//SetVolume(g_HighSoundNo, 0.5f);
							//PlaySound(g_HighSoundNo, 0);
							pPlayer->frame = 50;
							break;
						}
						else {
							//pPlayer->isHigh = true;
							//pPlayer->sp.y = -0.1f;
							pPlayer->Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + pPlayer->size.y / 2;
							// ���n���ɂ���
							if (!pPlayer->isHigh) {
								//pPlayer->sp.y = -0.1f;
								pPlayer->isHigh = true;
								break;
							}
							else {
								pPlayer->isHigh = false;
							}
						}

					}

					/*
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
						pPlayer->Position.y = (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 - pPlayer->size.y / 2;
					}
					// �v���C���[�̉��Ƀu���b�N����������
					if (pPlayer->Position.x + pPlayer->size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
						pPlayer->Position.x - pPlayer->size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
						pPlayer->Position.y - pPlayer->size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
						pPlayer->oldpos.y - pPlayer->size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
					{
						//pPlayer->Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + pPlayer->size.y / 2;

					}
				}
			}
			//-----------------------------------------------------
			//�v���C���[�ƌ��̓����蔻��(Player��Key)
			//-----------------------------------------------------
			for (int i = 0; i < KEY_MAX; i++) {
				if (pKey[i].UseFlag) {
					if (CollisionBB(pKey[i].Position, pPlayer->Position, pKey[i].Size, pPlayer->size)) {
						pPlayer->HaveKey++;
						pKey[i].GetKey = true;
						pKey[i].UseFlag = false;
						SetVolume(g_BrokenSoundNo, 0.5f);
						PlaySound(g_KeySoundNo, 0);
					}
				}
			}
			//-----------------------------------------------------------------
			//�ʏ팮�擾�v���C���[�ƌ��ŊJ�����̓����蔻��(Player��OpenKey)
			//-----------------------------------------------------------------
			for (int i = 0; i < OPEN_KEY_MAX * STAGE_OPEN_KEY_MAX; i++) {
				if (pOpenKey[i].DrawFlag) {
					if (CollisionBB((pOpenKey + i)->Position, pPlayer->Position, (pOpenKey + i)->Size, pPlayer->size)) {
						if (pPlayer->HaveKey > 0) {
							if (i == 0 || i == 3 || i == 6) {
								(pOpenKey + i)->KeyOpen = true;
								(pOpenKey + i + 1)->KeyOpen = true;
								(pOpenKey + i + 2)->KeyOpen = true;

								(pOpenKey + i)->DrawFlag = false;
								(pOpenKey + i + 1)->DrawFlag = false;
								(pOpenKey + i + 2)->DrawFlag = false;
								pPlayer->HaveKey--;
							}
							//SetVolume(g_OpenKeySoundNo, 0.5f);
							PlaySound(g_OpenKeySoundNo, 0);
						}
					}
				}
			}

			//-----------------------------------------------------
			//�v���C���[�ƌ��t�����̓����蔻��(Player��OpenKey)
			//-----------------------------------------------------
			bool OpenKeyFlag = false;

			for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
				for (int i = 0; i < OPEN_KEY_MAX; i++) {
					if ((pOpenKey + j + i)->DrawFlag) {
						//�v���[���[�Ɣ��̔���
						//���̍��ƃv���C���[�̉E
						if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 >= pPlayer->oldpos.x + pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 3 &&
							(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 3)
						{
							pPlayer->Position.x = pPlayer->oldpos.x;
						}
						//���̉E�ƃv���C���[�̍�
						if ((pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 <= pPlayer->oldpos.x - pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
							(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2)
						{
							pPlayer->Position.x = pPlayer->oldpos.x;
						}
						//���́��ƃv���C���[�̏�
						if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
							(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 >= pPlayer->oldpos.y + pPlayer->size.y / 2)
						{
							pPlayer->Position.y = pPlayer->oldpos.y;
							pPlayer->sp.y = 0.0f;
						}
						//���́��ƃv���C���[�́�
						if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
							(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2 &&
							(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 <= pPlayer->oldpos.y - pPlayer->size.y / 2)
						{
							OpenKeyFlag = true;
							if (!pPlayer->isOpenKey)
							{
								pPlayer->Position.y = pOpenKey[i].Position.y + pOpenKey[i].Size.y / 2 + pPlayer->size.y / 2 + 0.02f;
								pPlayer->jump = false;
								pPlayer->fall = false;
								pPlayer->WarpFlag = false;
								pPlayer->isOpenKey = true;
								pPlayer->sp.y = 0.0f;
								pPlayer->frame = 0;

							}
							else
							{
								pPlayer->isOpenKey = false;

							}
						}
						else if (!OpenKeyFlag) {
							pPlayer->isOpenKey = false;

						}
						//����jumpstand�̔���
						for (int j = 0; j < JUMPSTAND_MAX; j++) {
							if ((pOpenKey + j + i)->DrawFlag) {
								if (!(pOpenKey + j + i)->KeyOpen) {
									if (CollisionBB((pOpenKey + j + i)->Position, pJumpStand[j].pos, (pOpenKey + j + i)->Size, pJumpStand[j].size)) {
										pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
									}
								}
							}
						}
						//���Ɠ����u���b�N�̔���
						for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
							if ((pOpenKey + j + i)->DrawFlag) {
								if (!(pOpenKey + j + i)->KeyOpen) {
									if (CollisionBB((pOpenKey + j + i)->Position, pMoveBlock[j].pos, (pOpenKey + j + i)->Size, pMoveBlock[j].size)) {
										pMoveBlock[j].pos.y = pMoveBlock[j].oldpos.y;
									}
								}
							}
						}
					}
				}
			}
			//------------------------------------------------------------------
			//�X�g�[���[�p��
			//------------------------------------------------------------------
			for (int i = 0; i < STORYKEY_MAX; i++)
			{
				if (pSKey[i].bUse) {
					if (CollisionBB(pPlayer->Position, pSKey->pos, pPlayer->size, pSKey->size))
					{
						pSKey[i].bUse = false;
						pSKey[i].HaveSKey++;
					}
				}
			}
			////------------------------------------------------------------------
			////�S�[����p���ƃv���C���[�̓����蔻��(GKey��Player)
			////------------------------------------------------------------------
			//if (pGKey->UseFlag) {
			//	if (CollisionBB(pGKey->pos, pPlayer->Position, pGKey->size, pPlayer->size)) {
			//		pGKey->UseFlag = false;
			//		pGKey->GetGKey = true;
			//		//SetVolume(g_GKeySoundNo, 0.5f);
			//		PlaySound(g_GKeySoundNo, 0);
			//	}
			//}
			////-------------------------------------------------------------------
			////�S�[����p���擾�v���C���[�ƌ��ŊJ�����̓����蔻��(Player��Goal)
			////-------------------------------------------------------------------

			//if (pGoal->UseFlag) {
			//	if (!Mouse_IsLeftDown() && !pCursor->bHave && pGKey->GetGKey) {
			//		if (CollisionBB(pGoal->Pos, pPlayer->Position, pGoal->Size, pPlayer->size)) {
			//			pGoal->UseFlag = false;
			//			//SetVolume(g_GoalSoundNo, 0.5f);
			//			PlaySound(g_GoalSoundNo, 0);
			//			//
			//			for (int i = 0; i < START_MAX; i++) {
			//				pStart[i].GoalFlag = true;
			//			}
			//			//
			//			//SetResultType(WIN);
			//			//StartFade(FADE::FADE_OUT);
			//			//pTime->EndTime();
			//			//pTimeParam->EndFlag = true;
			//		}
			//	}
			//}
			//------------------------------------------------------
			//�G�̖ڂ̑O�ƃv���C���[�����蔻��(�v���C���[�����ʏꍇ)
			//------------------------------------------------------
			//���񂿂���
			//SE�������Ă�Ƃ��ɋC�ɂȂ�������ǉ����Ă݂����Ǘ]�v�Ȃ��Ƃ��Ă��炲�߂�˒ǉ������̓R�����g�A�E�g���Ƃ���
			//�G�l�~�[�֘A��SE�����͂��낢�댈�܂����琏���ǉ��\��
			//OK
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (pEnemy[i].UseFlag) {
					pEnemy[i].AIFlag = false;
					if (pEnemy[i].dir == ENEMY_DIRECTION::DIRECTION_LEFT)
					{
						if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x - 40.0f, pEnemy[i].pos.y), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x + 80, pEnemy[i].size.y), pPlayer->size)) {
							pEnemy[i].AIFlag = true;
						}
						if (Keyboard_IsKeyDown(KK_LEFTCONTROL) ||		// keyboard Ctrl�@��
							Keyboard_IsKeyTrigger(KK_C) ||					// keyboard C
							IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
						{
							if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x + 4.0f, pEnemy[i].pos.y), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x + 5.0f, pEnemy[i].size.y), pPlayer->size)) {
								pEnemy[i].UseFlag = false;
								pEnemy[i].DedFlag = true;
								SetVolume(g_EnemySoundNo, 0.8f);
								PlaySound(g_EnemySoundNo, 0);
							}

						}

					}
					else if (pEnemy[i].dir == ENEMY_DIRECTION::DIRECTION_RIGHT)
					{
						if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x + 40.0f, pEnemy[i].pos.y), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x + 80, pEnemy[i].size.y), pPlayer->size)) {
							pEnemy[i].AIFlag = true;
						}
						if (Keyboard_IsKeyDown(KK_LEFTCONTROL) ||		// keyboard Ctrl�@��
							Keyboard_IsKeyTrigger(KK_C) ||					// keyboard C
							IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
						{
							if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x - 4.0f, pEnemy[i].pos.y), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x, pEnemy[i].size.y), pPlayer->size)) {
								pEnemy[i].UseFlag = false;
								pEnemy[i].DedFlag = true;
								SetVolume(g_EnemySoundNo, 0.8f);
								PlaySound(g_EnemySoundNo, 0);
							}

						}


					}
					else if (pEnemy[i].dir == ENEMY_DIRECTION::DIRECTION_UP)
					{
						if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x, pEnemy[i].pos.y + 40.0f), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x, pEnemy[i].size.y + 80.0f), pPlayer->size)) {
							pEnemy[i].AIFlag = true;
						}
						if (Keyboard_IsKeyTrigger(KK_LEFTCONTROL) ||		// keyboard Ctrl�@��
							Keyboard_IsKeyTrigger(KK_C) ||					// keyboard C
							IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
						{
							if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x, pEnemy[i].pos.y - 4.0f), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x, pEnemy[i].size.y), pPlayer->size)) {
								pEnemy[i].UseFlag = false;
								pEnemy[i].DedFlag = true;
								SetVolume(g_EnemySoundNo, 0.8f);
								PlaySound(g_EnemySoundNo, 0);
							}

						}

					}
					else if (pEnemy[i].dir == ENEMY_DIRECTION::DIRECTION_DOWN)
					{
						if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x, pEnemy[i].pos.y - 40.0f), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x, pEnemy[i].size.y + 80.0f), pPlayer->size)) {
							pEnemy[i].AIFlag = true;
						}
						if (Keyboard_IsKeyTrigger(KK_LEFTCONTROL) ||		// keyboard Ctrl�@��
							Keyboard_IsKeyTrigger(KK_C) ||					// keyboard C
							IsButtonTriggered(0, XINPUT_GAMEPAD_B))			// GamePad B
						{
							if (CollisionBB(D3DXVECTOR2(pEnemy[i].pos.x, pEnemy[i].pos.y + 4.0f), pPlayer->Position, D3DXVECTOR2(pEnemy[i].size.x, pEnemy[i].size.y), pPlayer->size)) {
								pEnemy[i].UseFlag = false;
								pEnemy[i].DedFlag = true;
								SetVolume(g_EnemySoundNo, 0.8f);
								PlaySound(g_EnemySoundNo, 0);
							}

						}


					}
				}
			}


			//------------------------------------
			//�����u���b�N�ƃo�l�����蔻��
			//-----------------------------------
			for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
				if (pMoveBlock[i].bUse)
				{
					for (int j = 0; j < JUMPSTAND_MAX; j++) {
						if (pJumpStand[j].UseJumpStand) {

							if (CollisionBB(pMoveBlock[i].pos, pJumpStand[j].pos, pMoveBlock[i].size, pJumpStand[j].size)) {
								pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�o�l�Ɖ����炱�킷���u���b�R�����蔻��
			//-----------------------------------
			for (int i = 0; i < THORN_BLOCK_MAX; i++) {
				if (pThornBlock[i].UseFlag)
				{
					for (int j = 0; j < JUMPSTAND_MAX; j++) {
						if (pJumpStand[j].UseJumpStand) {

							if (CollisionBB(pThornBlock[i].Postion, pJumpStand[j].pos, pThornBlock[i].Size, pJumpStand[j].size)) {
								pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�o�l�ƃg�Q�u���b�N�����蔻��
			//-----------------------------------

			for (int i = 0; i < BROKEN_MAX; i++) 
			{
				if (pBroken[i].UseFlag)
				{
					for (int j = 0; j < JUMPSTAND_MAX; j++) 
					{
						if (pJumpStand[j].UseJumpStand)
						{


							//�v���C���[��E����������u���b�N��
							if (pBroken[i].Postion.x - pBroken[i].Size.x / 2 < pJumpStand[j].pos.x + pJumpStand[j].size.x / 3 &&
								pBroken[i].Postion.x + pBroken[i].Size.x / 2 > pJumpStand[j].pos.x - pJumpStand[j].size.x / 3 &&
								pBroken[i].Postion.y + pBroken[i].Size.y / 2 > pJumpStand[j].pos.y - pJumpStand[j].size.y / 2 &&
								pBroken[i].Postion.y + pBroken[i].Size.y / 2 <= pJumpStand[j].oldpos.y - pJumpStand[j].size.y / 2)
							{
								pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�o�l�ƃg�Q�u���b�N�����蔻��
			//-----------------------------------
			for (int i = 0; i < HIGH_MAX; i++) {
				if (pHigh[i].UseFlag)
				{
					for (int j = 0; j < JUMPSTAND_MAX; j++) {
						if (pJumpStand[j].UseJumpStand) {
							if (CollisionBB(pHigh[i].Postion, pJumpStand[j].pos, pHigh[i].Size, pJumpStand[j].size)) {
								pJumpStand[j].pos.y = pJumpStand[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�����u���b�Nj�ƃW�����v�ŉ󂷃u���b�Ni�����蔻��
			//-----------------------------------
			for (int i = 0; i < BROKEN_MAX; i++) {
				if (pBroken[i].UseFlag)
				{
					for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
						if (pMoveBlock[j].bUse)
						{
							if (CollisionBB(pMoveBlock[j].pos, pBroken[i].Postion, pMoveBlock[j].size, pBroken[i].Size)) {
								pMoveBlock[j].pos.y = pMoveBlock[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�����u���b�Nj�ƃg�Q�u���b�Ni�����蔻��
			//-----------------------------------
			for (int i = 0; i < THORN_BLOCK_MAX; i++) {
				if (pThornBlock[i].UseFlag)
				{
					for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
						if (pMoveBlock[j].bUse)
						{
							if (CollisionBB(pMoveBlock[j].pos, pThornBlock[i].Postion, pMoveBlock[j].size, pThornBlock[i].Size)) {
								pMoveBlock[j].pos.y = pMoveBlock[j].oldpos.y;
							}
						}
					}
				}
			}
			//------------------------------------
			//�e�ƃv���C���[�����蔻��
			//-----------------------------------
			if (pPlayer->UseFlag)
			{
				for (int i = 0; i < BULLET_MAX; i++)
				{
					if (pBullet[i].use)
					{
						if (CollisionBB(pPlayer->Position, pBullet[i].pos, pPlayer->size, D3DXVECTOR2(pBullet[i].w, pBullet[i].h)))
						{
							SetVolume(g_CandleSoundNo, 0.8f);
							PlaySound(g_CandleSoundNo, 0);
							pPlayer->hp--;
							pBullet[i].use = false;

						}

					}
				}

			}
		}
	}
	//------------------------------------
	//�h�b�y���Q���K�[�ƃv���C���[�̓����蔻��
	//------------------------------------
	if (CollisionBB(pDoppel->Position, pPlayer->Position, pDoppel->size, pPlayer->size))
	{
		if (pDoppel->UseFlag)
		{
			pPlayer->hp--;
			SetVolume(g_CandleSoundNo, 0.8f);
			PlaySound(g_CandleSoundNo, 0);
			for (int i = 0; i < SPAWN_POINT_MAX; i++) {//���X�|��������HP�����葱���Ă���
				if (pSpawnPoint[i].UseFlag) {
					if (pPlayer->PieceIndex == pSpawnPoint[i].PieceIndex) {
						pPlayer->Position = pSpawnPoint[i].Position;
					}
				}
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
//void PieceCollision()
//{
//
//	SplitStage* pSplitStage = GetSplitStage();
//	SpawnPoint* pSpawnPoint = GetSpawnPoint();
//
//	Piece* pPiece = GetPiece();
//	JOINT* pJoint = GetJoint();
//	PLAYER* pPlayer = GetPlayer();
//
//	bool colFlag = false;//�������ē�������
//	bool colFlag2 = false;//�������ē�������
//	bool pFlag = false;
//	for (int i = 0; i < PUZZLE_MAX; i++)
//	{
//		if (pPiece[i].UseFlag)
//		{
//			if (pPiece[i].MoveEndFlag)	//�����I�������
//			{
//				if (!pPiece[i].InventoryFlag)
//				{
//
//
//					pPiece[i].MoveEndFlag = false;
//
//					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
//						pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
//						pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
//						pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x &&
//						pPiece[i].no == pPlayer->PieceIndex)
//					{
//						pFlag = true;
//					}
//
//					if (!SpritStageCollision(pPiece[i]))
//					{
//						//pPiece[i].pos = pPiece[i].OldMovePos;
//						Rotreturn(pPiece[i].no);
//						colFlag2 = true;
//						D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
//						PositionPlas(temp, pPiece[i].no);
//						pPiece[i].pos = pPiece[i].OldMovePos;
//						if (pFlag)
//						{
//							pPlayer->Position = pPlayer->OneOldpos;
//							pPlayer->oldpos = pPlayer->Position;
//
//							pPlayer->hp--;
//						}
//
//						break;
//					}
//
//
//					for (int j = 0; j < JOINT_MAX; j++)
//					{
//						if (pJoint[j].pieNo == pPiece[i].no)	//�����I������s�[�X�̒��ɂ�������
//						{
//							for (int k = 0; k < JOINT_MAX; k++)
//							{
//								if (pJoint[k].useFlag)
//								{
//
//
//									if (pJoint[j].pieNo != pJoint[k].pieNo)//�s�[�X�ԍ����������
//									{
//
//
//										//�W���C���g���d�Ȃ��Ă�����
//										colFlag = CollisionBB(pJoint[j].pos, pJoint[k].pos, pJoint[j].size, pJoint[k].size);
//
//										if (colFlag)
//										{
//
//											//���ʂ������Ă�����
//											if (pJoint[j].type == JOINT_TYPE::TYPE_BUMP && pJoint[k].type == JOINT_TYPE::TYPE_DIP ||
//												pJoint[k].type == JOINT_TYPE::TYPE_BUMP && pJoint[j].type == JOINT_TYPE::TYPE_DIP)
//											{
//												colFlag2 = true;
//
//												//�W���C���g���E��������
//												if (pPiece[i].pos.x + pPiece[i].size.x / 3 < pJoint[j].pos.x)
//												{
//
//
//													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;
//
//													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x - PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);
//
//													if (fourPieceCollision(pPiece[i], i))
//													{
//														PositionPlas(temp, pPiece[i].no);
//														pPiece[i].OldMovePos = pPiece[i].pos;
//														if (pFlag)
//														{
//															pPlayer->Position += temp;
//															pPlayer->oldpos = pPlayer->Position;
//														}
//														// �q�o�i�G�t�F�N�g
//														SetEffectSpark(pJoint[j].pos, 0.0f);
//														// �s�[�X�̃A�j���[�V����
//														StartPieceAnimation(pJoint[k].indexno);
//														StartPieceAnimation(pJoint[j].indexno);
//														//SetVolume(g_MatchPieceSoundNo, 0.5f);
//														PlaySound(g_MatchPieceSoundNo, 0);
//													}
//													else
//													{
//														Rotreturn(pPiece[i].no);
//														colFlag2 = true;
//														temp = pPiece[i].OldMovePos - pPiece[i].pos;
//														PositionPlas(temp, pPiece[i].no);
//														pPiece[i].pos = pPiece[i].OldMovePos;
//														if (pFlag)
//														{
//															pPlayer->Position = pPlayer->OneOldpos;
//														}
//													}
//												}
//												//�W���C���g������������
//												else if (pPiece[i].pos.x - pPiece[i].size.x / 3 > pJoint[j].pos.x)
//												{
//													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;
//
//													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_SIZE, pPiece[pJoint[k].indexno].pos.y);
//
//													if (fourPieceCollision(pPiece[i], i))
//													{
//
//														PositionPlas(temp, pPiece[i].no);
//														pPiece[i].OldMovePos = pPiece[i].pos;
//														if (pFlag)
//														{
//															pPlayer->Position += temp;
//															pPlayer->oldpos = pPlayer->Position;
//
//														}
//														pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);
//														// �q�o�i�G�t�F�N�g
//														SetEffectSpark(pJoint[j].pos, 0.0f);
//														// �s�[�X�̃A�j���[�V����
//														StartPieceAnimation(pJoint[k].indexno);
//														StartPieceAnimation(pJoint[j].indexno);
//														//SetVolume(g_MatchPieceSoundNo, 0.5f);
//														PlaySound(g_MatchPieceSoundNo, 0);
//													}
//													else
//													{
//														Rotreturn(pPiece[i].no);
//														colFlag2 = true;
//														temp = pPiece[i].OldMovePos - pPiece[i].pos;
//														PositionPlas(temp, pPiece[i].no);
//
//														pPiece[i].pos = pPiece[i].OldMovePos;
//														if (pFlag)
//														{
//															pPlayer->Position = pPlayer->OneOldpos;
//														}
//													}
//												}
//												//�W���C���g���ゾ������
//												else if (pPiece[i].pos.y - pPiece[i].size.y / 3 > pJoint[j].pos.y)
//												{
//													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT) - pPiece[i].pos;
//
//													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT);
//
//													if (fourPieceCollision(pPiece[i], i))
//													{
//														PositionPlas(temp, pPiece[i].no);
//														pPiece[i].OldMovePos = pPiece[i].pos;
//														if (pFlag)
//														{
//															pPlayer->Position += temp;
//															pPlayer->oldpos = pPlayer->Position;
//
//														}
//														// �q�o�i�G�t�F�N�g
//														SetEffectSpark(pJoint[j].pos, 90.0f);
//														// �s�[�X�̃A�j���[�V����
//														StartPieceAnimation(pJoint[k].indexno);
//														StartPieceAnimation(pJoint[j].indexno);
//														//SetVolume(g_MatchPieceSoundNo, 0.5f);
//														PlaySound(g_MatchPieceSoundNo, 0);
//													}
//													else
//													{
//														Rotreturn(pPiece[i].no);
//														colFlag2 = true;
//														temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
//														PositionPlas(temp, pPiece[i].no);
//
//														pPiece[i].pos = pPiece[i].OldMovePos;
//														if (pFlag)
//														{
//															pPlayer->Position = pPlayer->OneOldpos;
//														}
//
//													}
//
//												}
//												//�W���C���g������������
//												else if (pPiece[i].pos.y + pPiece[i].size.y / 3 < pJoint[j].pos.y)
//												{
//													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT) - pPiece[i].pos;
//
//													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT);
//
//													if (fourPieceCollision(pPiece[i], i))
//													{
//														PositionPlas(temp, pPiece[i].no);
//														pPiece[i].OldMovePos = pPiece[i].pos;
//														if (pFlag)
//														{
//															pPlayer->Position += temp;
//															pPlayer->oldpos = pPlayer->Position;
//
//														}
//														// �q�o�i�G�t�F�N�g
//														SetEffectSpark(pJoint[j].pos, 90.0f);
//														// �s�[�X�̃A�j���[�V����
//														StartPieceAnimation(pJoint[k].indexno);
//														StartPieceAnimation(pJoint[j].indexno);
//														//SetVolume(g_MatchPieceSoundNo, 0.5f);
//														PlaySound(g_MatchPieceSoundNo, 0);
//													}
//													else
//													{
//														Rotreturn(pPiece[i].no);
//														colFlag2 = true;
//														temp = pPiece[i].OldMovePos - pPiece[i].pos;
//														PositionPlas(temp, pPiece[i].no);
//
//														pPiece[i].pos = pPiece[i].OldMovePos;
//
//														if (pFlag)
//														{
//															pPlayer->Position = pPlayer->OneOldpos;
//														}
//
//													}
//
//												}
//
//												break;
//											}
//											break;
//										}
//									}
//
//								}
//							}
//						}
//
//
//					}
//					if (!colFlag2)
//					{
//
//						if (fourNomalPieceCollision(pPiece[i], i))
//						{
//
//						}
//						else
//						{
//							Rotreturn(pPiece[i].no);
//
//							colFlag2 = true;
//							D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].pos;
//							PositionPlas(temp, pPiece[i].no);
//							pPiece[i].pos = pPiece[i].OldMovePos;
//							pPiece[i].OldPos = pPiece[i].pos;
//							if (pFlag)
//							{
//								pPlayer->Position = pPlayer->OneOldpos;
//								pPlayer->oldpos = pPlayer->Position;
//							}
//
//						}
//
//
//						for (int m = 0; m < 3; m++)
//						{
//							if (!colFlag2)
//							{
//
//								for (int n = 0; n < 4; n++)
//								{
//
//									if (pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) - pSplitStage->size.y / 2 < pPiece[i].pos.y &&
//										pSplitStage->pos.y + SPLIT_SIZE - (m * SPLIT_SIZE) + pSplitStage->size.y / 2 > pPiece[i].pos.y &&
//										pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) - pSplitStage->size.x / 2 < pPiece[i].pos.x &&
//										pSplitStage->pos.x - SPLIT_SIZE - SPLIT_SIZE / 2 + (n * SPLIT_SIZE) + pSplitStage->size.x / 2 > pPiece[i].pos.x)
//									{
//										pPiece[i].pos = pSplitStage->Split34[n][m];
//
//										if (fourNomalPieceCollision(pPiece[i], i))
//										{
//											D3DXVECTOR2 temp = pPiece[i].pos - pPiece[i].OldPos;
//
//											PositionPlas(temp, pPiece[i].no);
//											if (pFlag)
//											{
//												pPlayer->Position += temp;
//												pPlayer->oldpos = pPlayer->Position;
//
//											}
//
//										}
//										else
//										{
//											colFlag2 = true;
//											D3DXVECTOR2 temp = pPiece[i].OldMovePos - pPiece[i].OldPos;
//											PositionPlas(temp, pPiece[i].no);
//											pPiece[i].pos = pPiece[i].OldMovePos;
//											Rotreturn(pPiece[i].no);
//											if (pFlag)
//											{
//												pPlayer->Position = pPlayer->OneOldpos;
//											}
//
//										}
//
//										break;
//									}
//								}
//							}
//						}
//
//					}
//				}
//
//			}
//		}
//	}
//
//}



//==========================
//�p�Y���s�[�X�����蔻��(�h�b�y���Q���K�[��)
//==========================
void PieceCollision()
{
	
	SplitStage* pSplitStage = GetSplitStage();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();

	Piece* pPiece = GetPiece();
	JOINT* pJoint = GetJoint();
	PLAYER* pPlayer = GetPlayer();
	DOPPELGANGER* pDoppel = GetDoppelganger();
	bool colFlag = false;//�������ē�������
	bool colFlag2 = false;//�������ē�������
	bool pFlag =false;
	bool dFlag = false;
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (pPiece[i].UseFlag)
		{
			if (pPiece[i].MoveEndFlag)	//�����I�������
			{
				if (!pPiece[i].InventoryFlag)
				{


					pPiece[i].MoveEndFlag = false;

					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pPlayer->Position.y &&
						pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pPlayer->Position.y &&
						pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pPlayer->Position.x &&
						pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pPlayer->Position.x &&
						pPiece[i].no == pPlayer->PieceIndex)
					{
						pFlag = true;
					}

					if (pPiece[i].pos.y - PUZZLE_HEIGHT / 2 < pDoppel->Position.y &&
						pPiece[i].pos.y + PUZZLE_HEIGHT / 2 > pDoppel->Position.y &&
						pPiece[i].pos.x - PUZZLE_WIDHT / 2 < pDoppel->Position.x &&
						pPiece[i].pos.x + PUZZLE_WIDHT / 2 > pDoppel->Position.x &&
						pPiece[i].no == pDoppel->PieceIndex &&
						pDoppel->UseFlag == true)
					{
						dFlag = true;
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
							pPlayer->oldpos = pPlayer->Position;

							//pPlayer->hp--;
						}
						if (dFlag)
						{
							pDoppel->Position = pDoppel->OneOldpos;
							pDoppel->oldpos = pDoppel->Position;
						}

						break;
					}


					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[i].no)	//�����I������s�[�X�̒��ɂ�������
						{
							for (int k = 0; k < JOINT_MAX; k++)
							{
								if (pJoint[k].useFlag)
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
													PositionPlas(temp, pPiece[i].no);

													if (fourPieceCollision(pPiece[i], i))
													{
														//PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;
														}
														if (dFlag)
														{
															pDoppel->Position += temp;
															pDoppel->oldpos = pDoppel->Position;
														}
														// �q�o�i�G�t�F�N�g
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// �s�[�X�̃A�j���[�V����
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
														//SetVolume(g_MatchPieceSoundNo, 0.5f);
														PlaySound(g_MatchPieceSoundNo, 0);
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
														if (dFlag)
														{
															pDoppel->Position = pDoppel->OneOldpos;
														}
													}
												}
												//�W���C���g������������
												else if (pPiece[i].pos.x - pPiece[i].size.x / 3 > pJoint[j].pos.x)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);
													PositionPlas(temp, pPiece[i].no);

													if (fourPieceCollision(pPiece[i], i))
													{

														//PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;
														}
														if (dFlag)
														{
															pDoppel->Position += temp;
															pDoppel->oldpos = pDoppel->Position;
														}
														pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x + PUZZLE_WIDHT, pPiece[pJoint[k].indexno].pos.y);
														// �q�o�i�G�t�F�N�g
														SetEffectSpark(pJoint[j].pos, 0.0f);
														// �s�[�X�̃A�j���[�V����
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
														//SetVolume(g_MatchPieceSoundNo, 0.5f);
														PlaySound(g_MatchPieceSoundNo, 0);
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
														if (dFlag)
														{
															pDoppel->Position = pDoppel->OneOldpos;
														}

													}
												}
												//�W���C���g���ゾ������
												else if (pPiece[i].pos.y - pPiece[i].size.y / 3 > pJoint[j].pos.y)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y + PUZZLE_HEIGHT);
													PositionPlas(temp, pPiece[i].no);

													if (fourPieceCollision(pPiece[i], i))
													{
														//PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;
														}
														if (dFlag)
														{
															pDoppel->Position += temp;
															pDoppel->oldpos = pDoppel->Position;
														}
														// �q�o�i�G�t�F�N�g
														SetEffectSpark(pJoint[j].pos, 90.0f);
														// �s�[�X�̃A�j���[�V����
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
														//SetVolume(g_MatchPieceSoundNo, 0.5f);
														PlaySound(g_MatchPieceSoundNo, 0);
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
														if (dFlag)
														{
															pDoppel->Position = pDoppel->OneOldpos;
														}

													}

												}
												//�W���C���g������������
												else if (pPiece[i].pos.y + pPiece[i].size.y / 3 < pJoint[j].pos.y)
												{
													D3DXVECTOR2 temp = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT) - pPiece[i].pos;

													pPiece[i].pos = D3DXVECTOR2(pPiece[pJoint[k].indexno].pos.x, pPiece[pJoint[k].indexno].pos.y - PUZZLE_HEIGHT);
													PositionPlas(temp, pPiece[i].no);

													if (fourPieceCollision(pPiece[i], i))
													{
														//PositionPlas(temp, pPiece[i].no);
														pPiece[i].OldMovePos = pPiece[i].pos;
														if (pFlag)
														{
															pPlayer->Position += temp;
															pPlayer->oldpos = pPlayer->Position;
														}
														if (dFlag)
														{
															pDoppel->Position += temp;
															pDoppel->oldpos = pDoppel->Position;
														}
														// �q�o�i�G�t�F�N�g
														SetEffectSpark(pJoint[j].pos, 90.0f);
														// �s�[�X�̃A�j���[�V����
														StartPieceAnimation(pJoint[k].indexno);
														StartPieceAnimation(pJoint[j].indexno);
														//SetVolume(g_MatchPieceSoundNo, 0.5f);
														PlaySound(g_MatchPieceSoundNo, 0);
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
														if (dFlag)
														{
															pDoppel->Position = pDoppel->OneOldpos;
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
								pPlayer->oldpos = pPlayer->Position;
							}
							if (dFlag)
							{
								pDoppel->Position = pDoppel->OneOldpos;
								pDoppel->oldpos = pDoppel->Position;
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
												pPlayer->oldpos = pPlayer->Position;

											}
											if (dFlag)
											{
												pDoppel->Position += temp;
												pDoppel->oldpos = pDoppel->Position;
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
											if (dFlag)
											{
												pDoppel->Position = pDoppel->OneOldpos;
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
				//if (pFlag) {

				//	MOUSE* pMouse = GetMouse();

				//	pPlayer->Position = pPuzzle[i].Position - pMouse->PlPos;
				//}
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
	KEY* pKey = GetKey();
	OPENKEY* pOpenKey = GetOpenKey();

	THORNBLOCK* pThornBlock = GetThornBlock();
	JUMPSTAND* pJumpStand = GetJumpStand();
	SpawnPoint* pSpawnPoint = GetSpawnPoint();
	SWITCH* pSwitch = GetSwitch();
	SWITCHWALL* pSwitchWall = GetSwitchWall();
	WARP* pWarp = GetWarp();
	BROKEN* pBroken = GetBroken();
	SHEERFLOORS* pSheerFloors = GetSheerFloors();
	START* pStart = GetStart();
	HIGH* pHigh = GetHigh();
	MOVEBLOCK* pMoveBlock = GetMoveBlock();
	FALLBLOCK* pFallBlock = GetFallBlock();
	ENEMY* pEnemy = GetEnemy();
	EXPLAIN* pExplain = GetExplain();
	STORYKEY* pStoryKey = GetStoryKey();
	LAMP* pLamp = GetLamp();
	LAMP_SWITCH* pLampSwitch = GetLampSwitch();
	SpawnPointD* pSpawnPointD = GetSpawnPointD();

	for (int i = 0; i < BLOCK_CHIP_MAX; i++)
	{
		if (pBlock[i].UseFlag)
		{

			if (pBlock[i].PieceIndex == pinNo)
			{

				pBlock[i].Position += num;

			}

		}

	}
	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (pBroken[i].UseFlag)
		{

			if (pBroken[i].index == pinNo)
			{

				pBroken[i].Postion += num;

			}

		}

	}
	for (int i = 0; i < HIGH_MAX; i++)
	{//�u���b�N������
		if (pHigh[i].UseFlag)
		{
			if (pHigh[i].index == pinNo)
			{
				pHigh[i].Postion += num;
			}

		}

	}

	for (int i = 0; i < SHEERFLOORS_NUM; i++)
	{//�u���b�N������
		if (pSheerFloors[i].use)
		{
			if (pSheerFloors[i].index == pinNo)
			{
				pSheerFloors[i].pos += num;
			}

		}

	}
	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (pMoveBlock[i].bUse)
		{
			if (pMoveBlock[i].NowPieceIndex == pinNo)
			{
				pMoveBlock[i].pos += num;
				pMoveBlock[i].oldpos = pMoveBlock[i].pos;
			}

		}

	}
	for (int i = 0; i < FALLBLOCK_MAX; i++)
	{
		if (pFallBlock[i].UseFlag)
		{
			if (pFallBlock[i].PieceIndex == pinNo)
			{
				pFallBlock[i].Position += num;
			}
		}
	}

	for (int i = 0; i < START_MAX; i++) {
		if (pStart[i].UseFlag) {
			if (pStart[i].PieceIndex == pinNo) {
				pStart[i].pos += num;
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
	for (int i = 0; i < KEY_MAX; i++) {
		if (pKey[i].UseFlag) {
			if (pKey[i].index == pinNo) {
				pKey[i].Position += num;
			}
		}
	}
	
	for (int i = 0; i < OPEN_KEY_MAX * STAGE_OPEN_KEY_MAX; i++) {
		if ((pOpenKey + i)->UseFlag) {
			if ((pOpenKey + i)->index == pinNo) {
				(pOpenKey + i)->Position += num;
			}
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
			if (pJumpStand[i].NowPieceIndex == pinNo)
			{
				pJumpStand[i].pos += num;
				pJumpStand[i].oldpos = pJumpStand[i].pos;
				pJumpStand[i].LookFlag = true;
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
	for (int i = 0; i < SWITCH_MAX; i++)
	{
		if (pSwitch[i].UseFlag)
		{
			if (pSwitch[i].PieceIndex == pinNo)
			{
				pSwitch[i].pos += num;
			}

		}
	}
	for (int i = 0; i < SWITCHWALL_MAX * SWITCHWALL_LIMIT; i++)
	{
		if (pSwitchWall[i].UseFlag)
		{
			if (pSwitchWall[i].PieceIndex == pinNo)
			{
				pSwitchWall[i].pos += num;
			}

		}
	}
	//���[�v
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (pWarp[i].UseFlag)
		{
			if (pWarp[i].PieceIndex == pinNo)
			{
				pWarp[i].Position += num;
			}

		}
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (pEnemy[i].UseFlag)
		{
			if (pEnemy[i].index == pinNo)
			{
				pEnemy[i].pos += num;
			}
		}

	}
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (pExplain[i].bUse) {
			if (pExplain[i].PieceIndex == pinNo) {
				pExplain[i].pos += num;
			}
		}
	}
	for (int i = 0; i < STORYKEY_MAX; i++) {
		if (pStoryKey[i].bUse) {
			if (pStoryKey[i].no == pinNo) {
				pStoryKey[i].pos += num;
			}
		}
	}
	for (int i = 0; i < LAMP_MAX; i++) {
		if (pLamp[i].UseFlag) {
			if (pLamp[i].PieceIndex == pinNo) {
				pLamp[i].pos += num;
			}
		}
	}
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (pLampSwitch[i].UseFlag) {
			if (pLampSwitch[i].PieceIndex == pinNo) {
				pLampSwitch[i].pos += num;
			}
		}
	}
	for (int i = 0; i < SPAWN_POINT_D_MAX; i++) {
		if (pSpawnPoint[i].UseFlag) {
			if (pSpawnPoint[i].PieceIndex == pinNo) {
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
					if (p.pos.y + PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)return false;

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
					if (p.pos.y - PUZZLE_HEIGHT == pPiece[i].pos.y && p.pos.x == pPiece[i].pos.x)	return false;

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

}

//--------------------------------------------
//�h�b�y���Q���K�[�̈ړ���Ƀs�[�X�����邩
//�����F���̃s�[�X�A�ړ��������s�[�X�̓Y�����A�ړ��������ꏊ
//----------------------------------------------
bool DoppelPieceOpen(Piece p, int index, DIRECSION direcsion)
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

					if (p.pos.x + PUZZLE_WIDHT == pPiece[i].pos.x && p.pos.y == pPiece[i].pos.y)	return false;

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

}
//--------------------------------------------
//4�����Ƀp�Y�������邩��������s�[�X�̏o�����肪�L���Ă��邩
//----------------------------------------------
bool fourPieceCollision(Piece piece, int index)
{
	JOINT* pJoint = GetJoint();
	Piece* pPiece = GetPiece();
	punum = -1;

	bool hitFlag;
	bool 	JointFlag = false;
	bool 	JointFlag2 = false;
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
				JointFlag2 = true;
				if (piece.pos.x + PIECE_SIZE / 3 < pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo ==pPiece[punum].no)
						{
							if (pPiece[punum].pos.x - PIECE_SIZE / 3 > pJoint[j].pos.x)
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
		if (!JointFlag&& JointFlag2)
		{
			return false;
		}


	}
	JointFlag = false;
	JointFlag2 = false;

	//�����J���Ă��Ȃ�������
	hitFlag = PieceOpen(piece, index, LEFT);

	if (!hitFlag)
	{
		//�p�Y���̃`�b�v�̍��ƉE���L���Ă��邩
		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				JointFlag2 = true;
				if (piece.pos.x - PIECE_SIZE / 3 > pJoint[i].pos.x)	//�W���C���g���s�[�X�̉E��������
				{

					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.x + PIECE_SIZE / 3 < pJoint[j].pos.x)
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
		if (!JointFlag&& JointFlag2)
		{
			return false;
		}

	}
	hitFlag = PieceOpen(piece, index, UP);
	JointFlag = false;
	JointFlag2 = false;


	if (!hitFlag)
	{	//�オ�J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y + PIECE_SIZE / 3 < pJoint[i].pos.y)	//�W���C���g���s�[�X�̏ゾ������
				{
					JointFlag2 = true;
					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{

							if (pPiece[punum].pos.y - PIECE_SIZE / 3 > pJoint[j].pos.y)	//��
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
		if (!JointFlag&& JointFlag2)
		{
			return false;


		}

	}

	hitFlag = PieceOpen(piece, index, DOWN);
	JointFlag = false;
	JointFlag2 = false;


	if (!hitFlag)
	{
		//�����J���Ă��Ȃ�������

		for (int i = 0; i < JOINT_MAX; i++)
		{
			if (pJoint[i].pieNo == piece.no)	//���̃s�[�X�̃W���C���g��������
			{
				if (piece.pos.y - PIECE_SIZE / 3 > pJoint[i].pos.y)	//�W���C���g���s�[�X�̉���������
				{
					JointFlag2 = true;
					for (int j = 0; j < JOINT_MAX; j++)
					{
						if (pJoint[j].pieNo == pPiece[punum].no)
						{
							if (pPiece[punum].pos.y + PIECE_SIZE / 3 < pJoint[j].pos.y)	//��
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
		if (!JointFlag&& JointFlag2)
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
				case DOWN:

					//piece�̏�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PIECE_SIZE - (PIECE_SIZE / 2) < pPiece[i].pos.y &&
						piece.pos.y - PIECE_SIZE + (PIECE_SIZE / 2) > pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE / 3 >= pPiece[i].pos.x)
					{

						punum = i;
						return false;
					}

					break;
				case UP:
					//if (piece.pos.y + PUZZLE_SIZE == pPiece[i].pos.y)	return false;
										//piece�̉��ɕʂ̃p�Y�������邩

					if (piece.pos.y + PIECE_SIZE - PIECE_SIZE / 2 < pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE + PIECE_SIZE / 2 > pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE / 3 <= pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE / 3 >= pPiece[i].pos.x)
					{
						punum = i;
						return false;
					}

					break;
				case LEFT:
					//if (piece.pos.x - PUZZLE_SIZE == pPiece[i].pos.x)	return false;
										//piece�̍��ɕʂ̃p�Y�������邩

					if (piece.pos.y - PIECE_SIZE / 3 <= pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE / 3 >= pPiece[i].pos.y &&
						piece.pos.x - PIECE_SIZE - PIECE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x - PIECE_SIZE + PIECE_SIZE / 3 > pPiece[i].pos.x)
					{
						punum = i;

						return false;
					}

					break;
				case RIGHT:
					//if (piece.pos.x + PUZZLE_SIZE == pPiece[i].pos.x)	return false;
					//piece�̉E�ɕʂ̃p�Y�������邩
					if (piece.pos.y - PIECE_SIZE / 3 < pPiece[i].pos.y &&
						piece.pos.y + PIECE_SIZE / 3 > pPiece[i].pos.y &&
						piece.pos.x + PIECE_SIZE - PIECE_SIZE / 3 < pPiece[i].pos.x &&
						piece.pos.x + PIECE_SIZE + PIECE_SIZE / 3 > pPiece[i].pos.x)
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
				if (pJoint[j].pos.y > piece.pos.y + piece.size.y / 3)
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

				if (pPiece[punum].pos.y - pPiece[punum].size.y / 3 > pJoint[i].pos.y)	//��
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
				if (pJoint[j].pos.y < piece.pos.y - piece.size.y / 3)
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
				if (pPiece[punum].pos.y + pPiece[punum].size.y / 3 < pJoint[i].pos.y)	//��
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
	CURSOR* pCursor = GetCurso();
	for (int i = 0; i < pCursor->RotIndex; i++)
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

	D3DXVECTOR2 up = pSprit->Split34[0][0];
	D3DXVECTOR2 down = pSprit->Split34[0][2];
	D3DXVECTOR2 right = pSprit->Split34[3][0];
	D3DXVECTOR2 left = pSprit->Split34[0][1];

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


	if (x < left.x - 180 / 2);
	{
		if (p.pos.x < left.x - 180 / 2)
		{
			return false;

		}
	}

	return true;
}


