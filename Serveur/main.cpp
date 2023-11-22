#include "Server.h"
#include "Window.h"
#include "Web.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Server* serv = Server::GetInstance();
    SimpleHttpServer* smp =  new SimpleHttpServer();
    SOCKADDR_IN InternetAddr;
    MSG msg;
    DWORD Ret;
    WSADATA wsaData;

    serv->Init(hInstance);
    smp->start();

    while (Ret = GetMessage(&msg, NULL, 0, 0))
    {
        if (Ret == -1)
        {
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