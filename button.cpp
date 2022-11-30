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
#include "input.h"


//==================================================
// 初期化
//==================================================
void Button::Init()
{

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
	// ボタンとマウスの当たり判定
	// 当たり判定用
	D3DXVECTOR2 min, max;
	min = D3DXVECTOR2(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2);
	max = D3DXVECTOR2(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
	D3DXVECTOR2 mousePos;
	mousePos.x = (float)GetMousePosX();
	mousePos.y = (float)GetMousePosY();
	if (IsMouseLeftPressed() && (min.x < mousePos.x && max.x > mousePos.x && min.y < mousePos.y && max.y > mousePos.y)) {					// 当たっている状態で押している
		ChangeType(BUTTON_TYPE::TYPE_PRESSED);
		
	}
	else {			// 当たっていないし押されていない
		ChangeType(BUTTON_TYPE::TYPE_NORMAL);
	}
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
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y, m_size.x, m_size.y, 0.0f, m_color, 0.0f, 1.0f, 1.0f, 1);
	}
	else {						// 押されている状態
		m_drawPos.y = m_pos.y + 10.0f;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y, m_size.x, m_size.y, 0.0f, D3DXCOLOR(m_color.r - 0.3f, m_color.g - 0.3f, m_color.b - 0.3f, m_color.a), 0.0f, 1.0f, 1.0f, 1);
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