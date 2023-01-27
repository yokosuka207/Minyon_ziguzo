#include "texture.h"
/*==============================================================================

   �e�N�X�`���̊Ǘ�[texture.cpp]
														 Author :�V���Ė�
														 Date   :6/13
--------------------------------------------------------------------------------*/
///============================
//�}�N����`
//-----------------------------
#define		MAX_TEXTURE_NUM		(110)//�e�N�X�`���̓ǂݍ��ݍő喇��

///============================
//�v���g�^�C�v�錾
//-----------------------------


///============================
//�O���[�o���ϐ�
//-----------------------------
//���[�h�����e�N�X�`���̏��z��
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];
//���[�h�����e�N�X�`���̖���
static UINT g_TextureIndex = 0;
//���[�h�����e�N�X�`���t�@�C���̃o�b�t�@
static char g_TextureNameBroken[MAX_TEXTURE_NUM][256];

///--------------------------------
//�e�N�X�`���̃��[�h
//�����F�t�@�C����
//�߂�l�F�e�N�X�`���C���f�b�N�X
//---------------------------------
int LoadTexture(char * filename)
{
	//���łɓǂݍ��܂ꂽ�����̃e�N�X�`��������ꍇ�͂��̔ԍ���Ԃ�
	for (int i = 0; i < g_TextureIndex; i++)
	{
		//if (strcmp(&g_TextureName[i][0], filename))�������ł�����

		//���O��������������
		if (strcmp(g_TextureNameBroken[i], filename) == 0)
		{
			return i;
		}
	}
	//�ǂݍ��ݍő吔�𒴂��Ă�����G���[

	if (g_TextureIndex == MAX_TEXTURE_NUM)
	{
		return -1;//�G���[�Ƃ��ă}�C�i�X�C�`��Ԃ�
	}
	//�e�N�X�`���̃��[�h

	HRESULT		hr = D3DX11CreateShaderResourceViewFromFile
	(
	GetDevice(),filename,NULL,NULL,&g_pTexture[g_TextureIndex],NULL
	);
	if (hr !=  S_OK)	//���܂�������S�QOK�ƂȂ�̂ňႤ�������ꍇ
	{
		return -1;
	}
	//�e�N�X�`�����̓o�^	���O�̔�	�ő啶����	�R�s�[���������O
	strcpy_s(g_TextureNameBroken[g_TextureIndex], 256, filename);

	int retIndex = g_TextureIndex;	//�ۑ�

	g_TextureIndex++;	//�C���N�������g

	return retIndex;	//�ǂݍ��񂾃e�N�X�`���̔ԍ���Ԃ�
}
//--------------------------------------
//�e�N�X�`���̉��
//--------------------------------------
void Uninittexture()
{
	for (int i = 0; i < g_TextureIndex; i++)
	{
		if (g_pTexture[i] !=NULL)
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}
//----------------------------------------
//�e�N�X�`���̎擾
//�����F�e�N�X�`���C���f�b�N�X
//�߂�l�F�e�N�X�`�����̃|�C���^
//---------------------------------------
ID3D11ShaderResourceView ** GetTexture(int index)
{
	//�s���l�̃`�F�b�N
	if (index <0)	//�O����
	{
		return NULL;
	}
	if (index >= g_TextureIndex)	//�ǂݍ��ݐ��I�[�o�[
	{
		return NULL;

	}

	return &g_pTexture[index];	//index���\���z��̃|�C���^
}
