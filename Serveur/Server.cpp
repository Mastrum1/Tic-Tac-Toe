#include "Server.h"
//____CLIENT 1 TURN______
//Client1 joue
//Read -> ID Joueur
//Read -> Coord
//Send -> Client2 = Client1's Coord
//Send -> Data = Grid + Client1's Coord

int Server::Init(HINSTANCE hInstance)
{
	WSADATA wsaData;
	SOCKADDR_IN InternetAddr;
    Window window(hInstance);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        OutputDebugString(L"\nWAS EXPLODED\n");
        return -1;
    }

    SOCKET Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Listen == INVALID_SOCKET)
    {
        OutputDebugString(L"\nLISTEN EXPLODED\n");
        return 1;
    }

    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    InternetAddr.sin_port = htons(31350);

    if (WSAAsyncSelect(Listen, window.GetWnd(), WM_SOCKET, FD_ACCEPT | FD_CLOSE) != 0)
    {
        OutputDebugString(L"\nWSAAsync EXPLODED\n");
        return 1;
    }

    if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
    {
        OutputDebugString(L"\nBind EXPLOSED\n");
        return 1;
    }


    if (listen(Listen, 5))
    {
        OutputDebugString(L"\nlisten EXPLODED\n");
        return 1;
    }

}

