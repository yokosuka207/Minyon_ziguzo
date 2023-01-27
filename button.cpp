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
#include "mouse.h"
#include "xinput.h"

//**************************************************
// マクロ定義
//**************************************************
#define NUM_SIZE	30
#define NUM_DIFFERENCE_X	140
#define NUM_DIFFERENCE_Y	10
#define NUM_TEXTURE_NUM_X	10
#define NUM_TEXTURE_UV_W	1.0f / NUM_TEXTURE_NUM_X
#define NUM_TEXTURE_UV_H	1.0f

static char* g_NumberTextureName = (char*)"data/texture/number.png";					// 数字

//==================================================
// 初期化
//==================================================
void Button::Init()
{
	m_type = BUTTON_TYPE::TYPE_NORMAL;
	m_numTexNo = LoadTexture(g_NumberTextureName);
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
	// ボタンの状態リセット
	ChangeType(BUTTON_TYPE::TYPE_NORMAL);
	m_numCol = m_color;
}


//==================================================
// 描画処理
//==================================================
void Button::Draw()
{
	// ボタンの描画
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) {			// ノーマル状態
		// テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
		m_drawPos.y = m_pos.y;
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_DrawSize.x, m_DrawSize.y, 0.0f,
			m_color, 0.0f, 1.0f, 1.0f, 1);
		// 数字の描画
		if (m_num >= 0) {
			// テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_numTexNo));
			// 十の位
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f, 
				m_numCol, m_num / 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
			// 一の位
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X + NUM_SIZE, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f,
				m_numCol, m_num % 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
		}
	}
	else {						// 押されている状態
		m_drawPos.y = m_pos.y + 10.0f;
		D3DXCOLOR col = D3DXCOLOR(m_color.r - 0.3f, m_color.g - 0.3f, m_color.b - 0.3f, m_color.a);		// ボタンの色
		D3DXCOLOR numCol = D3DXCOLOR(m_numCol.r - 0.3f, m_numCol.g - 0.3f, m_numCol.b - 0.3f, m_numCol.a);		// 数字の色
		// テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_texNo));
		SpriteDrawColorRotation(m_pos.x, m_drawPos.y,0.0f, m_DrawSize.x, m_DrawSize.y, 0.0f, 
			col, 0.0f, 1.0f, 1.0f, 1);
		// 数字の描画
		if (m_num >= 0) {
			// テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_numTexNo));
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f,
				numCol, m_num / 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
			SpriteDrawColorRotation(m_pos.x + NUM_DIFFERENCE_X + NUM_SIZE, m_drawPos.y + NUM_DIFFERENCE_Y, 0.0f, NUM_SIZE, NUM_SIZE, 0.0f, 
				numCol, m_num % 10, NUM_TEXTURE_UV_W, NUM_TEXTURE_UV_H, NUM_TEXTURE_NUM_X);
		}
	}


}


//==================================================
// セッター
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
// 押された判定	マウス：左クリック
//				ボタン：B
//==================================================
bool Button::TriggerButton()
{
	// 当たり判定
	if (CollisionMouse()) {
		if (Mouse_IsLeftTrigger() ||
			IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {
			return true;
		}
	}
	return false;
}

//==================================================
// ボタンのタイプ変更
//==================================================
void Button::ChangeType() 
{
	if (m_type == BUTTON_TYPE::TYPE_NORMAL) m_type = BUTTON_TYPE::TYPE_PRESSED;
	else m_type = BUTTON_TYPE::TYPE_NORMAL;
}

//==================================================
// ２転換の距離を返す
//==================================================
float DistanceTwoPoints(D3DXVECTOR2 p1, D3DXVECTOR2 p2) 
{
	D3DXVECTOR2 line;
	line.x = abs((int)p2.x - (int)p1.x);
	line.y = abs((int)p2.y - (int)p1.y);
	return line.x * line.x + line.y * line.y;
}
