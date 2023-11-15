#include "Server.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window(hInstance);
    SOCKADDR_IN InternetAddr;
    MSG msg;
    DWORD Ret;
    WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
        OutputDebugString(L"WAS EXPLODED");
		return -1;
	}	

    int Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Listen == INVALID_SOCKET)
    {
        OutputDebugString(L"LISTEN EXPLODED");
        return 1;
    }

    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    InternetAddr.sin_port = htons(31350);

    if (WSAAsyncSelect(Listen, window.wnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE) != 0)
    {
        OutputDebugString(L"WSAAsync EXPLODED");
        return 1;
    }

    if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
    {
        OutputDebugString(L"Bind EXPLOSED");
        return 1;
    }


    if (listen(Listen, 5))
    {
        OutputDebugString(L"listen EXPLODED");
        return 1;
    }


    while (Ret = GetMessage(&msg, NULL, 0, 0))
    {
        if (Ret == -1)
        {
            OutputDebugString(L"in While");
            return 1;
        }

        else 
        {
            OutputDebugString(L"in Else");
        }

        OutputDebugString(L"Tranlating");
        TranslateMessage(&msg);
        OutputDebugString(L"Dispatching");
        DispatchMessage(&msg);
    }
}



//int main() {
//	Server s;
//	s.Init();
//	return 0;
//}