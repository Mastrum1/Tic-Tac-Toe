#include "Window.h"
#include "Server.h"

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
    Server* serv = Server::GetInstance();
    switch (uMsg)
    {
        case WM_SOCKET:
        {
            if (WSAGETSELECTERROR(lParam))
            {
                serv->CloseConnexion(wParam);
                return 0;
            }

            // Determine what event occurred on the socket

            switch (WSAGETSELECTEVENT(lParam))
            {
                case FD_ACCEPT:
                {
                    serv->AcceptConnexion(wParam, hwnd);
                    return 0;
                }

                case FD_READ: 
                {
                    serv->Read(wParam);
                    return 0;
                }

                case FD_CLOSE:
                {
                    serv->CloseConnexion(wParam);
                    return 0;
                }
            }

            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND Window::GetWnd()
{
    return wnd;
}
