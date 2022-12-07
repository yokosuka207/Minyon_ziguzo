//--------------------------
//player.cpp
//--------------------------

#include"main.h"
#include"inputx.h"
#include"keyboard.h"
#include"camera.h"
#include"texture.h"

#include"player3D.h"


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
	{
		//�O���[�o�����W
		MoveSpeed.x = MoveSpeed.y = MoveSpeed.z = 0.0f;
		if (Keyboard_IsKeyDown(KK_W))//W
		{
			MoveSpeed.y = MOVE_SPEED;
		}
		if (Keyboard_IsKeyDown(KK_S))//S
		{
			MoveSpeed.y = -MOVE_SPEED;
		}
		if (Keyboard_IsKeyDown(KK_A))//A
		{
			MoveSpeed.x += -MOVE_SPEED;
		}
		if (Keyboard_IsKeyDown(KK_D))//D
		{
			MoveSpeed.x += MOVE_SPEED;
		}

		if (Keyboard_IsKeyDown(KK_UP))//W
		{
			MoveSpeed.z = MOVE_SPEED;
		}
		if (Keyboard_IsKeyDown(KK_DOWN))//S
		{
			MoveSpeed.z = -MOVE_SPEED;
		}


		Position += MoveSpeed;

	}

	//{//���[�J�����W�œ���
	//	Rotation.x = Rotation.y = Rotation.z = 0.0f;

	//	if (Keyboard_IsKeyDown(KK_A))//A
	//	{
	//		Rotation.y = D3DXToRadian(-ROTAION_SPEED);
	//	}
	//	if (Keyboard_IsKeyDown(KK_D))//D
	//	{
	//		Rotation.y = D3DXToRadian(ROTAION_SPEED);
	//	}
	//	MoveSpeed.x = MoveSpeed.y = MoveSpeed.z = 0.0f;

	//	if (Keyboard_IsKeyDown(KK_W))//W
	//	{
	//		MoveSpeed.z = MOVE_SPEED;
	//	}
	//}

}

void PLAYER3D::Draw()
{


	{	//���[�J�����W�ňړ�����
			//�X�P�[�����O�s��
		//D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
		////��]�s��쐬
		//D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
		////���s�ړ��s��
		//D3DXMatrixTranslation(&TranslationMatrix, MoveSpeed.x, MoveSpeed.y, MoveSpeed.z);

		//D3DXMATRIX	tempM;	//����̓�����\�����[���h�s��

		//D3DXMatrixMultiply(&tempM, &ScalingMatrix, &RotationMatrix);	//tempM = Scaling* Rotation
		//D3DXMatrixMultiply(&tempM, &tempM, &TranslationMatrix);	//tempM = tempM* Translation

		//D3DXMatrixMultiply(&WorldMatrix, &tempM, &WorldMatrix);
	}
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
