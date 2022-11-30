/*================================================================================

	セーブヘッダー[save.h]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _SAVE_H_
#define _SAVE_H_


#include "button.h"

class Save
{
private:
	float m_BGTexNo = -1;		// テクスチャ番号		0～2：データの番号		3：背景

	D3DXVECTOR2 m_BGPos;
	D3DXVECTOR2 m_BGSize;
	D3DXCOLOR m_BGColor;

public:
	Save() {}
	~Save() {}

	// 基本関数
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// セーブ
	void Saved(int no);
	// セーブデータの削除
	void DeleteSaveData(int no);
};

#endif // !_SAVE_H_
