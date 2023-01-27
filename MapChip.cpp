/*==============================================================================

   �}�b�v�`�b�v�Ǘ� [MapChip.cpp]
														 Author : ���؁@��
														 Date   : 2022/11/01
--------------------------------------------------------------------------------
 Update: 
 22/11/01 fusegi
 22/11/02 fusegi
 22/11/04 fusegi
==============================================================================*/

#include "MapChip.h"
#include "puzzle.h"
#include "puzzlecip.h"
#include "block.h"
#include "puzzlecip.h"
#include "warp.h"
#include "goal.h"
#include "joint.h"
#include "texture.h"
#include "sprite.h"
#include "jump_stand.h"
#include "SplitStage.h"
#include "Key.h"
#include "OpenKey.h"
#include "fallblock.h"
#include "thorn_block.h"
#include "switch.h"
#include "SwitchWall.h"
#include "StageSelect.h"
#include "SheerFloors.h"
#include "broken.h"
#include "high_broken.h"
#include "spawnpoint.h"
#include "MoveBlock.h"
#include "doppelganger.h"
#include "enemy.h"
#include "player.h"
#include "start.h"
#include "JumpStandExplain.h"
#include "StoryKey.h"
#include "lamp.h"
#include "lamp_switch.h"
#include "spawnpoint_d.h"

#include "xkeyboard.h"
#include"bullet.h"

//**************************************************
//�@�}�N����`
//**************************************************
#define PIECE_TEX_MAX	20
#define PIECE_NUMPATTERN	4
#define PIECE_UV_H	1.0f / 5
#define PIECE_UV_W	1.0f / PIECE_NUMPATTERN

//**************************************************
// �\���̒�`
//**************************************************
Piece g_PieceMapChip[PUZZLE_MAX];

//**************************************************
// �O���[�o���ϐ�:
//**************************************************
static ID3D11ShaderResourceView* g_MapChipTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
//static char* g_MapChipTextureName = (char*)"data\\texture\\black&white.jpg";	//�e�N�X�`���t�@�C���p�X
//static char* g_MapChipTextureName = (char*)"data\\texture\\�p�Y���s�[�X�C����\\16.png";	//�e�N�X�`���t�@�C���p�X
// �e�s�[�X�̃e�N�X�`���t�@�C����
static char* g_MapChipTextureName[PIECE_TEX_MAX] = {
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\00.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\01.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\02.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\03.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\04.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\05.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\06.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\07.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\08.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\09.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\10.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\11.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\12.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\13.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\14.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\15.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\16.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\17.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\18.png",
	(char*)"data\\texture\\�p�Y���s�[�X_�X�v���C�g�V�[�g\\19.png"};
// �e�e�N�X�`���̔ԍ�
static int g_MapChipTextureNo[PIECE_TEX_MAX];
// �X�e�[�W��񂪓����Ă���t�@�C���̖��O
static char* g_StageFileName[21] = {
	//(char*)"data/MapData/map.txt",			// �f�o�b�O�p�}�b�v
	(char*)"data/MapData/Stage01.txt",
	(char*)"data/MapData/Stage02.txt",
	(char*)"data/MapData/Stage03.txt",
	(char*)"data/MapData/Stage04.txt",
	(char*)"data/MapData/Stage05.txt",
	(char*)"data/MapData/Stage06.txt",
	(char*)"data/MapData/Stage07.txt",
	(char*)"data/MapData/Stage08.txt",
	(char*)"data/MapData/Stage09.txt",
	(char*)"data/MapData/Stage10.txt",
	(char*)"data/MapData/Stage11.txt",
	(char*)"data/MapData/Stage12.txt",
	(char*)"data/MapData/Stage13.txt",
	(char*)"data/MapData/Stage14.txt",
	(char*)"data/MapData/Stage15.txt",
	(char*)"data/MapData/Stage16.txt",
	(char*)"data/MapData/Stage17.txt",
	(char*)"data/MapData/Stage18.txt",
	(char*)"data/MapData/Stage19.txt",
	(char*)"data/MapData/Stage20.txt",
	(char*)"data/MapData/Stage21.txt"
};

// �e�X�e�[�W�e�s�[�X�̏��
static int g_StagePieceInfo[21][8] = {
	{  82,  180,   01,    0,    0,    0,    0,    0,},	// 1	��			 ��������������������������������������������������
	{ 121,  131,   61,    0,    0,    0,    0,    0,},	// 2  	��			 ���E21�X�e�[�W									 ��
	{  82,   91,  133,    0,    0,    0,    0,    0,},	// 3	��			 ���E�e�X�e�[�W�ő�s�[�X��7					 ��
	{  00, -131,  153,  170,    0,    0,    0,    0,},	// 4	��			 ���E�e�N�X�`���̖��O���炵���l��				 ��
	{ 182, -131,  111,  111,    0,    0,    0,    0,},	// 5	��			 ��			�\�ƕS�̈ʂ̐���					 ��
	{  32,   62,  192, -150,    0,    0,    0,    0,},	// 6	��			 ���E��̈ʂ͉�]��							 ��
	{ 182,  151,  171,   52,    0,    0,    0,    0,},	// 7	��			 ��				�e�N�X�`�����Q�l�ɍ�(�����v)��� ��
	{ 170,   00, -141,   73, -141,    0,    0,    0,},	// 8	��			 ��											     ��
	{  10,   10,   53,   33,   20,    0,    0,    0,},	// 9	��			 ���E���E�𔽓]���������ꍇ�� -(�}�C�i�X) �ɂ��� ��
	{ 143,   10,  150,   51,   61,    0,    0,    0,},	// 10	��			 ��������������������������������������������������
	{  43,  110, -131,  181,   10,    0,    0,    0,},	// 11	��							
	{ 101,  190,   72,   01,   40,    0,    0,    0,},	// 12	��						
	{  10,   43,  140,   43,   53,    0,    0,    0,},	// 13	��					
	{  52,   72,  181,   01,   10,    0,    0,    0,},	// 14	��				
	{-131, -143, -140, -151, -141,   10,    0,    0,},	// 15	��							
	{-140,  160,  171,   73,   20,   63,    0,    0,},	// 16	��							
	{ 101,  190,   60,   70,   53,   10,    0,    0,},	// 17	��							
	{  52,  190,  171, -153,  191,   10,    0,    0,},	// 18	��							
	{-131,   20,  132,  113,   10,   53, -141,    0,},	// 19	��							
	{  20,  161,   61,  132,   00,  133,  120,    0,},	// 20	��							
	{  43,  180,  160,  190,  182,  180,  112,   80,},	// 21	��							
};										 

/*�@�@�@				�@		�^�_			���G��Ȋ댯�I  �s�p�ӂɓ��ݍ��܂Ȃ������������I
*							�@�^	�_				
*							�^�E�@�E�@�_		
*						�@�^�Q_	�@�@ _�Q�_		
*							�@�b �} �b			
*							�@�b �W	�b			
*							�@�b �� �b			
*							�@�b �J �b			
*							�@�b �X �b			
*							�@�b�Q�Q�b					
*							    || ||
*							   || ||		
*/

HRESULT InitMapChip() {
	for (int p = 0; p < PUZZLE_MAX; p++) {
		g_PieceMapChip[p].UseFlag = false;
		g_PieceMapChip[p].no = -1;
		g_PieceMapChip[p].TexNo = 0;
		g_PieceMapChip[p].direction = 2;
		g_PieceMapChip[p].pos = D3DXVECTOR2(0.0f,0.0f);
		g_PieceMapChip[p].OldMovePos = g_PieceMapChip[p].OldPos = g_PieceMapChip[p].pos;
		g_PieceMapChip[p].size = D3DXVECTOR2(PIECE_SIZE, PIECE_SIZE);		// 180 x 180
		g_PieceMapChip[p].MoveEndFlag = false;
		g_PieceMapChip[p].MoveFlag = false;
		g_PieceMapChip[p].InventoryFlag = false;
		g_PieceMapChip[p].uvH = PIECE_UV_H;
		g_PieceMapChip[p].uvW = PIECE_UV_W;
		g_PieceMapChip[p].PatNo = 0;
		g_PieceMapChip[p].startAngle = 0;
		g_PieceMapChip[p].texDir = 2;
		g_PieceMapChip[p].bAnim = false;
		for (int d = 0; d < BLOCK_CHIP_DIRECTION; d++) {
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					g_PieceMapChip[p].chip[d][i][j] = 0;
				}
			}
		}
	}
	// �e�N�X�`���ǂݍ���
	for (int i = 0; i < PIECE_TEX_MAX; i++) {
		g_MapChipTextureNo[i] = LoadTexture(g_MapChipTextureName[i]);
	}

	STAGESELECT* pStageSelect = GetSelect();
	FileLoad(ReturnStageNo());	//���Ƃ�no�ɕύX����Hfusegi	yeah

	RotateChipData();

	SplitStage* pSplitStage = GetSplitStage();
	SetPieceMapChip(pSplitStage->Split34[0][0], 0);
	if (ReturnStageNo() == 20) {
		SetPieceMapChip(pSplitStage->Split34[1][1], 7);
	}

	return S_OK;
}
void UninitMapChip() {
	if (g_MapChipTexture != NULL) {
		g_MapChipTexture->Release();
		g_MapChipTexture = NULL;
	}
}
void UpdateMapChip() {
	// �A�j���[�V����
	for (Piece& p : g_PieceMapChip) {
		if (p.UseFlag &&
			p.bAnim) {
			p.PatNo += 0.5f;
			if (p.PatNo >= 16) {
				p.bAnim = false;
			}
		}
	}
}
void DrawMapChip() {
	float DrawSize;
	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (g_PieceMapChip[p].UseFlag) {
			//SetWorldViewProjection2D();

			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PieceMapChip[p].TexNo));
			if (g_PieceMapChip[p].InventoryFlag) {
				DrawSize = 150.0f;
			}
			else {
				DrawSize = PUZZLE_DRAW_SIZE;
			}

			if (g_PieceMapChip[p].uvW > 0) {
				SpriteDrawColorRotation(
					g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y, 0.0f,
					DrawSize, -DrawSize, (g_PieceMapChip[p].startAngle + g_PieceMapChip[p].texDir) * 90, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f),
					16, g_PieceMapChip[p].uvW, g_PieceMapChip[p].uvH, PIECE_NUMPATTERN
				);
			}
			else {
				SpriteDrawColorRotation(
					g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y, 0.0f,
					DrawSize, -DrawSize, (g_PieceMapChip[p].startAngle + g_PieceMapChip[p].texDir) * 90, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f),
					19, g_PieceMapChip[p].uvW, g_PieceMapChip[p].uvH, PIECE_NUMPATTERN
				);
			}
			// �A�j���[�V����������킹��
			if (g_PieceMapChip[p].bAnim) {
				SetBlendState(BLEND_MODE_ADD);
				if (g_PieceMapChip[p].no == 0) {
					SpriteDrawColorRotation(
						g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y, 0.0f,
						DrawSize, -DrawSize, (g_PieceMapChip[p].startAngle + g_PieceMapChip[p].texDir) * 90, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f),
						g_PieceMapChip[p].PatNo, g_PieceMapChip[p].uvW, g_PieceMapChip[p].uvH, PIECE_NUMPATTERN
					);
				}
				else {
					SpriteDrawColorRotation(
						g_PieceMapChip[p].pos.x, g_PieceMapChip[p].pos.y, 0.0f,
						DrawSize, -DrawSize, (g_PieceMapChip[p].startAngle + g_PieceMapChip[p].texDir) * 90, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f),
						g_PieceMapChip[p].PatNo, g_PieceMapChip[p].uvW, g_PieceMapChip[p].uvH, PIECE_NUMPATTERN
					);
				}
				SetBlendState(BLEND_MODE_ALPHABLEND);
			}
		}
	}
}
void SetMapChip(D3DXVECTOR2 pos, int no, int Pin) {
	g_PieceMapChip[Pin].size = D3DXVECTOR2(PIECE_SIZE, PIECE_SIZE);

	int brokenIndex = 0;	//����u���b�N�̌�
	int HighbrokenIndex = 0;	//��������u���b�N�̌�
	//p=�u���b�N�ő吔
		//i=y����
	for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
		//j=x����
		for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
			// ���S���W�ϐ�
			//D3DXVECTOR2 position = D3DXVECTOR2((pos.x - PUZZLE_SIZE / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - PUZZLE_SIZE / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2);
			D3DXVECTOR2 position = D3DXVECTOR2((pos.x + PUZZLE_SIZE / 2) - j * BLOCK_CHIP_SIZE - BLOCK_CHIP_SIZE / 2, (pos.y - PUZZLE_SIZE / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2);
			D3DXVECTOR2 DrawSize = D3DXVECTOR2(BLOCK_DRAW_SIZE, BLOCK_DRAW_SIZE);

			switch (g_PieceMapChip[Pin].chip[g_PieceMapChip[Pin].direction][i][j]) {
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLANK) :	//0				
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PUSH) :	//1�@��
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_BUMP,Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PULL) :	//2�@��
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_DIP,Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_NONE) :	//3�@��
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLOCK) :	//4�@��
				SetBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_CHIP) :	//5�@�A�C�e���s�[�X
				SetChipPuzzuleChip(position, DrawSize, no + 1);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_WARP) :	//6�@���[�v
				cipSetWarp(position, DrawSize,no,false);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_GOAL) :	//7�@�S�[��
				SetGoal(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_JUMP) :	//8�@�W�����v��
				SetJumpStand(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SPIKE) :	//9�@�g�Q
				SetThornBlock(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_FALL) :	//10�@���Ɨ�����u���b�N
				SetFallBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_KEY):	//11�@��
				SetKey(position, D3DXVECTOR2(25.0f,25.0f), g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_DOOR):	//12�@���t���̔�
				SetOpenKey(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCH):	//13�@�{�^��
				SetSwitch(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL3):	//14�@�{�^���ŊJ�����~3
				SetSwitchWall(position, DrawSize, no, g_PieceMapChip[no].direction, 3);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL4):	//15�@�{�^���ŊJ�����~4
				SetSwitchWall(position, DrawSize, no, g_PieceMapChip[no].direction, 4);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SHEET):	//16�@�����鏰
				SetSheerFloors(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BROKEN):	//17�@���n�ŉ��鏰
				
				SetBroken(position, DrawSize, no,brokenIndex);
				brokenIndex++;
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_HIGHBROKEN):	//18�@�W�����v�ŉ���u���b�N
				SetHigh(position, DrawSize, no,HighbrokenIndex);
				HighbrokenIndex++;

				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_MIRROR):	//19�@��
				//Set
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SPWANPOINT)://20�@�X�|�[���|�C���g
				SetSpawnPoint(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_MOVEBLOCK)://21�@�������u���b�N
				SetMoveBlock(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_DOPPELGANGER)://22�@�h�b�y���Q���K�[
				SetDoppelGanger(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMY_LEFT)://23�@�G
				SetEnemy(position, DrawSize, g_PieceMapChip[no].direction, no, ENEMY_DIRECTION::DIRECTION_LEFT);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMY_RIGHT)://24�@�G
				SetEnemy(position, DrawSize, g_PieceMapChip[no].direction, no, ENEMY_DIRECTION::DIRECTION_RIGHT);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_START):	//25 �X�^�[�g�n�_
				SetStart(position, DrawSize, g_PieceMapChip[no].direction, no);
				SetSpawnPoint(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN):	//26 �q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 26);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN2):	//27 �A�q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 27);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN3):	//28 �B�q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 28);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_BLOCKEXPLAIN):	//29 �q���g�u���b�N(Block)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 29);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMYEXPLAIN):	//30 �q���g�u���b�N(Enemy)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 30);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_BROKENEXPLAIN): //31 �q���g�u���b�N(BrokenBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 31);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_MOVEEXPLAIN):	//32 �q���g�u���b�N(MoveBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 32);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SHEEREXPLAIN):	//33 �q���g�u���b�N(SheerFloorsBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 33);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_STORYKEY):	//34 �X�g�[���[�����
				SetStoryKey(position, DrawSize, no, g_PieceMapChip[no].direction);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_LAMP):	//35 �X��
				SetLamp(position, DrawSize, no, g_PieceMapChip[no].direction, 4);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_LAMP_SWITCH):	//36 �X���X�C�b�`
				SetLampSwitch(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SPWANPOINT_D)://37�@�h�b�y���Q���K�[�̏����ʒu?
				SetSpawnPointD(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN4):	//38 �q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 38);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN5):	//39 �q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 39);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN6):	//�g���܂���
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 40);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN7):	//41 �q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 41);
				break;
			default:
				break;
			}
		}
	}
}
void FileLoad(int StageNo) {
	FILE* fp;
	//�I�[�v��
	fp = fopen(g_StageFileName[StageNo], "r");
	if (!fp) {
		exit(999);
	}
	//��X�e�[�W���ǂݍ���
	for (int p = 0; p < PUZZLE_MAX; p++) {
		for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
			for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
				fscanf(fp, "%d", &g_PieceMapChip[p].chip[0][i][j]);
			}
		}
	}
	//�N���[�Y
	fclose(fp);
}
void RotateChipData() {
	//�X�e�[�Wp
	for (int p = 0; p < PUZZLE_MAX; p++) {
		//����d
		for (int d = 0; d < BLOCK_CHIP_DIRECTION - 1; d++) {
			//i = x
			for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
				//j = y
				for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
					g_PieceMapChip[p].chip[d + 1][j][BLOCK_CHIP_ARRAY - 1 - i] =
						g_PieceMapChip[p].chip[d][i][j];
				}
			}
		}
	}
}
//==================================================
// �s�[�X��]�i�E�j
//==================================================
void RotateMapChipR(int PieceNo) {
	// �����̕ϐ��� +1
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_PieceMapChip[i].no == PieceNo)
		{
			g_PieceMapChip[i].direction++;
			g_PieceMapChip[i].texDir--;
			// 0�`3�͈̔͂���o�Ȃ��悤�ɂ���
			if (g_PieceMapChip[i].direction >= 4) {
				g_PieceMapChip[i].direction = 0;
			}
			// 0�`3�͈̔͂���o�Ȃ��悤�ɂ���
			if (g_PieceMapChip[i].texDir <= -1) {
				g_PieceMapChip[i].texDir = 3;
			}

			// �e��f���[�g
			//deleteBlock(PieceNo);
			//DeleteJoint(PieceNo);
			DeleteMapChip(i);

			// �s�[�X�č\��
			SetPieceMapChip(g_PieceMapChip[i].pos, PieceNo);
			break;
		}
	}
}
//==================================================
// �s�[�X��]�i���j
//==================================================
void RotateMapChipL(int PieceNo) {
	// �����̕ϐ��� -1
	for (int i = 0; i < PUZZLE_MAX; i++)
	{
		if (g_PieceMapChip[i].no == PieceNo)
		{

			g_PieceMapChip[i].direction--;
			g_PieceMapChip[i].texDir++;
			// 0�`3�͈̔͂���o�Ȃ��悤�ɂ���
			if (g_PieceMapChip[i].direction <= -1) {
				g_PieceMapChip[i].direction = 3;
			}
			// 0�`3�͈̔͂���o�Ȃ��悤�ɂ���
			if (g_PieceMapChip[i].texDir >= 4) {
				g_PieceMapChip[i].texDir = 0;
			}

			// �e��f���[�g
			//deleteBlock(PieceNo);
			//DeleteJoint(PieceNo);
			DeleteMapChip(i);

			// �s�[�X�č\��
			SetPieceMapChip(g_PieceMapChip[i].pos, PieceNo);
			break;
		}
	}
}
//==================================================
//�s�[�X�̉�]��C���x���g��������o���Ƃ��Ɏg���s�[�X�������֐�
//==================================================
void DeleteMapChip(int PieceNo) {


	if (g_PieceMapChip[PieceNo].UseFlag) {
		g_PieceMapChip[PieceNo].UseFlag = false;
	}
	deleteBlock(g_PieceMapChip[PieceNo].no);
	DeleteJoint(g_PieceMapChip[PieceNo].no);
	DeleteJumpStand(g_PieceMapChip[PieceNo].no);
	DeleteChipPiece(g_PieceMapChip[PieceNo].no);
	DeleteThornBlock(g_PieceMapChip[PieceNo].no);
	DeleteSwitch(g_PieceMapChip[PieceNo].no);
	DeleteSwitchWall(g_PieceMapChip[PieceNo].no);
	DeleteKey(g_PieceMapChip[PieceNo].no);
	DeleteOpenKey(g_PieceMapChip[PieceNo].no);
	DeleteFallBlock(g_PieceMapChip[PieceNo].no);
	DeleteMoveBlock(g_PieceMapChip[PieceNo].no);
	DeleteBroken(g_PieceMapChip[PieceNo].no);
	DeleteHigh(g_PieceMapChip[PieceNo].no);
	DeleteSheet(g_PieceMapChip[PieceNo].no);
	DeleteGoal(g_PieceMapChip[PieceNo].no);
	DeleteSpawnPoint(g_PieceMapChip[PieceNo].no);
	DeleteDoppelGanger(g_PieceMapChip[PieceNo].no);
	DeleteEnemy(g_PieceMapChip[PieceNo].no);
	DeleteWarp(g_PieceMapChip[PieceNo].no);
	DeleteStart(g_PieceMapChip[PieceNo].no);
	DeleteExplain(g_PieceMapChip[PieceNo].no);
	DeleteStoryKey(g_PieceMapChip[PieceNo].no);
	DeleteLamp(g_PieceMapChip[PieceNo].no);
	DeleteLampSwitch(g_PieceMapChip[PieceNo].no);
	DeleteSpawnPointD(g_PieceMapChip[PieceNo].no);
	DeleteBullet();
}
Piece* GetPiece() {
	return g_PieceMapChip;
}

//========================================
// �s�[�X�̃Z�b�g
//========================================
void SetPieceMapChip(D3DXVECTOR2 pos, int PieceNo) {
	int stageNo = ReturnStageNo();
	int PieceInfo = g_StagePieceInfo[stageNo][PieceNo];
	if (!g_PieceMapChip[PieceNo].UseFlag) {
		g_PieceMapChip[PieceNo].pos = pos;
		g_PieceMapChip[PieceNo].no = PieceNo;
		SetMapChip(pos, PieceNo, PieceNo);
		if (PieceInfo < 0) {
			g_PieceMapChip[PieceNo].uvW = -PIECE_UV_W;
		}
		else {
			g_PieceMapChip[PieceNo].uvW = PIECE_UV_W;
		}
		g_PieceMapChip[PieceNo].TexNo = g_MapChipTextureNo[abs(PieceInfo / 10)];
		g_PieceMapChip[PieceNo].startAngle = abs(PieceInfo % 10) - 2;
		g_PieceMapChip[PieceNo].InventoryFlag = false;
		g_PieceMapChip[PieceNo].UseFlag = true;
	}

	//for (int p = 0; p < PUZZLE_MAX; p++) {
	//	if (!g_PieceMapChip[p].UseFlag) {
	//		g_PieceMapChip[p].pos = pos;
	//		g_PieceMapChip[p].no = PieceNo;
	//		SetMapChip(pos, PieceNo, p);
	//		if (PieceInfo < 0) {
	//			g_PieceMapChip[p].uvW = -PIECE_UV_W;
	//		}
	//		else {
	//			g_PieceMapChip[p].uvW = PIECE_UV_W;
	//		}
	//		g_PieceMapChip[p].TexNo = g_MapChipTextureNo[abs(PieceInfo / 10)];
	//		g_PieceMapChip[p].startAngle = abs(PieceInfo % 10) - 2;
	//		g_PieceMapChip[p].InventoryFlag = false;

	//		g_PieceMapChip[p].UseFlag = true;
	//		break;
	//	}
	//}
}
//--------------------------------
//�C���x���g�����̃}�b�v�`�b�v
//--------------------------------
void SetInventoryMapChip(D3DXVECTOR2 pos, int no, int Pin) {
	int stageNo = ReturnStageNo();
	int PieceInfo = g_StagePieceInfo[stageNo][no];

	for (int p = 0; p < PUZZLE_MAX; p++) {
		if (!g_PieceMapChip[p].UseFlag) {

			g_PieceMapChip[p].size = D3DXVECTOR2(96.0f, 96.0f);
			g_PieceMapChip[p].pos = pos;
			g_PieceMapChip[p].no = no;
			g_PieceMapChip[p].InventoryFlag = true;
			Pin = p;

			if (PieceInfo < 0) {
				g_PieceMapChip[p].uvW = -PIECE_UV_W;
			}
			else {
				g_PieceMapChip[p].uvW = PIECE_UV_W;
			}
			g_PieceMapChip[p].TexNo = g_MapChipTextureNo[abs(PieceInfo / 10)];
			g_PieceMapChip[p].startAngle = abs(PieceInfo % 10) - 2;

			g_PieceMapChip[p].UseFlag = true;
			break;
		}
	}
	int brokenIndex = 0;
	int HighbrokenIndex = 0;
	//p=�u���b�N�ő吔
		//i=y����
	for (int i = 0; i < BLOCK_CHIP_ARRAY; i++) {
		//j=x����
		for (int j = 0; j < BLOCK_CHIP_ARRAY; j++) {
			// ���S���W�ϐ�
			//D3DXVECTOR2 position = D3DXVECTOR2((pos.x - PUZZLE_SIZE / 2) + j * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2, (pos.y - PUZZLE_SIZE / 2) + i * BLOCK_CHIP_SIZE + BLOCK_CHIP_SIZE / 2);
			D3DXVECTOR2 position = D3DXVECTOR2((pos.x + INVENTORY_PUZZLE_SIZE / 2) - j * 6.0f - 6.0f / 2, (pos.y - INVENTORY_PUZZLE_SIZE / 2) + i * 6.0f + 6.0f / 2);
			D3DXVECTOR2 DrawSize = D3DXVECTOR2(6.0f, 6.0f);

			switch (g_PieceMapChip[Pin].chip[g_PieceMapChip[no].direction][i][j]) {
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLANK):	//0				
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PUSH):	//1�@��
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_BUMP, Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_PULL):	//2�@��
				SetJoint(position, DrawSize, no, JOINT_TYPE::TYPE_DIP, Pin);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_NONE):	//3�@��
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BLOCK):	//4�@��
				SetBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_CHIP):	//5�@�A�C�e���s�[�X
				SetChipPuzzuleChip(position, DrawSize, no + 1);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_WARP):	//6�@���[�v
				cipSetWarp(position, DrawSize,no,true);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_GOAL):	//7�@�S�[��
				SetGoal(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_JUMP):	//8�@�W�����v��
				SetJumpStand(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SPIKE):	//9�@�g�Q
				SetThornBlock(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_FALL):	//10�@���Ɨ�����u���b�N
				SetFallBlock(position, DrawSize, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_KEY):	//11�@��
				SetKey(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_DOOR):	//12�@���t���̔�
				SetOpenKey(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCH):	//13�@�{�^��
				SetSwitch(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL3):	//14�@�{�^���ŊJ�����~3
				SetSwitchWall(position, DrawSize, no, g_PieceMapChip[no].direction, 3);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SWITCHWALL4):	//15�@�{�^���ŊJ�����~4
				SetSwitchWall(position, DrawSize, no, g_PieceMapChip[no].direction, 4);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_SHEET):	//16�@�����鏰
				SetSheerFloors(position, DrawSize, g_PieceMapChip[no].direction, no);
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_BROKEN):	//17�@���n�ŉ��鏰
				SetBroken(position, DrawSize, no, brokenIndex);
				brokenIndex++;
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_HIGHBROKEN):	//18�@���n�ŉ��鏰
				SetHigh(position, DrawSize, no, HighbrokenIndex);
				HighbrokenIndex++;
				break;
			case static_cast <int> (MAPCHIP_TYPE::TYPE_MIRROR):	//19�@��
				//Set
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SPWANPOINT)://20�@�X�|�[���|�C���g
				SetSpawnPoint(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_MOVEBLOCK)://21�@�������u���b�N
				SetMoveBlock(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_DOPPELGANGER)://22�@�h�b�y���Q���K�[
				SetDoppelGanger(position, DrawSize, no);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMY_LEFT)://23�@�G
				SetEnemy(position, DrawSize, g_PieceMapChip[no].direction, no, ENEMY_DIRECTION::DIRECTION_LEFT);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMY_RIGHT)://24�@�G
				SetEnemy(position, DrawSize, g_PieceMapChip[no].direction, no, ENEMY_DIRECTION::DIRECTION_RIGHT);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_START):	//25 �X�^�[�g�n�_
				SetStart(position, DrawSize, g_PieceMapChip[no].direction, no);
				SetSpawnPoint(position, DrawSize, no);
				break;
			//
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN):	//26 �q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 26);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN2):	//27 �A�q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 27);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_PIACEEXPLAIN3):	//28 �B�q���g�u���b�N(Piace)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 28);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_BLOCKEXPLAIN):	//29 �q���g�u���b�N(Block)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 29);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_ENEMYEXPLAIN):	//30 �q���g�u���b�N(Enemy)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 30);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_BROKENEXPLAIN): //31 �q���g�u���b�N(BrokenBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 31);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_MOVEEXPLAIN):	//32 �q���g�u���b�N(MoveBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 32);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_SHEEREXPLAIN):	//33 �q���g�u���b�N(SheerFloorsBlock)
				SetExplain(position, DrawSize, no, g_PieceMapChip[no].direction, 33);
				break;
			case static_cast<int>(MAPCHIP_TYPE::TYPE_STORYKEY):	//34 �X�g�[���[�����
				SetStoryKey(position, DrawSize, no, g_PieceMapChip[no].direction);
				break;
			default:
				break;
			}
		}
	}
}

void StartPieceAnimation(int PieceNo)
{
	for (Piece& p : g_PieceMapChip) {
		if (p.no == PieceNo &&
			p.UseFlag) {
			p.bAnim = true;
			p.PatNo = 0;
			break;
		}
	}
}
