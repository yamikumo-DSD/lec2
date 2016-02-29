//create_main_window.cpp

#include "create_main_window.h"
#include "constants.h"
#include "win_proc.h"

namespace WinProg
{
	bool CreateMainWindow(HINSTANCE _hInstance, int _nCmdShow)
	{
		WNDCLASSEX wcx;

		wcx.cbClsExtra = 0;
		wcx.cbSize = sizeof(wcx);
		wcx.cbWndExtra = 0;
		wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wcx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcx.hIcon = nullptr;
		wcx.hIconSm = nullptr;
		wcx.hInstance = _hInstance;
		wcx.lpfnWndProc = WinProc;
		wcx.lpszClassName = Constants::CLASS_NAME;
		wcx.lpszMenuName = nullptr;
		wcx.style = CS_HREDRAW | CS_VREDRAW;

		if (RegisterClassEx(&wcx) == 0) { return false; }

		auto hwnd = CreateWindow
		(
			Constants::CLASS_NAME,
			Constants::APP_TITLE,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			Constants::WINDOW_WIDTH,
			Constants::WINDOW_HEIGHT,
			static_cast<HWND>(nullptr),
			static_cast<HMENU>(nullptr),
			_hInstance,
			static_cast<LPVOID>(nullptr)
		);

		auto button = CreateWindowEx
		(
			WS_EX_LEFT, 
			TEXT("Button"),
			TEXT("Click!"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 100, 20,
			hwnd, 
			static_cast<HMENU>(nullptr), 
			_hInstance, 
			static_cast<LPVOID>(nullptr)
		);

		if (!hwnd)
		{
			return false;
		}
		else
		{
			if (!button) { return false; }
			else
			{
				ShowWindow(hwnd, _nCmdShow);
				UpdateWindow(hwnd);
				return true;
			}
		}
	}
}