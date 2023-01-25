//=============================================================================
//
//�v���C���[����
//
//�����/��t���l�@�����/2022/06/27
//���̐���ҁF�V���Ė�	����X�V��2022/10/24
//=============================================================================
#pragma once

#include "player.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"

#include "block.h"
//#include "thorn_block.h"
#include "broken.h"
#include "warp.h"
#include "scene.h"
#include "pause.h"
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
#include "OpenKey.h"
#include "Key.h"
#include "fallblock.h"
#include "SheerFloors.h"
#include "high_broken.h"
#include "MoveBlock.h"
#include "goal_key.h"
#include "pause.h"
#include "goal_key.h"
#include"spawnpoint.h"
#include"cursor.h"
#include "sound.h"
#include "start.h"
//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static PLAYER g_Player;
static char* g_TextureNameBroken = (char*)"data\\texture\\�v���C���[.png";

static int g_PlayerRightSoundNo = 0;
static char g_PlayeRightSoundName[] = "data\\SoundData\\SE\\�v�C�ŕ����E.wav";
static int g_PlayerLeftSoundNo = 0;
static char g_PlayerLeftSoundName[] = "data\\SoundData\\SE\\�v�C�ŕ�����.wav";

//�v���C���[���n�������������ł�
//

static Time		g_Time;

//=============================================================================
//����������
//=============================================================================
HRESULT InitPlayer()
{
	Piece* pPiece = GetPiece();
	START* pStart = GetStart();
	//�v���C���[�̏�����
	//g_Player.Position = D3DXVECTOR2(pPiece->pos.x+30.0f,pPiece->pos.y);
	g_Player.Position = D3DXVECTOR2(pStart[0].pos.x, pStart[0].pos.y);
	g_Player.OneOldpos = g_Player.oldpos = g_Player.Position;
	g_Player.sp = D3DXVECTOR2(0.0f,-8.0f);
	g_Player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Player.Drawsize = D3DXVECTOR2(33.0f, 33.0f);
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.rot = 180.0f;
	g_Player.UseFlag = true;
	g_Player.jump = false;
	//g_Player.getjump = false;
	//g_Player.GetJumpStand = false;		//�W�����v��p
	g_Player.fall = false;
	//g_Player.getfall = false;
	//g_Player.WarpFlag = false;
	g_Player.isGround = true;
	g_Player.isSheerFloors = false;
	g_Player.isSheerFloorsUse = false;
	//g_Player.isHigh = false;
	g_Player.isMoveBlock = false;
	g_Player.isBrokenBlock = false;
	g_Player.isFallBlock = false;
	g_Player.texno = LoadTexture(g_TextureNameBroken);

	g_Player.PaternNo = 0;//�p�^�[���ԍ�
	g_Player.uv_w = PLAYER_UV_W;//���T�C�Y
	g_Player.uv_h = PLAYER_UV_H;//�c�T�C�Y
	g_Player.NumPatern = 4;//������

	g_Player.hp = PLAYER_HP;
	g_Player.frame = 0;
	g_Player.CoolTime = PLAYER_COOLTIME;
	g_Player.PieceIndex = 0;

	g_Player.SoundRightFlag = false;
	g_Player.SoundLeftFlag = false;
	g_PlayerRightSoundNo = LoadSound(g_PlayeRightSoundName);
	g_PlayerLeftSoundNo = LoadSound(g_PlayerLeftSoundName);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitPlayer()
{
	StopSound(g_PlayerRightSoundNo);
	StopSound(g_PlayerLeftSoundNo);
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdatePlayer()
{	//-------------------------------------------------
	//�v���C���[���֗^���Ă����Ԃ̃M�~�b�N�Ƃ̏���
	//-------------------------------------------------

	MOUSE* pMouse = GetMouse();
	if (!Mouse_IsLeftDown())
	{

		if (g_Player.UseFlag == true)
		{
			//�ړ�
			if (GetThumbLeftX(0) > 0.3f ||					// GamePad	�E�X�e�B�b�N	�E
				Keyboard_IsKeyDown(KK_D))				// Keyboard	D
			{//������Ă���Ƃ��̏���
				g_Player.sp.x = 1.3f;
				g_Player.PaternNo -= 0.25f;

				// ������ς���
				g_Player.dir = PLAYER_DIRECTION::RIGHT;
				g_Player.uv_w = -PLAYER_UV_W;
			}
			else if (GetThumbLeftX(0) < -0.3f ||			// GamePad	�E�X�e�B�b�N	��
				Keyboard_IsKeyDown(KK_A))				// Keyboard	A
			{//������Ă���Ƃ��̏���
				g_Player.sp.x = -1.3f;
				g_Player.PaternNo += 0.25f;

				// ������ς���
				g_Player.dir = PLAYER_DIRECTION::LEFT;
				g_Player.uv_w = PLAYER_UV_W;
			}
			else
			{
				g_Player.sp.x = 0;
			}
			// �A�j���[�V�����p�^�[���ԍ���0�`15�͈͓̔��ɂ���
			if (g_Player.PaternNo >= 15) { g_Player.PaternNo -= 15; }
			if (g_Player.PaternNo < 0) { g_Player.PaternNo += 15; }
			//============================================================
			//	����
			//============================================================
			if (!g_Player.SoundRightFlag) {
				if (g_Player.PaternNo == 9.0f) {
					SetVolume(g_PlayerRightSoundNo, 0.5f);
					PlaySound(g_PlayerRightSoundNo, 0);
					g_Player.SoundRightFlag = true;
				}
			}
			else {
				if (g_Player.PaternNo != 9.0f) {
					g_Player.SoundRightFlag = false;
				}
			}
			if (!g_Player.SoundLeftFlag) {
				if (g_Player.PaternNo == 1.0f) {
					SetVolume(g_PlayerLeftSoundNo, 0.5f);
					PlaySound(g_PlayerLeftSoundNo, 0);
					g_Player.SoundLeftFlag = true;
				}
			}
			else {
				if (g_Player.PaternNo != 1.0f) {
					g_Player.SoundLeftFlag = false;
				}
			}
			if (g_Player.sp.x == 0)
			{
				g_Player.PaternNo = 17;

				if (g_Player.uv_w < 0)
				{
					g_Player.PaternNo = 18;

				}
			}
			if (g_Player.sp.y != 0)
			{
				g_Player.PaternNo = 16;
				if (g_Player.uv_w < 0)
				{
					g_Player.PaternNo = 19;

				}

			}

			//----------------
			//�W�����v��̏ꍇ
			//----------------
			JUMPSTAND* p_JumpStand = GetJumpStand();

			for (int i = 0; i < JUMPSTAND_MAX; i++) {
				if (p_JumpStand[i].UseJumpStand) {
					if (IsButtonPressed(0, XINPUT_GAMEPAD_B) ||		// GamePad	B
						Keyboard_IsKeyDown(KK_LEFTCONTROL))			// Keyboard	Ctrl�@��
					{
						if (CollisionBB(g_Player.Position, p_JumpStand[i].pos, g_Player.size, p_JumpStand[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
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
					if (IsButtonPressed(0, XINPUT_GAMEPAD_B) ||		// GamePad	B
						Keyboard_IsKeyDown(KK_LEFTCONTROL))			// Keyboard	Ctrl�@��
					{
						if (CollisionBB(g_Player.Position, pMoveBlock[i].pos, g_Player.size, pMoveBlock[i].size + D3DXVECTOR2(10.0f, 0.0f))) {
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
			SpawnPoint* pSpawnPoint = GetSpawnPoint();
			for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
				if (block[i].UseFlag)
				{
					// �v���C���[�̉��Ƀu���b�N����������
					if ((g_Player.Position.y - g_Player.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
						(g_Player.Position.y + g_Player.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
						(g_Player.Position.x + g_Player.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
						(g_Player.Position.x - g_Player.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
					{	// ���n���ɂ���
						if (!g_Player.isGround) {
							g_Player.sp.y = 0.0f;
							g_Player.isGround = true;
							g_Player.PieceIndex = block[i].PieceIndex;
							break;
						}
					}
					else {
						g_Player.isGround = false;
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
					if (g_Player.Position.x + g_Player.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Player.oldpos.x + g_Player.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
						g_Player.Position.y - g_Player.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Player.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Player.size.x / 2;
					}
					//�v���C���[�E�E�u���b�N��
					if (g_Player.Position.x - g_Player.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Player.oldpos.x - g_Player.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Player.Position.y + g_Player.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
						g_Player.Position.y - g_Player.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Player.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Player.size.x / 2;
					}

					//�v���C���[��E�u���b�N��,���n����
					if (!GetThumbLeftY(0) < -0.3f ||		// GamePad	���X�e�B�b�N	��
						!Keyboard_IsKeyDown(KK_S))		// Keyboard S
					{
						if (pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 < g_Player.Position.x + g_Player.size.x / 2 &&
							pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 > g_Player.Position.x - g_Player.size.x / 2 &&
							pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 > g_Player.Position.y - g_Player.size.y / 2 &&
							pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 <= g_Player.oldpos.y - g_Player.size.y / 2)
						{
							//g_Player.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Player.size.y / 2);
							//g_Player.sp.y = 0.0f;
							for (int i = 0; i < JUMPSTAND_MAX; i++)
							{
								p_JumpStand[i].JumpStandFlag = false;

							}
							g_Player.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 + g_Player.size.y / 2;
							g_Player.jump = false;
							g_Player.sp.y = -0.3f;

							g_Player.fall = false;
							if (!g_Player.isSheerFloors) {
								//g_Player.sp.y = 0.0f;
								g_Player.isSheerFloors = true;

							}
							else {
								g_Player.sp.y = 0.0f;

								g_Player.isSheerFloors = false;
							}
						}

						//�v���C���[���E�u���b�N��,��������
						if (g_Player.Position.x + g_Player.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
							g_Player.Position.x - g_Player.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
							g_Player.Position.y - g_Player.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
							g_Player.oldpos.y - g_Player.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
						{

						}
					}
				}

			}

			if (GetThumbLeftY(0) < -0.3f ||			// GamePad	���X�e�B�b�N	��
				Keyboard_IsKeyDown(KK_S))		// Keyboard	S
			{
				g_Player.isSheerFloors = false;
			}

			// �W�����v
			if ((g_Player.isGround || g_Player.isSheerFloors || g_Player.isHigh || g_Player.isMoveBlock||g_Player.isBrokenBlock||g_Player.isFallBlock)
				&& g_Player.sp.y <= 0 && (Keyboard_IsKeyDown(KK_SPACE) ||		// keyboard SPACE
					IsButtonTriggered(0, XINPUT_GAMEPAD_A)))						// GamePad A
			{

				g_Player.sp.y = 2.8f;			// �X�s�[�h��y���}�C�i�X�ɂ���
				//SetVolume(g_PlayerRightSoundNo, 0.5f);
				PlaySound(g_PlayerRightSoundNo, 0);


				if (g_Player.isGround) {
					g_Player.isGround = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Player.isSheerFloors) {
					g_Player.isSheerFloors = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Player.isHigh) {
					g_Player.isHigh = false;			// �t���O���W�����v���ɂ���
				}
				if (g_Player.isMoveBlock) {
					g_Player.isMoveBlock = false;
				}
			}

			// ��
			if (!g_Player.isGround && !g_Player.isHigh && !g_Player.isSheerFloors && !g_Player.isMoveBlock&&!g_Player.isBrokenBlock&&!g_Player.isFallBlock) {
				g_Player.sp.y -= 0.1f;			// �X�s�[�h��y�𑝂₷
			}
	
			//���f
			g_Player.oldpos = g_Player.Position;
			g_Player.Position += g_Player.sp;




			



			//�v���C���[�E���[�v �����蔻�� collision.cpp�ֈړ�

			{
				//�v���C���[�ƃp�Y���̉�ʊO����
				Piece* pPiece = GetPiece();

				for (int i = 0; i < PUZZLE_MAX; i++)
				{
					if (pPiece[i].UseFlag)
					{
						bool hitflag = CollisionBB(g_Player.Position, pPiece[i].pos, g_Player.size, pPiece[i].size);

						if (hitflag)
						{
							if (g_Player.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, DOWN);

								if (!hitflag2)
								{
									g_Player.sp.y -= 0.2f;//����
								}
								else
								{//���ɉ����Ȃ����S����ꍇ
									if (pSpawnPoint[i].UseFlag)
									{
										if (g_Player.PieceIndex == pSpawnPoint[i].PieceIndex)
										{
											g_Player.Position = pSpawnPoint[i].Position;
											g_Player.hp--;
											break;
										}
									}

								}
							}
							else if (g_Player.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
							{

								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, RIGHT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//����
								}
								else
								{
									g_Player.Position.x = g_Player.oldpos.x;
								}


							}
							else if (g_Player.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, LEFT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//����
								}
								else
								{
									g_Player.Position.x = g_Player.oldpos.x;
								}


							}
							else if (g_Player.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = PlayerPieceOpen(pPiece[i], i, UP);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//����
								}
								else
								{

									g_Player.fall = true;
									//g_Player.sp.y = 0;
									//g_Player.getfall = true;
									g_Player.frame = 50;
									//g_Player.sp.y += 0.2;//����
								}

							}
						}
					}


				}


			}
			if (IsButtonTriggered(0, XINPUT_GAMEPAD_BACK) || 	// GamePad	L�^�u
				Keyboard_IsKeyTrigger(KK_R))						// Keyboard	R
			{
				ResetGame();
			}

			//�v���C���[�ƃp�Y���̉�ʊO����
			Piece* pPiece = GetPiece();

			for (int i = 0; i < PUZZLE_MAX; i++)
			{
				if (pPiece[i].UseFlag)
				{
					bool hitflag = CollisionBB(g_Player.Position, pPiece[i].pos, g_Player.size, pPiece[i].size);

					if (hitflag)
					{
						if (g_Player.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, DOWN);

							if (!hitflag2)
							{
								g_Player.sp.y -= 0.2;//����
							}
							else
							{//���ɉ����Ȃ����S����ꍇ
								for (int i = 0; i < SPAWN_POINT_MAX; i++)
								{
									if (pSpawnPoint[i].UseFlag)
									{
										if (g_Player.PieceIndex == pSpawnPoint[i].PieceIndex)
										{
											g_Player.Position = pSpawnPoint[i].Position;

										}


									}
								}

							}
						}
						else if (g_Player.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
						{

							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, RIGHT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//����
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						else if (g_Player.Position.x <= pPiece[i].pos.x - PUZZLE_WIDHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, LEFT);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//����
							}
							else
							{
								g_Player.Position.x = g_Player.oldpos.x;
							}


						}
						else if (g_Player.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
						{
							bool hitflag2 = PlayerPieceOpen(pPiece[i], i, UP);

							if (!hitflag2)
							{
								//g_Player.sp.y += 0.2;//����
							}
							else
							{

								g_Player.fall = true;
								//g_Player.sp.y = 0;
								//g_Player.getfall = true;
								g_Player.frame = 50;
								//g_Player.sp.y += 0.2;//����
							}

						}
					}
				}


			}


			}

		}


		
	
}
//=============================================================================
//�`�揈��
//=============================================================================
void DrawPlayer()
{
	if (g_Player.UseFlag == true)
	{
		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Player.texno));
		//�X�v���C�g��\��
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_Player.Position.x, g_Player.Position.y,-0.2f, g_Player.Drawsize.x, g_Player.Drawsize.y, g_Player.rot, g_Player.col, g_Player.PaternNo, g_Player.uv_w, g_Player.uv_h, g_Player.NumPatern);
	}
}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
PLAYER* GetPlayer()
{
	return &g_Player;
}

void SetPlayerPosition(D3DXVECTOR2 pos)
{
	g_Player.Position = pos;
}
