#include "pch/pch.h"

#include "Client/Client.h"


WindowMessage::WindowMessage()
{
    m_Hwnd = NULL;
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

LRESULT WindowMessage::ClientWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Client* _client = Client::GetInstance();
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        closesocket(_client->GetSocket());
        return 0;

        case WM_SOCKET:
        {
            if (WSAGETSELECTERROR(lParam))
            {
				std::cout << "Socket error" << std::endl;
                closesocket(_client->GetSocket());
				return 0;
			}
            switch (WSAGETSELECTEVENT(lParam))
            {
			case FD_READ:
            {
				_client->ClientReceiveMessage();
				break;
			}
			case FD_CLOSE:
				std::cout << "Connection closed" << std::endl;
                closesocket(_client->GetSocket());
				return 0;
			}
			break;
		}

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
    while (GetMessage(&msg, NULL, 0, 0))
    {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}
