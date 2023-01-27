/*================================================================================

	�{�^������[button.cpp]

												Author: ꎓ� ��o
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "button.h"
#include "sprite.h"
#include "texture.h"
#include "mouse.h"
#include "xinput.h"

//**************************************************
// �}�N����`
//**************************************************
#define NUM_SIZE	30
#define NUM_DIFFERENCE_X	140
#define NUM_DIFFERENCE_Y	10
#define NUM_TEXTURE_NUM_X	10
#define NUM_TEXTURE_UV_W	1.0f / NUM_TEXTURE_NUM_X
#define NUM_TEXTURE_UV_H	1.0f

static char* g_NumberTextureName = (char*)"data/texture/number.png";					// ����

//==================================================
// ������
//==================================================
void Button::Init()
{
	m_type = BUTTON_TYPE::TYPE_NORMAL;
	m_numTexNo = LoadTexture(g_NumberTextureName);
}


//==================================================
// �I������
//==================================================
void Button::Uninit()
{

}


//==================================================
// �X�V����
//==================================================
void Button::Update()
{
	// �{�^���̏�ԃ��Z�b�g
	ChangeType(BUTTON_TYPE::TYPE_NORMAL);
	m_numCol = m_color;
}


//==================================================
// �`�揈��
//==================================================
void Button::Draw()
{
	// �{�^���̕`��
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) {			// �m�[�}�����
		// �e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
		m_drawPos.y = m_pos.y;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_DrawSize.x, m_DrawSize.y, 0.0f,
			m_color, 0.0f, 1.0f, 1.0f, 1);
		// �����̕`��
		if (m_num >= 0) {
			// �e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_numTexNo));
			// �\�̈�
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f, 
				m_numCol, m_num / 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
			// ��̈�
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X + NUM_SIZE, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f,
				m_numCol, m_num % 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
		}
	}
	else {						// ������Ă�����
		m_drawPos.y = m_pos.y + 10.0f;
		D3DXCOLOR col = D3DXCOLOR(m_color.r - 0.3f, m_color.g - 0.3f, m_color.b - 0.3f, m_color.a);		// �{�^���̐F
		D3DXCOLOR numCol = D3DXCOLOR(m_numCol.r - 0.3f, m_numCol.g - 0.3f, m_numCol.b - 0.3f, m_numCol.a);		// �����̐F
		// �e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_DrawSize.x, m_DrawSize.y, 0.0f, 
			col, 0.0f, 1.0f, 1.0f, 1);
		// �����̕`��
		if (m_num >= 0) {
			// �e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_numTexNo));
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f,
				numCol, m_num / 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X + NUM_SIZE, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f, 
				numCol, m_num % 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
		}
	}


}


//==================================================
// �Z�b�^�[
//==================================================
void Button::SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si,D3DXVECTOR2 ds, D3DXCOLOR co , float no)
{
	m_pos = m_drawPos = po;
	m_size = si;
	m_DrawSize = ds;
	m_color = co;
	m_texNo = no;
}


//==================================================
// �����蔻��
//==================================================
bool Button::CollisionMouse()
{
	// �{�^���̍���, �E��
	D3DXVECTOR2 min, max;		
	min = D3DXVECTOR2(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2);
	max = D3DXVECTOR2(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
	// �}�E�X�̍��W
	D3DXVECTOR2 mousePos;
	mousePos.x = (float)GetMousePosX();
	mousePos.y = (float)GetMousePosY();

	// �����蔻��
	if (min.x < mousePos.x && max.x > mousePos.x && min.y < mousePos.y && max.y > mousePos.y) {
		return true;
	}
	return false;
}

//==================================================
// �����ꂽ����	�}�E�X�F���N���b�N
//				�{�^���FB
//==================================================
bool Button::TriggerButton()
{
	// �����蔻��
	if (CollisionMouse()) {
		if (Mouse_IsLeftTrigger() ||
			IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {
			return true;
		}
	}
	return false;
}

//==================================================
// �{�^���̃^�C�v�ύX
//==================================================
void Button::ChangeType() 
{
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) m_type = BUTTON_TYPE::TYPE_PRESSED;
	else m_type = BUTTON_TYPE::TYPE_NORMAL;
}

//==================================================
// �Q�]���̋�����Ԃ�
//==================================================
float DistanceTwoPoints(D3DXVECTOR2 p1, D3DXVECTOR2 p2) 
{
	D3DXVECTOR2 line;
	line.x = abs((int)p2.x - (int)p1.x);
	line.y = abs((int)p2.y - (int)p1.y);
	return line.x * line.x + line.y * line.y;
}
