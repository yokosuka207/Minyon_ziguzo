#ifndef _FIN_H_
#define _FIN_H_

#include "main.h"

typedef struct {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	D3DXCOLOR	color;

	float		PaternNo;
	float		uv_w;
	float		uv_h;
	int			NumPatern;
}FIN;

void InitFin();
void UninitFin();
void UpdateFin();
void DrawFin();

#endif // !_FIN_H_

