/*================================================================================
	cursor.cpp
 
		�J�[�\��
												Author: SaitoReito
												 Date : 2022/09/12
================================================================================*/
#include "cursor.h"		// ���g
#include "sprite.h"		// �X�v���C�g
#include "texture.h"	// �e�N�X�`��
//#include "input.h"		// ����
#include "xinput.h"	// x����

//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
#define CURSOR_SIZE_W	(50)		// �J�[�\���̃|���S���̉��̃T�C�Y
#define CURSOR_SIZE_H	(50)		// �J�[�\���̃|���S���̏c�̃T�C�Y

#define CURSOR_SPEED	(2)		// �J�[�\���̈ړ����x

//--------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------

//--------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------
static CURSOR g_Cursor;
static char *g_TextureName = (char*)"data\\texture\\cursor.png";


//==================================================
// �J�[�\��������
//==================================================
HRESULT InitCursor()
{
	// �J�[�\���̏�����
	{
		g_Cursor.size = D3DXVECTOR2(CURSOR_SIZE_W, CURSOR_SIZE_H);
		g_Cursor.pos = g_Cursor.oldPos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Cursor.sp = D3DXVECTOR2(1.0f, 1.0f);
		g_Cursor.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Cursor.texNo = LoadTexture(g_TextureName);

		g_Cursor.useFlag = false;
	}

	return S_OK;
}

//==================================================
// �J�[�\���I������
//==================================================
void UninitCursor()
{

}

//==================================================
// �J�[�\���X�V����
//==================================================
void UpdateCursor()
{
	if (g_Cursor.useFlag) {
		g_Cursor.oldPos = g_Cursor.pos;
		//[----------�ړ�----------
		if(GetThumbRightX(0) < -0.2f || GetThumbRightX(0) > 0.2f) {				// �E�X�e�B�b�N	���E
			g_Cursor.pos.x += GetThumbRightX(0) * 12;	// ���E�ړ�
		}
		if(GetThumbRightY(0) < -0.2f || GetThumbRightY(0) > 0.2f) {				// �E�X�e�B�b�N	�㉺
			g_Cursor.pos.y -= GetThumbRightY(0) * 12;	// �㉺�ړ�
		}
		//----------�ړ�----------]

		//[----------�ǔ��� (�ǂ̏㉺���E)----------
		// �㉺
		if (g_Cursor.pos.y - g_Cursor.size.y / 2 < SCREEN_LIMIT_UP ||
			g_Cursor.pos.y + g_Cursor.size.y / 2 > SCREEN_LIMIT_DOWN) 
		{
			g_Cursor.pos.y = g_Cursor.oldPos.y;
		}
		// ���E
		if(	g_Cursor.pos.x - g_Cursor.size.x / 2 < SCREEN_LIMIT_LEFT ||
			g_Cursor.pos.x + g_Cursor.size.x / 2 > SCREEN_LIMIT_RIGHT) 
		{
			g_Cursor.pos.x = g_Cursor.oldPos.x;
		}
		//-----------------------------------------]
	}
}

//==================================================
// �J�[�\���\������
//==================================================
void DrawCursor()
{
	if (g_Cursor.useFlag) {
		// �e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Cursor.texNo));
		// �|���S���̕`��
		SpriteDrawColorRotation(g_Cursor.pos.x, g_Cursor.pos.y,-0.2f, g_Cursor.size.x, g_Cursor.size.y, 0.0f, g_Cursor.color, 1.0f, 1.0f, 1.0f, 1);
	}
}

//==================================================
// �J�[�\���Z�b�g�֐�
// �����F���S���W, �T�C�Y
//==================================================
void SetCursor(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_Cursor.pos = g_Cursor.oldPos = pos;
	g_Cursor.size = size;

	g_Cursor.useFlag = true;
}


//==================================================
// �J�[�\���Q�b�g�֐�
//==================================================
CURSOR* GetCurso()
{
	return &g_Cursor;
}

//==================================================
// �J�[�\���폜�֐�
//==================================================
void DeleteCursor()
{
	g_Cursor.useFlag = false;
}
