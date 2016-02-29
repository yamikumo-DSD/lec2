#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "create_main_window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto exit_flag = false;
	MSG msg;

	if (!WinProg::CreateMainWindow(hInstance, nCmdShow)) { return 0; }

	while (!exit_flag)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) { exit_flag = true; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} //main loop

	return static_cast<int>(msg.wParam);
}//WinMain