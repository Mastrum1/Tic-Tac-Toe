#include "Server.h"
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Server* serv = Server::GetInstance();
    SOCKADDR_IN InternetAddr;
    MSG msg;
    DWORD Ret;
    WSADATA wsaData;

    serv->Init(hInstance);

    while (Ret = GetMessage(&msg, NULL, 0, 0))
    {
        if (Ret == -1)
        {
            OutputDebugString(L"\nin While\n");
            return 1;
        }

        else 
        {
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}



//int main() {
//	Server s;
//	s.Init();
//	return 0;
//}