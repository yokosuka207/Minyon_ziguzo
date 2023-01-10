//--------------------------------------------------------------------------------------
// File: Keyboard.cpp
//
// �L�[�{�[�h���W���[��
//
//--------------------------------------------------------------------------------------
// 2020/06/07
//     DirectXTK���A�Ȃ񂿂����C����p�ɃV�F�C�v�A�b�v����
//
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------
#include "xkeyboard.h"

#include <assert.h>


static_assert(sizeof(Keyboard_State) == 256 / 8, "�L�[�{�[�h��ԍ\���̂̃T�C�Y�s��v");


static Keyboard_State gState = {};

//-----����-----
#define KEY_MAX    6        // �L�[�`�F�b�N�z��
Keyboard_Keys g_DownKeys[KEY_MAX] = { KK_NONE };


static void keyDown(int key)
{
    if (key < 0 || key > 0xfe) { return; }

    unsigned int* p = (unsigned int*)&gState;
    unsigned int bf = 1u << (key & 0x1f);
    p[(key >> 5)] |= bf;
}


static void keyUp(int key)
{
    if (key < 0 || key > 0xfe) { return; }

    unsigned int* p = (unsigned int*)&gState;
    unsigned int bf = 1u << (key & 0x1f);
    p[(key >> 5)] &= ~bf;
}


void Keyboard_Initialize(void)
{
    Keyboard_Reset();
}


bool Keyboard_IsKeyDown(Keyboard_Keys key, const Keyboard_State* pState)
{


    if (key <= 0xfe)
    {
        unsigned int* p = (unsigned int*)pState;
        unsigned int bf = 1u << (key & 0x1f);
        return (p[(key >> 5)] & bf) != 0;
    }
    return false;
}


bool Keyboard_IsKeyUp(Keyboard_Keys key, const Keyboard_State* pState)
{
    if (key <= 0xfe)
    {
        unsigned int* p = (unsigned int*)pState;
        unsigned int bf = 1u << (key & 0x1f);
        return (p[(key >> 5)] & bf) == 0;
    }
    return false;
}

bool Keyboard_IsKeyDown(Keyboard_Keys key)
{
    return Keyboard_IsKeyDown(key, &gState);
}


bool Keyboard_IsKeyUp(Keyboard_Keys key)
{
    return Keyboard_IsKeyUp(key, &gState);
}


//[-----����-----
bool Keyboard_IsKeyTrigger(Keyboard_Keys key)
{
    if (Keyboard_IsKeyDown(key)) {
        int i;
        for (i = 0; i < KEY_MAX; i++) {
            if (g_DownKeys[i] == key) {
                break;
            }
        }
        if (i == KEY_MAX) {
            for (int i = 0; i < KEY_MAX; i++) {
                if (KK_NONE == g_DownKeys[i]) {
                    g_DownKeys[i] = key;
                    return true;
                }
            }
        }
    }
    else {
        for (int i = 0; i < KEY_MAX; i++) {
            if (g_DownKeys[i] == key) {
                g_DownKeys[i] = KK_NONE;
                break;
            }
        }
    }
    return false;
}

bool Keyboard_IsKeyRelease(Keyboard_Keys key)
{
    if (Keyboard_IsKeyDown(key)) {
        int i;
        for (i = 0; i < KEY_MAX; i++) {
            if (g_DownKeys[i] == key) {
                break;
            }
        }
        if (i == KEY_MAX) {
            for (int i = 0; i < KEY_MAX; i++) {
                if (KK_NONE == g_DownKeys[i]) {
                    g_DownKeys[i] = key;
                    break;
                }
            }
        }
    }
    else {
        for (int i = 0; i < KEY_MAX; i++) {
            if (g_DownKeys[i] == key) {
                g_DownKeys[i] = KK_NONE;
                return true;
            }
        }
    }
    return false;
}
//-----����-----]

// �L�[�{�[�h�̌��݂̏�Ԃ��擾����
const Keyboard_State* Keyboard_GetState(void)
{
    return &gState;
}


void Keyboard_Reset(void)
{
    ZeroMemory(&gState, sizeof(Keyboard_State));
}


// �L�[�{�[�h����̂��߂̃E�H���ǂ����b�Z�[�W�v���V�[�W���t�b�N�֐�
void Keyboard_ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    bool down = false;

    switch (message)
    {
    case WM_ACTIVATEAPP:
        Keyboard_Reset();
        return;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        down = true;
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        break;

    default:
        return;
    }

    int vk = (int)wParam;
    switch (vk)
    {
    case VK_SHIFT:
        vk = (int)MapVirtualKey(((unsigned int)lParam & 0x00ff0000) >> 16u, MAPVK_VSC_TO_VK_EX);
        if (!down)
        {
            // ���V�t�g�ƉE�V�t�g�̗����������ɉ����ꂽ�ꍇ�ɃN���A�����悤�ɂ��邽�߂̉����
            keyUp(VK_LSHIFT);
            keyUp(VK_RSHIFT);
        }
        break;

    case VK_CONTROL:
        vk = ((UINT)lParam & 0x01000000) ? VK_RCONTROL : VK_LCONTROL;
        break;

    case VK_MENU:
        vk = ((UINT)lParam & 0x01000000) ? VK_RMENU : VK_LMENU;
        break;
    }

    if (down)
    {
        keyDown(vk);
    }
    else
    {
        keyUp(vk);
    }
}
