/*==============================================================================
�X�v���C�g�`��
   �|���S������[sprite.h]
														 Author :�V���Ė�
														 Date   :6/13
--------------------------------------------------------------------------------*/

#include"renderer.h"
#include"sprite.h"


///============================
//�}�N����`
//-----------------------------
#define	NUM_TRIANGLE_VERTEX	(4)		//�O�p�`�p���_��
#define	NUM_PUZZLE_VERTEX	(64)		//�O�p�`�p���_��


///============================
//�v���g�^�C�v�錾
//���̒������ł����֐�
//-----------------------------


///============================
//�O���[�o���ϐ�
//-----------------------------

static	ID3D11Buffer		*g_VertexBufferTriangle = NULL;	//���_�o�b�t�@


//static float PaternNo = 0;	//�p�^�[���ԍ�
//float uv_w = 0.5f;	//���T�C�Y
//float uv_h = 0.5f;	//�c�T�C�Y
//int NumPatern = 2;	//������

//======================
//������
//=========================
void SpriteInit()
{
	{//�O�p�`�p�̒��_����������
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
	}

}
//======================
//�I������
//======================
void SpriteUninit()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//�g���I������̂ŉ������
		g_VertexBufferTriangle = NULL;
	}

}




//=================================================
//�O�p�`�p���_�i�[����
//�\�����WX, �\�����WY,���T�C�Y,�c�T�C�Y,��]���x,�F
//���x,�e�N�X�`���̃p�^�[��,�e�N�X�`���̉��T�C�Y,�c�T�C�Y,���p�^�[���̐�
//=================================================
void SpriteDrawColorRotation(float PosX, float PosY,float PosZ, int Size_W, int Size_H, float Kakudo,D3DXCOLOR COL
	,float PaternNo, float uv_w, float uv_h, int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//static float sokudo = 0.0f;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, PosZ);
	vertex[0].Diffuse = COL;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, PosZ);
	vertex[1].Diffuse = COL;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f  , 0.0f);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,PosZ);
	vertex[2].Diffuse = COL;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f , 1.0f);
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, PosZ);
	vertex[3].Diffuse = COL;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f , 1.0f);
	//offset += sokudo / 60.0f;

	//UV�A�j���[�V����
	//�ق�Ƃ͈����ɂ���p�����[�^�[

	//static float PaternNo = 0;	//�p�^�[���ԍ�
	//float uv_w = 0.5f;	//���T�C�Y
	//float uv_h = 0.5f;	//�c�T�C�Y
	//int NumPatern = 2;	//������


	//UV���W�̌v�Z
	int no = PaternNo;	//�p�^�[���ԍ��𐮐��l�ɂ���
	float u = (no % NumPatern) * uv_w;
	float v = (no / NumPatern) * uv_h;

	//UV���W�̏�������
	vertex[0].TexCoord = D3DXVECTOR2(u, v);	//����
	vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);//�E��
	vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);//����
	vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);//�E��


	PaternNo += 0.01f;
	if (PaternNo >= 4.0f)
	{
		PaternNo -= 4.0f;
	}
	//texcoord��������ΐF�X�ł���
	//�x�����W�A���֕ϊ�����
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		//���@�藝
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + PosX;	//���s�ړ��i���S�����炷�j
		vertex[i].Position.y = y + PosY;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//�������ݏI��


	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	//�O�p�`�̒��_�f�[�^���i�[
	GetDeviceContext()->Draw(NUM_TRIANGLE_VERTEX, 0);

}

