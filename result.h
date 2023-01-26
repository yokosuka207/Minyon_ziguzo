#pragma once
//====================
//マクロ定義
//=====================

#define RESULT_MAX (5)

typedef enum
{
	WIN =0,
	LOSE,
}RESULT_TYPE;


typedef	struct
{
	bool			UseFlag;
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
	RESULT_TYPE		type;
}RESULT;

//======================
//プロトタイプ宣言
//======================
void	InitResult();
void	UninitResult();
void	UpdateResult();
void	DrawResult();
void SetResultType(RESULT_TYPE ty);
void SetResult(D3DXVECTOR3 pos, D3DXVECTOR2 size);
RESULT* GetResult();