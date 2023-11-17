#include "WindowMessage.h"

WindowMessage::WindowMessage()
{
    WindowInit(GetModuleHandle(NULL));
}

WindowMessage::~WindowMessage()
{
}

void WindowMessage::WindowInit(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style = 0;// CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = 0;
    wc.hIcon = nullptr;
    wc.hIconSm = nullptr;
    wc.lpszMenuName = nullptr;
    wc.hbrBackground = 0;
    wc.lpszClassName = L"Client";
    wc.hInstance = hInstance;
    wc.lpfnWndProc = ClientWinProc;

    RegisterClassEx(&wc);

    m_Hwnd = CreateWindow(L"Client", L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0, hInstance, 0);

    if (!m_Hwnd)
    {
        OutputDebugString(L"\nWindow creation failed\n");
    }
    std::cout << "Window created" << std::endl;
}

WindowMessage* WindowMessage::GetWindowInstance()
{
    static WindowMessage instance;
    return &instance;
}

LRESULT WindowMessage::ClientWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void WindowMessage::UpdateWindowMessage()
{
    //Draw Window
    UpdateWindow(m_Hwnd);

    //Message Loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}
