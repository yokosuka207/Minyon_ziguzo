/*================================================================================

	ボタン処理[button.cpp]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "button.h"
#include "sprite.h"
#include "texture.h"
//#include "input.h"


//==================================================
// 初期化
//==================================================
void Button::Init()
{
	m_type = BUTTON_TYPE::TYPE_NORMAL;
}


//==================================================
// 終了処理
//==================================================
void Button::Uninit()
{

}


//==================================================
// 更新処理
//==================================================
void Button::Update()
{
	//// 当たっている状態でマウスを押したら
	//if (IsMouseLeftPressed() && CollisionMouse()) {
	//	ChangeType(BUTTON_TYPE::TYPE_PRESSED);

	//}
	//else {			// 当たっていないし押されてもいない
	//	ChangeType(BUTTON_TYPE::TYPE_NORMAL);
	//}
}


//==================================================
// 描画処理
//==================================================
void Button::Draw()
{
	// テクスチャの設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
	// 四角形の描画
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) {			// ノーマル状態
		m_drawPos.y = m_pos.y;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_size.x, m_size.y, 0.0f, m_color, 0.0f, 1.0f, 1.0f, 1);
	}
	else {						// 押されている状態
		m_drawPos.y = m_pos.y + 10.0f;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_size.x, m_size.y, 0.0f, D3DXCOLOR(m_color.r - 0.3f, m_color.g - 0.3f, m_color.b - 0.3f, m_color.a), 0.0f, 1.0f, 1.0f, 1);
	}
}


//==================================================
// セッター
//==================================================
void Button::SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si,D3DXCOLOR co , float no)
{
	m_pos = m_drawPos = po;
	m_size = si;
	m_color = co;
	m_texNo = no;
}


//==================================================
// 当たり判定
//==================================================
bool Button::CollisionMouse()
{
	// ボタンの左上, 右下
	D3DXVECTOR2 min, max;		
	min = D3DXVECTOR2(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2);
	max = D3DXVECTOR2(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
	// マウスの座標
	D3DXVECTOR2 mousePos;
	mousePos.x = (float)GetMousePosX();
	mousePos.y = (float)GetMousePosY();

	// 当たり判定
	if (min.x < mousePos.x && max.x > mousePos.x && min.y < mousePos.y && max.y > mousePos.y) {
		return true;
	}
	return false;
}

//==================================================
// 押された判定
//==================================================
bool Button::ReleaseButton()
{
	// 仮のbool型
	static bool bPress = false;

	// 当たり判定
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

