#pragma once
#include "pch/pch.h"

static class WindowMessage
{
public:
	WindowMessage();
	virtual ~WindowMessage();

	void WindowInit(HINSTANCE hInstance);
	static WindowMessage* GetWindowInstance();

	static LRESULT CALLBACK ClientWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UpdateWindowMessage();

private:
	HWND m_Hwnd;
};

