#pragma once

class WindowMessage
{
public:
	WindowMessage();
	virtual ~WindowMessage();

	void WindowInit(HINSTANCE hInstance);
	HWND GetHwnd() { return m_Hwnd; };

	static LRESULT CALLBACK ClientWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UpdateWindowMessage();

private:
	HWND m_Hwnd;

};

