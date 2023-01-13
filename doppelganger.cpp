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
//#include "input.h"
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

#include"spawnpoint.h"

#include "fade.h"
#include "result.h"

 
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

//=============================================================================
//����������
//=============================================================================
HRESULT InitDoppelganger()
{
	Piece* pPiece = GetPiece();

	
	g_Doppel.Position = D3DXVECTOR2(pPiece->pos.x - 30.0f, pPiece->pos.y);
	//g_Doppel.OneOldpos = g_Doppel.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Doppel.sp = D3DXVECTOR2(0, -8);
	g_Doppel.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);
	g_Doppel.Drawsize = D3DXVECTOR2(33.0f, 33.0f);
	g_Doppel.col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
	g_Doppel.rot = 180.0f;
	g_Doppel.UseFlag = true;
	g_Doppel.jump = false;
	//g_Doppel.getjump = false;
	g_Doppel.GetJumpStand = false;		//�W�����v��p
	g_Doppel.fall = false;
	//g_Doppel.getfall = false;
	g_Doppel.WarpFlag = false;
	g_Doppel.isGround = true;
	g_Doppel.isSheerFloors = false;
	g_Doppel.isSheerFloorsUse = false;
	g_Doppel.isHigh = false;
	g_Doppel.isMoveBlock = false;
	g_Doppel.texno = LoadTexture(g_TextureNameBroken);

	g_Doppel.PaternNo = 0;//�p�^�[���ԍ�
	g_Doppel.uv_w = DOPPELGANGER_UV_W;//���T�C�Y
	g_Doppel.uv_h = DOPPELGANGER_UV_H;//�c�T�C�Y
	g_Doppel.NumPatern = 4;//������


	g_Doppel.frame = 0;
	g_Doppel.CoolTime = PLAYER_COOLTIME;
	g_Doppel.PieceIndex = 0;


	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitDoppelganger()
{

}

//=============================================================================
//�X�V����
//=============================================================================

//�h�b�y���Q���K�[ �ȉ� ���v���C���[  �Ə̂�

void UpdateDoppelganger()
{	
	MOUSE* pMouse = GetMouse();
	if (!pMouse->UseFlag)
	{
		PLAYER* pPlayer = GetPlayer();
		//-------------------------------------------------
		//�v���C���[�Ɣ��v���C���[�̈ړ�����
		//-------------------------------------------------

		if (pPlayer->UseFlag == true)
		{
			g_Doppel.sp.x = pPlayer->sp.x * -1;
			
			//pDoppel->sp == pPlayer->sp;
			//pDoppel->Position = pPlayer->Position;

			g_Doppel.UseFlag = true;

			if (g_Doppel.UseFlag == true)
			{


				//�ړ�
				if (pPlayer->dir == PLAYER_DIRECTION::RIGHT)
				{
					//�v���C���[�̑��x���v���X���ꂽ�甽�v���C���[���E�Ɉړ�

					//g_Doppel.Position.x += g_Doppel.sp.x;
					if (g_Doppel.sp.x != 0) {
						g_Doppel.PaternNo += 0.25f;
					}


					// ������ς���
					g_Doppel.dir = DOPPELGANGER_DIRECTION::RIGHT;
					g_Doppel.uv_w = -DOPPELGANGER_UV_W;
				}
				else if (pPlayer->dir == PLAYER_DIRECTION::LEFT)
				{
					//�v���C���[�̑��x���v���X���ꂽ�甽�v���C���[�����Ɉړ�
					//g_Doppel.Position.x += g_Doppel.sp.x;
					if (g_Doppel.sp.x != 0) {
						g_Doppel.PaternNo += 0.25f;
					}


					// ������ς���
					g_Doppel.dir = DOPPELGANGER_DIRECTION::LEFT;
					g_Doppel.uv_w = DOPPELGANGER_UV_W;
				}
				else
				{
					g_Doppel.sp.x = 0;
				}
				//fuck
				// �A�j���[�V�����p�^�[���ԍ���0�`15�͈͓̔��ɂ���
				if (g_Doppel.PaternNo >= 16) { g_Doppel.PaternNo = 0; }
				//if (g_Doppel.PaternNo < 0) { g_Doppel.PaternNo = -17; }


				//�h�b�y���Q���K�[�e����
				//SetBullet(g_Doppel.Position, D3DXVECTOR2(BULLET_SIZE_H, BULLET_SIZE_W), 1);

			//}



			//-------------------
			//��{�u���b�N�̏ꍇ
			//-------------------
				BLOCK* block = GetChipBlock();

				for (int i = 0; i < BLOCK_CHIP_MAX; i++) {
					if (block[i].UseFlag)
					{
						// �v���C���[�̉��Ƀu���b�N����������
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < block[i].Position.y + block[i].Size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 > block[i].Position.y - block[i].Size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > block[i].Position.x - block[i].Size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < block[i].Position.x + block[i].Size.x / 2))
						{	// ���n���ɂ���
							if (!g_Doppel.isGround) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isGround = true;
								g_Doppel.PieceIndex = block[i].PieceIndex;
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
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 2 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 - g_Doppel.size.x / 2;
					}
					//���v���C���[�E�E�u���b�N��
					if (g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y + g_Doppel.size.y / 3 > pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 3 &&
						g_Doppel.Position.y - g_Doppel.size.y / 3 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 3)
					{
						//g_Doppel.Position.x = pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 + g_Doppel.size.x / 2;
					}

					////���v���C���[��E�u���b�N��,���n����

					if ((g_Doppel.oldpos.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
						CollisionBB(g_Doppel.Position, pSheerFloors[i].pos, g_Doppel.size, pSheerFloors[i].size))
					{
						g_Doppel.Position.y = pSheerFloors[i].pos.y - (pSheerFloors[i].size.y / 2 + g_Doppel.size.y / 2);
						g_Doppel.sp.y = 0.0f;
						//p_JumpStand->JumpStandFlag = false;

						g_Doppel.isSheerFloors = true;
						g_Doppel.sp.y = 0.0f;


					}


					//���v���C���[���E�u���b�N��,��������
					if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2 &&
						g_Doppel.Position.y - g_Doppel.size.y / 2 < pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 &&
						g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2)
					{

					}
				}

				for (int i = 0; i < SHEERFLOORS_NUM; i++)
				{
					if (!GetThumbLeftY(0) < 0.3f ||					// GamePad	���X�e�B�b�N	��
						!Keyboard_IsKeyDown(KK_DOWN))				// Keyboard	��
					{
						// ���v���C���[�̉��Ƀu���b�N����������
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f > pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 < pSheerFloors[i].pos.y - pSheerFloors[i].size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > pSheerFloors[i].pos.x - pSheerFloors[i].size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < pSheerFloors[i].pos.x + pSheerFloors[i].size.x / 2))
						{	// ���n���ɂ���
							//g_Doppel.Position.y = pSheerFloors[i].pos.y + pSheerFloors[i].size.y / 2 - g_Doppel.size.y / 2 - 0.02f;

							if (!g_Doppel.isSheerFloors) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isSheerFloors = true;
								break;
							}
						}
						else {
							g_Doppel.isSheerFloors = false;
						}
					}
				}

				if (GetThumbLeftY(0) < -0.3f ||			// GamePad	���X�e�B�b�N	��
					Keyboard_IsKeyDown(KK_DOWN))		// Keyboard	��
				{
					g_Doppel.isSheerFloors = false;
				}

				// �W�����v
				if ((g_Doppel.isGround || g_Doppel.isSheerFloors || g_Doppel.isHigh || g_Doppel.isMoveBlock) && g_Doppel.sp.y <=0 && Keyboard_IsKeyDown(KK_SPACE))//&& Keyboard_IsKeyDown(KK_SPACE
				{

					g_Doppel.sp.y = 2.5f;			// �X�s�[�h��y���}�C�i�X�ɂ���

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
				}

				// ��
				if (!g_Doppel.isGround && !g_Doppel.isSheerFloors && !g_Doppel.isMoveBlock) {
					g_Doppel.sp.y -= 0.1f;			// �X�s�[�h��y�𑝂₷
				}

				//���f
				g_Doppel.oldpos = g_Doppel.Position;
				g_Doppel.Position += g_Doppel.sp;


				//���v���C���[�ƃ`�b�v�u���b�N �����蔻��
				{
					for (int i = 0; i < BLOCK_MAX; i++)
					{
						BLOCK* block = GetBlock();
						BLOCK* cipblock = GetChipBlock();

						if ((cipblock + i)->UseFlag == true)
						{
							//�v���C���[���E�u���b�N�E
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 - g_Doppel.size.x / 2;
							}
							//�v���C���[�E�E�u���b�N��
							if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 3 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 3 &&
								g_Doppel.Position.y - g_Doppel.size.y / 3 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 3)
							{
								g_Doppel.Position.x = (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 + g_Doppel.size.x / 2;
							}

							//�v���C���[��E�u���b�N��,���n����
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (cipblock + i)->Position.y + (cipblock + i)->Size.y / 2 + g_Doppel.size.y / 2 + 0.02f;
								g_Doppel.jump = false;
								g_Doppel.fall = false;
								//g_Doppel.WarpFlag = false;
								//g_Doppel.isGround = true;
								g_Doppel.sp.y = 0;
								g_Doppel.frame = 0;
							}
							//�v���C���[���E�u���b�N��,��������
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (cipblock + i)->Position.x - (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (cipblock + i)->Position.x + (cipblock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (cipblock + i)->Position.y - (cipblock + i)->Size.y / 2)
							{
								g_Doppel.fall = true;
								g_Doppel.getfall = true;
								g_Doppel.frame = 50;
							}
						}
					}
				}



				//----------------
				//�W�����v��̏ꍇ
				//----------------
				JUMPSTAND* p_JumpStand = GetJumpStand();

				for (int i = 0; i < JUMPSTAND_MAX; i++) {
					if (p_JumpStand[i].UseJumpStand) {
						if (IsButtonTriggered(0, XINPUT_GAMEPAD_B) ||		// GamePad	B
							Keyboard_IsKeyDown(KK_B))						// Keyboard	B
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

				////���v���C���[�E�����u���b�N �����蔻��
				{
					MOVEBLOCK* pMoveBlock = GetMoveBlock();

					for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
						if (pMoveBlock[i].bUse)
						{
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
								g_Doppel.Position.y = pMoveBlock[i].pos.y - pMoveBlock[i].size.y / 2 - g_Doppel.size.y / 2;
								// ���n���ɂ���
								if (!g_Doppel.isMoveBlock) {
									g_Doppel.sp.y = 0.0f;
									g_Doppel.isMoveBlock = true;
									break;
								}
							}
							else {
								g_Doppel.isMoveBlock = false;
							}
							//�v���C���[���E�u���b�N��,��������
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > pMoveBlock[i].pos.x - pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < pMoveBlock[i].pos.x + pMoveBlock[i].size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= pMoveBlock[i].pos.y + pMoveBlock[i].size.y / 2)
							{
								pMoveBlock[i].sp = g_Doppel.sp;
								pMoveBlock[i].pos.y += pMoveBlock[i].sp.x;
							}
						}
					}
				}


				//========================================================================
				//�v���C���[�E���[�v�@�����蔻��(Player��Warp�̓����蔻��)
				//=========================================================================

				g_Doppel.CoolTime--;

				if (g_Doppel.CoolTime < 0)
				{
					g_Doppel.CoolTime = 0;

					//�v���C���[�E���[�v�@�����蔻��
					for (int i = 0; i < BLOCK_MAX; i++)
					{
						WARP* warp = GetWarp();
						if ((warp + i)->UseFlag == true)
						{
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (warp + i)->Position.x - (warp + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (warp + i)->Position.x + (warp + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (warp + i)->Position.y - (warp + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (warp + i)->Position.y + (warp + i)->Size.y / 2)
							{
								if (i % 2 == 0)
								{
									if (!g_Doppel.WarpFlag)
									{
										g_Doppel.Position = (warp + i + 1)->Position;
										g_Doppel.CoolTime = PLAYER_COOLTIME;
										g_Doppel.WarpFlag = true;
									}

								}
								else if (i % 2 == 1)
								{
									if (!g_Doppel.WarpFlag)
									{
										g_Doppel.Position = (warp + i - 1)->Position;
										g_Doppel.CoolTime = PLAYER_COOLTIME;

										g_Doppel.WarpFlag = true;

									}
								}
							}
						}
					}
				}



				////�g�Q�E���v���C���[  �����蔻��
				{
					for (int i = 0; i < THORN_BLOCK_MAX; i++) {

						THORNBLOCK* pThornBlock = GetThornBlock();


						if (pThornBlock[i].UseFlag) {

							if (CollisionBB(pThornBlock[i].Postion, g_Doppel.Position, pThornBlock[i].Size, g_Doppel.size))
							{
								//GKey* pGkey = GetGKey();

								g_Doppel.UseFlag = false;

								/*pGKey->UseFlag = false;
								pGKey->GetGKey = true;*/

							}

						}
					}
				}

				//�v���C���[��������������
				if (pPlayer->Position.y - pPlayer->size.y > SCREEN_HEIGHT)
				{
					g_Doppel.UseFlag = false;
				}



				//������u���b�N�@�����蔻�� 
				{
					for (int i = 0; i < FALLBLOCK_MAX; i++)
					{
						FALLBLOCK* FallBlock = GetFallBlock();
						if ((FallBlock + i)->UseFlag == true)
						{
							//�v���C���[���E�u���b�N�E����
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 - g_Doppel.size.x / 2;
							}
							//�v���C���[�E�E������u���b�N��
							if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.x = (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 + g_Doppel.size.x / 2;
							}
							//�v���C���[��E������u���b�N��
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y + g_Doppel.size.y / 2 > (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (FallBlock + i)->Position.y - (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
								g_Doppel.getfall = false;
								g_Doppel.fall = false;
								g_Doppel.frame = 50;
								(FallBlock + i)->Position.y++;
							}
							//�v���C���[���E������u���b�N
							if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (FallBlock + i)->Position.x - (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.x - g_Doppel.size.x / 2 < (FallBlock + i)->Position.x + (FallBlock + i)->Size.x / 2 &&
								g_Doppel.Position.y - g_Doppel.size.y / 2 < (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 &&
								g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2)
							{
								g_Doppel.Position.y = (FallBlock + i)->Position.y + (FallBlock + i)->Size.y / 2 - g_Doppel.size.y / 2;
							}
						}
					}
				}

				//========================================================================
				//�v���C���[�E����u���b�N�@�����蔻��(Player��BrokenBlock�̓����蔻��)
				//=========================================================================

				for (int i = 0; i < BROKEN_MAX; i++)
				{

					BROKEN* pBroken = GetBroken();

					if ((pBroken + i)->UseFlag == true)
					{
						//�v���C���[���E����u���b�N�E
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							pPlayer->Position.x = (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 - pPlayer->size.x / 2;
						}
						//�v���C���[�E�E����u���b�N��
						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 + pPlayer->size.x / 2;
						}

						//�v���C���[��E����u���b�N��
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2 &&
							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pBroken + i)->Postion.y + (pBroken + i)->Size.y / 2)
						{
							g_Doppel.Position.y = (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 - pPlayer->size.y / 2;
							g_Doppel.jump = false;
							g_Doppel.fall = false;
							g_Doppel.frame = 0;
						}
						//�v���C���[���E����u���b�N��,����
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pBroken + i)->Postion.x - (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pBroken + i)->Postion.x + (pBroken + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2 &&
							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pBroken + i)->Postion.y - (pBroken + i)->Size.y / 2)
						{
							(pBroken + i)->UseFlag = false;
							g_Doppel.fall = true;
							g_Doppel.getfall = true;
							g_Doppel.frame = 50;
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
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.oldpos.x + g_Doppel.size.x / 2 <= (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 - g_Doppel.size.x / 2;
						}
						//�v���C���[�E�E����������u���b�N��
						if (g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.oldpos.x - g_Doppel.size.x / 2 >= (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.x = (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 + g_Doppel.size.x / 2;
						}

						//�v���C���[��E����������u���b�N��
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y - g_Doppel.size.y / 2 < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 &&
							g_Doppel.oldpos.y - g_Doppel.size.y / 2 >= (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2)
						{
							if (g_Doppel.sp.y >= -10.0f)
							{
								//pPlayer->isHigh = false;
								(pHigh + i)->UseFlag = false;
								g_Doppel.frame = 50;
							}
							else
							{
								//pPlayer->isHigh = true;
								g_Doppel.sp.y = 0.0f;
								g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
							}

						}

						//�v���C���[���E����������u���b�N��,
						if (g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2 &&
							g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2 &&
							g_Doppel.oldpos.y + g_Doppel.size.y / 2 <= (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2)
						{
							g_Doppel.Position.y = (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2 + g_Doppel.size.y / 2;
						}

						// �v���C���[�̉��Ƀu���b�N����������
						if ((g_Doppel.Position.y - g_Doppel.size.y / 2 - 0.05f < (pHigh + i)->Postion.y + (pHigh + i)->Size.y / 2) &&
							(g_Doppel.Position.y + g_Doppel.size.y / 2 > (pHigh + i)->Postion.y - (pHigh + i)->Size.y / 2) &&
							(g_Doppel.Position.x + g_Doppel.size.x / 2 > (pHigh + i)->Postion.x - (pHigh + i)->Size.x / 2) &&
							(g_Doppel.Position.x - g_Doppel.size.x / 2 < (pHigh + i)->Postion.x + (pHigh + i)->Size.x / 2))
						{	// ���n���ɂ���
							if (!g_Doppel.isHigh) {
								g_Doppel.sp.y = 0.0f;
								g_Doppel.isHigh = true;
								break;
							}
						}
						else {
							g_Doppel.isHigh = false;
						}
					}
				}


				////------------------------------------
				////�h�b�y���Q���K�[�e�p�����蔻��
				////------------------------------------
				//	//DOPPELGANGER* pDoppel = GetDoppelganger();
				//	BULLET* pBullet = GetBullet();
				//	

				//	if (g_Doppel.UseFlag == true)
				//	{
				//		pBullet->use = true;

				//		if (pBullet->use == true)
				//		{
				//			if (pPlayer->UseFlag)
				//			{
				//				bool hit = CollisionBB(pBullet->pos, pPlayer->Position, D3DXVECTOR2(pBullet->w, pBullet->h), D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H));

				//				if (hit == true)//�������Ă���
				//				{
				//					if (pBullet->hit)
				//					{
				//						pPlayer->hp - (pBullet->Damage);
				//						if (pPlayer->hp <= 0)
				//						{
				//							pPlayer->UseFlag = false;
				//							StartFade(FADE::FADE_OUT);
				//							SetResultType(LOSE);
				//							/*pTime->EndTime();
				//							pTimeParam->EndFlag = true;*/
				//						}

				//					}
				//				}
				//				else//�����Ă��Ȃ�
				//				{

				//				}
				//			}
				//		}
				//	}


				Piece* pPiece = GetPiece();
				SpawnPoint* pSpawnPoint = GetSpawnPoint();

				for (int i = 0; i < PUZZLE_MAX; i++)
				{
					if (pPiece[i].UseFlag)
					{
						bool hitflag = CollisionBB(g_Doppel.Position, pPiece[i].pos, g_Doppel.size, pPiece[i].size);

						if (hitflag)
						{
							if (g_Doppel.Position.y < pPiece[i].pos.y - PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, DOWN);

								if (!hitflag2)
								{
									g_Doppel.sp.y -= 0.2;//����
								}
								else
								{//���ɉ����Ȃ����S����ꍇ
									for (int i = 0; i < SPAWN_POINT_MAX; i++)
									{
										if (pSpawnPoint[i].UseFlag)
										{
											if (g_Doppel.PieceIndex == pSpawnPoint[i].PieceIndex)
											{
												g_Doppel.Position = pSpawnPoint[i].Position;

											}


										}
									}

								}
							}
							else if (g_Doppel.Position.x >= pPiece[i].pos.x + PUZZLE_WIDHT / 2)
							{

								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, RIGHT);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//����
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
									//g_Player.sp.y += 0.2;//����
								}
								else
								{
									g_Doppel.Position.x = g_Doppel.oldpos.x;
								}


							}
							else if (g_Doppel.Position.y >= pPiece[i].pos.y + PUZZLE_HEIGHT / 2)
							{
								bool hitflag2 = DoppelPieceOpen(pPiece[i], i, UP);

								if (!hitflag2)
								{
									//g_Player.sp.y += 0.2;//����
								}
								else
								{

									g_Doppel.fall = true;
									//g_Player.sp.y = 0;
									//g_Player.getfall = true;
									g_Doppel.frame = 50;
									//g_Player.sp.y += 0.2;//����
								}

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
		g_Doppel.Position = pos;
		g_Doppel.size = size;
		g_Doppel.PieceIndex = index;
		g_Doppel.UseFlag = true;
	}
}
void DeleteDoppelGanger(int index) {
	if (g_Doppel.UseFlag && g_Doppel.PieceIndex == index) {
		g_Doppel.UseFlag = false;
	}
}