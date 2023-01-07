/*==============================================================================

   �t�F�[�h�w�b�_�[ [fade.h]
														 Author : ���؁@��
														 Date   : 2022/12/27
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#define FADE_SPEED (0.02f)

#define FADE_SPPED_X (22.0f * 10)	//1422 / 60
#define FADE_SPPED_Y (12.5f * 10)	//800 / 60

enum class FADE {
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,

	FADE_NUM
};
typedef struct {
	bool	ExceptFlag;	//��O�i�V�[���؂�ւ��́j
	bool	FadeFlag;	//�t�F�[�h���Ă���Ԃ̍Ĕ����h�~
	float	alpha;		//�����x�؂�ւ�
	D3DXVECTOR2	scaling;		//�T�C�Y�̕ω�
	FADE	state;		

	int				TexNo;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		size;
	int				PaternNo;
	float			uv_w;
	float			uv_h;
	float			rot;
	int				NumPatern;

}FADEPARAM;

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void StartFade(FADE state);
FADEPARAM* GetFadeParam();
#endif // !_FADE_H_