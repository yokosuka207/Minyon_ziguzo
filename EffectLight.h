/*================================================================================

	ライトヘッダー[EffectLight.h]

												Author: 稲葉 陸斗
												 Date : 2023/01/23
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#pragma once
#ifndef _LIGHTSPARK_H_
#define _LIGHTSPARK_H_

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
	bool stop;
}LIGHT;

void InitEffectLight();
void UninitEffectLight();
void UpdateEffectLight();
void DrawEffectLight();

void SetEffectLight(D3DXVECTOR2 pos, float rot, int index);
void StopEffectLight(int index);

#endif // !_LIGHTSPARK_H_
