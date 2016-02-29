#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

namespace WinProg
{
	LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}