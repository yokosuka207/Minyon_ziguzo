
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);					//サウンド初期化(windowsのハンドル)
void UninitSound(void);						//サウンドの終了

int LoadSound(char* pFilename);				//サウンドの読み込み("ファイルネーム")
void PlaySound(int index, int loopCount);	//サウンドの再生(再生したい曲,下記参照)
											//loopCount = 0 :一回再生
											//loopCount < 0 :ループ
											//loopCount = 1 :2回再生
void StopSound(int index);					//サウンドの停止(停止する曲)
void StopSoundAll(void);					//すべてのサウンドの停止
void SetVolume(int index, float vol);		//音量の設定(設定したい曲,音量)
