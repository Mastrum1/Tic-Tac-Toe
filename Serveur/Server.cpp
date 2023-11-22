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
        LogClient(Accept);
        OutputDebugString(L"\nConnexion accepted\n");
    }
    else OutputDebugString(L"\nConnexion rejeted\n");

    WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
}

void Server::CloseConnexion(SOCKET sock)
{
    for (auto& c : db->_clientsList)
    {
        if (c.second->getSocket() == sock)
        {
			db->_clientsList.erase(c.second->getID());
		}
	}
	closesocket(sock);
    OutputDebugString(L"\nSocket closed\n");
}

void Server::Read()
{
    OutputDebugString(L"\nReading..\n");
    int byteNum = recv(hClient, _buffer, 1024 - 1, 0);
    _buffer[byteNum] = 0;
    json data = json::parse(_buffer);
    
    //Check informations of the game avec a move and send it to the other player (Not Completed)
    if (data["Type"] == REQUEST_ID) {

        if (data["Cmd"] == SET) {
            _dataList[(int)data["ID"]]->setGridCoord((int)data["x"], (int)data["y"], (int)data["Player"]);
            //Check if the game is ended
            if ((int)data["GameEnded"] != -1) {
				_dataList[(int)data["ID"]]->setEnded((int)data["GameEnded"]);
                //envoyer la fin de partie
			}
        }

        //Check in the database if the player is already registered in the local database
        if (data["Cmd"] == CONNECTION_ID) {
            for (auto& c : db->_clientsList) {
                if (data["Name"] == c.second->getName()) {
                    db->_clientsList.insert(std::pair<int, Client*>(c.second->getID(), c.second));
                    db->_clientsList[data["ID"]]->setSocket(hClient);
                    send(hClient, "Connection Completed", 21, 0);
                }
            }
            //Complete the player passeport if not founded 
            if (data["ID"] == -1) {
                Client myClient = db->createClientinDB((std::string)data["Name"]);
                json myClientJson;
                myClientJson["Type"] = NOTIFICATION_ID;
                myClientJson["Cmd"] = SENDPASSPORT_ID;
                myClientJson["ID"] = myClient.getID();
                myClientJson["Name"] = myClient.getName();
                myClientJson["RoundCount"] = myClient.getRoundCount();
                myClientJson["RoundWin"] = myClient.getRoundWin();
                myClientJson["RoundLose"] = myClient.getRoundLose();
                send(hClient, myClientJson.dump().c_str(), myClientJson.dump().size(), 0);
                send(hClient, "Connection Completed", 21, 0);
                db->_clientsList.insert(std::pair<int, Client*>(myClient.getID(), &myClient));
                db->_clientsList[myClient.getID()]->setSocket(hClient);
            }
            OutputDebugString(L"\nCompleted\n");
        }

        if (data["Cmd"] == MATCHMAKING_ID) {
            bool founded = false;
            for (auto& d : _dataList) {
                if (d.second->isStarted() == 0 && d.second->isPrivate() == 0 && founded == false); {
                    founded = true;
                    d.second->setClient2(db->_clientsList[data["ID"]]);
                    d.second->setStarted(true);
                    json myData;
                    myData["Cmd"] = NOTIFICATION_ID;
                    myData["ID"] = d.second->getID();
                    myData["Player"] = 1;
                    send(d.second->getClient1()->getSocket(), myData.dump().c_str(), myData.dump().size(), 0);
                    myData["Player"] = 2;
                    send(d.second->getClient2()->getSocket(), myData.dump().c_str(), myData.dump().size(), 0);     
                    OutputDebugString(L"\nGame Joined\n");
                }
            }
            if (founded == false) {
                Data* GameData = new Data();
                GameData->setID(_dataList.size() + 1);
                GameData->setPrivate(false);
                GameData->setClient1(db->_clientsList[data["ID"]]);
                _dataList.insert(std::pair<int, Data*>(GameData->getID(), GameData));
                OutputDebugString(L"\nGame Created\n");
            }
        }
    }
}

void Server::LogClient(WPARAM wParam) {
    hClient = (SOCKET)wParam;
    json Login;
    Login["Type"] = NOTIFICATION_ID;
    Login["Cmd"] = CONNECTION_ID;
    Login["Msg"] = "Connection Pending";
    send(hClient, Login.dump().c_str(), Login.dump().size(), 0);
}



