/*==============================================================================

   �w�i�Ǘ� [bg.cpp]
														 Author :
														 Date   :6/23
--------------------------------------------------------------------------------*/

#include"bg.h"
#include"texture.h"
#include"sprite.h"
//�ύX

static	ID3D11Buffer		*g_VertexBufferBG = NULL;	//�w�i�|���S���p
static ID3D11ShaderResourceView	*g_texture;	//�摜�ꖇ�ň�̕ϐ����K�v
//static char *g_textureName = (char*)"data\\texture\\R.png";	//�e�N�X�`���t�@�C���p�X
//static char *g_textureName = (char*)"data\\texture\\game-pipora-min_1.png";	//�e�N�X�`���t�@�C���p�X
static char *g_textureName = (char*)"data\\texture\\runningman003.png";	//�e�N�X�`���t�@�C���p�X

static ID3D11ShaderResourceView	*g_texture_under;	//�摜�ꖇ�ň�̕ϐ����K�v
static char *g_texture_under_Name = (char*)"data\\texture\\gray.jpg";	//�e�N�X�`���t�@�C���p�X
static int g_TextureNoBG = 0;

BG *Bg;	//�w�i�\���̂̃|�C���^�ϐ�

HRESULT BgInit()
{
	//SpriteInit();

	g_TextureNoBG = LoadTexture(g_texture_under_Name);
	if (g_TextureNoBG == -1)
	{//���[�h�G���[
		exit(999);	//�����I������
	}
	Bg = new BG;	//���I�C���X�^���X��
	Bg->Position = D3DXVECTOR3(0.0f, 0.0f, 0);
	Bg->Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Bg->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Bg->Rotation = 0.0f;

	return S_OK;

}

void BgUninit()
{
	if (g_VertexBufferBG)
	{
		g_VertexBufferBG->Release();//�g���I������̂ŉ������
		g_VertexBufferBG = NULL;
	}
	if (g_texture_under)
	{
		g_texture_under->Release();
		g_texture_under = NULL;
	}

	if (Bg)
	{
		delete Bg;
		Bg = NULL;
	}


}

void BgUpdate()
{
}

void BgDraw()
{
	//SetWorldViewProjection2D();

	{	//�w�i�|���S���\��

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNoBG));

		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
		SpriteDrawColorRotation(
			Bg->Position.x, Bg->Position.y,0.5f, Bg->Size.x, Bg->Size.y
			, Bg->Rotation, Bg->Color, 0, 1.0f, 1.0f, 1);
	}

}
//=================================================
//�w�i�|���S�����_�i�[����
//�\�����WX, �\�����WY,���T�C�Y,�c�T�C�Y,��]���x,�F
//=================================================


void SetVertexBG(float PosX, float PosY, int Size_W, int Size_H, float Kakudo, D3DXCOLOR COL, float sokudo)
{
	//D3D11_MAPPED_SUBRESOURCE msr;
	////���_�o�b�t�@�ւ̏������݋������炤
	//GetDeviceContext()->Map(g_VertexBufferBG, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	////���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	//VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	////static float sokudo = 0.0f;
	////���_ V0���Z�b�g
	//vertex[0].Position = D3DXVECTOR3(-Size_W / 2, -Size_H / 2, 0.0f);
	//vertex[0].Diffuse = COL;
	//vertex[0].TexCoord = D3DXVECTOR2(0.0f + sokudo, 0.0f);
	////���_ V1���Z�b�g
	//vertex[1].Position = D3DXVECTOR3(+Size_W / 2, -Size_H / 2, 0.0f);
	//vertex[1].Diffuse = COL;
	//vertex[1].TexCoord = D3DXVECTOR2(1.0f + sokudo, 0.0f);
	////���_ V2���Z�b�g
	//vertex[2].Position = D3DXVECTOR3(-Size_W / 2, +Size_H / 2, 0.0f);
	//vertex[2].Diffuse = COL;
	//vertex[2].TexCoord = D3DXVECTOR2(0.0f + sokudo, 1.0f);
	////���_ V3���Z�b�g
	//vertex[3].Position = D3DXVECTOR3(+Size_W / 2, +Size_H / 2, 0.0f);
	//vertex[3].Diffuse = COL;
	//vertex[3].TexCoord = D3DXVECTOR2(1.0f + sokudo, 1.0f);
	////offset += sokudo / 60.0f;




	////texcoord��������ΐF�X�ł���
	////�x�����W�A���֕ϊ�����
	//float	rad = D3DXToRadian(Kakudo);
	//float	x, y;

	//for (int i = 0; i < 4; i++)
	//{
	//	//���@�藝		
	//	x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
	//	y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

	//	vertex[i].Position.x = x + PosX;	//���s�ړ��i���S�����炷�j
	//	vertex[i].Position.y = y + PosY;
	//}

	////UV�A�j���[�V����
	//GetDeviceContext()->Unmap(g_VertexBufferBG, 0);//�������ݏI��
}
