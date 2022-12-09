/*================================================================================

	セーブヘッダー[save.h]

												Author: 齊藤 零登
												 Date : 2022/11/29
----------------------------------------------------------------------------------
Update:
	2022/12/07	SaitoReito
================================================================================*/
#pragma once
#ifndef _SAVE_H_
#define _SAVE_H_


#include "button.h"

struct SaveData
{
	int clearStageNum = 0;
};

class Save
{
private:
	float m_BGTexNo = -1;		// テクスチャ番号		0～2：データの番号		3：背景

	D3DXVECTOR2 m_BGPos;
	D3DXVECTOR2 m_BGSize;
	D3DXCOLOR m_BGColor;

	int m_dataNo;			// セーブデータの番号

	SaveData m_saveData;		// セーブするデータ

public:
	Save() {}
	Save(int no) :m_dataNo(no){}
	~Save() {}

	// 基本関数
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// セーブ
	void DataSave();
	// セーブデータの削除
	void DeleteSaveData();
	// ロード
	void DataLoad();

	// ゲッター
	int GetDataNo()const { return m_dataNo; }		// データ番号
	// セッター
	void SetDataNo(int no) { if (0 < no && no < 4) { m_dataNo = no; } }		// データ番号(1～3)

private:
	// ファイルの有無チェック
	bool ExistFile(char* fileName);
};

#endif // !_SAVE_H_
