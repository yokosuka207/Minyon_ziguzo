/*==============================================================================

   ���_�Ǘ� [polygon.cpp]
														 Author :
														 Date   :5/30
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include"sprite.h"
#include"texture.h"
#include"input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX_LINESTRIP (64)	//���C���X�g���b�v���_�ő吔
//#define	NUM_TRIANGLE_VERTEX	(4)		//�O�p�`�p���_��

#define	BOX_W	(100)	//�l�p�`�̉��̃T�C�Y
#define	BOX_H	(100)	//�l�p�`�̏c�̃T�C�Y



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void	SetVertexLineStrip(int);							//���C���X�g���b�v���_�i�[����
//void	SetVertexTringle(float, float, int, int, float,D3DXCOLOR,float);	//�O�p�`�p���_�i�[����
void	SetVertexLine(float, float, float, float);			//�����p���_�i�[����
void	SetVertexCircle(float, float, float, int, D3DXCOLOR);	//���p�`�̕\��


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	ID3D11Buffer		*g_VertexBufferLineStrip = NULL;//���C���X�g���b�v�p
//static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;	//�l�p�`�p
static	ID3D11Buffer		*g_VertexBufferLine = NULL;		//�����p

static	ID3D11Buffer		*g_VertexBufferCircle = NULL;	//���p�`�p



float	PositionX = 0;//��ʒ������W
float	PositionY = 0;
float	Kakudo = 0; //�l�p�`�̉�]�p�x

float	StartPositionX = 0;				//�����̃X�^�[�g���W
float	StartPositionY = 0;
float	EndPositionX = SCREEN_WIDTH;	//�����̏I�����W
float	EndPositionY = SCREEN_HEIGHT;


//�e�N�X�`���̕ۑ��ϐ�


D3DXVECTOR3	Goal = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);	//��ʒ���
D3DXVECTOR3	Speed;
D3DXVECTOR3	Start;


//�L�����N�^�[�\����

//�w�i�\����
//typedef struct
//{
//	//���̎l������Ύ�芸�����\���ł���
//	D3DXVECTOR3		Position;	//�\�����W
//	D3DXCOLOR		Color;		//�\���F
//	float			Rotation;	//�p�x
//	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
//
//}BG;
//BG *Bg;	//�w�i�\���̂̃|�C���^�ϐ�


//�e�N�X�`���̔ԍ��̔�
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{

	//�����̏�����
	srand(timeGetTime());
	//�|���S���̕\���������_���ɂ���
	PositionX = SCREEN_WIDTH/2;
	PositionY = SCREEN_HEIGHT/2;

	Start.x = PositionX;
	Start.y = PositionY;
	Start.z = 0.0f;

	//�ړI�n�܂ł̃x�N�g�������
	Speed = Goal - Start;
	//���K�����Ē�����1�ɂ���(�|�C���^)
	D3DXVec3Normalize(&Speed, &Speed);
	//�x�N�g����C�ӂɒ����ɂ���
	//x.y.z�ɂR����������
	Speed *= 1.0f;

	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`�����[�h
	{
		//D3DX11CreateShaderResourceViewFromFile(
		//	pDevice,	//DirectX�{�̂̏��
		//	g_textureName,	//�e�N�X�`���̃t�@�C����
		//	NULL, NULL, &g_texture,	//���[�h�����e�N�X�`���̏��
		//	NULL
		//);

		//D3DX11CreateShaderResourceViewFromFile(
		//	pDevice,	//DirectX�{�̂̏��
		//	g_texture_under_Name,	//�e�N�X�`���̃t�@�C����
		//	NULL, NULL, &g_texture_under,	//���[�h�����e�N�X�`���̏��
		//	NULL
		//);
		

	}

	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX_LINESTRIP;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLineStrip);
		// ���_�o�b�t�@�X�V
		SetVertexLineStrip(4);
	}
	/*{//�O�p�`�p�̒��_����������
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_TRIANGLE_VERTEX;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		//�O�p�`�p���_�i�[����
		//SetVertexTringle(PositionX, PositionY, BOX_W, BOX_H, 0,col);
	}*/
	{//�����p
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 2;			//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLine);
		//�����p���_�i�[����
		SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY );
	}
	{//���p�`�p
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 64;	//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferCircle);

		//���p�`�p���_�i�[����
		D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		SetVertexCircle(300.0f, 500.0f, 100.0f, 32, col);

	}
	
	//{//�w�i�|���S���p�̒��_����������
	//// ���_�o�b�t�@����
	//	D3D11_BUFFER_DESC bd;
	//	ZeroMemory(&bd, sizeof(bd));
	//	bd.Usage = D3D11_USAGE_DYNAMIC;
	//	bd.ByteWidth = sizeof(VERTEX_3D) * NUM_TRIANGLE_VERTEX;//���_1�����_���̃T�C�Y�ō��
	//	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferBG);
	//	//�O�p�`�p���_�i�[����
	//	//D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	//SetVertexBG(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, col, 0.0f);
	//}

	//�X�v���C�g�̏�����
	//SpriteInit();


	//�w�i�̏�����

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBufferLineStrip)
	{
		g_VertexBufferLineStrip->Release();//�g���I������̂ŉ������
		g_VertexBufferLineStrip = NULL;
	}

	//if (g_VertexBufferTriangle)
	//{
	//	g_VertexBufferTriangle->Release();//�g���I������̂ŉ������
	//	g_VertexBufferTriangle = NULL;
	//}

	if (g_VertexBufferLine)
	{
		g_VertexBufferLine->Release();//�g���I������̂ŉ������
		g_VertexBufferLine = NULL;
	}

	if (g_VertexBufferCircle)
	{
		g_VertexBufferCircle->Release();//�g���I������̂ŉ������
		g_VertexBufferCircle = NULL;
	}
	//�X�v���C�g�̏I������
	SpriteUninit();

	//BG�\���̂̉��
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	//���S�Ɍ������ړ�
	Start += Speed;

	PositionX = Start.x;
	PositionY = Start.y;

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	//{
	//	// �\���������|���S���̒��_�o�b�t�@��ݒ�
	//	UINT stride = sizeof(VERTEX_3D);
	//	UINT offset = 0;
	//	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferLineStrip, &stride, &offset);
	//	// �v���~�e�B�u�g�|���W�ݒ�
	//	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);// LINELIST);
	// �}�e���A���ݒ�
		/*MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);*/
		//SetVertexLineStrip(4);
		//// �|���S���`��
		//GetDeviceContext()->Draw(4, 0);
	//�w�i�|���S���\��
	//{
	//	//�w�i�|���S���\��
	//		UINT stride = sizeof(VERTEX_3D);
	//		UINT offset = 0;
	//		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferBG, &stride, &offset);
	//		// �v���~�e�B�u�g�|���W�ݒ�
	//		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//		
	//		//�F��^����
	//		D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	SetVertexBG(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f,col,0.0f);
	//	//		Kakudo += 3.0f;
	//			//�e�N�X�`���̐ݒ�(Drew�̒��O�ɏ���)
	//			//�����͕ς��Ȃ�
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_texture_under);
	//	//GetDeviceContext()->PSSetShaderResources(0, 1, NULL);����Ńe�N�X�`�����g��Ȃ�
	//	// �|���S���`��
	//	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);
	//}

	//�l�p�`�̕`��

	{		//SetBlendState(BLEND_MODE::BLEND_MODE_SUBTRACT);

		//�l�p�`�̕`��
		// �\���������|���S���̒��_�o�b�t�@��ݒ�
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		//// �v���~�e�B�u�g�|���W�ݒ�
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		////�O�p�`�̒��_�f�[�^���i�[
			//�F��^����
				//Kakudo += 3.0f;
				//textuer_sokudo += 1.0f / 60.0f;
				//�e�N�X�`���̐ݒ�(Drew�̒��O�ɏ���)
				//�����͕ς��Ȃ�
		//GetDeviceContext()->PSSetShaderResources(0, 1, NULL);����Ńe�N�X�`�����g��Ȃ�


		 //SetSamplerState(FILTER_MODE::FILTER_MODE_POINT, ADDRESS_MODE ::ADDRESS_MODE_MIRROR);
		// �|���S���`��
	//	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);
		//SetBlendState(BLEND_MODE::BLEND_MODE_ALPHABLEND);

	}

	//	// �Q�c�\�������邽�߂̃}�g���N�X��ݒ�

	{//�����̕`��
		// �\���������|���S���̒��_�o�b�t�@��ݒ�
	//	UINT stride = sizeof(VERTEX_3D);
	//	UINT offset = 0;
	//	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferLine, &stride, &offset);
	//	// �v���~�e�B�u�g�|���W�ݒ�
	//	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//	//�����̒��_�f�[�^���i�[
	//	SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY);
	//	// �|���S���`��
	//	GetDeviceContext()->Draw(2, 0);
	}
	{//���p�`�̕`��
		//// �\���������|���S���̒��_�o�b�t�@��ݒ�
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferCircle, &stride, &offset);
		//// �v���~�e�B�u�g�|���W�ݒ�
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		////���p�`�̒��_�f�[�^���i�[
		//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//SetVertexCircle(300.0f, 300.0f, 100.0f, 16, col);
		//// �|���S���`��
		//GetDeviceContext()->Draw(16+1, 0);
	}

	
}


//=============================================================================
// ���_�f�[�^�ݒ�
//=============================================================================
void SetVertexLineStrip(int	NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferLineStrip, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[0].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 50.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);


	GetDeviceContext()->Unmap(g_VertexBufferLineStrip, 0);
}

////=================================================
////�O�p�`�p���_�i�[����
////�\�����WX, �\�����WY,���T�C�Y,�c�T�C�Y,��]���x,�F
////=================================================
//void SetVertexTringle(float PosX, float PosY, int Size_W, int Size_H, float Kakudo,D3DXCOLOR COL,float sokudo)
//{
//	D3D11_MAPPED_SUBRESOURCE msr;
//	//���_�o�b�t�@�ւ̏������݋������炤
//	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
//	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;
//
//	//static float sokudo = 0.0f;
//
//	//���_ V0���Z�b�g
//	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, 0.0f);
//	vertex[0].Diffuse = COL;
//	vertex[0].TexCoord = D3DXVECTOR2(0.0f+sokudo, 0.0f);
//	//���_ V1���Z�b�g
//	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, 0.0f);
//	vertex[1].Diffuse = COL;
//	vertex[1].TexCoord = D3DXVECTOR2(3.0f + sokudo, 0.0f);
//	//���_ V2���Z�b�g
//	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,0.0f);
//	vertex[2].Diffuse = COL;
//	vertex[2].TexCoord = D3DXVECTOR2(0.0f + sokudo, 3.0f);
//	//���_ V3���Z�b�g
//	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, 0.0f);
//	vertex[3].Diffuse = COL;
//	vertex[3].TexCoord = D3DXVECTOR2(3.0f + sokudo, 3.0f);
//	//offset += sokudo / 60.0f;
//
//	//UV�A�j���[�V����
//	static float PaternNo = 0;	//�p�^�[���ԍ�
//	float uv_w = 0.5f;	//���T�C�Y
//	float uv_h = 0.5f;	//�c�T�C�Y
//	int NumPatern = 2;	//������
//
//
//	//UV���W�̌v�Z
//	int no = PaternNo;	//�p�^�[���ԍ��𐮐��l�ɂ���
//	float u = (no % NumPatern) * uv_w;
//	float v = (no / NumPatern) * uv_h;
//
//	//UV���W�̏�������
//	//vertex[0].TexCoord = D3DXVECTOR2(u, v);	//����
//	//vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);//�E��
//	//vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);//����
//	//vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);//�E��
//
//
//	PaternNo += 0.01f;
//	if (PaternNo >= 4.0f)
//	{
//		PaternNo -= 4.0f;
//	}
//	//texcoord��������ΐF�X�ł���
//	//�x�����W�A���֕ϊ�����
//	float	rad = D3DXToRadian(Kakudo);
//	float	x, y;
//
//	for (int i = 0; i < 4; i++)
//	{
//		//���@�藝		
//		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
//		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);
//
//		vertex[i].Position.x = x + PosX;	//���s�ړ��i���S�����炷�j
//		vertex[i].Position.y = y + PosY;
//	}
//
//	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//�������ݏI��
//}

//===============================
//�����̒��_���i�[
//in
//  �J�n���WX, �J�n���WY, �I�����WX, �I�����WY
//
void	SetVertexLine(float StartX, float StartY, float EndX, float EndY)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(StartX, StartY, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(EndX, EndY, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	GetDeviceContext()->Unmap(g_VertexBufferLine, 0);//�������ݏI��

}

//==============================
//���C���ő��p�`�̕\��
//in
//�@�\�����WX, �\�����WY, ���a, ���_��, �F
//==========================================
void	SetVertexCircle(float PosX, float PosY, float Rad, int NumVertex, D3DXCOLOR col)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferCircle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float	kakudo = 0;
	for (int i = 0; i < NumVertex; i++)
	{
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + PosX;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + PosY;
		vertex[i].Position.z = 0.0f;
		vertex[i].Diffuse = col;
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		kakudo += (360.0f / NumVertex);
	}
	//�Ō�̒��_�ɍŏ��̒��_���R�s�[���Đ}�`�����
	vertex[NumVertex].Position = vertex[0].Position;
	vertex[NumVertex].Diffuse = vertex[0].Diffuse;
	vertex[NumVertex].TexCoord = vertex[0].TexCoord;

	GetDeviceContext()->Unmap(g_VertexBufferCircle, 0);//�������ݏI��



}

