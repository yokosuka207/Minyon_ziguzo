//=============================================================================
//
//�h�b�y���Q���K�[(���v���C���[)����  �����͓G����Ȃ��I�H
//
//�����/�e�n��@
//=============================================================================
#pragma once

#include "doppelganger.h"

#include "player.h"
#include "main.h"
//#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"


#include "block.h"
#include "thorn_block.h"
#include "broken.h"
#include "bullet.h"

#include "scene.h"
//#include "pause.h"
//#include "piece.h"
#include"puzzlecip.h"
#include"game.h"
#include"puzzle.h"
#include"collision.h"
#include"mouse.h"
#include"jump_stand.h"		//�W�����v��
#include"MapChip.h"
#include"thorn_block.h"
#include "time.h"
//#include "OpenKey.h"
//#include "Key.h"
#include "warp.h"
#include "fallblock.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "MoveBlock.h"
#include "goal_key.h"
//#include "pause.h"

#include"spawnpoint_d.h"

#include "fade.h"
#include "result.h"








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
#include "EffectLight.h"
#include "enemy.h"			//�G�l�~�[

#include "JumpStandExplain.h"		

#include "EffectSpark.h"	// �q�o�i�G�t�F�N�g
#include"switch.h"	//�X�C�b�`
#include"SwitchWall.h"//switch�̕�
#include"cursor.h"

#include"sound.h"
#include"bullet.h"

#include "sound.h"
//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static DOPPELGANGER g_Doppel;
static char* g_TextureNameBroken = (char*)"data\\texture\\�h�b�y���Q���K�[.png";

static Time		g_Time;

bool g_bHave = false;
static bool oneFlag = false;

static D3DXVECTOR2 InitPos;

//���ʉ�
//����u���b�N
static int g_BrokenSoundNo = 0;
static char g_BrokenSoundName[] = "data\\SoundData\\SE\\�ؔ�������(������).wav";
//�X�C�b�`
static int g_SwitchSoundNo = 0;
static char g_SwitchSoundName[] = "data\\SoundData\\SE\\�X�C�b�`(�j�R�j�E�R�����Y).wav";
//�X���X�C�b�`
static int g_LampSwitchSoundNo = 0;
static char g_LampSwitchSoundName[] = "data\\SoundData\\SE\\�X�C�b�`(�j�R�j�E�R�����Y).wav";
//���[�v
static int g_WarpSoundNo = 0;
static char g_WarpSoundName[] = "data\\SoundData\\SE\\���[�v(�������ʉ��ŗV�ڂ��I).wav";
//�����Ƃ�������鏰
static int g_HighSoundNo = 0;
static char g_HighSoundName[] = "data\\SoundData\\SE\\�^�C�v���C�^�[.wav";
//�낤����
static int g_CandleSoundNo = 0;
static char g_CandleSoundName[] = "data\\SoundData\\SE\\�낤����(���ʉ����{).wav";

//=============================================================================
//����������
//=============================================================================
HRESULT InitDoppelganger()
{
	oneFlag = false;
	InitPos = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Piece* pPiece = GetPiece();

	g_Doppel.Position = D3DXVECTOR2(pPiece->pos.x - 30.0f, pPiece->pos.y);
	g_Doppel.OneOldpos = g_Doppel.oldpos = g_Doppel.Position;
	g_Doppel.sp = D3DXVECTOR2(0.0f, -8.0f);
	g_Doppel.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Doppel.Drawsize = D3DXVECTOR2(33.0f, 33.0f);
	g_Doppel.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Doppel.rot = 180.0f;
	g_Doppel.UseFlag = false;
	g_Doppel.jump = false;
	//g_Doppel.getjump = false;
	//g_Doppel.GetJumpStand = false;		//�W�����v��p
	g_Doppel.fall = false;
	//g_Doppel.getfall = false;
	//g_Doppel.WarpFlag = false;
	g_Doppel.isGround = true;
	g_Doppel.isSheerFloors = false;
	g_Doppel.isSheerFloorsUse = false;
	//g_Doppel.isHigh = false;
	g_Doppel.isMoveBlock = false;
	g_Doppel.texno = LoadTexture(g_TextureNameBroken);

	g_Doppel.PaternNo = 0;//�p�^�[���ԍ�
	g_Doppel.uv_w = PLAYER_UV_W;//���T�C�Y
	g_Doppel.uv_h = PLAYER_UV_H;//�c�T�C�Y
	g_Doppel.NumPatern = 4;//������

	//g_Doppel.hp = PLAYER_HP;
	g_Doppel.frame = 0;
	g_Doppel.CoolTime = PLAYER_COOLTIME;
	g_Doppel.PieceIndex = -1;

	g_Doppel.LightFrame = 0;

	g_Doppel.hp = 3;

	for (int i = 0; i < LAMP_SWITCH_MAX; i++)
	{
		g_Doppel.LampSwitchFlag[i] = true;
	}

	g_BrokenSoundNo = LoadSound(g_BrokenSoundName);
	g_SwitchSoundNo = LoadSound(g_SwitchSoundName);
	g_LampSwitchSoundNo = LoadSound(g_LampSwitchSoundName);
	g_WarpSoundNo = LoadSound(g_WarpSoundName);
	g_HighSoundNo = LoadSound(g_HighSoundName);
	g_CandleSoundNo = LoadSound(g_CandleSoundName);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitDoppelganger()
{
	StopSound(g_BrokenSoundNo);
	StopSound(g_SwitchSoundNo);
	StopSound(g_LampSwitchSoundNo);
	StopSound(g_WarpSoundNo);
	StopSound(g_HighSoundNo);
	StopSound(g_CandleSoundNo);
}

//=============================================================================
//�X�V����
//=============================================================================


void UpdateDoppelganger()
{	
	MOUSE* pMouse = GetMouse();
	CURSOR* pCursor = GetCurso();
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {		// GamePad B
		if (!g_bHave) {
			g_bHave = true;
		}
		else {
			g_bHave = false;
		}
	}

	if (Mouse_IsLeftRelease()) {		// moues ��
		//g_bHave = false;
	}

	if (!Mouse_IsLeftDown() &&			// mouse ��
		!pCursor->bHave)
	{

		if (g_Doppel.UseFlag == true)
		{
			//�ړ�
			if (GetThumbLeftX(0) > 0.3f ||					// GamePad	�E�X�e�B�b�N	�E
				Keyboard_IsKeyDown(KK_D))				// Keyboard	D
			{//������Ă���Ƃ��̏���
				g_Doppel.sp.x = -1.3f;
				g_Doppel.PaternNo += 0.25f;

				// ������ς���
				g_Doppel.dir = DOPPELGANGER_DIRECTION::RIGHT;
				g_Doppel.uv_w = -DOPPELGANGER_UV_W;
			}
			else if (GetThumbLeftX(0) < -0.3f ||			// GamePad	�E�X�e�B�b�N	��
				Keyboard_IsKeyDown(KK_A))				// Keyboard	A
			{//������Ă���Ƃ��̏���
				g_Doppel.sp.x = 1.3f;
				g_Doppel.PaternNo -= 0.25f;

				// ������ς���
				g_Doppel.dir = DOPPELGANGER_DIRECTION::LEFT;
				g_Doppel.uv_w = DOPPELGANGER_UV_W;
			}
			else
			{
				g_Doppel.sp.x = 0;
			}
			// �A�j���[�V�����p�^�[���ԍ���0�`15�͈͓̔��ɂ���
			if (g_Doppel.PaternNo >= 15) { g_Doppel.PaternNo -= 15; }
			if (g_Doppel.PaternNo < 0) { g_Doppel.PaternNo += 15; }
			//============================================================
			//	����
			//============================================================
			/*if (!g_Doppel.SoundRightFlag) {
				if (g_Doppel.PaternNo == 9.0f) {
					SetVolume(g_DoppelRightSoundNo, 0.5f);
					PlaySound(g_DoppelRightSoundNo, 0);
					g_Doppel.SoundRightFlag = true;
				}
			}
			else {
				if (g_Doppel.PaternNo != 9.0f) {
					g_Doppel.SoundRightFlag = false;
				}
			}
			if (!g_Doppel.SoundLeftFlag) {
				if (g_Doppel.PaternNo == 1.0f) {
					SetVolume(g_DoppelLeftSoundNo, 0.5f);
					PlaySound(g_DoppelLeftSoundNo, 0);
					g_Doppel.SoundLeftFlag = true;
				}
			}
			else {
				if (g_Doppel.PaternNo != 1.0f) {
					g_Doppel.SoundLeftFlag = false;
				}
			}*/
			


			//----------------
			//�W�����v��̏ꍇ
			//----------------
			JUMPSTAND* p_JumpStand = GetJumpStand();

			for (int i = 0; i < JUMPSTAND_MAX; i++) {
				if (p_JumpStand[i].UseJumpStand) {
					if (IsButtonPressed(0, XINPUT_GAMEPAD_B) ||					// GamePad	B
						Keyboard_IsKeyDown(KK_LEFTCONTROL) ||					// Keyboard	Ctrl�@��
						Keyboard_IsKeyDown(KK_C))								// Keyboard	C
					{
						if (CollisionBB(g_Doppel.Position, p_JumpStand[i].pos, g_Doppel.size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
							p_JumpStand[i].GetJumpStand = true;
						}
					}
					else
					{
						p_JumpStand[i].GetJumpStand = false;
					}
				}
			}

			//-------------
			//������̏ꍇ
			//-------------
			MOVEBLOCK* pMoveBlock = GetMoveBlock();

			for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
				if (pMoveBlock[i].bUse) {
					if (IsButtonPressed(0, XINPUT_GAMEPAD_B) ||					// GamePad	B
						Keyboard_IsKeyDown(KK_LEFTCONTROL) ||					// Keyboard	Ctrl ��
						Keyboard_IsKeyDown(KK_C))								// Keyboard	C
					{
						if (CollisionBB(g_Doppel.Position, pMoveBlock[i].pos, g_Doppel.size, pMoveBlock[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
							pMoveBlock[i].GetMoveBlock = true;
						}
					}
					else
					{
						pMoveBlock[i].GetMoveBlock = false;
					}
				}
			}

			//-------------------
			//��{�u���b�N�̏ꍇ
			//-------------------
			BLOCK* block = GetChipBlock();
			SpawnPointD* pSpawnPointD = GetSpawnPointD();
			for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
				if (block[i].UseFlag)
				{
					// �h�b�y���Q���K�[�̉��Ƀu���b�N����������
					if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
						(g_Doppel.Position.y + g_Doppel.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
						(g_Doppel.Position.x + g_Doppel.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
						(g_Doppel.Position.x - g_Doppel.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
					{	// ���n���ɂ���
						if (!g_Doppel.isGround) {
							g_Doppel.sp.y = 0.0f;
							g_Doppel.isGround = true;
							//g_Doppel.PieceIndex = block[i].PieceIndex;
							break;
						}
					}
					else {
						g_Doppel.isGround = false;
					}
				}
			}

			//---------------
			//�����鏰�̏ꍇ
			//---------------

			SHEERFLOORS* pSheerFloors = GetSheerFloors();
			for (int i = 0; i < SHEERFLOORS_NUM; i++)
			{
				if (pSheerFloors[i].use)
				{
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Doppel.size.x / 2;
					}
					//�h�b�y���Q���K�[�E�E�u���b�N��
					if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
						g_Doppel.Position.y - g_Doppel.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Doppel.size.x / 2;
					}

					//�h�b�y���Q���K�[��E�u���b�N��,���n����
					if (!GetThumbLeftY(0) < -0.3f ||		// GamePad	���X�e�B�b�N	��
						!Keyboard_IsKeyDown(KK_S))		// Keyboard S
					{
						if (pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
							pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
							pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2 &&
							pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 <= g_Doppel.oldpos.y - g_Doppel.size.y / 2)
						{
							//g_Doppel.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Doppel.size.y / 2);
							//g_Doppel.sp.y = 0.0f;
							for (int i = 0; i < JUMPSTAND_MAX; i++)
							{
								p_JumpStand[i].JumpStandFlag = false;

							}
							g_Doppel.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 + g_Doppel.size.y / 2;
							g_Doppel.jump = false;
							g_Doppel.sp.y = -0.3f;

							g_Doppel.fall = false;
							if (!g_Doppel.isSheerFloors) {
								//g_Doppel.sp.y = 0.0f;
								g_Doppel.isSheerFloors = true;

							}
							else {
								g_Doppel.sp.y = 0.0f;

								g_Doppel.isSheerFloors = false;
							}



						}

						//�h�b�y���Q���K�[���E�u���b�N��,��������
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
						{

						}
					}
				}

			}



			if (g_Doppel.sp.x == 0)
			{
				g_Doppel.PaternNo = 17;

				if (g_Doppel.uv_w > 0)
				{
					g_Doppel.PaternNo = 18;
				}
			}
			if (g_Doppel.sp.y != 0 && !g_Doppel.isFallBlock)
			{
				g_Doppel.PaternNo = 16;
				if (g_Doppel.uv_w > 0)
				{
					g_Doppel.PaternNo = 19;
				}

			}

				// �X�P�X�P�u���b�N���~���
			if (GetThumbLeftY(0) < -0.3f ||			// GamePad	���X�e�B�b�N	��
				Keyboard_IsKeyDown(KK_S))		// Keyboard	S
			{
				g_Doppel.isSheerFloors = false;
			}

			// �W�����v
			if ((g_Doppel.isGround || g_Doppel.isSheerFloors || g_Doppel.isHigh || g_Doppel.isMoveBlock || g_Doppel.isFallBlock || g_Doppel.isBrokenBlock) && g_Doppel.sp.y <= 0 &&
				(Keyboard_IsKeyDown(KK_SPACE) || IsButtonPressed(0, XINPUT_GAMEPAD_A)))
			{

				g_Doppel.sp.y = 2.8f;			// �X�s�[�h��y���}�C�i�X�ɂ���
				//SetVolume(g_DoppelRightSoundNo, 0.5f);
				//PlaySound(g_DoppelRightSoundNo, 0);


				if (g_Doppel.isGround) {
					g_Doppel.isGround = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Doppel.isSheerFloors) {
					g_Doppel.isSheerFloors = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Doppel.isHigh) {
					g_Doppel.isHigh = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Doppel.isMoveBlock) {
					g_Doppel.isMoveBlock = false;
				}
				if (g_Doppel.isFallBlock) {
					g_Doppel.isFallBlock = false;

				}if (g_Doppel.isBrokenBlock) {
					g_Doppel.isBrokenBlock = false;
				}
			}

			// ��
			if (!g_Doppel.isGround && !g_Doppel.isHigh && !g_Doppel.isSheerFloors && !g_Doppel.isMoveBlock && !g_Doppel.isFallBlock && !g_Doppel.isBrokenBlock) {
				g_Doppel.sp.y -= 0.1f;			// �X�s�[�h��y�𑝂₷
			}

			//���f
			g_Doppel.oldpos = g_Doppel.Position;
			g_Doppel.Position += g_Doppel.sp;








			//�h�b�y���Q���K�[�E���[�v �����蔻�� collision.cpp�ֈړ�

			//{
			//	//�h�b�y���Q���K�[�ƃp�Y���̉�ʊO����
			//	Piece* pPiece = GetPiece();

			//	for (int i = 0; i < PUZZLE_MAX; i++)
			//	{
			//		if (pPiece[i].UseFlag)
			//		{
			//			bool hitflag = CollisionBB(g_Doppel.Position, pPiece[i].pos, g_Doppel.size, pPiece[i].size);

			//			if (hitflag)
			//			{
			//				if (g_Doppel.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
			//				{
			//					bool hitflag2 = DoppelPieceOpen(pPiece[i], i, DOWN);

			//					if (!hitflag2)
			//					{
			//						g_Doppel.sp.y -= 0.2f;//����
			//					}
			//					else
			//					{//���ɉ����Ȃ����S����ꍇ
			//						for (int i = 0; i < SPAWN_POINT_D_MAX; i++)
			//						{
			//							if (pSpawnPointD[i].UseFlag)
			//							{
			//								if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex)
			//								{
			//									g_Doppel.Position = pSpawnPointD[i].Position;
			//									/////////////////////////////////////////////////////g_Doppel.hp--;
			//								}
			//							}
			//						}
			//					}
			//				}
			//				else if (g_Doppel.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
			//				{

			//					bool hitflag2 = DoppelPieceOpen(pPiece[i], i, RIGHT);

			//					if (!hitflag2)
			//					{
			//						//g_Doppel.sp.y += 0.2;//����
			//					}
			//					else
			//					{
			//						g_Doppel.Position.x = g_Doppel.oldpos.x;
			//					}


			//				}
			//				else if (g_Doppel.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
			//				{
			//					bool hitflag2 = DoppelPieceOpen(pPiece[i], i, LEFT);

			//					if (!hitflag2)
			//					{
			//						//g_Doppel.sp.y += 0.2;//����
			//					}
			//					else
			//					{
			//						g_Doppel.Position.x = g_Doppel.oldpos.x;
			//					}


			//				}
			//				else if (g_Doppel.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
			//				{
			//					bool hitflag2 = DoppelPieceOpen(pPiece[i], i, UP);

			//					if (!hitflag2)
			//					{
			//						//g_Doppel.sp.y += 0.2;//����
			//					}
			//					else
			//					{

			//						g_Doppel.fall = true;
			//						//g_Doppel.sp.y = 0;
			//						//g_Doppel.getfall = true;
			//						g_Doppel.frame = 50;
			//						//g_Doppel.sp.y += 0.2;//����
			//					}

			//				}
			//			}
			//		}


			//	}


			//}

			//�h�b�y���Q���K�[�ƃp�Y���̉�ʊO����
			Piece* pPiece = GetPiece();
			bool SpawnFlag = false;
			bool SpawnFlag2 = false;
			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				if (pPiece[i].UseFlag)
				{
					if (pPiece[i].no == g_Doppel.PieceIndex)
					{


						bool hitflag = CollisionBB(g_Doppel.Position, pPiece[i].pos, g_Doppel.size, pPiece[i].size);

						if (hitflag)
						{
							if (g_Doppel.Position.y <= pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, DOWN);

								if (!hitflag2)
								{
									//g_Doppel.sp.y -= 0.2f;//����
								}
								else
								{//���ɉ����Ȃ����S����ꍇ
									SpawnFlag2 = true;
									if (pSpawnPointD[i].UseFlag)
									{
										if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex)
										{
											SpawnFlag = true;
											g_Doppel.Position = pSpawnPointD[i].Position;
											g_Doppel.oldpos = g_Doppel.Position;

										}


									}


								}
							}
							else if (g_Doppel.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
							{

								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, RIGHT);

								if (!hitflag2)
								{
									//g_Doppel.sp.y += 0.2;//����
								}
								else
								{
									g_Doppel.Position.x = g_Doppel.oldpos.x;
								}


							}
							else if (g_Doppel.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, LEFT);

								if (!hitflag2)
								{
									//g_Doppel.sp.y += 0.2;//����
								}
								else
								{
									g_Doppel.Position.x = g_Doppel.oldpos.x;
								}


							}
							else if (g_Doppel.Position.y > pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, UP);

								if (!hitflag2)
								{
									//g_Doppel.sp.y += 0.2;//����
								}
								else
								{

									//g_Doppel.sp.y += 0.2;//����
								}

							}
						}
					}
				}


			}
			if (!SpawnFlag && SpawnFlag2)
			{
				g_Doppel.Position = D3DXVECTOR2(pPiece[7].pos.x + 60.0f, pPiece[7].pos.y + 3.0f);
				g_Doppel.oldpos = g_Doppel.Position;
				g_Doppel.sp.y = 0.0f;
				
			}


		

	


	PLAYER* pPlayer = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
//	SpawnPointD* pSpawnPointD = GetSpawnPointD();

	WARP* pWarp = GetWarp();

	BLOCK* pBlock = GetBlock();
	BLOCK* pChipblock = GetChipBlock();
//	MOVEBLOCK* pMoveBlock = GetMoveBlock();
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

	RESULT* pResult = GetResult();

//	Piece* pPiece = GetPiece();
	BULLET* pBullet = GetBullet();
	CURSOR* pCursor = GetCurso();



	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		if (pSwitchWall[i].UseFlag) {
			//�v���[���[�ƕǂ̔���
			//�ǂ̍��ƃh�b�y���Q���K�[�̉E
			if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 >= g_Doppel.oldpos.x + g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
				pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2)
			{
				g_Doppel.Position.x = g_Doppel.oldpos.x;
			}
			//�ǂ̉E�ƃh�b�y���Q���K�[�̍�
			if (pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 <= g_Doppel.oldpos.x - g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
				pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2)
			{
				g_Doppel.Position.x = g_Doppel.oldpos.x;
			}
			//�ǂ́��ƃh�b�y���Q���K�[�̏�
			if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 < g_Doppel.Position.y - g_Doppel.size.y / 2 &&
				pSwitchWall[i].pos.y - pSwitchWall[i].size.y / 2 >= g_Doppel.oldpos.y - g_Doppel.size.y / 2)
			{
				g_Doppel.Position = g_Doppel.oldpos;
			}
			//�ǂ́��ƃh�b�y���Q���K�[�́�
			if (pSwitchWall[i].pos.x - pSwitchWall[i].size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.x + pSwitchWall[i].size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
				pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 > g_Doppel.Position.y + g_Doppel.size.y / 2 &&
				pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 <= g_Doppel.oldpos.y + g_Doppel.size.y / 2)
			{
				g_Doppel.Position.y = pSwitchWall[i].pos.y + pSwitchWall[i].size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
				g_Doppel.jump = false;
				g_Doppel.fall = false;
				g_Doppel.WarpFlag = false;
				g_Doppel.sp.y = 0;
				g_Doppel.frame = 0;
			}

			//�ǂ�jumpstand�̔���
			for (int j = 0; j < JUMPSTAND_MAX; j++) {
				if (CollisionBB(pSwitchWall[i].pos, pJumpStand[j].pos, pSwitchWall[i].size, pJumpStand[j].size)) {
					pJumpStand[j].pos = pJumpStand[j].oldpos;
				}
			}
			//�ǂƓ����u���b�N�̔���
			for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
				if (CollisionBB(pSwitchWall[i].pos, pMoveBlock[j].pos, pSwitchWall[i].size, pMoveBlock[j].size)) {
					pMoveBlock[j].pos = pMoveBlock[j].oldpos;
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
		//�h�b�y���Q���K�[�ƃg�Q�u���b�N�̔���(�h�b�y���Q���K�[���g�Q��)
		for (int i = 0; i < THORN_BLOCK_MAX; i++) {
			if (pThornBlock[i].UseFlag) {
				if (CollisionBB(pThornBlock[i].Postion, g_Doppel.Position, pThornBlock[i].Size, g_Doppel.size)) {

					/////////////////////////////////////////////////////g_Doppel.hp--;
					//SetVolume(g_CandleSoundNo, 0.5f);
					///////////////////////////////////////////////////////////////PlaySound(g_CandleSoundNo, 0);
					for (int i = 0; i < SPAWN_POINT_D_MAX; i++) {//���X�|��������HP�����葱���Ă���
						if (pSpawnPointD[i].UseFlag) {
							if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex) {
								g_Doppel.Position = D3DXVECTOR2(pPiece[7].pos.x + 60.0f, pPiece[7].pos.y + 3.0f);
							}
						}
					}
				}
			}
		}
	}
	//�h�b�y���Q���K�[��������
	if (g_Doppel.Position.y - g_Doppel.size.y < -SCREEN_HEIGHT / 2) {
		/////////////////////////////////////////////////////////////g_Doppel.hp--;
		//SetVolume(g_CandleSoundNo, 0.5f);
		///////////////////////////////////////////////////////////////PlaySound(g_CandleSoundNo, 0);
		for (int i = 0; i < SPAWN_POINT_D_MAX; i++) {//���X�|��������HP�����葱���Ă���
			if (pSpawnPointD[i].UseFlag) {
				if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex) {
					g_Doppel.Position = D3DXVECTOR2(pPiece[7].pos.x + 60.0f, pPiece[7].pos.y + 3.0f);
				}
			}
		}
	}
	////�h�b�y���Q���K�[�c�@�[��
	//if (g_Doppel.hp <= 0) {
	//	g_Doppel.UseFlag = false;
	//	SetResultType(LOSE);
	//	StartFade(FADE::FADE_ALPHA_OUT);
	//	pTime->EndTime();
	//	pTimeParam->EndFlag = true;
	//}///////////////////////////////////////////////////////////////////////////////////

	//========================================================================
	//�h�b�y���Q���K�[�E�`�b�v�u���b�N�@�����蔻��(DoppelGanger��ChipBlock�̓����蔻��)
	//=========================================================================
	for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
		if ((pChipblock + i)->UseFlag) {
			//�h�b�y���Q���K�[���E�u���b�N�E
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 - g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[�E�E�u���b�N��
			if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 + g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[��E�u���b�N��,���n����
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 &&
				g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2)
			{
				g_Doppel.PieceIndex = pChipblock[i].PieceIndex;

				g_Doppel.Position.y = (pChipblock + i)->Position.y + (pChipblock + i)->Size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
				g_Doppel.jump = false;
				g_Doppel.fall = false;
				g_Doppel.WarpFlag = false;
				g_Doppel.sp.y = 0;
				g_Doppel.frame = 0;
			}
			//�h�b�y���Q���K�[���E�u���b�N��,��������
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pChipblock + i)->Position.x - (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pChipblock + i)->Position.x + (pChipblock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 &&
				g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2)
			{
				g_Doppel.Position.y = (pChipblock + i)->Position.y - (pChipblock + i)->Size.y / 2 - g_Doppel.size.y / 2 - 0.02f;
				g_Doppel.sp.y = 0;
				for (int i = 0; i < JUMPSTAND_MAX; i++)
				{
					pJumpStand[i].JumpStandFlag = false;

				}
				g_Doppel.isHigh = false;

				g_Doppel.fall = true;
				g_Doppel.getfall = true;
				g_Doppel.frame = 50;
			}
		}
	}



	//========================================================================
	//�h�b�y���Q���K�[�E���[�v�@�����蔻��(DoppelGanger��Warp�̓����蔻��)
	//========================================================================	
	g_Doppel.CoolTime--;
	if (g_Doppel.CoolTime < 0) {
		g_Doppel.CoolTime = 0;
		//�h�b�y���Q���K�[�E���[�v�@�����蔻��
		for (int i = 0; i < WARP_MAX; i++) {
			if ((pWarp + i)->UseFlag) {
				if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pWarp + i)->Position.x - (pWarp + i)->Size.x / 2 &&
					g_Doppel.Position.x - g_Doppel.size.x / 2 < (pWarp + i)->Position.x + (pWarp + i)->Size.x / 2 &&
					g_Doppel.Position.y + g_Doppel.size.y / 2 > (pWarp + i)->Position.y - (pWarp + i)->Size.y / 2 &&
					g_Doppel.Position.y - g_Doppel.size.y / 2 < (pWarp + i)->Position.y + (pWarp + i)->Size.y / 2)
				{
					if (i % 2 == 0)
					{
						if (pWarp[i + 1].UseFlag)
						{
							if (!pWarp[i + 1].InventoryFlag)
							{
								if (!g_Doppel.WarpFlag)
								{
									g_Doppel.Position = (pWarp + i + 1)->Position;
									g_Doppel.CoolTime = PLAYER_COOLTIME;
									SetVolume(g_WarpSoundNo, 0.5f);
									PlaySound(g_WarpSoundNo, 0);
									pSwitch[i].NotPressed = false;
									g_Doppel.WarpFlag = true;
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
								if (!g_Doppel.WarpFlag)
								{
									g_Doppel.Position = (pWarp + i - 1)->Position;
									g_Doppel.CoolTime = PLAYER_COOLTIME;
									//SetVolume(g_SwitchSoundNo, 0.5f);
									PlaySound(g_WarpSoundNo, 0); 
									g_Doppel.WarpFlag = true;

								}
							}
						}
					}
				}
			}
		}
	}
	
	//========================================================================
	//�h�b�y���Q���K�[�E����u���b�N�@�����蔻��(DoppelGanger��BrokenBlock�̓����蔻��)
	//=========================================================================
	for (int i = 0; i < BROKEN_MAX; i++) {
		if ((pBroken + i)->UseFlag) {
			//�h�b�y���Q���K�[���E����u���b�N�E
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[�E�E����u���b�N��
			if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[��E����u���b�N��
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
				g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
			{
				g_Doppel.Position.y = (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 + g_Doppel.size.y / 2;
				g_Doppel.jump = false;
				g_Doppel.fall = false;
				g_Doppel.frame = 0;
			}
			//�h�b�y���Q���K�[���E����u���b�N��,����
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
				g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
			{
				(pBroken + i)->breakFlag = true;
				//SetVolume(g_SwitchSoundNo, 0.5f);
				PlaySound(g_BrokenSoundNo, 0);
				(pBroken + i)->UseFlag = false;
				g_Doppel.fall = true;
				g_Doppel.getfall = true;
				g_Doppel.frame = 50;
			}
		}
	}
	//====================================================================
	//�h�b�y���Q���K�[�Ɠ����u���b�N�̓����蔻��(DoppelGanger��MoveBlock�̓����蔻��)
	//====================================================================
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		if (pMoveBlock[i].bUse) {
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = g_Doppel.sp;
				pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
			}
			if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = g_Doppel.sp;
				pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
			}
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
				g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
			{
				pMoveBlock[i].sp = g_Doppel.sp;
				pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;

			}
			//�h�b�y���Q���K�[���E�u���b�N��,��������
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
				g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
			{
				g_Doppel.Position.y = pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 + g_Doppel.size.y / 2;
				pMoveBlock[i].MoveFlag = true;
				// ���n���ɂ���
				if (!g_Doppel.isMoveBlock) {
					g_Doppel.sp.y = 0.0f;
					g_Doppel.isMoveBlock = true;
					break;
				}

			}
			else {
				pMoveBlock[i].MoveFlag = false;

				g_Doppel.isMoveBlock = false;
			}


		}
	}
	//====================================================================
	//�h�b�y���Q���K�[�Ɨ�����u���b�N�̓����蔻��(DoppelGanger��FallBlock�̓����蔻��)
	//====================================================================
	bool FallFlag = false;
	for (int i = 0; i < FALLBLOCK_MAX; i++) {
		if ((pFallBlock + i)->UseFlag) {
			//�h�b�y���Q���K�[���E�u���b�N�E����
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 - g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[�E�E������u���b�N��
			if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 + g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[��E������u���b�N��
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 &&
				g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2)
			{
				g_Doppel.Position.y = (pFallBlock + i)->Position.y - (pFallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;

			}
			//�h�b�y���Q���K�[���E������u���b�N
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pFallBlock + i)->Position.x - (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pFallBlock + i)->Position.x + (pFallBlock + i)->Size.x / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 &&
				g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2)
			{
				g_Doppel.Position.y = (pFallBlock + i)->Position.y + (pFallBlock + i)->Size.y / 2 + g_Doppel.size.y / 2;
				g_Doppel.getfall = false;
				g_Doppel.jump = false;
				g_Doppel.fall = false;
				g_Doppel.frame = 50;
				g_Doppel.isFallBlock = true;
				(pFallBlock + i)->oldpos = (pFallBlock + i)->Position;
				(pFallBlock + i)->Position.y -= 3.0f;
				FallFlag = true;
			}
			else if (!FallFlag)
			{
				g_Doppel.isFallBlock = false;
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
	//�h�b�y���Q���K�[�ƍ��������u���b�N�̓����蔻��(DoppelGanger��High�̓����蔻��)
	//====================================================================
	for (int i = 0; i < HIGH_MAX; i++) {
		if ((pHigh + i)->UseFlag) {
			//�h�b�y���Q���K�[���E����������u���b�N�E
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[�E�E����������u���b�N��
			if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				g_Doppel.Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + g_Doppel.size.x / 2;
			}
			//�h�b�y���Q���K�[��E����������u���b�N��
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
				g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
			{
				if (g_Doppel.sp.y <= -5.0f) {
					//g_Doppel.isHigh = false;
					(pHigh + i)->UseFlag = false;
					pHigh[i].breakFlag = true;
					//SetVolume(g_HighSoundNo, 0.5f);
					//PlaySound(g_HighSoundNo, 0);
					g_Doppel.frame = 50;
				}
				else {
					//g_Doppel.isHigh = true;
					g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
					if (!g_Doppel.isHigh) {
						//pPlayer->sp.y = -0.1f;
						g_Doppel.isHigh = true;
						break;
					}
					else {
						g_Doppel.isHigh = false;
					}
				}

			}/*
			else
			{
				g_Doppel.isHigh = false;
			}*/
			//�h�b�y���Q���K�[���E����������u���b�N��,
			if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
				g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
				g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
			{
				g_Doppel.Position.y = (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 - g_Doppel.size.y / 2;
			}
			// �h�b�y���Q���K�[�̉��Ƀu���b�N����������
			if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
				(g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
				(g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
				(g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
			{
			}
		}
	}
	//-----------------------------------------------------
	//�h�b�y���Q���K�[�ƌ��t�����̓����蔻��(DoppelGanger��OpenKey)
	//-----------------------------------------------------
	for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			if ((pOpenKey + j + i)->DrawFlag) {
				//�v���[���[�Ɣ��̔���
				//���̍��ƃh�b�y���Q���K�[�̉E
				if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 >= g_Doppel.oldpos.x + g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
					(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2)
				{
					g_Doppel.Position.x = g_Doppel.oldpos.x;
				}
				//���̉E�ƃh�b�y���Q���K�[�̍�
				if ((pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 <= g_Doppel.oldpos.x - g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
					(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2)
				{
					g_Doppel.Position.x = g_Doppel.oldpos.x;
				}
				//���́��ƃh�b�y���Q���K�[�̏�
				if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
					(pOpenKey + j + i)->Position.y - (pOpenKey + j + i)->Size.y / 2 >= g_Doppel.oldpos.y + g_Doppel.size.y / 2)
				{
					g_Doppel.Position = g_Doppel.oldpos;
				}
				//���́��ƃh�b�y���Q���K�[�́�
				if ((pOpenKey + j + i)->Position.x - (pOpenKey + j + i)->Size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.x + (pOpenKey + j + i)->Size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
					(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2 &&
					(pOpenKey + j + i)->Position.y + (pOpenKey + j + i)->Size.y / 2 <= g_Doppel.oldpos.y - g_Doppel.size.y / 2)
				{
					g_Doppel.Position.y = pOpenKey[i].Position.y + pOpenKey[i].Size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
					g_Doppel.jump = false;
					g_Doppel.fall = false;
					g_Doppel.WarpFlag = false;
					g_Doppel.sp.y = 0;
					g_Doppel.frame = 0;
				}
			}
		}
	}

	if (!Mouse_IsLeftDown() &&
		!pCursor->bHave)
	{


		for (int i = 0; i < JUMPSTAND_MAX; i++)
		{
			if (pJumpStand[i].UseJumpStand)
			{
				//�W�����v��E�E�h�b�y���Q���K�[��
				if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pJumpStand[i].pos.x - pJumpStand[i].size.x / 2 &&
					g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pJumpStand[i].pos.x - pJumpStand[i].size.x / 2 &&
					g_Doppel.Position.y + g_Doppel.size.y / 2 > pJumpStand[i].pos.y - pJumpStand[i].size.y / 2 &&
					g_Doppel.Position.y - g_Doppel.size.y / 2 < pJumpStand[i].pos.y + pJumpStand[i].size.y / 2)
				{
					g_Doppel.Position.x = pJumpStand[i].pos.x - pJumpStand[i].size.x / 2 - g_Doppel.size.x / 2;
					//pJumpStand[i].sp = g_Doppel.sp;
					//pJumpStand[i].pos.x += pJumpStand[i].sp.x;
					//SetVolume(pJumpStandSoundMoveNo, 0.5f);
					//PlaySound(pJumpStandSoundMoveNo, 0);
				}
				//�h�b�y���Q���K�[�E�E�W�����v�䍶
				if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pJumpStand[i].pos.x + pJumpStand[i].size.x / 2 &&
					g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pJumpStand[i].pos.x + pJumpStand[i].size.x / 2 &&
					g_Doppel.Position.y + g_Doppel.size.y / 2 > pJumpStand[i].pos.y - pJumpStand[i].size.y / 2 &&
					g_Doppel.Position.y - g_Doppel.size.y / 2 < pJumpStand[i].pos.y + pJumpStand[i].size.y / 2)
				{
					g_Doppel.Position.x = pJumpStand[i].pos.x + pJumpStand[i].size.x / 2 + g_Doppel.size.x / 2;
					//pJumpStand[i].sp = g_Doppel.sp;
					//pJumpStand[i].pos.x += pJumpStand[i].sp.x;
					//SetVolume(pJumpStandSoundMoveNo, 0.5f);
					//PlaySound(pJumpStandSoundMoveNo, 0);
				}


				if (pJumpStand[i].GetJumpStand)//�W�����v�����������
				{
					pJumpStand[i].spD = g_Doppel.sp;
					pJumpStand[i].pos.x += pJumpStand[i].spD.x;

					//�������鉹
					if (pJumpStand[i].oldpos.x != pJumpStand[i].pos.x && pJumpStand[i].JumpStandNotMove == true)//���������u��
					{
						//SetVolume(pJumpStandSoundMoveNo, 0.5f);
						//////////////////////////////////////////////PlaySound(pJumpStandSoundMoveNo, -1);
						pJumpStand[i].JumpStandNotMove = false;
					}
				}
				if (pJumpStand[i].oldpos.x == pJumpStand[i].pos.x)//�������ĂȂ���
				{
					pJumpStand[i].JumpStandNotMove = true;
					///////////////////////////////////////////////////StopSound(pJumpStandSoundMoveNo);
				}

				{




					//�h�b�y���Q���K�[���E��jumpstand
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pJumpStand[i].pos.x - pJumpStand[i].size.x / 2 &&
						g_Doppel.Position.x - g_Doppel.size.x / 2 < pJumpStand[i].pos.x + pJumpStand[i].size.x / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pJumpStand[i].pos.y + pJumpStand[i].size.y / 2 &&
						g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pJumpStand[i].pos.y + pJumpStand[i].size.y / 2)
					{
						pJumpStand[i].JumpStandFlagD = true;

						//SetVolume(pJumpStandSoundNo, 1.5f);
						///////////////////////////////////////////////////////////////////PlaySound(pJumpStandSoundNo, 0);

						g_Doppel.sp.y = 0.0f;
						pJumpStand[i].JumpPowerD = 4.8f;
						//g_Doppel.sp.y = 5.0f;
						pJumpStand[i].JumpGravity = 0.1f;

					}

					if (pJumpStand[i].JumpStandFlagD)
					{
						if (pJumpStand[i].JumpPowerD > -10.0f)
						{
							pJumpStand[i].JumpPowerD -= pJumpStand[i].JumpGravity;

						}
						g_Doppel.Position.y += pJumpStand[i].JumpPowerD;
						//g_Doppel.Position.y -= g_Doppel.sp.y;


						for (int j = 0; j < BLOCK_CHIP_MAX; j++)
						{

							if ((pChipblock + j)->UseFlag)
							{
								//��
								if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pChipblock + j)->Position.x - (pChipblock + j)->Size.x / 2 &&
									g_Doppel.Position.x - g_Doppel.size.x / 2 < (pChipblock + j)->Position.x + (pChipblock + j)->Size.x / 2 &&
									g_Doppel.Position.y - g_Doppel.size.y / 2 < (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2 &&
									g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2)
								{
									pJumpStand[i].JumpPowerD = 0.0f;
									g_Doppel.sp.y = 0.0f;
									//pJumpStand[i].JumpGravity = 0.0f;
									g_Doppel.Position.y = (pChipblock + j)->Position.y + (pChipblock + j)->Size.y / 2 + g_Doppel.size.y / 2;
									pJumpStand[i].JumpStandFlagD = false;
								}
								//��
								if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pChipblock + j)->Position.x - (pChipblock + j)->Size.x / 2 &&
									g_Doppel.Position.x - g_Doppel.size.x / 2 < (pChipblock + j)->Position.x + (pChipblock + j)->Size.x / 2 &&
									g_Doppel.Position.y + g_Doppel.size.y / 2 > (pChipblock + j)->Position.y - (pChipblock + j)->Size.y / 2 &&
									g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pChipblock + j)->Position.y - (pChipblock + j)->Size.y / 2)
								{
									pJumpStand[i].JumpPowerD = 0.0f;
									g_Doppel.sp.y = 0.0f;
									//pJumpStand[i].JumpGravity = 0.0f;
									g_Doppel.Position.y = (pChipblock + j)->Position.y - (pChipblock + j)->Size.y / 2 - g_Doppel.size.y / 2;
									pJumpStand[i].JumpStandFlagD = false;

								}
							}
						}

					}

				}
			}
		}
	}



























	//=========================================
	//�v���[���[�ƊX���X�C�b�`�n(switch,SwitchWall)
	//=========================================
	LAMP* p_Lamp = GetLamp();
	LAMP_SWITCH* p_LampSwitch = GetLampSwitch();
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (p_LampSwitch[i].UseFlag) {
			//�X���X�C�b�`�ƃv���C���[�̓����蔻��
			if (p_LampSwitch[i].pos.x - p_LampSwitch[i].size.x / 2 < pPlayer->Position.x + pPlayer->size.x / 2 &&
				p_LampSwitch[i].pos.x + p_LampSwitch[i].size.x / 2 > pPlayer->Position.x - pPlayer->size.x / 2 &&
				p_LampSwitch[i].pos.y - p_LampSwitch[i].size.y / 2 < pPlayer->Position.y + pPlayer->size.y / 2 &&
				p_LampSwitch[i].pos.y + p_LampSwitch[i].size.y / 2 > pPlayer->Position.y - pPlayer->size.y / 2 &&
				g_Doppel.LampSwitchFlag[i] == true)
			{
				p_LampSwitch[i].PressFlag = true;//�����ꂽ��
				p_LampSwitch[i].PaternNo = 1;
				if (p_LampSwitch[i].NotPressed)
				{
					SetVolume(g_LampSwitchSoundNo, 0.5f);
					PlaySound(g_LampSwitchSoundNo, 0);
					p_LampSwitch[i].NotPressed = false;
				}
			}
			/*else {
				StopEffectLight(i);
				p_LampSwitch[i].PressFlag = false;
				p_LampSwitch[i].PaternNo = 0;
				p_LampSwitch[i].NotPressed = true;
			}*/

			//�X���X�C�b�`�ƃh�b�y���Q���K�[�̓����蔻��
			if (p_LampSwitch[i].pos.x - p_LampSwitch[i].size.x / 2 < g_Doppel.Position.x + g_Doppel.size.x / 2 &&
				p_LampSwitch[i].pos.x + p_LampSwitch[i].size.x / 2 > g_Doppel.Position.x - g_Doppel.size.x / 2 &&
				p_LampSwitch[i].pos.y - p_LampSwitch[i].size.y / 2 < g_Doppel.Position.y + g_Doppel.size.y / 2 &&
				p_LampSwitch[i].pos.y + p_LampSwitch[i].size.y / 2 > g_Doppel.Position.y - g_Doppel.size.y / 2 &&
				g_Doppel.LampSwitchFlag[i] == true)
			{
				p_LampSwitch[i].PressFlag = true;//�����ꂽ��
				p_LampSwitch[i].PaternNo = 1;
				if (p_LampSwitch[i].NotPressed)
				{
					SetVolume(g_LampSwitchSoundNo, 0.5f);
					PlaySound(g_LampSwitchSoundNo, 0);
					p_LampSwitch[i].NotPressed = false;
					p_LampSwitch[i].NotPressed = false;
				}
			}
			/*else {
				StopEffectLight(i);
				p_LampSwitch[i].PressFlag = false;
				p_LampSwitch[i].PaternNo = 0;
				p_LampSwitch[i].NotPressed = true;
			}*/

			//�X���X�C�b�`�Ɩؔ��̓����蔻��
			for (int j = 0; j < MOVE_BLOCK_MAX; j++) {
				if (CollisionBB(p_LampSwitch[i].pos, pMoveBlock[j].pos, p_LampSwitch[i].size, pMoveBlock[j].size) &&
					g_Doppel.LampSwitchFlag[i] == true) {
					p_LampSwitch[i].PressFlag = true;//�����ꂽ��
					p_LampSwitch[i].PaternNo = 1;
					if (p_LampSwitch[i].NotPressed == true)
					{
						//SetVolume(g_SwitchSoundNo, 0.5f);
						//PlaySound(g_SwitchSoundNo, 0);
						p_LampSwitch[i].NotPressed = false;
					}
				}
				/*else {
					StopEffectLight(i);
					p_LampSwitch[i].PressFlag = false;
					p_LampSwitch[i].PaternNo = 0;
					p_LampSwitch[i].NotPressed = true;
				}*/
			}


			//�S����false
			for (int j = 0; j < MOVE_BLOCK_MAX; j++) 
			{
				if ((!CollisionBB(p_LampSwitch[i].pos, pPlayer->Position, p_LampSwitch[i].size, pPlayer->size))&&
					(!CollisionBB(p_LampSwitch[i].pos, g_Doppel.Position, p_LampSwitch[i].size, g_Doppel.size)) &&
					(!CollisionBB(p_LampSwitch[i].pos, pMoveBlock[j].pos, p_LampSwitch[i].size, pMoveBlock[j].size)))
				{
					p_LampSwitch[i].PressFlag = false;
					p_LampSwitch[i].PaternNo = 0;
					p_LampSwitch[i].NotPressed = true;
				}
			}




			if (p_LampSwitch[i].PressFlag)
			{
				//  switch index 0,1			switch wall	index 0,3
				if (p_LampSwitch[i].LampSwitchIndex == p_Lamp[i].SwitchIndex)
				{
					SetEffectLight(p_Lamp[i].pos, p_Lamp[i].rot, i);
					p_Lamp[i].PaternNo = 1.0f;
					if (CollisionBB(g_Doppel.Position, p_Lamp[i].pos, g_Doppel.size, p_Lamp[i].size))
					{
						g_Doppel.LightFrame++;
						if (g_Doppel.LightFrame >= 30)
						{
							g_Doppel.LightFrame = 0;
							g_Doppel.hp--;
							SetVolume(g_CandleSoundNo, 0.8f);
							PlaySound(g_CandleSoundNo, 0);
							g_Doppel.LampSwitchFlag[i] = false;
							for (int i = 0; i < SPAWN_POINT_D_MAX; i++) {//���X�|��������HP�����葱���Ă���
								if (pSpawnPointD[i].UseFlag) {
									if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex) {
										g_Doppel.Position = pSpawnPointD[i].Position;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				StopEffectLight(i);
				p_Lamp[i].PaternNo = 0.0f;
			}
			//if (p_LampSwitch[i].PressFlag) 
			//{
			//	for (int j = 0; j < p_Lamp[i].LampMax; j++) 
			//	{
			//		//  switch index 0,1			switch wall	index 0,3
			//		if (p_LampSwitch[i].LampSwitchIndex == p_Lamp[i].SwitchIndex) 
			//		{
			//			SetEffectLight(p_Lamp[i + j].pos, p_Lamp[i + j].rot, i);
			//			p_Lamp[i + j].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			//			if (CollisionBB(g_Doppel.Position, p_Lamp[i + j].pos, g_Doppel.size, p_Lamp[i + j].size))
			//			{
			//				g_Doppel.hp--;
			//				g_Doppel.LampSwitchFlag[i] = false;
			//				if (pSpawnPointD[i].UseFlag)
			//				{
			//					if (g_Doppel.PieceIndex == pSpawnPointD[i].PieceIndex)
			//					{
			//						g_Doppel.Position = pSpawnPointD[i].Position;
			//					}
			//				}
			//			}
			//		}
			//	}
			//}
			//else 
			//{
			//	for (int j = 0; j < p_Lamp[i].LampMax; j++) 
			//	{
			//		p_Lamp[i + j].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			//		StopEffectLight(i + j);
			//	}
			//}
		}
	}












	if (g_Doppel.hp <= 0)
	{
		g_Doppel.UseFlag = false;
	}












	//MOUSE* pMouse = GetMouse();
	//if (!Mouse_IsLeftDown())
	//{
	//	PLAYER* pPlayer = GetPlayer();
	//	//-------------------------------------------------
	//	//�v���C���[�Ɣ��v���C���[�̈ړ�����
	//	//-------------------------------------------------

	//	if (pPlayer->UseFlag == true)
	//	{
	//		g_Doppel.sp.x = pPlayer->sp.x * -1;
	//		
	//		//pDoppel->sp == pPlayer->sp;
	//		//pDoppel->Position = pPlayer->Position;

	//		//g_Doppel.UseFlag = true;

	//		if (g_Doppel.UseFlag == true)
	//		{


	//			//�ړ�
	//			if (pPlayer->dir == PLAYER_DIRECTION::RIGHT)
	//			{
	//				//�v���C���[�̑��x���v���X���ꂽ�甽�v���C���[���E�Ɉړ�

	//				//g_Doppel.Position.x += g_Doppel.sp.x;
	//				if (g_Doppel.sp.x != 0) {
	//					g_Doppel.PaternNo += 0.25f;
	//				}


	//				// ������ς���
	//				g_Doppel.dir = DOPPELGANGER_DIRECTION::RIGHT;
	//				g_Doppel.uv_w = -DOPPELGANGER_UV_W;
	//			}
	//			else if (pPlayer->dir == PLAYER_DIRECTION::LEFT)
	//			{
	//				//�v���C���[�̑��x���v���X���ꂽ�甽�v���C���[�����Ɉړ�
	//				//g_Doppel.Position.x += g_Doppel.sp.x;
	//				if (g_Doppel.sp.x != 0) {
	//					g_Doppel.PaternNo += 0.25f;
	//				}


	//				// ������ς���
	//				g_Doppel.dir = DOPPELGANGER_DIRECTION::LEFT;
	//				g_Doppel.uv_w = DOPPELGANGER_UV_W;
	//			}
	//			else
	//			{
	//				g_Doppel.sp.x = 0;
	//			}
	//			//fuck
	//			// �A�j���[�V�����p�^�[���ԍ���0�`15�͈͓̔��ɂ���
	//			if (g_Doppel.PaternNo > 16) { g_Doppel.PaternNo -= 16; }
	//			if (g_Doppel.PaternNo < 0) { g_Doppel.PaternNo += 16; }

	//			

	//			//�h�b�y���Q���K�[�e����
	//			//SetBullet(g_Doppel.Position, D3DXVECTOR2(BULLET_SIZE_H, BULLET_SIZE_W), 1);

	//		//}



	//		//-------------------
	//		//��{�u���b�N�̏ꍇ
	//		//-------------------
	//			BLOCK* block = GetChipBlock();

	//			for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
	//				if (block[i].UseFlag)
	//				{
	//					// �v���C���[�̉��Ƀu���b�N����������
	//					if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
	//						(g_Doppel.Position.y + g_Doppel.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
	//						(g_Doppel.Position.x + g_Doppel.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
	//						(g_Doppel.Position.x - g_Doppel.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
	//					{	// ���n���ɂ���
	//						if (!g_Doppel.isGround) {
	//							g_Doppel.sp.y = 0.0f;
	//							g_Doppel.isGround = true;
	//							g_Doppel.PieceIndex = block[i].PieceIndex;
	//							break;
	//						}
	//					}
	//					else {
	//						g_Doppel.isGround = false;
	//					}
	//				}
	//			}

	//			//---------------
	//			//�����鏰�̏ꍇ
	//			//---------------
	//			SHEERFLOORS* pSheerFloors = GetSheerFloors();
	//			for (int i = 0; i < SHEERFLOORS_NUM; i++)
	//			{
	//				if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.Position.y + g_Doppel.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
	//					g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
	//				{
	//					//g_Doppel.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Doppel.size.x / 2;
	//				}
	//				//���v���C���[�E�E�u���b�N��
	//				if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.Position.y + g_Doppel.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
	//					g_Doppel.Position.y - g_Doppel.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
	//				{
	//					//g_Doppel.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Doppel.size.x / 2;
	//				}

	//				////���v���C���[��E�u���b�N��,���n����

	//				if ((g_Doppel.oldpos.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
	//					CollisionBB(g_Doppel.Position, pSheerFloors[i].pos, g_Doppel.size, pSheerFloors[i].size))
	//				{
	//					g_Doppel.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Doppel.size.y / 2);
	//					g_Doppel.sp.y = 0.0f;
	//					//p_JumpStand->JumpStandFlag = false;

	//					g_Doppel.isSheerFloors = true;
	//					g_Doppel.sp.y = 0.0f;


	//				}


	//				//���v���C���[���E�u���b�N��,��������
	//				if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
	//					g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
	//					g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
	//				{

	//				}
	//			}

	//			for (int i = 0; i < SHEERFLOORS_NUM; i++)
	//			{
	//				if (!GetThumbLeftY(0) < 0.3f ||					// GamePad	���X�e�B�b�N	��
	//					!Keyboard_IsKeyDown(KK_DOWN))				// Keyboard	��
	//				{
	//					// ���v���C���[�̉��Ƀu���b�N����������
	//					if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f > pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2) &&
	//						(g_Doppel.Position.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
	//						(g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2) &&
	//						(g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2))
	//					{	// ���n���ɂ���
	//						//g_Doppel.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 - g_Doppel.size.y / 2 - 0.02f;

	//						if (!g_Doppel.isSheerFloors) {
	//							g_Doppel.sp.y = 0.0f;
	//							g_Doppel.isSheerFloors = true;
	//							break;
	//						}
	//					}
	//					else {
	//						g_Doppel.isSheerFloors = false;
	//					}
	//				}
	//			}

	//			if (GetThumbLeftY(0) < -0.3f ||			// GamePad	���X�e�B�b�N	��
	//				Keyboard_IsKeyDown(KK_DOWN))		// Keyboard	��
	//			{
	//				g_Doppel.isSheerFloors = false;
	//			}

	//			// �W�����v
	//			if ((g_Doppel.isGround || g_Doppel.isSheerFloors || g_Doppel.isHigh || g_Doppel.isMoveBlock) && g_Doppel.sp.y <=0 && Keyboard_IsKeyDown(KK_SPACE))//&& Keyboard_IsKeyDown(KK_SPACE
	//			{

	//				g_Doppel.sp.y = 2.5f;			// �X�s�[�h��y���}�C�i�X�ɂ���

	//				if (g_Doppel.isGround) {
	//					g_Doppel.isGround = false;			// �t���O���W�����v���ɂ���
	//				}
	//				if (g_Doppel.isSheerFloors) {
	//					g_Doppel.isSheerFloors = false;			// �t���O���W�����v���ɂ���
	//				}
	//				if (g_Doppel.isHigh) {
	//					g_Doppel.isHigh = false;			// �t���O���W�����v���ɂ���
	//				}
	//				if (g_Doppel.isMoveBlock) {
	//					g_Doppel.isMoveBlock = false;
	//				}
	//			}

	//			// ��
	//			if (!g_Doppel.isGround && !g_Doppel.isSheerFloors && !g_Doppel.isMoveBlock) {
	//				g_Doppel.sp.y -= 0.1f;			// �X�s�[�h��y�𑝂₷
	//			}

	//			//���f
	//			g_Doppel.oldpos = g_Doppel.Position;
	//			g_Doppel.Position += g_Doppel.sp;


	//			//���v���C���[�ƃ`�b�v�u���b�N �����蔻��
	//			{
	//				for (int i = 0; i < BLOCK_MAX; i++)
	//				{
	//					BLOCK* block = GetBlock();
	//					BLOCK* cipblock = GetChipBlock();

	//					if ((cipblock + i)->UseFlag == true)
	//					{
	//						//�v���C���[���E�u���b�N�E
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.x = (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 - g_Doppel.size.x / 2;
	//						}
	//						//�v���C���[�E�E�u���b�N��
	//						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 3 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 3 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 3 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 3)
	//						{
	//							g_Doppel.Position.x = (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 + g_Doppel.size.x / 2;
	//						}

	//						//�v���C���[��E�u���b�N��,���n����
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 &&
	//							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.y = (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
	//							g_Doppel.jump = false;
	//							g_Doppel.fall = false;
	//							//g_Doppel.WarpFlag = false;
	//							//g_Doppel.isGround = true;
	//							g_Doppel.sp.y = 0;
	//							g_Doppel.frame = 0;
	//						}
	//						//�v���C���[���E�u���b�N��,��������
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
	//							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2)
	//						{
	//							g_Doppel.fall = true;
	//							g_Doppel.getfall = true;
	//							g_Doppel.frame = 50;
	//						}
	//					}
	//				}
	//			}



	//			//----------------
	//			//�W�����v��̏ꍇ
	//			//----------------
	//			JUMPSTAND* p_JumpStand = GetJumpStand();

	//			for (int i = 0; i < JUMPSTAND_MAX; i++) {
	//				if (p_JumpStand[i].UseJumpStand) {
	//					if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad	B
	//						Keyboard_IsKeyDown(KK_B))						// Keyboard	B
	//					{
	//						if (CollisionBB(g_Doppel.Position, p_JumpStand[i].pos, g_Doppel.size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
	//							p_JumpStand[i].GetJumpStand = true;
	//						}
	//					}
	//					else
	//					{
	//						p_JumpStand[i].GetJumpStand = false;
	//					}
	//				}
	//			}

	//			////���v���C���[�E�����u���b�N �����蔻��
	//			{
	//				MOVEBLOCK* pMoveBlock = GetMoveBlock();

	//				for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
	//					if (pMoveBlock[i].bUse)
	//					{
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
	//						{
	//							pMoveBlock[i].sp = g_Doppel.sp;
	//							pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;

	//						}
	//						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
	//						{
	//							pMoveBlock[i].sp = g_Doppel.sp;
	//							pMoveBlock[i].pos.x += pMoveBlock[i].sp.x;
	//						}
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 &&
	//							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2)
	//						{
	//							g_Doppel.Position.y = pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 - g_Doppel.size.y / 2;
	//							// ���n���ɂ���
	//							if (!g_Doppel.isMoveBlock) {
	//								g_Doppel.sp.y = 0.0f;
	//								g_Doppel.isMoveBlock = true;
	//								break;
	//							}
	//						}
	//						else {
	//							g_Doppel.isMoveBlock = false;
	//						}
	//						//�v���C���[���E�u���b�N��,��������
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
	//							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
	//						{
	//							pMoveBlock[i].sp = g_Doppel.sp;
	//							pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
	//						}
	//					}
	//				}
	//			}


	//			//========================================================================
	//			//�v���C���[�E���[�v�@�����蔻��(Player��Warp�̓����蔻��)
	//			//=========================================================================

	//			g_Doppel.CoolTime--;

	//			if (g_Doppel.CoolTime < 0)
	//			{
	//				g_Doppel.CoolTime = 0;

	//				//�v���C���[�E���[�v�@�����蔻��
	//				for (int i = 0; i < BLOCK_MAX; i++)
	//				{
	//					WARP* warp = GetWarp();
	//					if ((warp + i)->UseFlag == true)
	//					{
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
	//						{
	//							if (i % 2 == 0)
	//							{
	//								if (!g_Doppel.WarpFlag)
	//								{
	//									g_Doppel.Position = (warp + i + 1)->Position;
	//									g_Doppel.CoolTime = PLAYER_COOLTIME;
	//									g_Doppel.WarpFlag = true;
	//								}

	//							}
	//							else if (i % 2 == 1)
	//							{
	//								if (!g_Doppel.WarpFlag)
	//								{
	//									g_Doppel.Position = (warp + i - 1)->Position;
	//									g_Doppel.CoolTime = PLAYER_COOLTIME;

	//									g_Doppel.WarpFlag = true;

	//								}
	//							}
	//						}
	//					}
	//				}
	//			}



	//			////�g�Q�E���v���C���[  �����蔻��
	//			{
	//				for (int i = 0; i < THORN_BLOCK_MAX; i++) {

	//					THORNBLOCK* pThornBlock = GetThornBlock();


	//					if (pThornBlock[i].UseFlag) {

	//						if (CollisionBB(pThornBlock[i].Postion, g_Doppel.Position, pThornBlock[i].Size, g_Doppel.size))
	//						{
	//							//GKey* pGkey = GetGKey();

	//							g_Doppel.UseFlag = false;

	//							/*pGKey->UseFlag = false;
	//							pGKey->GetGKey = true;*/

	//						}

	//					}
	//				}
	//			}

	//			//�v���C���[��������������
	//			if (pPlayer->Position.y - pPlayer->size.y > SCREEN_HEIGHT)
	//			{
	//				g_Doppel.UseFlag = false;
	//			}



	//			//������u���b�N�@�����蔻�� 
	//			{
	//				for (int i = 0; i < FALLBLOCK_MAX; i++)
	//				{
	//					FALLBLOCK* FallBlock = GetFallBlock();
	//					if ((FallBlock + i)->UseFlag == true)
	//					{
	//						//�v���C���[���E�u���b�N�E����
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.x = (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 - g_Doppel.size.x / 2;
	//						}
	//						//�v���C���[�E�E������u���b�N��
	//						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.x = (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 + g_Doppel.size.x / 2;
	//						}
	//						//�v���C���[��E������u���b�N��
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
	//							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.y = (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
	//							g_Doppel.getfall = false;
	//							g_Doppel.fall = false;
	//							g_Doppel.frame = 50;
	//							(FallBlock + i)->Position.y++;
	//						}
	//						//�v���C���[���E������u���b�N
	//						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
	//							g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 &&
	//							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
	//						{
	//							g_Doppel.Position.y = (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
	//						}
	//					}
	//				}
	//			}

	//			//========================================================================
	//			//�v���C���[�E����u���b�N�@�����蔻��(Player��BrokenBlock�̓����蔻��)
	//			//=========================================================================

	//			for (int i = 0; i < BROKEN_MAX; i++)
	//			{

	//				BROKEN* pBroken = GetBroken();

	//				if ((pBroken + i)->UseFlag == true)
	//				{
	//					//�v���C���[���E����u���b�N�E
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
	//					{
	//						pPlayer->Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - pPlayer->size.x / 2;
	//					}
	//					//�v���C���[�E�E����u���b�N��
	//					if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
	//					{
	//						g_Doppel.Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + pPlayer->size.x / 2;
	//					}

	//					//�v���C���[��E����u���b�N��
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
	//						g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
	//					{
	//						g_Doppel.Position.y = (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 - pPlayer->size.y / 2;
	//						g_Doppel.jump = false;
	//						g_Doppel.fall = false;
	//						g_Doppel.frame = 0;
	//					}
	//					//�v���C���[���E����u���b�N��,����
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
	//						g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
	//					{
	//						(pBroken + i)->UseFlag = false;
	//						g_Doppel.fall = true;
	//						g_Doppel.getfall = true;
	//						g_Doppel.frame = 50;
	//					}
	//				}
	//			}

	//			//====================================================================
	//			//�v���C���[�ƍ��������u���b�N�̓����蔻��(Player��High�̓����蔻��)
	//			//====================================================================

	//			for (int i = 0; i < HIGH_MAX; i++)
	//			{

	//				HIGH* pHigh = GetHigh();

	//				if ((pHigh + i)->UseFlag == true)
	//				{
	//					//�v���C���[���E����������u���b�N�E
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
	//					{
	//						g_Doppel.Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - g_Doppel.size.x / 2;
	//					}
	//					//�v���C���[�E�E����������u���b�N��
	//					if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
	//					{
	//						g_Doppel.Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + g_Doppel.size.x / 2;
	//					}

	//					//�v���C���[��E����������u���b�N��
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
	//						g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
	//					{
	//						if (g_Doppel.sp.y >= -10.0f)
	//						{
	//							//pPlayer->isHigh = false;
	//							(pHigh + i)->UseFlag = false;
	//							g_Doppel.frame = 50;
	//						}
	//						else
	//						{
	//							//pPlayer->isHigh = true;
	//							g_Doppel.sp.y = 0.0f;
	//							g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
	//						}

	//					}

	//					//�v���C���[���E����������u���b�N��,
	//					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
	//						g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
	//						g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
	//					{
	//						g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
	//					}

	//					// �v���C���[�̉��Ƀu���b�N����������
	//					if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
	//						(g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
	//						(g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
	//						(g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
	//					{	// ���n���ɂ���
	//						if (!g_Doppel.isHigh) {
	//							g_Doppel.sp.y = 0.0f;
	//							g_Doppel.isHigh = true;
	//							break;
	//						}
	//					}
	//					else {
	//						g_Doppel.isHigh = false;
	//					}
	//				}
	//			}


	//			////------------------------------------
	//			////�h�b�y���Q���K�[�e�p�����蔻��
	//			////------------------------------------
	//			//	//DOPPELGANGER* pDoppel = GetDoppelganger();
	//			//	BULLET* pBullet = GetBullet();
	//			//	

	//			//	if (g_Doppel.UseFlag == true)
	//			//	{
	//			//		pBullet->use = true;

	//			//		if (pBullet->use == true)
	//			//		{
	//			//			if (pPlayer->UseFlag)
	//			//			{
	//			//				bool hit = CollisionBB(pBullet->pos, pPlayer->Position, D3DXVECTOR2(pBullet->w, pBullet->h), D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H));

	//			//				if (hit == true)//�������Ă���
	//			//				{
	//			//					if (pBullet->hit)
	//			//					{
	//			//						pPlayer->hp - (pBullet->Damage);
	//			//						if (pPlayer->hp <= 0)
	//			//						{
	//			//							pPlayer->UseFlag = false;
	//			//							StartFade(FADE::FADE_OUT);
	//			//							SetResultType(LOSE);
	//			//							/*pTime->EndTime();
	//			//							pTimeParam->EndFlag = true;*/
	//			//						}

	//			//					}
	//			//				}
	//			//				else//�����Ă��Ȃ�
	//			//				{

	//			//				}
	//			//			}
	//			//		}
	//			//	}


	//			Piece* pPiece = GetPiece();
	//			SpawnPoint* pSpawnPoint = GetSpawnPoint();

	//			for (int i = 0; i < PUZZLE_MAX; i++)
	//			{
	//				if (pPiece[i].UseFlag)
	//				{
	//					bool hitflag = CollisionBB(g_Doppel.Position, pPiece[i].pos, g_Doppel.size, pPiece[i].size);

	//					if (hitflag)
	//					{
	//						if (g_Doppel.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
	//						{
	//							bool hitflag2 = DoppelPieceOpen(pPiece[i], i, DOWN);

	//							if (!hitflag2)
	//							{
	//								g_Doppel.sp.y -= 0.2;//����
	//							}
	//							else
	//							{//���ɉ����Ȃ����S����ꍇ
	//								for (int i = 0; i < SPAWN_POINT_MAX; i++)
	//								{
	//									if (pSpawnPoint[i].UseFlag)
	//									{
	//										if (g_Doppel.PieceIndex == pSpawnPoint[i].PieceIndex)
	//										{
	//											g_Doppel.Position = pSpawnPoint[i].Position;

	//										}


	//									}
	//								}

	//							}
	//						}
	//						else if (g_Doppel.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
	//						{

	//							bool hitflag2 = DoppelPieceOpen(pPiece[i], i, RIGHT);

	//							if (!hitflag2)
	//							{
	//								//g_Player.sp.y += 0.2;//����
	//							}
	//							else
	//							{
	//								g_Doppel.Position.x = g_Doppel.oldpos.x;
	//							}


	//						}
	//						else if (g_Doppel.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
	//						{
	//							bool hitflag2 = DoppelPieceOpen(pPiece[i], i, LEFT);

	//							if (!hitflag2)
	//							{
	//								//g_Player.sp.y += 0.2;//����
	//							}
	//							else
	//							{
	//								g_Doppel.Position.x = g_Doppel.oldpos.x;
	//							}


	//						}
	//						else if (g_Doppel.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
	//						{
	//							bool hitflag2 = DoppelPieceOpen(pPiece[i], i, UP);

	//							if (!hitflag2)
	//							{
	//								//g_Player.sp.y += 0.2;//����
	//							}
	//							else
	//							{

	//								g_Doppel.fall = true;
	//								//g_Player.sp.y = 0;
	//								//g_Player.getfall = true;
	//								g_Doppel.frame = 50;
	//								//g_Player.sp.y += 0.2;//����
	//							}

	//						}
	//					}
	//				}


	//			}
	//		}
	//	}
	//}
}
}
}


//=============================================================================
//�`�揈��
//=============================================================================
void DrawDoppelganger()
{
	if (g_Doppel.UseFlag == true)
	{
		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Doppel.texno));
		//�X�v���C�g��\��
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Doppel.Position.x, g_Doppel.Position.y, -0.2f, g_Doppel.Drawsize.x, g_Doppel.Drawsize.y, g_Doppel.rot, g_Doppel.col, g_Doppel.PaternNo, g_Doppel.uv_w *-1, g_Doppel.uv_h, g_Doppel.NumPatern);
	}
}

void SetDoppelGanger(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	if (!g_Doppel.UseFlag)
	{
		g_Doppel.Position = g_Doppel.OneOldpos = g_Doppel.oldpos = pos;
		g_Doppel.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
		g_Doppel.PieceIndex = index;
		g_Doppel.UseFlag = true;
		InitPos = pos;

	}
}
void DeleteDoppelGanger(int index) {
	if (g_Doppel.UseFlag && g_Doppel.PieceIndex == index) {
		g_Doppel.UseFlag = false;
	}
}

DOPPELGANGER* GetDoppelganger()
{
	return &g_Doppel;
}