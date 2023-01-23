/*==============================================================================

   �g�Q�u���b�N [thorn_block.cpp]
														 Author		:���Ԍ��C
														 Date		:2022/11/09
														 �ŏI�X�V	:2022/11/224
==============================================================================*/

#include "thorn_block.h"
#include "main.h"
#include "polygon.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
static THORNBLOCK g_ThornBlock[THORN_BLOCK_MAX];
static ID3D11ShaderResourceView* g_textureThornBlock;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_TextureNameThornBlock = (char*)"data\\texture\\Spikes.png";

//THORNBLOCK InitData[] =
//{
//	{true,D3DXVECTOR2(THORN_BLOCK_W,THORN_BLOCK_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
//};


//=============================================================================
//����������
//=============================================================================
HRESULT InitThornBlock()
{
	//srand(time(NULL));

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		g_ThornBlock[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].texno = LoadTexture(g_TextureNameThornBlock);
		g_ThornBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ThornBlock[i].rot = 0.0f;
		g_ThornBlock[i].uv_w = 1.0f / 1.0f;
		g_ThornBlock[i].uv_h = 1.0f / 1.0f;
		g_ThornBlock[i].PaternNo = 0;
		g_ThornBlock[i].NumPatern = 1;
		g_ThornBlock[i].PieceIndex = -1;
		g_ThornBlock[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void UninitThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{

	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++){
		if (g_ThornBlock[i].UseFlag){
			//SetWorldViewProjection2D();



			//�e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));
			//�X�v���C�g��\��
			SpriteDrawColorRotation(
				g_ThornBlock[i].Postion.x, 
				g_ThornBlock[i].Postion.y + 1.0f, 
				0.0f,
				g_ThornBlock[i].Size.x, 
				-g_ThornBlock[i].Size.y + 4.0f,
				g_ThornBlock[i].rot,
				g_ThornBlock[i].col, 
				g_ThornBlock[i].PaternNo,
				g_ThornBlock[i].uv_w,
				g_ThornBlock[i].uv_h,
				g_ThornBlock[i].NumPatern
			);

		}
	}
}
void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (!g_ThornBlock[i].UseFlag) {
			switch (direction) {
			case 0:g_ThornBlock[i].rot = (direction + 2) * 90;
				break;
			case 1:g_ThornBlock[i].rot = direction * 90;
				break;
			case 2:g_ThornBlock[i].rot = (direction - 2) * 90;
				break;
			case 3:g_ThornBlock[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_ThornBlock[i].Postion = pos;
			g_ThornBlock[i].Size = size;
			g_ThornBlock[i].PieceIndex = PieceNo;
			g_ThornBlock[i].UseFlag = true;
			break;
		}
	}
 }
void DeleteThornBlock(int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (g_ThornBlock[i].UseFlag) {
			if (g_ThornBlock[i].PieceIndex == PieceNo){
				g_ThornBlock[i].UseFlag = false;
			}
		}
	}
}

 //�Ȃ񂩓�������̂ŃR�����g�A�E�g���Ă����܂�
 // 
//int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s)
//{
//	//PUZZLE* pPuzzle = GetPuzzle();
//
//	for (int i = 0; i < THORN_BLOCK_MAX; i++)
//	{
//		if (!g_ThornBlock[i].UseFlag)
//		{
//
//			g_ThornBlock[i].Postion = Pos;
//			g_ThornBlock[i].Size = s;
//			g_ThornBlock[i].UseFlag = true;
//			return i;
//
//		}
//
//
//	}

//}

//=============================================================================
//�Q�b�g�֐�
//=============================================================================
THORNBLOCK* GetThornBlock()
{
	return g_ThornBlock;
}