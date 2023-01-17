/*================================================================================

	��������[ray.h]

												Author: ꎓ� ��o
												 Date : 2023/01/09
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "ray.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"

#include "cursor.h"
#include "issuer.h"
#include "block.h"
#include "MapChip.h"

//**************************************************
// �}�N����`
//**************************************************
#define		RAY_MAX	16

//**************************************************
// �O���[�o���ϐ�
//**************************************************
RAY g_Ray[RAY_MAX];
static char* g_RayTextureName = (char*)"data\\texture\\yello.jpg";

//==================================================
// ������
//==================================================
void InitRay()
{
	// �e�l�̏�����
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		g_Ray[i].pos = D3DXVECTOR2(0.0f, 0.0f);				// ���W
		g_Ray[i].StartPos = D3DXVECTOR2(0.0f, 0.0f);		// �n�_���W
		g_Ray[i].EndPos = D3DXVECTOR2(0.0f, 0.0f);			// �I�_���W
		g_Ray[i].size = D3DXVECTOR2(1.0f, 10.0f);			// �T�C�Y
		g_Ray[i].dir = D3DXVECTOR2(0.0f, 0.0f);				// �������o���x�N�g��
		g_Ray[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Ray[i].texNo = LoadTexture(g_RayTextureName);		// �e�N�X�`���C���f�b�N�X
		g_Ray[i].rot = 0;									// �p�x

		g_Ray[i].PieceIndex = -1;							// �s�[�X�̓Y�����i�[
		g_Ray[i].IssuerIndex = -1;							// ���ˑ��u�̔ԍ�

		g_Ray[i].bUse = false;								// �g�p�t���O
	}
}

//==================================================
// �I���֐�
//==================================================
void UninitRay()
{
}

//==================================================
// �X�V�֐�
//==================================================
void UpdateRay()
{
	// �u���b�N���炤
	BLOCK* pBlock = GetBlock();
	// �s�[�X�����炤
	Piece* pPiece = GetPiece();
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		// �g�p��
		if (g_Ray[i].bUse) {
			int j = 0;
			g_Ray[i].EndPos = g_Ray[i].StartPos;
			while (1) {
				g_Ray[i].EndPos += g_Ray[i].dir;
				// ��ʊO�Ƃ̔���
				if (!CollisionBB(g_Ray[i].EndPos, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT))){
					break;
				}
				// �u���b�N�Ƃ̓����蔻��
				for (int i = 0; i < BLOCK_MAX; i++){
					if (CollisionBB(g_Ray[i].EndPos, pBlock[i].Position, D3DXVECTOR2(0.0f, 0.0f), pBlock[i].Size)) {
						break;
					}
				}
				// �s�[�X�Ƃ̓����蔻��
				for (int i = 0; i < PUZZLE_MAX; i++) {
					if (!CollisionBB(g_Ray[i].EndPos, pPiece[i].pos, D3DXVECTOR2(0.0f, 0.0f), pPiece[i].size)) {
						break;
					}
				}
				j++;
				if (j > 1000)break;
			}

			// ���������
			D3DXVECTOR2 Length = g_Ray[i].EndPos - g_Ray[i].StartPos;
			g_Ray[i].size.x = D3DXVec2Length(&Length);

			g_Ray[i].rot = atan2(Length.x, Length.y);

			g_Ray[i].pos.x = g_Ray[i].size.x / 2;
			g_Ray[i].pos.y = g_Ray[i].size.y / 2;
		}
	}
}

//==================================================
// �`��֐�
//==================================================
void DrawRay()
{
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		// �g�p��
		if (g_Ray[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Ray[i].texNo));

			SpriteDrawColorRotation(
				g_Ray[i].pos.x, g_Ray[i].pos.y, -0.1f,
				g_Ray[i].size.x, g_Ray[i].size.y, g_Ray[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, -1.0f, 1
			);
		}
	}
}

//==================================================
// �Z�b�g�֐�
//==================================================
void SetRay(D3DXVECTOR2 SPos, D3DXVECTOR2 dir, int INo, int PNo)
{
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		// �g�p���ł͂Ȃ�
		if (!g_Ray[i].bUse) {
			g_Ray[i].StartPos = SPos;
			g_Ray[i].dir = dir;
			g_Ray[i].IssuerIndex = INo;
			g_Ray[i].PieceIndex = PNo;
			g_Ray[i].bUse = true;

			break;
		}
	}
}

//==================================================
// �f���[�g�֐�
//==================================================
void DeleteRayP(int PNo)
{
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		// �s�[�X�̔ԍ�������
		if (g_Ray[i].PieceIndex == PNo) {
			g_Ray[i].bUse = false;
		}
	}
}

void DeleteRay(int INo)
{
	// �S�`�F�b�N
	for (int i = 0; i < RAY_MAX; i++) {
		// �s�[�X�̔ԍ�������
		if (g_Ray[i].IssuerIndex == INo) {
			g_Ray[i].bUse = false;
		}
	}
}




