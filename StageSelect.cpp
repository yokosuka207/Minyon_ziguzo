//=============================================================================
//
//	�X�e�[�W�Z���N�g����[StageSelect.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/11/25
//=============================================================================

#include "texture.h"
#include "sprite.h"
#include "StageSelect.h"
//#include "input.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "xmouse.h"

#include "cursor.h"
#include "MapChip.h"
#include "scene.h"
#include "player.h"
#include "fade.h"
//*****************************************************************************
//	�}�N����`
//*****************************************************************************

#define STAIRS_LEFT	75
#define STAIRS_RIGHT	285



//*****************************************************************************
//	�O���[�o���ϐ�
//*****************************************************************************
static STAGESELECT g_StageSelect[STAGE_MAX];
static STAGESELECT g_StageSelectBlack[STAGE_MAX];
static STAGESELECT_BG g_StageSelectBg;
static STAGESELECT_BG g_StageSelectfence[21];
static STAGESELECT_BLOCK g_StageSelectBlock[3];
static STAGESELECT_STAIRS g_StageSelectStairs[12];

static ID3D11ShaderResourceView* g_StageSelectTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectTextureName = (char*)"data\\texture\\�h�A.png";	//�e�N�X�`���t�@�C���p�X
static ID3D11ShaderResourceView* g_StageSelect2Texture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelect2TextureName = (char*)"data\\texture\\black.png";	//�e�N�X�`���t�@�C���p�X
static ID3D11ShaderResourceView* g_StageSelectTextureBg;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectBgTextureName = (char*)"data\\texture\\�X���[�W�Z���N�g�w�i.png";	//�e�N�X�`���t�@�C���p�X
static ID3D11ShaderResourceView* g_StageSelectTextureBlock;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectBlockTextureName = (char*)"data\\texture\\�X�e�[�W�I����.png";	//�e�N�X�`���t�@�C���p�X
static ID3D11ShaderResourceView* g_StageSelectTextureStairs;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectStairsTextureName = (char*)"data\\texture\\jumpstand.png";	//�e�N�X�`���t�@�C���p�X
static ID3D11ShaderResourceView* g_StageSelectTexturefence;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_StageSelectfenceTextureName = (char*)"data\\texture\\��.png";	//�e�N�X�`���t�@�C���p�X


static PLAYER ply;
static ID3D11ShaderResourceView* g_StageSelectTexturePly;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNamePly = (char*)"data\\texture\\�v���C���[.png";

static int TexNo;	//�e�N�X�`���i�[

int StageNo = 0;

static bool OneFlag =true;	//ge�Q�[���̍ŏ����ǂ���



//-----------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------
HRESULT InitStageSelect() {
	StageNo = 0;

	g_StageSelectBg.pos = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	g_StageSelectBg.size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_StageSelectBg.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_StageSelectBg.texno = LoadTexture(g_StageSelectBgTextureName);

	int a = 0;
	int b = 0;

	for (int i = 0; i < 21; i++)
	{
		if (i % 7 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		g_StageSelectfence[i].pos = D3DXVECTOR2(250.0f+(170.0f*b), 220.0f + (250 * a));
		g_StageSelectfence[i].size = D3DXVECTOR2(170.0f, 110.0f);
		g_StageSelectfence[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectfence[i].texno = LoadTexture(g_StageSelectfenceTextureName);
		b++;
	}


	for (int i = 0; i < 3; i++)
	{
		g_StageSelectBlock[i].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, 250.0f + (250 * i));
		g_StageSelectBlock[i].size = D3DXVECTOR2(SCREEN_WIDTH, 15.0f);
		g_StageSelectBlock[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectBlock[i].texno = LoadTexture(g_StageSelectBlockTextureName);

	}
	 a = 0;
	 b = 0;

	for (int i = 0; i < 12; i++)
	{
		if (i % 6 == 0 && i != 0)
		{
			a++;
			b = 0;
		}

		g_StageSelectStairs[i].pos = D3DXVECTOR2(90.0f+(b*25.0f), 270.0f+(b*40.0f) + (250 * a));
		g_StageSelectStairs[i].size = D3DXVECTOR2(30.0f, 40.0f);
		g_StageSelectStairs[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_StageSelectStairs[i].texno = LoadTexture(g_StageSelectStairsTextureName);
		b++;


	}

	//g_Texturenumber = LoadTexture(g_StageSelectStairsTextureName);


	 a = 0;
	b = 0;


	if (OneFlag)
	{


		for (int i = 0; i < STAGE_MAX; i++)
		{
			if (i % 7 == 0 && i != 0)
			{
				a++;
				b = 0;
			}
			//�h�A
			g_StageSelect[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (180.0f) + (250.0f * a));
			g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);
			g_StageSelect[i].UseFlag = true;
			g_StageSelect[i].StagePieceIndex = i;
			g_StageSelect[i].StageUseFlag = true;
			g_StageSelect[i].texno = LoadTexture(g_StageSelectTextureName);


			g_StageSelectBlack[i].pos = D3DXVECTOR2((300.0f) + (120.0f * b), (175.0f) + (250.0f * a));
			g_StageSelectBlack[i].size = D3DXVECTOR2(120.0f, 150.0f);
			g_StageSelectBlack[i].texno = LoadTexture(g_StageSelect2TextureName);
			b++;
			if (i == 0)
			{
				g_StageSelect[i].StageUseFlag = true;
				g_StageSelect[i].size = D3DXVECTOR2(140.0f, 150.0f);

			}

		}
		TexNo = LoadTexture(g_StageSelect2TextureName);

		OneFlag = false;
	}


	ply.Position = D3DXVECTOR2(30.0f, 30.0f);
	ply.OneOldpos = ply.oldpos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	ply.sp = D3DXVECTOR2(0.0f, 8.0f);
	ply.size = D3DXVECTOR2(100.0f, 117.0f);
	ply.col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
	ply.rot = 0.0f;
	ply.UseFlag = true;
	ply.jump = false;
	//ply.getjump = false;
	ply.GetJumpStand = false;		//�W�����v��p
	ply.fall = false;
	ply.getfall = false;
	ply.WarpFlag = false;
	ply.isGround = true;
	ply.isSheerFloors = false;
	ply.isSheerFloorsUse = false;
	ply.isHigh = false;
	ply.isMoveBlock = false;
	ply.texno = LoadTexture(g_TextureNamePly);

	ply.PaternNo = 0;//�p�^�[���ԍ�
	ply.uv_w = PLAYER_UV_W;//���T�C�Y
	ply.uv_h = PLAYER_UV_H;//�c�T�C�Y
	ply.NumPatern = 4;//������

	ply.hp = 3;
	ply.frame = 0;
	ply.CoolTime = PLAYER_COOLTIME;
	ply.PieceIndex = 0;



	return S_OK;
}

//-----------------------------------------------------------------------------
//	�I������
//-----------------------------------------------------------------------------
void UninitStageSelect() {
	if (g_StageSelectTexture) {
		g_StageSelectTexture->Release();
		g_StageSelectTexture = NULL;
	}
}

//-----------------------------------------------------------------------------
//	�X�V����
//-----------------------------------------------------------------------------
void UpdateStageSelect() {

	if (ply.UseFlag == true)
	{
		if (ply.isGround)
		{


			//�ړ�
			if (Keyboard_IsKeyDown(KK_RIGHT))//�E�L�[
			{//������Ă���Ƃ��̏���
				ply.sp.x = 2.0f;
				ply.PaternNo += 0.25f;
				if (ply.isHigh)
				{
					ply.sp.x = 3.0f;
					ply.sp.y = 4.0f;

				}

				// ������ς���
				ply.dir = PLAYER_DIRECTION::RIGHT;
				ply.uv_w = PLAYER_UV_W;
			}
			else if (Keyboard_IsKeyDown(KK_LEFT))//���L�[
			{//������Ă���Ƃ��̏���
				ply.sp.x = -2.0f;
				ply.PaternNo -= 0.25f;
				if (ply.isHigh)
				{
					ply.sp.x = -3.0f;
					ply.sp.y = -3.5f;

				}

				// ������ς���
				ply.dir = PLAYER_DIRECTION::LEFT;
				ply.uv_w = -PLAYER_UV_W;
			}
			else
			{
				if (ply.isHigh)
				{
					ply.sp.y = 0.0f;
				}
				ply.sp.x = 0;

			}
		}
		if (STAIRS_LEFT < ply.Position.x && ply.Position.x < STAIRS_RIGHT) {
			if (Keyboard_IsKeyDown(KK_DOWN))//�E�L�[
			{

				if (ply.Position.y < SCREEN_HEIGHT - 110.0f)
				{
					ply.sp.x = 0;

					ply.sp.y = 5.0f;
					ply.isGround = false;

				}
			}
		}

		// �A�j���[�V�����p�^�[���ԍ���0�`15�͈͓̔��ɂ���
		if (ply.PaternNo > 15) { ply.PaternNo -= 15; }
		if (ply.PaternNo < 0) { ply.PaternNo += 15; }

		ply.oldpos = ply.Position;
		ply.Position += ply.sp;




		for (int i = 0; i < 3; i++)
		{
			{
				//�v���C���[���E�u���b�N�E
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.oldpos.x + ply.size.x / 2 <= g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2)
				{
					ply.Position.x = g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 - ply.size.x / 2;
				}
				//�v���C���[�E�E�u���b�N��
				if (ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.oldpos.x - ply.size.x / 2 >= g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 3 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 3 &&
					ply.Position.y - ply.size.y / 3 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 3)
				{
					ply.Position.x = g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 + ply.size.x / 2;
				}
				if (ply.isGround)
				{
					//�v���C���[��E�u���b�N��,���n����
					if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
						ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
						ply.Position.y + ply.size.y / 2 > g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 &&
						ply.oldpos.y + ply.size.y / 2 <= g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2)
					{
						ply.Position.y = g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 - ply.size.y / 2 - 0.02f;
						ply.jump = false;
						ply.fall = false;
						ply.WarpFlag = false;
						//ply.isGround = true;
						ply.sp.y = 0;
						ply.frame = 0;
						ply.isHigh = false;

					}
				}
				//�v���C���[���E�u���b�N��,��������
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectBlock[i].pos.x - g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectBlock[i].pos.x + g_StageSelectBlock[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 < g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2 &&
					ply.oldpos.y + ply.size.y / 2 >= g_StageSelectBlock[i].pos.y + g_StageSelectBlock[i].size.y / 2)
				{
					ply.Position.y = g_StageSelectBlock[i].pos.y - g_StageSelectBlock[i].size.y / 2 - ply.size.y / 2 - 0.02f;
					ply.isHigh = false;
					ply.sp.y = 0.0f;
					ply.fall = true;
					ply.getfall = true;
					ply.frame = 50;
				}
			}
		}
		for (int i = 0; i < 12; i++)
		{
			{
				//�v���C���[���E�u���b�N�E
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.oldpos.x + ply.size.x / 2 <= g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2)
				{
					//ply.Position.x = g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 - ply.size.x / 2;
				}
				//�v���C���[�E�E�u���b�N��
				if (ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.oldpos.x - ply.size.x / 2 >= g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 3 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 3 &&
					ply.Position.y - ply.size.y / 3 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 3)
				{
					//ply.Position.x = g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 + ply.size.x / 2;
					//ply.sp = D3DXVECTOR2(0.0f,-4.0f);
					if (Keyboard_IsKeyDown(KK_UP))
					{
						ply.isHigh = true;	//��ɏ��

					}
				}

				//�v���C���[��E�u���b�N��,���n����
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y + ply.size.y / 2 > g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 &&
					ply.oldpos.y + ply.size.y / 2 <= g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2)
				{
					ply.isGround = true;

					ply.Position.y = g_StageSelectStairs[i].pos.y - g_StageSelectStairs[i].size.y / 2 - ply.size.y / 2 - 0.02f;
					ply.jump = false;
					ply.fall = false;
					ply.WarpFlag = false;
					//ply.isGround = true;
					ply.sp.y = 4.0f;
					ply.frame = 0;
				}
				//�v���C���[���E�u���b�N��,��������
				if (ply.Position.x + ply.size.x / 2 > g_StageSelectStairs[i].pos.x - g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.x - ply.size.x / 2 < g_StageSelectStairs[i].pos.x + g_StageSelectStairs[i].size.x / 2 &&
					ply.Position.y - ply.size.y / 2 < g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2 &&
					ply.oldpos.y - ply.size.y / 2 >= g_StageSelectStairs[i].pos.y + g_StageSelectStairs[i].size.y / 2)
				{
					ply.fall = true;
					ply.getfall = true;
					ply.frame = 50;
				}
			}
		}


	}


	


	//�X�e�[�W�I��

	for (int i = 0; i < STAGE_MAX; i++)
	{
		if (g_StageSelect[i].StageUseFlag)
		{
			if (ply.Position.x - ply.size.x / 2 > g_StageSelect[i].pos.x - g_StageSelect[i].size.x / 2 &&
				ply.Position.x + ply.size.x / 2 < g_StageSelect[i].pos.x + g_StageSelect[i].size.x / 2 &&
				ply.Position.y + ply.size.y / 2 > g_StageSelect[i].pos.y - g_StageSelect[i].size.y / 2 &&
				ply.Position.y - ply.size.y / 2 < g_StageSelect[i].pos.y + g_StageSelect[i].size.y / 2)
			{


				if (Keyboard_IsKeyTrigger(KK_A)) {
					StageNo = i;
					//SetScene(SCENE::SCENE_GAME);
					StartFade(FADE::FADE_OUT);
					break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	�`�揈��
//-----------------------------------------------------------------------------
void DrawStageSelect() {
	

	{	//�w�i�|���S���\��
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBg.texno));
		SpriteDrawColorRotation(
			g_StageSelectBg.pos.x, g_StageSelectBg.pos.y, 0.5f, g_StageSelectBg.size.x, g_StageSelectBg.size.y
			, 0.0f, g_StageSelectBg.color, 0, 1.0f, 1.0f, 1);
	}
	for (int i = 0; i < 3; i++)
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectBlock[i].texno));

		SpriteDrawColorRotation(
			g_StageSelectBlock[i].pos.x, g_StageSelectBlock[i].pos.y, 0.5f, g_StageSelectBlock[i].size.x, g_StageSelectBlock[i].size.y
			, 0.0f, g_StageSelectBlock[i].color, 0, 1.0f, 1.0f, 1);

	}

	//�K�i
	for (int i = 0; i < 12; i++)
	{
		SetWorldViewProjection2D();

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectStairs[i].texno));

		SpriteDrawColorRotation(
			g_StageSelectStairs[i].pos.x, g_StageSelectStairs[i].pos.y, 0.5f, g_StageSelectStairs[i].size.x+10, g_StageSelectStairs[i].size.y+10
			, 0.0f, g_StageSelectStairs[i].color, 0, 1.0f, 1.0f, 1);

	}

	

		for (int i = 0; i < STAGE_MAX; i++)
		{

		
		SetWorldViewProjection2D();
		if (g_StageSelect[i].StageUseFlag)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelect[i].texno));

		}
		else
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TexNo));

		}

		//g_StageSelect[i].pos.x = g_SelectDistance;

			SpriteDrawColorRotation(
				g_StageSelect[i].pos.x, g_StageSelect[i].pos.y - 10, 0.0f,
				g_StageSelect[i].size.x / 2, g_StageSelect[i].size.y,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0,
				1.0f,
				1.0f,
				1
			);
			//g_StageSelect[i].pos.x -= 30;
		
		}

		if (ply.UseFlag == true)
		{
			SetWorldViewProjection2D();

			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ply.texno));
			//�X�v���C�g��\��
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(ply.Position.x, ply.Position.y, -0.0f, ply.size.x, ply.size.y, ply.rot, ply.col, ply.PaternNo, ply.uv_w, ply.uv_h, ply.NumPatern);
		}

		for (int i = 0; i < 21; i++)
		{

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StageSelectfence[i].texno));
			SpriteDrawColorRotation(
				g_StageSelectfence[i].pos.x, g_StageSelectfence[i].pos.y, 0.5f, g_StageSelectfence[i].size.x, g_StageSelectfence[i].size.y
				, 0.0f, g_StageSelectfence[i].color, 0, 1.0f, 1.0f, 1);

		}

	
}

//-----------------------------------------------------------------------------
//	�X�e�[�W�Z�b�g�֐�
//-----------------------------------------------------------------------------
void SetStageSelect(int a) {

	

}
//-----------------------------------------------------------------------------
//	�X�e�[�W�Z���N�g���O���Œl��ς����悤�ɂ���֐�
//-----------------------------------------------------------------------------
STAGESELECT* GetSelect() {
	return g_StageSelect;
}
int ReturnStageNo()
{
	return StageNo;
}

