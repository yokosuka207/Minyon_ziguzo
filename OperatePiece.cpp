/*==============================================================================

   �p�Y�����쏈�� [OperatePiece.cpp]
														 Author : ���؁@��
														 Date   : 2022/11/08
--------------------------------------------------------------------------------
 Update:
==============================================================================*/

#include "OperatePiece.h"
#include "texture.h"
#include "sprite.h"
#include "puzzle.h"

//**************************************************
//�@�}�N����`
//**************************************************

//**************************************************
// �O���[�o���ϐ�:
//**************************************************
static	ID3D11Buffer* g_OperatePieceVertexBuffer = NULL;	//�|���S���p
static ID3D11ShaderResourceView* g_OperatePieceTexture;	//�摜�ꖇ�ň�̕ϐ����K�v

static char* g_OperatePieceTextureName = (char*)"data\\texture\\green.png";	//�e�N�X�`���t�@�C���p�X

HRESULT OperatePiece::Init() {
	Piece* pMapChip = GetPiece();
	for (int p = 0; p < PUZZLE_MAX; p++) {
		pMapChip[p].UseFlag = false;
		pMapChip[p].no = 0;
		pMapChip[p].TexNo = LoadTexture(g_OperatePieceTextureName);
		pMapChip[p].direction = 0;

		pMapChip[p].pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		pMapChip[p].size = D3DXVECTOR2(PIECE_SIZE, PIECE_SIZE);
		for (int d = 0; d < BLOCK_CHIP_DIRECTION; d++) {
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					pMapChip[p].chip[d][i][j] = 0;
				}
			}
		}
	}
	FileLoad(0);
	SetMapChip(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 0);
	return S_OK;
}
void OperatePiece::Uninit() {
	if (g_OperatePieceTexture)
	{
		g_OperatePieceTexture->Release();
		g_OperatePieceTexture = NULL;
	}
}
void OperatePiece::Update() {
	Piece* pMapChip = GetPiece();

}
void OperatePiece::Draw() {
	Piece* pMapChip = GetPiece();
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (pMapChip[p].UseFlag){
			SetMapChip(pMapChip[p].pos, pMapChip[p].no);

			SetWorldViewProjection2D();
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(pMapChip[p].TexNo));
			SpriteDrawColorRotation(
				pMapChip[p].pos.x, pMapChip[p].pos.y,
				pMapChip[p].size.x, pMapChip[p].size.y, pMapChip[p].direction * 90 , D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1
			);
		}
	}
}
void OperatePiece::Rotate(int PieceNo) {
	Piece* pMapChip = GetPiece();
	for (int p = 0; p < PUZZLE_MAX; p++) {

	}
}
void OperatePiece::SetOperatePiece(D3DXVECTOR2 pos, int PieceNo) {
	Piece* pMapChip = GetPiece();
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if(!pMapChip[p].UseFlag)
		pMapChip[p].pos = pos;
		pMapChip[p].no = PieceNo;
		pMapChip[p].UseFlag = true;
		break;
	}
}


