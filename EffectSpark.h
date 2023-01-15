/*================================================================================

	ヒバナエフェクトヘッダー[EffectSpark.h]

												Author: 齊藤 零登
												 Date : 2023/01/10
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _EFFECTSPARK_H_
#define _EFFECTSPARK_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR2	pos;
	D3DXVECTOR2	size;
	D3DXCOLOR col;
	float rot;
	int	TexNo;
	float PatternNo;

	bool bUse;
}EFFECT_SPARK;

void InitEffectSpark();
void UninitEffectSpark();
void UpdateEffectSpark();
void DrawEffectSpark();

void SetEffectSpark(D3DXVECTOR2 pos, float rot);

#endif // !_EFFECTSPARK_H_
