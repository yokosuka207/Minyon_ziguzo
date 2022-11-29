#include	"main.h"
#include	"renderer.h"
#include	"texture.h"
#include	"sprite.h"
#include	"input.h"
#include	"scene.h"
#include	"result.h"
#include	"mouse.h"
//======================
//マクロ定義
//=======================
//======================
//グローバル変数
//======================
static	ID3D11ShaderResourceView* g_ResultTexture = NULL;//テクスチャ情報
static	char* g_ResultTextureName = (char*)"data\\texture\\リザルト.jpg";

static	ID3D11ShaderResourceView* g_ResultGameEndTexture = NULL;//テクスチャ情報
static	char* g_ResultGameEndTextureName = (char*)"data\\texture\\GameEnd_haikei.jpg";

static	ID3D11ShaderResourceView* g_ResultTextureButton = NULL;//テクスチャ情報
static	char* g_ResultButtonTextureName = (char*)"data\\texture\\GameEnd_contie_button.jpg";

static	ID3D11ShaderResourceView* g_ResultTextureButton2 = NULL;//テクスチャ情報
static	char* g_ResultButtonTextureName2 = (char*)"data\\texture\\GameEnd_end_button.jpg";


RESULT	ResultObject[3];//タイトル画面オブジェクト	テクスチャ枚数分の配列

int		ResultTextureNo;//テクスチャ番号

int		ResultGameEndTextureNo;//テクスチャ番号
int		ResultButtonTextureNo;//テクスチャ番号
int		ResultButtonTextureNo2;//テクスチャ番号

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
	ResultGameEndTextureNo = LoadTexture(g_ResultGameEndTextureName);
	if (ResultGameEndTextureNo == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}
	ResultButtonTextureNo = LoadTexture(g_ResultButtonTextureName);
	if (ResultButtonTextureNo == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}
	ResultButtonTextureNo2 = LoadTexture(g_ResultButtonTextureName2);
	if (ResultButtonTextureNo2 == -1)
	{//読み込みエラー
		exit(999);	//強制終了
	}

	ResultObject[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	ResultObject[0].Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	ResultObject[0].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[0].Rotate = 0.0f;
	//ResultObject[0].type = LOSE;

	ResultObject[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 0);
	ResultObject[1].Size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8);
	ResultObject[1].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[1].Rotate = 0.0f;

	ResultObject[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 0);
	ResultObject[2].Size = D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 8);
	ResultObject[2].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ResultObject[2].Rotate = 0.0f;

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

	if (g_ResultGameEndTexture)
	{
		g_ResultGameEndTexture->Release();//使い終わったので解放する
		g_ResultGameEndTexture = NULL;
	}

	if (g_ResultTextureButton)
	{
		g_ResultTextureButton->Release();//使い終わったので解放する
		g_ResultTextureButton = NULL;
	}

	if (g_ResultTextureButton2)
	{
		g_ResultTextureButton2->Release();//使い終わったので解放する
		g_ResultTextureButton2 = NULL;
	}

}

//======================
//更新処理
//======================
void	UpdateResult()
{
	if (ResultObject[0].type == WIN) 
	{
		//キー入力のチェック
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			SetScene(SCENE::SCENE_TITLE);
		}
	}
	else if (ResultObject[0].type == LOSE)
	{
		MOUSE* pMouse = GetMouse();
		D3DXVECTOR2 MousePos = D3DXVECTOR2(GetMousePosX(), GetMousePosY());		// マウスの座標

		// 当たり判定用座標
		D3DXVECTOR2 min, max, min2, max2;		// min左上, max右下
		min = D3DXVECTOR2(ResultObject[1].Position.x - ResultObject[1].Size.x / 2, ResultObject[1].Position.y - ResultObject[1].Size.y / 2);
		max = D3DXVECTOR2(ResultObject[1].Position.x + ResultObject[1].Size.x / 2, ResultObject[1].Position.y + ResultObject[1].Size.y / 2);
		min2 = D3DXVECTOR2(ResultObject[2].Position.x - ResultObject[2].Size.x / 2, ResultObject[2].Position.x - ResultObject[2].Size.x / 2);
		max2 = D3DXVECTOR2(ResultObject[2].Position.x + ResultObject[2].Size.x / 2, ResultObject[2].Position.x + ResultObject[2].Size.x / 2);

		// マウスとcontinyボタンの当たり判定
		if (IsMouseLeftPressed())
		{
			if (min.x < MousePos.x && max.x > MousePos.x && min.y < MousePos.y && max.y > MousePos.y) 
			{
				SetScene(SCENE::SCENE_GAME);
			}
		}
		
		// マウスと終了ボタンの当たり判定
		if (IsMouseLeftPressed())
		{
			if (min2.x < MousePos.x && max2.x > MousePos.x && min2.y < MousePos.y && max2.y > MousePos.y)
			{
				SetScene(SCENE::SCENE_TITLE);
			}
		}
		
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
	if (ResultObject[0].type == LOSE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultGameEndTextureNo));
		//スプライトの描画
		SpriteDrawColorRotation
		(
			ResultObject[0].Position.x,
			ResultObject[0].Position.y,
			ResultObject[0].Size.x,
			ResultObject[0].Size.y,
			ResultObject[0].Rotate,
			ResultObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultButtonTextureNo));
		SpriteDrawColorRotation
		(//countinuButton
			ResultObject[1].Position.x,
			ResultObject[1].Position.y,
			ResultObject[1].Size.x,
			ResultObject[1].Size.y,
			ResultObject[1].Rotate,
			ResultObject[1].Color,
			0,
			1.0f,
			1.0f,
			1
		);

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultButtonTextureNo2));
		SpriteDrawColorRotation
		(//endButton
			ResultObject[2].Position.x,
			ResultObject[2].Position.y,
			ResultObject[2].Size.x,
			ResultObject[2].Size.y,
			ResultObject[2].Rotate,
			ResultObject[2].Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}
	else if (ResultObject[0].type == WIN)
	{

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(ResultTextureNo));

		//スプライトの描画
		SpriteDrawColorRotation
		(
			ResultObject[0].Position.x,
			ResultObject[0].Position.y,
			ResultObject[0].Size.x,
			ResultObject[0].Size.y,
			ResultObject[0].Rotate,
			ResultObject[0].Color,
			0,
			1.0f,
			1.0f,
			1
		);
	}

}

void SetResultType(RESULT_TYPE ty)
{
	ResultObject[0].type = ty;
}

RESULT* GetResult()
{
	return &ResultObject[0];
}
