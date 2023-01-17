#include "noizu.h"
#include"texture.h"
#include"sprite.h"

static ID3D11ShaderResourceView* g_texture_noizu;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_texture_noizu_Name = (char*)"data\\texture\\whitenoise.png";	//�e�N�X�`���t�@�C���p�X

static NOIZU g_Noizu;

HRESULT InitNoizu()
{
	g_Noizu.Position = D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	g_Noizu.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Noizu.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.03f);
	g_Noizu.PaternNo = 0;
	g_Noizu.NumPatern = 2;
	g_Noizu.uv_w = NOIZU_UV_W;
	g_Noizu.uv_h = NOIZU_UV_H;
	g_Noizu.texno = LoadTexture(g_texture_noizu_Name);
	g_Noizu.Rotation = 0.0f;

	g_Noizu.UseFlag = true;
	return S_OK;
}

void UninitNoizu()
{
	//g_Noizu.UseFlag = false;

}

void UpdateNoizu()
{
	g_Noizu.PaternNo += 0.3f;
	if (g_Noizu.PaternNo > 4.0f)
	{
		g_Noizu.PaternNo = 0.0f;
	}
}

void DrawNoizu()
{	
	SetWorldViewProjection2D();


	if (g_Noizu.UseFlag == true)
	{
		//�e�N�X�`���̐ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Noizu.texno));
		//�X�v���C�g��\��
		SpriteDrawColorRotation(g_Noizu.Position.x, g_Noizu.Position.y, 0.0f, g_Noizu.Size.x, g_Noizu.Size.y, g_Noizu.Rotation, g_Noizu.Color, 
			g_Noizu.PaternNo, g_Noizu.uv_w, g_Noizu.uv_h, g_Noizu.NumPatern);
	}

}
