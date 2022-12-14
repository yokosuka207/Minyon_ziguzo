//--------------------------
//player.cpp
//--------------------------

#include"main.h"
#include"input.h"
//#include"keyboard.h"
#include"camera.h"
#include"texture.h"

#include"player3D.h"
#include"player.h"

//--------------------
//�}�N����`
//--------------------


//--------------------
//�O���[�o���ϐ�
//--------------------

void PLAYER3D::Init()
{
	//LoadModel((char*)"data/MODEL/sl.obj", &Model);//�������ň��̂�

	//�s��̏�����
	D3DXMatrixIdentity(&WorldMatrix);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixIdentity(&TranslationMatrix);
	D3DXMatrixIdentity(&ScalingMatrix);
	//�x�N�g���̏�����
	D3DXVECTOR3	temp(0.0f, 0.0f, -100.0f);
	SetPosition(temp);
	temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetRotation(temp);
	temp.x = temp.y = temp.z = 1.0f;
	SetScaling(temp);


	//�X�P�[�����O�s��
	D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
	//��]�s��쐬
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
	//���s�ړ��s��
	D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

	D3DXMatrixMultiply(&WorldMatrix, &ScalingMatrix, &RotationMatrix);	//tempM = Scaling* Rotation
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TranslationMatrix);	//tempM = tempM* Translation

	//�g�p�t���O������
	SetUse(true);

}

void PLAYER3D::Uninit()
{
	//���f���f�[�^�̉��
	//UnloadModel(&Model);
}

void PLAYER3D::Update()
{
	PLAYER* pPlayer = GetPlayer();

	{
		//�O���[�o�����W
		MoveSpeed.x = MoveSpeed.y = MoveSpeed.z = 0.0f;
		if (GetKeyboardPress(DIK_W))//W
		{
			//MoveSpeed.y = -MOVE_SPEED;
		}
		if (GetKeyboardPress(DIK_S))//S
		{
			//MoveSpeed.y = MOVE_SPEED;
		}
		if (GetKeyboardPress(DIK_A))//A
		{
			//MoveSpeed.x += -MOVE_SPEED;
		}
		if (GetKeyboardPress(DIK_D))//D
		{
			//MoveSpeed.x += MOVE_SPEED;
		}

		//if (GetKeyboardPress(DIK_UP))//W
		//{
		//	MoveSpeed.z = MOVE_SPEED;
		//	zoomFlag = true;
		//}
		//if (GetKeyboardPress(DIK_DOWN))//S
		//{

		//	MoveSpeed.z = -MOVE_SPEED;
		//}
		//if (GetKeyboardPress(DIK_Z))
		//{
		//	Position = D3DXVECTOR3(0.0f,0.0f,0.0f);
		//	zoomFlag = false;

		//}



		Position += MoveSpeed;

	}


}

void PLAYER3D::Draw()
{


	{//�O���[�o�����W�ňړ�����


		//D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
		//��]�s��쐬
		//D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
		//���s�ړ��s��
		D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

		//���[���h�s��̍쐬	World = Scaling * Rotation * Translation	���Ԓ���(���̏�����Ȃ��Ƃ����Ȃ�)
		D3DXMatrixMultiply(&WorldMatrix,&ScalingMatrix,&RotationMatrix);	//World = Scaling* Rotation
		D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TranslationMatrix);	//World = World* Translation

			//���[���h�s��̍쐬	World = Scaling * Translation * Rotation	���Ԓ���(���̏�����Ȃ��Ƃ����Ȃ�)
		//D3DXMatrixMultiply(&WorldMatrix, &ScalingMatrix, &TranslationMatrix);	//World = Scaling* Rotation
		//D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &RotationMatrix);	//World = World* Translation
	}
	//���[���h�s����Z�b�g
	SetWorldMatrix(&WorldMatrix);
	//SetWorldMatrix(&tempM);

	//�\�����N�G�X�g
	//DrawModel(&Model);
}
