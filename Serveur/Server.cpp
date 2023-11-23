#include "Server.h"

using json = nlohmann::json;


Window::~Window()
{

}

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

    db->loadClientDB();

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

    WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
}

void Server::CloseConnexion(SOCKET sock)
{
    int _cID = db->_clientsSocketList[sock]->getID();
    if (db->_clientsSocketList[sock]->isInGame()) 
    {
        int gameID = db->_clientsSocketList[sock]->getGameID();
        json CloseConnection;

        CloseConnection["Type"] = NOTIFICATION_ID;
        CloseConnection["Cmd"] = PLAY_ID;
        CloseConnection["x"] = 0;
        CloseConnection["y"] = 0;
        CloseConnection["WinCondition"] = 3;
        send(_dataList[gameID]->getClient1()->getSocket(), CloseConnection.dump().c_str(), CloseConnection.dump().size(), 0);
        send(_dataList[gameID]->getClient2()->getSocket(), CloseConnection.dump().c_str(), CloseConnection.dump().size(), 0);
    }

    db->_clientsList.erase(_cID);
    db->_clientsSocketList[sock]->~Client();
    db->_clientsSocketList.erase(sock);
	closesocket(sock);
    OutputDebugString(L"\nSocket closed\n");
}

void Server::Read(WPARAM wParam)
{
    SOCKET hClient;
    hClient = (SOCKET)wParam;
    OutputDebugString(L"\nReading..\n");
    char _buffer[10000] = { 0 };
    int byteNum = recv(hClient, _buffer, 1024 , 0);
    _buffer[byteNum] = 0;
    json data = json::parse(_buffer);
    data["_clientSocket"] = hClient;

    std::string test = data.dump();
    OutputDebugStringA(test.c_str());

    _dataListVector.push_back(data);

    if (data["Type"] == REQUEST_ID) {
        if (data["Cmd"] == SET) {
            json myGame;
            
            myGame["Type"] = NOTIFICATION_ID;
            myGame["Cmd"] = PLAY_ID;
            myGame["x"] = data["x"];
            myGame["y"] = data["y"];
            myGame["WinCondition"] = data["WinCondition"];

            if (data["Player"] == 1) 
                send(_dataList[data["ID"]]->getClient2()->getSocket(), myGame.dump().c_str(), myGame.dump().size(), 0);
            
            else if (data["Player"] == 2)
                send(_dataList[data["ID"]]->getClient1()->getSocket(), myGame.dump().c_str(), myGame.dump().size(), 0);

            _dataList[data["ID"]]->setGridCoord(data["x"], data["y"], data["Player"]);

            if (data["WinCondition"] != -1) {
                if (data["WinCondition"] == 1) {
                    _dataList[data["ID"]]->getClient1()->addRoundCount();
                    _dataList[data["ID"]]->getClient1()->addRoundWin();
                    _dataList[data["ID"]]->getClient2()->addRoundCount();
                    _dataList[data["ID"]]->getClient2()->addRoundLose();
				}
                else if (data["WinCondition"] == 2) {
                    _dataList[data["ID"]]->getClient2()->addRoundCount();
                    _dataList[data["ID"]]->getClient2()->addRoundWin();
                    _dataList[data["ID"]]->getClient1()->addRoundCount();
                    _dataList[data["ID"]]->getClient1()->addRoundLose();
				}   
                db->updateClientinDB(_dataList[data["ID"]]->getClient1());
				db->updateClientinDB(_dataList[data["ID"]]->getClient2());
				_dataList[data["ID"]]->setEnded(data["WinCondition"]);
                _dataList[data["ID"]]->getClient1()->setInGame(false);
                _dataList[data["ID"]]->getClient2()->setInGame(false);
                _dataList[data["ID"]]->getClient1()->resetGameID();
                _dataList[data["ID"]]->getClient2()->resetGameID();
                myGame.clear();
                myGame["Type"] = NOTIFICATION_ID;
                myGame["Cmd"] = SENDPASSPORT_ID;

                //Player1
                myGame["ID"] = _dataList[data["ID"]]->getClient1()->getID();
                myGame["Name"] = _dataList[data["ID"]]->getClient1()->getName();
                myGame["RoundCount"] = _dataList[data["ID"]]->getClient1()->getRoundCount();
                myGame["RoundWin"] = _dataList[data["ID"]]->getClient1()->getRoundWin();
                myGame["RoundLose"] = _dataList[data["ID"]]->getClient1()->getRoundLose();
				send(_dataList[data["ID"]]->getClient1()->getSocket(), myGame.dump().c_str(), myGame.dump().size(), 0);

                //Player2
                myGame["ID"] = _dataList[data["ID"]]->getClient2()->getID();
                myGame["Name"] = _dataList[data["ID"]]->getClient2()->getName();
                myGame["RoundCount"] = _dataList[data["ID"]]->getClient2()->getRoundCount();
                myGame["RoundWin"] = _dataList[data["ID"]]->getClient2()->getRoundWin();
                myGame["RoundLose"] = _dataList[data["ID"]]->getClient2()->getRoundLose();
				send(_dataList[data["ID"]]->getClient2()->getSocket(), myGame.dump().c_str(), myGame.dump().size(), 0);

                _dataList[data["ID"]] = NULL;
            }
            myGame.clear();
        }

        //Check in the database if the player is already registered in the local database
        if (data["Cmd"] == CONNECTION_ID) {
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
                db->_clientsList.insert(std::pair<int, Client*>(data["ID"], &myClient));
                db->_clientsList[data["ID"]]->setSocket(hClient);
                db->_clientsSocketList.insert(std::pair<SOCKET, Client*>(hClient, &myClient));
                send(myClient.getSocket(), myClientJson.dump().c_str(), myClientJson.dump().size(), 0);
            }
            else
            {
                Client* c;
                if (c = db->pullClientDB(data["ID"]))
                {
                    db->_clientsList.insert(std::pair<int, Client*>(data["ID"], c));
                    db->_clientsSocketList.insert(std::pair<SOCKET, Client*>(hClient, c));
                    db->_clientsList[data["ID"]]->setSocket(hClient);
                    OutputDebugString(L"\nConnection Completed\n");
                }
            }
            OutputDebugString(L"\Passeport valided\n");
        }

        if (data["Cmd"] == MATCHMAKING_ID) {
            bool founded = false;
            json myData;
            for (auto& d : _dataList) {
                if (d.second->isStarted() == false && d.second->isPrivate() == false && founded == false && d.second != NULL); {
                    founded = true;
                    d.second->setClient2(db->_clientsList[data["ID"]]);
                    db->_clientsList[data["ID"]]->setInGame(true);
                    db->_clientsList[data["ID"]]->setGameID(d.second->getID());
                    d.second->setStarted(true);
                    myData["Type"] = NOTIFICATION_ID;
                    myData["Cmd"] = SETUPGAME_ID;
                    myData["ID"] = d.second->getID();
                    myData["Player"] = 1;
                    send(d.second->getClient1()->getSocket(), myData.dump().c_str(), myData.dump().size(), 0);
                    myData["Player"] = 2;
                    send(d.second->getClient2()->getSocket(), myData.dump().c_str(), myData.dump().size(), 0);
                    OutputDebugString(L"\nGame Joined\n");
                    myData.clear();
                    break;
                }
            }
            if (founded == false) {
                Data* GameData = new Data();
                GameData->setID(_dataList.size() + 1);
                GameData->setPrivate(false);
                GameData->setClient1(db->_clientsList[data["ID"]]);
                db->_clientsList[data["ID"]]->setInGame(true);
                db->_clientsList[data["ID"]]->setGameID(GameData->getID());
                _dataList.insert(std::pair<int, Data*>(GameData->getID(), GameData));

                OutputDebugString(L"\nGame Created\n");
            }
        }
    }
    data.clear();
}

void Server::LogClient(WPARAM wParam) {
    json Login;
    Login["Type"] = NOTIFICATION_ID;
    Login["Cmd"] = CONNECTION_ID;
    Login["Msg"] = "Connection Pending";
    send((SOCKET)wParam, Login.dump().c_str(), Login.dump().size(), 0);
}

Data* Server::getGameData(int index)
{
    return _dataList[index];
}

int Server::getDataListLenght() 
{
    return _dataList.size();
}

