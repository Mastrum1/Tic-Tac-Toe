#include "Server.h"

using json = nlohmann::json;

Server::Server()
{
    db = new DataBase();
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

    WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
}

void Server::CloseConnexion(SOCKET sock)
{
	closesocket(sock);
    OutputDebugString(L"\nSocket closed\n");
}

void Server::WriteInJson(json data) {

    std::ofstream outputFile("grid.json");
    if (outputFile.is_open()) {
        outputFile << std::setw(4) << data << std::endl;  // Pretty-print with indentation
        outputFile.close();
        OutputDebugString(L"\nJSON data written to file\n");
    }
    else {
        OutputDebugString(L"\nFailed to open file for writing\n");
    }
}

void Server::Read()
{
    OutputDebugString(L"\nReading..\n");
    int byteNum = recv(hClient, _buffer, 1024 - 1, 0);
    _buffer[byteNum] = 0;
    json data = json::parse(_buffer);
    
    // Writes the data in grid.json
    WriteInJson(data);

    Client _player1 = _dataList[(int)data["ID"]]->getClient1();
    Client _player2 = _dataList[(int)data["ID"]]->getClient2();
    
    //Check informations of the game avec a move and send it to the other player (Not Completed)
    if (data["Cmd"] == REQUEST_ID) {
        if (data["Type"] == SET) {
            _dataList[(int)data["ID"]]->setGridCoord((int)data["x"], (int)data["y"], (int)data["Player"]);
            //Check if the game is ended
            if ((int)data["GameEnded"] != -1) {
				_dataList[(int)data["ID"]]->setEnded((int)data["GameEnded"]);
                //envoyer la fin de partie
			}
        }
    }

    //Check in the database if the player is already registered  (Not Completed)
    else if (data["Cmd"] == REQUEST_ID) {
        if (data["Type"] == SET) {
            bool founded = false;
            for (auto& c : db->_clientsList){
                if (data["Name"] == c.second->getName()) {
                    send(hClient, "Connection Completed", 21, 0);
                    founded = true;
				}
            }
            if (founded == false) {
                db->createClientinDB(data["Name"]);

                //Renvoyer le passeport du client en JSON

                send(hClient, "Connection Completed", 21, 0);
            }
		}   
    }
    OutputDebugString(L"\nCompleted\n");
    send(hClient, "Completed", 2, 0);
}

void Server::HttpGet()
{
    std::ifstream htmlFile("Index.html", std::ios::in | std::ios::binary);

    if (!htmlFile.is_open()) {
        std::string errorResponse = "HTTP/1.0 404 Not Found\r\n\r\n";
        send(hClient, errorResponse.c_str(), errorResponse.length(), 0);
        closesocket(hClient);
        return;
    }

    std::string content((std::istreambuf_iterator<char>(htmlFile)), std::istreambuf_iterator<char>());

    std::string response =
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(content.length()) + "\r\n"
        "\r\n" + content;

    if (send(hClient, response.c_str(), response.length(), 0) == -1) {
        OutputDebugString(L"Error sending HTTP response.\n");
    }

    htmlFile.close();
    closesocket(hClient);
}

void Server::LogClient(WPARAM wParam) {
    hClient = (SOCKET)wParam;
    send(hClient, "Connection Pending", 19, 0);
}

//void Server::HttpPost() {
//    // Prepare the HTTP POST request
//    std::string httpRequest = "POST ../../../Tic-Tac-Toe/Serveur/Index.html HTTP/1.1\r\n"
//        "Host: " + std::string() + "\r\n"
//        "Content-Type: application/x-www-form-urlencoded\r\n"
//        "Content-Length: " + std::to_string(strlen(postData)) + "\r\n"
//        "\r\n" + postData;
//
//    // Send the HTTP request
//    if (send(clientSocket, httpRequest.c_str(), httpRequest.length(), 0) == -1) {
//        std::cerr << "Error sending HTTP request." << std::endl;
//        close(clientSocket);
//        return 1;
//    }
//
//}

