//win_proc.cpp

#include "win_proc.h"

namespace WinProg
{
	LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_DESTROY:
			{
				//If the window is destroyed, pass the quit message.
				PostQuitMessage(0);
				return 0;
			}
			case WM_COMMAND:
			{
				MessageBox(hwnd, TEXT("Hello world!"), TEXT("Popup"), MB_ICONINFORMATION);
				return 0;
			}
			default:
			{
				//If got other messages
				return DefWindowProc(hwnd, msg, wParam, lParam);
			}
		}
	}
}