/*================================================================================
	
	�C���x���g������[inventory.cpp]
		
												Author: ꎓ� ��o
												 Date : 2022/11/02
----------------------------------------------------------------------------------
Update:
	2022/11/01 Saito
	2022/11/02 Saito
	2022/11/04 Saito
	2022/11/16 Saito
================================================================================*/
#include "inventory.h"
#include "texture.h"
#include "sprite.h"
//#include "input.h"
#include "xinput.h"

#include "puzzle.h"
#include "MapChip.h"
#include"mouse.h"
//**************************************************
// �}�N����`
//**************************************************
#define INVENTORY_MAX			(4)
#define INVENTORY_SIZE_X		(96)
#define INVENTORY_SIZE_Y		(96)
#define INVENTORY_BIGSIZE_X		(120)
#define INVENTORY_BIGSIZE_Y		(120)

#define INVENTORY_BOX_SIZE_Y	(INVENTORYBG_SIZE_Y / INVENTORY_MAX)
#define INVENTORY_POS_X			(INVENTORYBG_POS_X)
#define INVENTORY_POS_Y			INVENTORY_BOX_SIZE_Y + INVENTORY_BOX_SIZE_Y / 2		// ���Ԗڂ������̒l�Ɋ|����


//**************************************************
// �v���g�^�C�v�錾
//**************************************************
//**************************************************
// �O���[�o���ϐ�
//**************************************************
static KEEP_PUZZLE_BG	g_InventoryBG;
static KEEP_PUZZLE		g_Inventory[INVENTORY_MAX];

// �e�N�X�`���̖��O
static char* g_InventoryBGTextureName = (char*)"data\\texture\\white.jpg";
static char* g_InventoryTextureName = (char*)"data\\texture\\blue.png";



//==================================================
// ������
//==================================================
HRESULT InitInventory() 
{
	// �e�e�N�X�`���̃��[�h
	float BGTexNo = LoadTexture(g_InventoryBGTextureName);
	float TexNo = LoadTexture(g_InventoryTextureName);

	// �w�i�̏�����
	g_InventoryBG.pos = D3DXVECTOR2(INVENTORYBG_POS_X, INVENTORYBG_POS_Y);
	g_InventoryBG.size = D3DXVECTOR2(INVENTORYBG_SIZE_X, INVENTORYBG_SIZE_Y);
	g_InventoryBG.color = D3DXCOLOR(0.0f, 0.4f, 0.5f, 0.2f);
	g_InventoryBG.texno = BGTexNo;

	// �C���x���g�����̃p�Y���̏�����
	for (int i = 0; i < INVENTORY_MAX; i++) {
		g_Inventory[i].PieNo = -1;

		g_Inventory[i].pos = D3DXVECTOR2(0.0f, INVENTORY_POS_Y);
		g_Inventory[i].size = D3DXVECTOR2(INVENTORY_SIZE_X, INVENTORY_SIZE_Y);
		g_Inventory[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Inventory[i].texno = TexNo;
		
		g_Inventory[i].IsIn = true;
		g_Inventory[i].IsCatch = false;
		g_Inventory[i].IsUse = false;
	}

	// �f�o�b�O�p
	//SetInventory(0);
	//SetInventory(1);
	//SetInventory(2);
	//SetInventory(3);

	return S_OK;
}

//==================================================
// �I������
//==================================================
void UninitInventory()
{

}

//==================================================
// �X�V����
//==================================================
void UpdateInventory()
{
	MOUSE* pMouse = GetMouse();
		D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// �}�E�X�̍��W

	for (int i = 0; i < INVENTORY_MAX; i++) {
		if (g_Inventory[i].IsUse) {
			// �����蔻��p���W
			D3DXVECTOR2 min, max;		// min����, max�E��
			min = D3DXVECTOR2(g_Inventory[i].pos.x - g_Inventory[i].size.x, g_Inventory[i].pos.y - g_Inventory[i].size.y);
			max = D3DXVECTOR2(g_Inventory[i].pos.x + g_Inventory[i].size.x, g_Inventory[i].pos.y + g_Inventory[i].size.y);

			// �}�E�X�Ə����p�Y���̓����蔻��
			if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y) {
				// ������Ƃł�������
				g_Inventory[i].size = D3DXVECTOR2(INVENTORY_BIGSIZE_X, INVENTORY_BIGSIZE_Y);
			}
			else {
				// ���̃T�C�Y�ɖ߂�
				g_Inventory[i].size = D3DXVECTOR2(INVENTORY_SIZE_X, INVENTORY_SIZE_Y);
			}

			// ���ɒu���o�[�W����
			float bgmax_x = -INVENTORYBG_POS_X_REVESE + INVENTORYBG_SIZE_X * 2.3f;

			// ����(�}�E�X��Press)
			if (Mouse_IsLeftDown()) {
				//----------Trigger����----------
				if (!g_Inventory[i].IsCatch) {
					// �}�E�X�Ə����p�Y�����������Ă�����
					float x = MousePos.x - SCREEN_WIDTH / 2 ;
					float y = -MousePos.y + SCREEN_HEIGHT / 2;
					//if (MousePos.y < 400) {
					//	y = y * -1;
					//	y += 30.0f;
					//}
					if (min.x < (x) && max.x >(x) && min.y < (y) && max.y >(y)) {
						// �����s�[�X��S�����ׂĒN�����܂�Ă��Ȃ������玩�������܂�
						for (int j = 0; j < INVENTORY_MAX; j++) {
							if (g_Inventory[j].IsCatch == true) {
								break;
							}
							if (j == INVENTORY_MAX - 1) {
								// ���܂���!!!!
								g_Inventory[i].IsCatch = true;
							}
						}
					}
				}
				//--------------------------------

				//----------Press����----------
				// ���܂�Ă�����
				if (g_Inventory[i].IsCatch) {
					// �p�Y�����}�E�X�̈ʒu�Ɉړ�
					float x = MousePos.x - SCREEN_WIDTH / 2 ;
					float y = -MousePos.y + SCREEN_HEIGHT / 2;
					//y = y * -1;

					g_Inventory[i].pos.x = x;
					g_Inventory[i].pos.y = y;
					DeleteMapChip(g_Inventory[i].PieNo);
					SetInventoryMapChip(g_Inventory[i].pos, g_Inventory[i].PieNo, g_Inventory[i].PieNo);

				}
				//-----------------------------
			}
			else {
				//----------Release����----------
				if (g_Inventory[i].IsCatch) {
					// �����ʒu�ɖ߂�
					//g_Inventory[i].pos = D3DXVECTOR2(i * INVENTORY_POS_X, INVENTORY_POS_Y);		// ��ver
					g_Inventory[i].pos = g_Inventory[i].pos = D3DXVECTOR2(-550.0f, 100.0f * 2 - i * 150.0f);// ��ver
					DeleteMapChip(g_Inventory[i].PieNo);
					SetInventoryMapChip(g_Inventory[i].pos, g_Inventory[i].PieNo, g_Inventory[i].PieNo);

					// ���ꂽ!!!!
					g_Inventory[i].IsCatch = false;
				}
				//-------------------------------
			}

			// �����p�Y����UI�͈͂̓����蔻��
			if (g_Inventory[i].pos.x > bgmax_x) {
				// �O�ɏo����
				// �s�[�X���o��
				//DeleteMapChip(g_Inventory[i].PieNo);
				//SetPieceMapChip(D3DXVECTOR2(pMouse->PosX,-pMouse->PosY), g_Inventory[i].PieNo);
				int Pieno = g_Inventory[i].PieNo;
				DeleteInventory(g_Inventory[i].PieNo);

				SetPieceMapChip(g_Inventory[i].pos, Pieno);

			}
		}
	}
}

//==================================================
// �`�揈��
//==================================================
void DrawInventory()
{
	SetWorldViewProjection2D();

	// �w�i�̕`��
	// �e�N�X�`���̐ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_InventoryBG.texno));
	// �u�����h
	SetBlendState(BLEND_MODE_SUBTRACT);
	// �l�p�`�̕`��
	SpriteDrawColorRotation(g_InventoryBG.pos.x, g_InventoryBG.pos.y,0.0f, g_InventoryBG.size.x, g_InventoryBG.size.y, 0.0f, g_InventoryBG.color, 1.0f, 1.0f, 1.0f, 1);
	// �u�����h���f�t�H�ɖ߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);

	// �C���x���g�����̃p�Y���̕`��
	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		if (g_Inventory[i].IsUse) {
			// �e�N�X�`���̐ݒ�
			//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Inventory[i].texno));
			// �l�p�`�̕`��
			//SpriteDrawColorRotation(g_Inventory[i].pos.x, g_Inventory[i].pos.y,0.1f, g_Inventory[i].size.x, g_Inventory[i].size.y, 0.0f, g_Inventory[i].color, 1.0f, 1.0f, 1.0f, 1);
		}
	}
}

//==================================================
// �Z�b�g�֐�
//==================================================
void SetInventory(int PieNo)
{
	{
		// �ێ�����p�Y���z��̒����m�F
		for (int i = 0; i < INVENTORY_MAX; i++) {
			// �g���Ă��Ȃ�������
			if (!g_Inventory[i].IsUse) {
				g_Inventory[i].PieNo = PieNo;

				g_Inventory[i].pos = D3DXVECTOR2(-550.0f, 100.0f*2 - i * 150.0f);
				SetInventoryMapChip(g_Inventory[i].pos, PieNo, PieNo);
				g_Inventory[i].IsUse = true;
				g_Inventory[i].IsCatch = true;

				break;
			}
		}
	}
}

//==================================================
// �Q�b�g�֐�
//==================================================
KEEP_PUZZLE * GetInventory()
{
	return g_Inventory;
}


//==================================================
// �Q�b�g�֐�
//==================================================
void DeleteInventory(int PieNo)
{
	for (int i = 0; i < INVENTORY_MAX; i++) {
		if (g_Inventory[i].IsUse)
		{
			if (g_Inventory[i].PieNo == PieNo) {
				DeleteMapChip(PieNo);
				g_Inventory[i].IsCatch = false;
				g_Inventory[i].PieNo = -1;
				g_Inventory[i].IsUse = false;

				break;
			}
		}
	}
}