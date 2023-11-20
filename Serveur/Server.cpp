#include "Server.h"

using json = nlohmann::json;

Server::Server()
{
}

Server* Server::_instance = nullptr;
Server* Server::GetInstance()
{
    if (_instance == nullptr)
    {
		_instance = new Server();
	}
	return _instance;
}

int Server::Init(HINSTANCE hInstance)
{
	WSADATA wsaData;
	SOCKADDR_IN InternetAddr;
    Window window(hInstance);

    OutputDebugString(L"\nServer Starting...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        OutputDebugString(L"\nWAS EXPLODED\n");
        return -1;
    }
    OutputDebugString(L"\nWSA ready\n");

    SOCKET Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Listen == INVALID_SOCKET)
    {
        OutputDebugString(L"\nLISTEN EXPLODED\n");
        return 1;
    }
    OutputDebugString(L"Listen socket ready\n");

    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    InternetAddr.sin_port = htons(31350);
    OutputDebugString(L"Address Set\n");

    if (WSAAsyncSelect(Listen, window.GetWnd(), WM_SOCKET, FD_ACCEPT | FD_CLOSE) != 0)
    {
        OutputDebugString(L"\nWSAAsync EXPLODED\n");
        return 1;
    }
    OutputDebugString(L"WSAAsyncSelect Ready\n");

    if (bind(Listen, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
    {
        OutputDebugString(L"\nBind EXPLOSED\n");
        return 1;
    }
    OutputDebugString(L"\nServer Ready\n");

    if (listen(Listen, 5))
    {
        OutputDebugString(L"\nlisten EXPLODED\n");
        return 1;
    }
    OutputDebugString(L"\nListening...\n");

}

void Server::AcceptConnexion(WPARAM wParam, HWND hwnd)
{
    SOCKET Accept;
    if (Accept = accept(wParam, NULL, NULL)) {
        LogClient(wParam);
        OutputDebugString(L"\nConnexion accepted\n");
    }
    else OutputDebugString(L"\nConnexion rejeted\n");

    send(Accept, "Connection Accepted", 19, 0);

    WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
}

void Server::CloseConnexion(SOCKET sock)
{
	closesocket(sock);
    OutputDebugString(L"\nSocket closed\n");
}

void Server::Read()
{
    OutputDebugString(L"\nReading..\n");
    int byteNum = recv(hClient, _buffer, 1024 - 1, 0);
    _buffer[byteNum] = 0;
    json data = json::parse(_buffer);
    
    if (data["Cmd"] == REQUEST_ID) {
        if (data["Type"] == SET) {
            _data[(int)data["ID"]]->setGridCoord((int)data["x"], (int)data["y"], (int)data["Player"]);
            //Check if the game is ended
            if ((int)data["GameEnded"] != -1) {
				_data[(int)data["ID"]]->setEnded((int)data["GameEnded"]);
                //envoyer la fin de partie
			}
        }
    }
    OutputDebugString(L"\nCompleted\n");
    send(hClient, "Completed", 2, 0);
}

void Server::LogClient(WPARAM wParam) {
    hClient = (SOCKET)wParam;
}



