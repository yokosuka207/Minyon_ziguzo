/*================================================================================

	ボタンヘッダー[button.h]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

enum class BUTTON_TYPE
{
	TYPE_NORMAL = 0,					// 押されていない
	TYPE_PRESSED,						// 押されている
	TYPE_MAX
};

// ボタンクラス
class Button
{
private:	
	D3DXVECTOR2 m_pos;										// 中心座標
	D3DXVECTOR2 m_drawPos;										// 表示座標
	D3DXVECTOR2 m_size;										// サイズ
	D3DXCOLOR m_color;	// 色
	BUTTON_TYPE m_type = BUTTON_TYPE::TYPE_NORMAL;			// 状態
	float m_texNo = -1;										// テクスチャの番号
public:
	Button() {}
	~Button() {}

	// 基本関数
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// 各種ゲッター
	D3DXVECTOR2 GetPosition() { return m_pos; }
	D3DXVECTOR2 GetSize() { return m_size; }
	
	// セッター
	// 引数：ポジション, サイズ, テクスチャ番号
	void SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si, D3DXCOLOR co, float no);
	void SetButtonTexNo(float no) { m_texNo = no; }			// テクスチャ切り替え

	// マウスとの当たり判定
	bool CollisionMouse();
	// ボタンが離された
	bool ReleaseButton();
private:
	// タイプ変更
	void ChangeType(BUTTON_TYPE type) { m_type = type; }
};

#endif // !_BUTTON_H_
