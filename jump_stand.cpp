
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "jump_stand.h"
#include "player.h"
#include "collision.h"
#include "block.h"
#include "puzzle.h"
#include "MapChip.h"
#include"mouse.h"
#include"sound.h"

//-------�z��ɂ��Ăق������i�}�b�v�`�b�v�̓s����K�v�j-------
static JUMPSTAND g_JumpStand[JUMPSTAND_MAX];
//------------------------------------------------------------
static PLAYER* p_Player;
static BLOCK* p_Block;

static ID3D11ShaderResourceView* g_textureBlock;	//�摜�ꖇ�ň�̕ϐ����K�v
//static char* g_textureName_Block= (char*)"data\\texture\\JumpStand.jpg";	//�e�N�X�`���t�@�C���p�X
static char* g_textureName_Block = (char*)"data\\texture\\jumpstand.png";	//�e�N�X�`���t�@�C���p�X
static int	  g_TextureNo = 0;	//�v���C���[�p�e�N�X�`���̎��ʎq
static int g_JumpStandSoundNo = 0;
static char g_JumpStandSoundName[] = "data\\SoundData\\SE\\�^�C�v���C�^�[.wav";

HRESULT InitJumpStand()
{
	p_Player = GetPlayer();
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		g_TextureNo = LoadTexture(g_textureName_Block);

		g_JumpStand[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_JumpStand[i].size = D3DXVECTOR2(JUMPSTAND_SIZE, JUMPSTAND_SIZE);
		g_JumpStand[i].rot = 0.0f;
		g_JumpStand[i].PieceIndex = -1;

		g_JumpStand[i].UseJumpStand = false;
		g_JumpStand[i].JumpStandFlag = false;

		g_JumpStand[i].JumpStandFlag = false;
		g_JumpStandSoundNo = LoadSound(g_JumpStandSoundName);
		return S_OK;
	}
}

void UninitJumpStand()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock = NULL;
	}

	StopSound(g_JumpStandSoundNo);
}

void UpdateJumpStand()
{
	//BLOCK* pCipBlock = GetChipBlock();
	MOUSE* pMouse = GetMouse();
	p_Player = GetPlayer();
	p_Block = GetChipBlock();

	if (!pMouse->UseFlag)
	{


		for (int i = 0; i < JUMPSTAND_MAX; i++)
		{
			if (g_JumpStand[i].UseJumpStand)
			{
				g_JumpStand[i].oldpos = g_JumpStand[i].pos;

				if (g_JumpStand[i].rot == 90 || g_JumpStand[i].rot == 270) {
					g_JumpStand[i].rot = 180.0f;
				}

				if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
					p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
					p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
					p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
				{
					g_JumpStand[i].sp = p_Player->sp;
					g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;

				}
				//�v���C���[�E�E����u���b�N��
				if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
					p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
					p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
					p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
				{
					g_JumpStand[i].sp = p_Player->sp;
					g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;
				}


				if (g_JumpStand[i].GetJumpStand)
				{
					g_JumpStand[i].sp = p_Player->sp;
					g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;
				}

				{
					g_JumpStand[i].pos.y--;


					p_Block = GetChipBlock();

					for (int j = 0; j < BLOCK_CHIP_MAX; j++)
					{
						if ((p_Block + j)->UseFlag)
						{
							if (g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].oldpos.y - g_JumpStand[i].size.y / 2 >= (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.y = g_JumpStand[i].oldpos.y;

							}
							if (g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].oldpos.x + g_JumpStand[i].size.x / 2 <= (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.x = g_JumpStand[i].oldpos.x;
							}
							if (g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].oldpos.x - g_JumpStand[i].size.x / 2 >= (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
								g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
								g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
							{
								g_JumpStand[i].pos.x = g_JumpStand[i].oldpos.x;
							}


						}
					}




					//�v���C���[���E��jumpstand
					if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
						p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
						p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 &&
						p_Player->oldpos.y - p_Player->size.y / 2 >= g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
					{
						g_JumpStand[i].JumpStandFlag = true;

						SetVolume(g_JumpStandSoundNo, 1.5f);
						
						PlaySound(g_JumpStandSoundNo, 0);

						p_Player->sp.y = 0.0f;
						g_JumpStand[i].JumpPower = 4.8f;
						//p_Player->sp.y = 5.0f;
						g_JumpStand[i].JumpGravity = 0.1f;
						
					}

					if (g_JumpStand[i].JumpStandFlag)
					{
						//p_Player->sp.y = 0.0f;

						if (g_JumpStand[i].JumpPower > -10.0f)
						{
							g_JumpStand[i].JumpPower -= g_JumpStand[i].JumpGravity;
							
						}
						p_Player->Position.y += g_JumpStand[i].JumpPower;
						//p_Player->Position.y -= p_Player->sp.y;


						for (int j = 0; j < BLOCK_CHIP_MAX; j++)
						{

							if ((p_Block + j)->UseFlag)
							{
								//��
								if (p_Player->Position.x + p_Player->size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
									p_Player->Position.x - p_Player->size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
									p_Player->Position.y - p_Player->size.y / 2 < (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 &&
									p_Player->oldpos.y - p_Player->size.y / 2 >= (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2)
								{
									g_JumpStand[i].JumpPower = 0.0f;
									p_Player->sp.y = 0.0f;
									//g_JumpStand[i].JumpGravity = 0.0f;
									p_Player->Position.y = (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 + p_Player->size.y / 2;
									g_JumpStand[i].JumpStandFlag = false;
								}
								if (p_Player->Position.x + p_Player->size.x / 2 > (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
									p_Player->Position.x - p_Player->size.x / 2 < (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
									p_Player->Position.y + p_Player->size.y / 2 > (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2 &&
									p_Player->oldpos.y + p_Player->size.y / 2 <= (p_Block + j)->Position.y - (p_Block + j)->Size.y / 2)
								{
									g_JumpStand[i].JumpPower = 0.0f;
									p_Player->sp.y = 0.0f;
									//g_JumpStand[i].JumpGravity = 0.0f;
									p_Player->Position.y = (p_Block + j)->Position.y + (p_Block + j)->Size.y / 2 + p_Player->size.y / 2;
									g_JumpStand[i].JumpStandFlag = false;

								}
							}
						}

					}

				}
			}
		}
	}
}

void DrawJumpStand()
{
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (g_JumpStand[i].UseJumpStand)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));

			SpriteDrawColorRotation(g_JumpStand[i].pos.x, g_JumpStand[i].pos.y,-0.1f,
				g_JumpStand[i].size.x, g_JumpStand[i].size.y, g_JumpStand[i].rot, D3DXCOLOR(3.0f, 0.0f, 0.0f, 1.0f),
				0, 1.0f, 1.0f, 1);
		}
	}
}

void SetJumpStand(D3DXVECTOR2 p)
{
	for (int i = 0; i < JUMPSTAND_MAX; i++) {

		if (!g_JumpStand[i].UseJumpStand)
		{

			g_JumpStand[i].pos = p;
			g_JumpStand[i].size = D3DXVECTOR2(BLOCK_CHIP_SIZE, BLOCK_CHIP_SIZE);

			g_JumpStand[i].UseJumpStand = true;
			g_JumpStand[i].JumpStandFlag = false;
			break;
		}
	}
}

JUMPSTAND* GetJumpStand()
{
	return g_JumpStand;
}

bool Collition_JumpStand()
{
	p_Player = GetPlayer();
	//p_Block= GetBlock();
	for (int i = 0; i < JUMPSTAND_MAX; i++)
	{
		//�v���C���[���E����u���b�N�E
		if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
			p_Player->oldpos.x + p_Player->size.x / 2 <= g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
			p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
			p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
		{
			p_Player->Position = p_Player->oldpos;
		}
		//�v���C���[�E�E����u���b�N��
		if (p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
			p_Player->oldpos.x - p_Player->size.x / 2 >= g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
			p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
			p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
		{
			p_Player->Position = p_Player->oldpos;
		}

		//�v���C���[���E����u���b�N��
		if (p_Player->Position.x + p_Player->size.x / 2 > g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 &&
			p_Player->Position.x - p_Player->size.x / 2 < g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 &&
			p_Player->Position.y - p_Player->size.y / 2 < g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 &&
			p_Player->oldpos.y - p_Player->size.y / 2 >= g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2)
		{
			return true;
		}

		return false;
	}
}

void SetJumpStand(D3DXVECTOR2 pos, D3DXVECTOR2 size,int direction, int PieceNo) {
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (!g_JumpStand[i].UseJumpStand) {
			switch (direction)
			{
			case 0:g_JumpStand[i].rot = (direction + 2) * 90;
				break;
			case 1:g_JumpStand[i].rot = direction * 90;
				break;
			case 2:g_JumpStand[i].rot = (direction - 2) * 90;
				break;
			case 3:g_JumpStand[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_JumpStand[i].pos = pos;
			g_JumpStand[i].size = size;
			g_JumpStand[i].PieceIndex = PieceNo;
			g_JumpStand[i].UseJumpStand = true;
			break;
		}
	}
}

void DeleteJumpStand(int PieceNo) {
	//�z��ɂ��Ȃ��ƃ}�b�v��ɑ��݂���W�����v��S�������邱�ƂɂȂ�
	//�����������̂� PieceNo�Ԗ� �̃s�[�X�ɑ��݂���W�����v��̂�
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (g_JumpStand[i].UseJumpStand) {
			if (g_JumpStand[i].PieceIndex == PieceNo)
			{
				g_JumpStand[i].UseJumpStand = false;

			}
		}
	}
}

//bool Player_Push_JumpStand()
//{
//
//}
