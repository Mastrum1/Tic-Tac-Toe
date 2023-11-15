#pragma once
#include "Server.h"

// add in pch
#define CLASS_NAME L"Test"

class Window
{
public:
	Window(HINSTANCE hInstance);
	virtual ~Window();

	static LRESULT CALLBACK ServerWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND wnd;
};

