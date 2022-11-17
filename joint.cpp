/*================================================================================

	���ʏ���[joint.cpp]

												Author: ꎓ� ��o
												 Date : 2022/11/16
----------------------------------------------------------------------------------
Update:
	
================================================================================*/
#include "joint.h"
#include "texture.h"
#include "sprite.h"

//**************************************************
// �}�N����`
//**************************************************

//**************************************************
// �v���g�^�C�v�錾
//**************************************************

//**************************************************
// �O���[�o���ϐ�
//**************************************************
JOINT g_Joint[JOINT_MAX];

// �e�N�X�`���̖��O
static char* g_JointTextureName = (char*)"data\\texture\\yello.jpg";


//==================================================
// ���ʏ�����
//==================================================
void InitJoint()
{
	// �e�N�X�`���ԍ������炤
	float texNo = LoadTexture(g_JointTextureName);

	// �e���ʂ̊e�p�����[�^�̏�����
	for (int i = 0; i < JOINT_MAX; i++) {
		g_Joint[i].pos = D3DXVECTOR2(0.0f, 0.0f);			
		g_Joint[i].size = D3DXVECTOR2(0.0f, 0.0f);	
		g_Joint[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Joint[i].pieNo = -1;								
		g_Joint[i].type = JOINT_TYPE::TYPE_BUMP;	
		g_Joint[i].texNo = texNo;

		g_Joint[i].useFlag = false;							
	}
}


//==================================================
// ���ʏI������
//==================================================
void UninitJoint()
{

}


//==================================================
// ���ʍX�V����
//==================================================
void UpdateJoint()
{
	// �ڐA�\��̓����蔻��
	for (int i = 0; i < JOINT_MAX; i++) {
		// �g�p��
		if (g_Joint[i].useFlag) {
			for (int j = i + 1; j < JOINT_MAX; j++) {
				// �g�p��
				if (g_Joint[j].useFlag) {
					// �����蔻��p�ϐ�
					D3DXVECTOR2 iMin, iMax;
					iMin = D3DXVECTOR2(g_Joint[i].pos.x - g_Joint[i].size.x, g_Joint[i].pos.y - g_Joint[i].size.y);
					iMax = D3DXVECTOR2(g_Joint[i].pos.x + g_Joint[i].size.x, g_Joint[i].pos.y + g_Joint[i].size.y);

					// �������Ă�I			(i �̊O�g�� j �̒��S���W�Ŕ���)
					if (iMin.x < g_Joint[j].pos.x && iMax.x > g_Joint[j].pos.x && iMin.y < g_Joint[j].pos.y && iMax.y < g_Joint[j].pos.y) {
						// ��������
					}
				}
			}
		}
	}
}


//==================================================
// ���ʕ`�揈��
//==================================================
void DrawJoint()
{
	// ���ʂ̕`��
	for (int i = 0; i < JOINT_MAX; i++){
		if (g_Joint[i].useFlag) {
			// �e�N�X�`���̐ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Joint[i].texNo));
			// �l�p�`�̕`��
			SpriteDrawColorRotation(g_Joint[i].pos.x, g_Joint[i].pos.y, g_Joint[i].size.x, g_Joint[i].size.y, 0.0f, g_Joint[i].color, 1.0f, 1.0f, 1.0f, 1);
		}
	}
}


//==================================================
// ���ʃZ�b�g�֐�
//==================================================
void SetJoint(D3DXVECTOR2 po, D3DXVECTOR2 si, int no, JOINT_TYPE ty)
{
	for (int i = 0; i < JOINT_MAX; i++) {
		// ���g�p�Ȃ�����̊e�l����
		if (!g_Joint[i].useFlag) {
			g_Joint[i].pos = po;
			g_Joint[i].size = si;
			g_Joint[i].pieNo = no;
			g_Joint[i].type = ty;

			g_Joint[i].useFlag = true;

			break;
		}
	}
}


//==================================================
// ���ʃQ�b�g�֐�
//==================================================
JOINT* GetJoint()
{
	return g_Joint;
}


//==================================================
// ���ʃf���[�g�֐�
//==================================================
void DeleteJoint(int no)
{
	for (int i = 0; i < JOINT_MAX; i++) {
		// �g�p���ň����Ɠ����ԍ��Ȃ疢�g�p�ɂ���
		if (g_Joint[i].useFlag && g_Joint[i].pieNo == no) {
			g_Joint[i].useFlag = false;
		}
	}
}
