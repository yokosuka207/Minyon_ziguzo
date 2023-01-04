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
//#include "input.h"


//==================================================
// ������
//==================================================
void Button::Init()
{
	m_type = BUTTON_TYPE::TYPE_NORMAL;
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
	//// �������Ă����ԂŃ}�E�X����������
	//if (IsMouseLeftPressed() && CollisionMouse()) {
	//	ChangeType(BUTTON_TYPE::TYPE_PRESSED);

	//}
	//else {			// �������Ă��Ȃ���������Ă����Ȃ�
	//	ChangeType(BUTTON_TYPE::TYPE_NORMAL);
	//}
}


//==================================================
// �`�揈��
//==================================================
void Button::Draw()
{
	// �e�N�X�`���̐ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
	// �l�p�`�̕`��
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) {			// �m�[�}�����
		m_drawPos.y = m_pos.y;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_size.x, m_size.y, 0.0f, m_color, 0.0f, 1.0f, 1.0f, 1);
	}
	else {						// ������Ă�����
		m_drawPos.y = m_pos.y + 10.0f;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_size.x, m_size.y, 0.0f, D3DXCOLOR(m_color.r - 0.3f, m_color.g - 0.3f, m_color.b - 0.3f, m_color.a), 0.0f, 1.0f, 1.0f, 1);
	}
}


//==================================================
// �Z�b�^�[
//==================================================
void Button::SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si,D3DXCOLOR co , float no)
{
	m_pos = m_drawPos = po;
	m_size = si;
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
// �����ꂽ����
//==================================================
bool Button::ReleaseButton()
{
	// ����bool�^
	static bool bPress = false;

	// �����蔻��
	//if (CollisionMouse()) {
	//	if (IsMouseLeftPressed()) {
	//		bPress = true;
	//	}
	//	else {
	//		if (bPress) {
	//			bPress = false;
	//			return true;
	//		}
	//	}
	//}
	return false;
}

