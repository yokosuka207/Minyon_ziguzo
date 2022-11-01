
#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"

//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView	*g_TitleTexture1 = NULL;//テクスチャ情報
static	char	*g_TitleTextureName1 = (char*)"data\\texture\\タイトル.jpg";

static	ID3D11ShaderResourceView	*g_TitleTexture2 = NULL;//テクスチャ情報
static	char	*g_TitleTextureName2 = (char*)"data\\texture\\ジグソーワールド.jpg";

typedef	struct
{
	D3DXVECTOR3		Position;	//表示座標
	D3DXVECTOR2		Size;		//サイズ
	D3DXCOLOR		Color;		//色
	float			Rotate;		//角度
}TITLE;

TITLE	TitleObject;//タイトル画面オブジェクト

int		TitleTextureNo1;//テクスチャ番号
int		TitleTextureNo2;//テクスチャ番号

int TitleNum;
//======================
//初期化
//======================
void	InitTitle()
{
	TitleNum = 0;
	//	テクスチャのロード
	TitleTextureNo1 = LoadTexture(g_TitleTextureName1);
	if (TitleTextureNo1 == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}
	TitleTextureNo2 = LoadTexture(g_TitleTextureName2);
	if (TitleTextureNo2 == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}

	TitleObject.Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	TitleObject.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	TitleObject.Color = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	TitleObject.Rotate = 0.0;


}
//======================
//終了処理
//======================
void	UninitTitle()
{
	if (g_TitleTexture1)
	{
		g_TitleTexture1->Release();
		g_TitleTexture1 = NULL;
	}


	if (g_TitleTexture2)
	{
		g_TitleTexture2->Release();
		g_TitleTexture2 = NULL;
	}

}

//======================
//更新処理
//======================
void	UpdateTitle()
{
	//キー入力のチェック
	if (GetKeyboardTrigger(DIK_A))
	{
		if (TitleNum == 1)
		{
			SetScene(SCENE::SCENE_GAME);

		}
		if (TitleNum == 0)
		{
			TitleNum++;
		}
	}


}
//======================
//描画処理
//======================
void	DrawTitle()
{
	//２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();
	//テクスチャのセット
	if (TitleNum == 0)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo1));
	}
	if (TitleNum == 1)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TitleTextureNo2));
	}

	//スプライトの描画
	SpriteDrawColorRotation
	(
		TitleObject.Position.x,
		TitleObject.Position.y,
		TitleObject.Size.x,
		TitleObject.Size.y,
		TitleObject.Rotate,
		TitleObject.Color,
		0,
		1.0f,
		1.0f,
		1
	);


}



