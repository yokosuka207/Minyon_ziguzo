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
//マクロ定義
//--------------------


//--------------------
//グローバル変数
//--------------------

void PLAYER3D::Init()
{
	//LoadModel((char*)"data/MODEL/sl.obj", &Model);//初期化で一回のみ

	//行列の初期化
	D3DXMatrixIdentity(&WorldMatrix);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixIdentity(&TranslationMatrix);
	D3DXMatrixIdentity(&ScalingMatrix);
	//ベクトルの初期化
	D3DXVECTOR3	temp(0.0f, 0.0f, -100.0f);
	SetPosition(temp);
	temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetRotation(temp);
	temp.x = temp.y = temp.z = 1.0f;
	SetScaling(temp);


	//スケーリング行列
	D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
	//回転行列作成
	D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
	//平行移動行列
	D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

	D3DXMatrixMultiply(&WorldMatrix, &ScalingMatrix, &RotationMatrix);	//tempM = Scaling* Rotation
	D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TranslationMatrix);	//tempM = tempM* Translation

	//使用フラグをおン
	SetUse(true);

}

void PLAYER3D::Uninit()
{
	//モデルデータの解放
	//UnloadModel(&Model);
}

void PLAYER3D::Update()
{
	PLAYER* pPlayer = GetPlayer();

	{
		//グローバル座標
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


	{//グローバル座標で移動する


		//D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
		//回転行列作成
		//D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
		//平行移動行列
		D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

		//ワールド行列の作成	World = Scaling * Rotation * Translation	順番注意(この順じゃないといけない)
		D3DXMatrixMultiply(&WorldMatrix,&ScalingMatrix,&RotationMatrix);	//World = Scaling* Rotation
		D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &TranslationMatrix);	//World = World* Translation

			//ワールド行列の作成	World = Scaling * Translation * Rotation	順番注意(この順じゃないといけない)
		//D3DXMatrixMultiply(&WorldMatrix, &ScalingMatrix, &TranslationMatrix);	//World = Scaling* Rotation
		//D3DXMatrixMultiply(&WorldMatrix, &WorldMatrix, &RotationMatrix);	//World = World* Translation
	}
	//ワールド行列をセット
	SetWorldMatrix(&WorldMatrix);
	//SetWorldMatrix(&tempM);

	//表示リクエスト
	//DrawModel(&Model);
}
