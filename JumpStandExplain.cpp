
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "xinput.h"
#include "xkeyboard.h"
#include "collision.h"
#include "JumpStandExplain.h"
#include "camera.h"

static EXPLAIN g_Explain[EXPLAIN_MAX];

// �q���g�\���I�u�W�F�N�g
static ID3D11ShaderResourceView* g_ExplainBlock;
static char* g_ExplainBlockName = (char*)"data\\texture\\�q���g�u���b�N.png";
static int	  g_ExplainBlockNo = 0;

// Piace �q���g
//=====================================================
// ���肵���s�[�X�����A�͂ށA�Ȃ���A�ړ��ł���
//=====================================================
static char* g_PiaceExplainName = (char*)"data\\texture\\PiaceExplain.png";
static int	  g_PiaceExplainNo = 0;
// Piace2 �q���g
//=====================================================
// ��]�ł���
//=====================================================
static char* g_Piace2ExplainName = (char*)"data\\texture\\PiaceExplain2.png";
static int	  g_Piace2ExplainNo = 0;
// Piace3 �q���g
//=====================================================
// �S�[������
//=====================================================
static char* g_Piace3ExplainName = (char*)"data\\texture\\PiaceExplain3.png";
static int	  g_Piace3ExplainNo = 0;
// Piace4 �q���g
//=====================================================
// �v���C���[������ۂɃs�[�X�ړ��ł���A��]�͂ł��Ȃ�
//=====================================================
static char* g_Piace4ExplainName = (char*)"data\\texture\\PiaceExplain4.png";
static int	  g_Piace4ExplainNo = 0;
// Piace5 �q���g
//=====================================================
// �s�[�X��]�A���Z�b�g�����
//=====================================================
static char* g_Piace5ExplainName = (char*)"data\\texture\\PiaceExplain5.png";
static int	  g_Piace5ExplainNo = 0;
// Piace6 �q���g
//=====================================================
// 
//=====================================================
//static ID3D11ShaderResourceView* g_Piace6Explain;
//static char* g_Piace6ExplainName = (char*)"data\\texture\\Piace6Explain.png";
//static int	  g_Piace6ExplainNo = 0;

// Piace7 �q���g
//=====================================================
// ���L�y�[�W�E��
//=====================================================
static char* g_Piace7ExplainName = (char*)"data\\texture\\PiaceExplain7.png";
static int	  g_Piace7ExplainNo = 0;

// Block �q���g
//=====================================================
// �s�[�X�̉�]�ɂ���ău���b�N��������
//=====================================================
static char* g_BlockExplainName = (char*)"data\\texture\\BlockExplain.png";
static int	  g_BlockExplainNo = 0;
// Enemy �q���g
//=====================================================
// �G����
//=====================================================
static char* g_EnemyExplainName = (char*)"data\\texture\\EnemyExplain.png";
static int	  g_EnemyExplainNo = 0;
// BrokenBlock �q���g
//=====================================================
// �Ђъ��ꂽ���@��������
//=====================================================
static char* g_BrokenExplainName = (char*)"data\\texture\\BrokenExplain.png";
static int	  g_BrokenExplainNo = 0;
// MoveBlock �q���g
//=====================================================
// ���̏�ɏd����������
//=====================================================
static char* g_MoveExplainName = (char*)"data\\texture\\MoveExplain.png";
static int	  g_MoveExplainNo = 0;
// SheerBlock �q���g
//=====================================================
// ������u���b�N�̏����
//=====================================================
static char* g_SheerExplainName = (char*)"data\\texture\\Piace6Explain.png";
static int	  g_SheerExplainNo = 0;


HRESULT InitExplain()
{
	//�q���g�\���u���b�N������
	g_ExplainBlockNo = LoadTexture(g_ExplainBlockName);

	
	g_PiaceExplainNo = LoadTexture(g_PiaceExplainName);
	g_Piace2ExplainNo = LoadTexture(g_Piace2ExplainName);
	g_Piace3ExplainNo = LoadTexture(g_Piace3ExplainName);
	g_Piace4ExplainNo = LoadTexture(g_Piace4ExplainName);
	g_Piace5ExplainNo = LoadTexture(g_Piace5ExplainName);
	//g_Piace6ExplainNo = LoadTexture(g_Piace6ExplainName);
	g_Piace7ExplainNo = LoadTexture(g_Piace7ExplainName);
	g_BlockExplainNo = LoadTexture(g_BlockExplainName);
	g_EnemyExplainNo = LoadTexture(g_EnemyExplainName);
	g_BrokenExplainNo = LoadTexture(g_BrokenExplainName);
	g_MoveExplainNo = LoadTexture(g_MoveExplainName);
	g_SheerExplainNo = LoadTexture(g_SheerExplainName);

	for (int i = 0; i < EXPLAIN_MAX; i++) {
		g_Explain[i].pos = D3DXVECTOR2(-127, 150);
		g_Explain[i].size = D3DXVECTOR2(EXPLAIN_SIZE, EXPLAIN_SIZE);
		g_Explain[i].rot = 0.0f;
		g_Explain[i].PieceIndex = -1;
		g_Explain[i].bUse = false;
	}

	return S_OK;
}

void UninitExplain()
{
	
}

void UpdateExplain()
{
	CAMERA* pCamera = GetCamera();
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].CollisionUse && 
			pCamera->fov != 45.0f)
		{
			if (Keyboard_IsKeyTrigger(KK_LEFTCONTROL) ||					// keyboard Ctrl ��
				Keyboard_IsKeyTrigger(KK_C) ||								// keyboard C
				IsButtonTriggered(0, XINPUT_GAMEPAD_B)) {					// GamePad B
				if (g_Explain[i].No == 0) {
					g_Explain[i].HintUse = true;
					g_Explain[i].No++;
				}
				else if (g_Explain[i].No == 1) {
					g_Explain[i].HintUse = false;
					g_Explain[i].No--;
				}
			}
		}
		else{
			g_Explain[i].HintUse = false;
			g_Explain[i].No = 0;
		}
	}
}

void DrawExplain()
{
	//SetWorldViewProjection2D();

	//�q���g�u���b�N
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].bUse)
		{
			//�u���b�N�\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ExplainBlockNo));

			SpriteDrawColorRotation(g_Explain[i].pos.x, g_Explain[i].pos.y, 0.0f,
				g_Explain[i].size.x, g_Explain[i].size.y, g_Explain[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0, 1.0f, 1.0f, 1);


			//�q���g�\��
			if (g_Explain[i].HintUse)
			{
				SetWorldViewProjection2D();

				switch (g_Explain[i].tex) {
				case 26:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PiaceExplainNo));
					break;
				case 27:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace2ExplainNo));
					break;
				case 28:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace3ExplainNo));
					break;
				case 29:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BlockExplainNo));
					break;
				case 30:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EnemyExplainNo));
					break;
				case 31:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BrokenExplainNo));
					break;
				case 32:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_BlockExplainNo));
					break;
				case 33:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SheerExplainNo));
					break;
				case 38:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace4ExplainNo));
					break;
				case 39:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace5ExplainNo));
					break;
				//case 40:
				//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace6ExplainNo));
				//	break;
				case 41:
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Piace7ExplainNo));
					break;
				}
				SpriteDrawColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f,
					HINT_SIZE_X, HINT_SIZE_Y, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					0, 1.0f, 1.0f, 1);
			}
		}
	}
}


void SetExplain(D3DXVECTOR2 pos, D3DXVECTOR2 size, int no, int direction, int q)
{
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (!g_Explain[i].bUse)
		{
			switch (direction) {
			case 0:g_Explain[i].rot = direction * 90;
				break;
			case 1:g_Explain[i].rot = (direction + 2) * 90;
				break;
			case 2:g_Explain[i].rot = direction * 90;
				break;
			case 3:g_Explain[i].rot = (direction - 2) * 90;
				break;
			default:
				break;
			}

			g_Explain[i].pos = pos;
			g_Explain[i].size = size;
			g_Explain[i].bUse = true;
			g_Explain[i].PieceIndex = no;

			g_Explain[i].tex = q;

			break;
		}

	}
}

EXPLAIN* GetExplain()
{
	return &g_Explain[0];
}

void DeleteExplain(int PieceNo)
{
	for (int i = 0; i < EXPLAIN_MAX; i++) {
		if (g_Explain[i].bUse) {
			if(g_Explain[i].PieceIndex == PieceNo)
			g_Explain[i].bUse = false;
		}
	}
}
