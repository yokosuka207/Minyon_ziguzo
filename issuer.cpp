/*================================================================================

	�����o���I�u�W�F�N�g����[issuer.h]

												Author: ꎓ� ��o
												 Date : 2023/01/07
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "issuer.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "xinput.h"		// GamePad����
#include "xkeyboard.h"	// Keyboard����
#include "ray.h"

#include "mouse.h"

//**************************************************
// �}�N����`
//**************************************************
#define		ISSUER_MAX	4

//**************************************************
// �O���[�o���ϐ�
//**************************************************
ISSUER g_Issuer[ISSUER_MAX];
static char* g_IssuerTextureName = (char*)"data\\texture\\issuer.png";

//==================================================
// ������
//==================================================
void InitIssuer()
{
	// �e�l�̏�����
	// �S�`�F�b�N
	for (int i = 0; i < ISSUER_MAX; i++) {
		g_Issuer[i].pos = D3DXVECTOR2(0.0f, 0.0f);	// ���W
		g_Issuer[i].size = D3DXVECTOR2(1.0f, 1.0f);	// �T�C�Y
		g_Issuer[i].dir = D3DXVECTOR2(0.0f, 0.0f);		// �������o���x�N�g��
		g_Issuer[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Issuer[i].texNo = LoadTexture(g_IssuerTextureName);	// �e�N�X�`���C���f�b�N�X
		g_Issuer[i].rot = 0;	// �`��p�x

		g_Issuer[i].PieceIndex = -1; // �s�[�X�̓Y�����i�[

		g_Issuer[i].bAct = false;	// �쓮�t���O
		g_Issuer[i].bUse = false;	// �g�p�t���O
	}

	// �f�o�b�O�p

	SetIssuer(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(15.0f, 15.0f), 0, 0);
}

//==================================================
// �I���֐�
//==================================================
void UninitIssuer()
{
}

//==================================================
// �X�V�֐�
//==================================================
void UpdateIssuer()
{
	// �S�`�F�b�N
	for (int i = 0; i < ISSUER_MAX; i++) {
		// �g�p��
		if (g_Issuer[i].bUse) {
			DeleteRay(i);
			if (g_Issuer[i].bAct) {
				SetRay(g_Issuer[i].pos, D3DXVECTOR2(1.0f, 0.0f), i, g_Issuer[i].PieceIndex);
			}
		}
	}
}

//==================================================
// �`��֐�
//==================================================
void DrawIssuer()
{
	// �S�`�F�b�N
	for (int i = 0; i < ISSUER_MAX; i++) {
		// �g�p��
		if (g_Issuer[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Issuer[i].texNo));

			SpriteDrawColorRotation(
				g_Issuer[i].pos.x, g_Issuer[i].pos.y, -0.1f,
				g_Issuer[i].size.x, g_Issuer[i].size.y, g_Issuer[i].rot * 90, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, -1.0f, 1
			);
		}
	}
}

//==================================================
// �Z�b�g�֐�
//==================================================
void SetIssuer(D3DXVECTOR2 pos, D3DXVECTOR2 size, float rot, int PNo)
{
	// �S�`�F�b�N
	for (int i = 0; i < ISSUER_MAX; i++) {
		// �g�p���ł͂Ȃ�
		if (!g_Issuer[i].bUse) {
			g_Issuer[i].pos = pos;
			g_Issuer[i].size = size;
			g_Issuer[i].rot = rot;
			g_Issuer[i].bUse = true;

			// ��]�����Ƃ��͍쓮�t���O��ێ�����
			if (g_Issuer[i].PieceIndex != PNo) {
				g_Issuer[i].PieceIndex = PNo;
				g_Issuer[i].bAct = false;
			}
			// �f�o�b�O�p
			g_Issuer[i].bAct = true;

			break;
		}
	}
}

//==================================================
// �f���[�g�֐�
//==================================================
void DeleteIssuer(int PNo)
{
	// �S�`�F�b�N
	for (int i = 0; i < ISSUER_MAX; i++) {
		// �s�[�X�̔ԍ�������
		if (g_Issuer[i].PieceIndex == PNo) {
			g_Issuer[i].bUse = false;
		}
	}
}




