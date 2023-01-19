//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
//#include "input.h"
//#include "keyboard.h"
#include "xkeyboard.h"
#include "mouse.h"
#include "camera.h"
#include"player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �J�����s��̃p�����[�^�[
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
//#define	POS_Y_CAM		(200.0f)		// �J�����̏����ʒu(Y���W)
//#define	POS_Z_CAM		(-400.0f)		// �J�����̏����ʒu(Z���W)
#define	POS_Y_CAM		(5.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-900.0f)		// �J�����̏����ʒu(Z���W)

// �v���W�F�N�V�����s��̃p�����[�^�[
#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(1.0f)											// �r���[���ʂ�NearZ�l	�߂�����������E����
#define	VIEW_FAR_Z		(10000.0f)										// �r���[���ʂ�FarZ�l	�����̌�������E����

#define	VALUE_MOVE_CAMERA	(1.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Camera;		// �J�����f�[�^
static CAMERA			g_Camera2;		// �J�����f�[�^

//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);	// �J�����̍��W
	g_Camera.at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �J�����̒����_
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �J�����̏�x�N�g��

	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);
	g_Camera.zoomFlag = false;
	g_Camera.fov = 45.0f;		// ����p�̏�����


	g_Camera2.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);	// �J�����̍��W
	g_Camera2.at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �J�����̒����_
	g_Camera2.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �J�����̏�x�N�g��

	g_Camera2.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	vx = g_Camera2.pos.x - g_Camera.at.x;
	vz = g_Camera2.pos.z - g_Camera.at.z;
	g_Camera2.len = sqrtf(vx * vx + vz * vz);
	g_Camera2.zoomFlag = false;
	g_Camera2.fov = 45.0f;		// ����p�̏�����
}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	PLAYER* pPlayer = GetPlayer();
	// �J�����������ɖ߂�
	if (Keyboard_IsKeyTrigger(KK_P))
	{
		UninitCamera();
		InitCamera();
	}

	// ����p��ύX����
	//if (Keyboard_IsKeyTrigger(KK_O))
	//{// �p�x��傫������
	//	g_Camera.fov += 1.0f;
	//}
	//else if (Keyboard_IsKeyTrigger(KK_L))
	//{// �p�x������������
	//	g_Camera.fov -= 1.0f;
	//}
	if (Keyboard_IsKeyDown(KK_UP))//W
	{
		g_Camera.fov = 20.0f;
		g_Camera.zoomFlag = true;
		if (g_Camera.fov < 20.0f)
		{
			g_Camera.fov = 20.0f;

		}

	}
	if (Keyboard_IsKeyDown(KK_DOWN))//S
	{
		g_Camera.fov = 48.0f;
		if (g_Camera.fov > 47.0f)
		{
			InitCamera();
			g_Camera.fov = 45.0f;

			g_Camera.zoomFlag = false;

		}

	}
	if (Keyboard_IsKeyDown(KK_Z))
	{

	}
	if (g_Camera.zoomFlag)
	{
		SetCameraAT(D3DXVECTOR3(pPlayer->Position.x, pPlayer->Position.y, 0.0f));	// �J�����̒����_
		g_Camera.pos.y = pPlayer->Position.y;
	}


}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	// DirectX�փJ�����s����Z�b�g
	SetViewMatrix(&g_Camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);
	//D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	// DirectX�փv���W�F�N�V�����s����Z�b�g
		
	// �J�����s��̋t�s����쐬

	//float det;
	//D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);

	SetProjectionMatrix(&g_Camera.mtxProjection);

}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
}

