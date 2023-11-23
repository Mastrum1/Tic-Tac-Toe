#include "Server.h"
#include "Window.h"
#include "Web.h"

DWORD WebThread(void* param)
{
    Web* web = Web::GetInstance();
    web->CreateWebServer();

    return 0;
}

DWORD ServerThread(void* param)
{
	Server* serv = Server::GetInstance();
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Server* serv = Server::GetInstance();

    HANDLE Thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerThread, NULL, 0, NULL);

    SOCKADDR_IN InternetAddr;
    MSG msg;
    DWORD Ret;
    WSADATA wsaData;

    serv->Init(hInstance);

    while (Ret = GetMessage(&msg, NULL, 0, 0))
    {
        if (Ret == -1)
        {
            return 1;
        }

        else 
        {

        }
        HANDLE threadWeb = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)WebThread, 0, 0, NULL);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;  
}
