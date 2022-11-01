#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"
#include"result.h"
//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView	*g_ResultTexture = NULL;//テクスチャ情報
static	char	*g_ResultTextureName = (char*)"data\\texture\\リザルト.jpg";
static	ID3D11ShaderResourceView	*g_ResultTexture2 = NULL;//テクスチャ情報
static	char	*g_ResultTextureName2 = (char*)"data\\texture\\スライド2.JPG";


RESULT	ResultObject;//タイトル画面オブジェクト

int		ResultTextureNo;//テクスチャ番号
int		ResultTextureNo2;//テクスチャ番号

int ResultSoundNo;	//タイトルサウンド番号
int ResultSoundNo2;	//タイトルサウンド番号

//======================
//初期化
//======================
void	InitResult()
{
	//	テクスチャのロード
	ResultTextureNo = LoadTexture(g_ResultTextureName);
	if (ResultTextureNo == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}
	//ResultTextureNo2 = LoadTexture(g_ResultTextureName2);
	//if (ResultTextureNo2 == -1)
	//{//読み込みエラー
	//	exit(999);	//強制終了
	//}

	ResultObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0);
	ResultObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject.Rotate = 0.0f;
	//ResultObject.type = LOSE;

}
//======================
//終了処理
//======================
void	UninitResult()
{
	if (g_ResultTexture)
	{
		g_ResultTexture->Release();//使い終わったので解放する
		g_ResultTexture = NULL;
	}


}

//======================
//更新処理
//======================
void	UpdateResult()
{
	//キー入力のチェック
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		SetScene(SCENE::SCENE_TITLE);


	}


}
//======================
//描画処理
//======================
void	DrawResult()
{
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();
	//テクスチャのセット
	//if (ResultObject.type ==LOSE)
	{
	//	GetDeviceContext()->PSSetShaderResources(0, 1, Gettexture(ResultTextureNo2));

	}
	//else	if (ResultObject.type == WIN)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultTextureNo));

	}
	
	//スプライトの描画
	SpriteDrawColorRotation
	(
		ResultObject.Position.x,
		ResultObject.Position.y,
		ResultObject.Size.x,
		ResultObject.Size.y,
		ResultObject.Rotate,
		ResultObject.Color,
		0,
		1.0f,
		1.0f,
		1
	);

}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject.type = ty;
}

RESULT * GetResult()
{
	return &ResultObject;
}
