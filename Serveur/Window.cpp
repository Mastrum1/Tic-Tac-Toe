#include "Window.h"

Window::Window(HINSTANCE hInstance)
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
    wc.lpszClassName = CLASS_NAME;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = ServerWinProc;

    RegisterClassEx(&wc);

   // wnd = CreateWindow(CLASS_NAME, L"", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0, hInstance, 0);
    wnd = CreateWindow(CLASS_NAME, L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, 0, hInstance, 0);

    if (!wnd)
    {
        OutputDebugString(L"\nWindow creation failed\n");
    }
}

Window::~Window()
{
}

LRESULT Window::ServerWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SOCKET Accept;
    switch (uMsg)
    {
    case WM_SOCKET:

        if (WSAGETSELECTERROR(lParam))
        {
            closesocket((SOCKET)wParam);
            return 0;
        }

        // Determine what event occurred on the socket

        switch (WSAGETSELECTEVENT(lParam))
        {
        case FD_ACCEPT:
            OutputDebugString(L"\nConnexion accepted\n");
            Accept = accept(wParam, NULL, NULL);
            WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
            return 0;

        case FD_READ:
            OutputDebugString(L"\nRead :\n");
            return 0;

        case FD_WRITE:
            return 0;

        case FD_CLOSE:
            OutputDebugString(L"\nSocket closed\n");
            closesocket((SOCKET)wParam);

            return 0;
        }

        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
