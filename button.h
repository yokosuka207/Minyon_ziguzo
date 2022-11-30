/*================================================================================

	ボタンヘッダー[button.h]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

// ボタンクラス
class Button
{
private:	
	D3DXVECTOR2 m_pos;										// 中心座標
	D3DXVECTOR2 m_size;										// サイズ
	D3DXCOLOR m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	int m_type = 1;											// 状態	1：ノーマル　-1：押されている
	float m_texNo = -1;											// テクスチャの番号
public:
	Button() {}
	// 引数：ポジション, サイズ, テクスチャ番号
	Button(D3DXVECTOR2 po, D3DXVECTOR2 si, float no) : m_pos(po), m_size(si), m_texNo(no) {}
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
	void SetButton(D3DXVECTOR2 po, D3DXVECTOR2 si, float no);

	// タイプ変更
	void ChangeType() { m_type *= -1; }
};

#endif // !_BUTTON_H_
