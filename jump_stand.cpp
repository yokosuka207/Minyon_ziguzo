
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "jump_stand.h"
#include "player.h"
#include "collision.h"
#include "block.h"
#include "puzzle.h"
#include "MapChip.h"

//-------�z��ɂ��Ăق������i�}�b�v�`�b�v�̓s����K�v�j-------
static JUMPSTAND g_JumpStand[JUMPSTAND_MAX];
//------------------------------------------------------------
static PLAYER* p_Player;
static BLOCK* p_Block;

static ID3D11ShaderResourceView* g_textureBlock;	//�摜�ꖇ�ň�̕ϐ����K�v
//static char* g_textureName_Block= (char*)"data\\texture\\JumpStand.jpg";	//�e�N�X�`���t�@�C���p�X
static char* g_textureName_Block= (char*)"data\\texture\\jump.png";	//�e�N�X�`���t�@�C���p�X
static int	  g_TextureNo = 0;	//�v���C���[�p�e�N�X�`���̎��ʎq

HRESULT InitJumpStand()
{
	p_Player = GetPlayer();
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		g_TextureNo = LoadTexture(g_textureName_Block);

		g_JumpStand[i].pos = D3DXVECTOR2(330.0f, 245.0f);
		g_JumpStand[i].size = D3DXVECTOR2(JUMPSTAND_SIZE, JUMPSTAND_SIZE);

		g_JumpStand[i].PieceIndex = -1;

		g_JumpStand[i].UseJumpStand = false;
		g_JumpStand[i].JumpStandFlag = false;

		return S_OK;
	}
}

void UninitJumpStand()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock= NULL;
	}
}

void UpdateJumpStand()
{
	for (int i = 0; i < JUMPSTAND_MAX; i++) {

		g_JumpStand[i].oldpos = g_JumpStand[i].pos;

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

		if (p_Player->GetJumpStand)
		{
			g_JumpStand[i].sp = p_Player->sp;
			g_JumpStand[i].pos.x += g_JumpStand[i].sp.x;
		}

		else
		{
			g_JumpStand[i].pos.y++;

			p_Block = GetChipBlock();

			for (int i = 0; i < BLOCK_CHIP_MAX; i++)
			{
				if ((p_Block + i)->UseFlag)
				{
					if (g_JumpStand[i].pos.x + g_JumpStand[i].size.x / 2 >= (p_Block + i)->Position.x - (p_Block + i)->Size.x / 2 &&
						g_JumpStand[i].pos.x - g_JumpStand[i].size.x / 2 <= (p_Block + i)->Position.x + (p_Block + i)->Size.x / 2 &&
						g_JumpStand[i].pos.y + g_JumpStand[i].size.y / 2 >= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 &&
						g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 <= (p_Block + i)->Position.y + (p_Block + i)->Size.y / 2)
					{
						g_JumpStand[i].pos.y--;
					}

				}
			}
		}

		if (g_JumpStand[i].UseJumpStand)
		{

			if (Collition_JumpStand())
			{
				g_JumpStand[i].JumpStandFlag = true;

				g_JumpStand[i].JumpPower = 17.0f;
				g_JumpStand[i].JumpGravity = 0.2f;
			}

			if (g_JumpStand[i].JumpStandFlag)
			{
				if (g_JumpStand[i].JumpPower > -10.0f)
				{
					g_JumpStand[i].JumpPower -= g_JumpStand[i].JumpGravity;
				}
				p_Player->Position.y -= g_JumpStand[i].JumpPower;

			for (int i = 0; i < BLOCK_MAX; i++)
			{
				p_Player = GetPlayer();
				p_Block = GetBlock();

					if ((p_Block + i)->UseFlag)
					{
						//��
						if (p_Player->Position.x + p_Player->size.x / 2 >= (p_Block + i)->Position.x - (p_Block + i)->Size.x / 2 &&
							p_Player->Position.x - p_Player->size.x / 2 <= (p_Block + i)->Position.x + (p_Block + i)->Size.x / 2 &&
							p_Player->Position.y + p_Player->size.y / 2 >= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 &&
							p_Player->oldpos.y   + p_Player->size.y / 2 <= (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2)
						{
							p_Player->Position.y = (p_Block + i)->Position.y - (p_Block + i)->Size.y / 2 - p_Player->size.y / 2;
							g_JumpStand[i].JumpStandFlag = false;
							g_JumpStand[i].JumpPower = 0.0f;
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

			SpriteDrawColorRotation(g_JumpStand[i].pos.x, g_JumpStand[i].pos.y,
				g_JumpStand[i].size.x, g_JumpStand[i].size.y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
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
			g_JumpStand[i].size = D3DXVECTOR2(JUMPSTAND_SIZE, JUMPSTAND_SIZE);

			g_JumpStand[i].UseJumpStand = true;
			g_JumpStand[i].JumpStandFlag = false;
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
	p_Block= GetBlock();
	for (int i = 0; i < JUMPSTAND_MAX; i++) {

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
			p_Player->Position.y + p_Player->size.y / 2 > g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2 &&
			p_Player->oldpos.y + p_Player->size.y / 2 <= g_JumpStand[i].pos.y - g_JumpStand[i].size.y / 2)
		{
			return true;
		}

		return false;
	}
}

void SetJumpStand(D3DXVECTOR2 pos,D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < JUMPSTAND_MAX; i++) {
		if (!g_JumpStand[i].UseJumpStand) {
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
			g_JumpStand[i].UseJumpStand = false;
		}
	}
}

//bool Player_Push_JumpStand()
//{
//
//}