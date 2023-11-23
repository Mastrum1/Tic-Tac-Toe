#include "Web.h"

Web::Web() {
}

Web::~Web() {
}

Web* Web::GetInstance() {
    static Web instance;
    return &instance;
}

std::string Web::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::ostringstream content;
        content << file.rdbuf();
        return content.str();
    }
    return "";
}

void Web::writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file) {
        file << content;
        file.close();
    }
}

void Web::updateFile(const std::string& filename, const std::string& newContent) {
    std::string existingContent = readFile(filename);

    existingContent = newContent;

    writeFile(filename, existingContent);
}

void Web::deleteFile(const std::string& filename) {
    if (remove(filename.c_str()) != 0) {
        OutputDebugStringW(L"Failed Destroying");
    }
}

void Web::rewriteIndexHtml(int clientSocket) {

    std::string fileContent = readFile("Index.html");
    Client _myGame;

    int numberOfGames;
    std::string buttonString;
    std::string marksString;
    std::string coordStringX;
    std::string coordStringY;
    Server* serv = Server::GetInstance();

    std::string gameId;
    Data* dataId;
    Data* gridValue;


    std::string cellTextX = "X";
    std::string cellTextY = "Y";


    for (int i = 0; i < serv->getDataListLenght(); i++) {
        std::string pageName = std::to_string(i + 1);

        dataId = serv->getGameData(i);
  
        if (dataId != nullptr) {

            int x{}, y{};

            dataId->getGridCoord(x, y);

            coordStringX += "x=" + std::to_string(x) + "\n";
            coordStringY += "y=" + std::to_string(y) + "\n";

            gameId = "game" + std::to_string(i + 1);
            buttonString += "<button onclick=\"window.open('tictactoe.html?gameId=" + gameId + "', '_blank');\">Game number " + std::to_string(i + 1) + "</button>\n";
            marksString += "if (cell.dataset.row == )"+ coordStringX + "(&& cell.dataset.col == )" + coordStringY + "() { cell.textContent = 'X' }\n";
        }
    }

    std::string modifiedContent = R"(
     <!DOCTYPE html>
     <html lang="en">
     <head>
         <meta charset="UTF-8">
         <meta name="viewport" content="width=device-width, initial-scale=1.0">
         <title>Modified HTML Page</title>
         <style>
             body {
                 display: flex;
                 align-items: center;
                 justify-content: center;
                 height: 100vh;
                 margin: 0;
                 text-align: center;
             }

             #content-container {
                 display: flex;
                 flex-direction: column;
                 align-items: center;
             }

             #grid-container {
                 display: grid;
                 grid-template-columns: repeat(3, 100px);
                 grid-gap: 5px;
                 margin-top: 10px;
             }

             .cell {
                 width: 100px;
                 height: 100px;
                 border: 1px solid #ccc;
                 display: flex;
                 align-items: center;
                 justify-content: center;
                 font-size: 24px;
                 cursor: pointer;
             }
         </style>
     </head>
     <body>
         <div id="content-container">
             <header>
                 <h1>Ha yes, a Tic Tac Toe game</h1>
             </header>

             <section>
               
                 <p>Admin page for spectating</p>
             </section>)" +
        buttonString +
        R"(<div id="grid-container"></div>

             <footer>
                 <p>This page has no more than 3 lines of CSS</p>
             </footer>
         </div>

         <script> 
             function createGrid() {
                 var gridContainer = document.getElementById('grid-container');

                 for (var i = 0; i < 3; i++) {
                     for (var j = 0; j < 3; j++) {
                         var cell = document.createElement('div');
                         cell.className = 'cell';
                         cell.dataset.row = i;
                         cell.dataset.col = j;
                         )" + marksString + R"(

                         gridContainer.appendChild(cell);
                     }
                 }
                
             }

             // Create the grid when the page loads
             document.addEventListener('DOMContentLoaded', createGrid);
         </script>

     </body>
     </html>
)";

    std::string httpResponse = "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(modifiedContent.size()) + "\r\n"
        "Connection: close\r\n\r\n" + modifiedContent;

    send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);

    updateFile("Index.html", modifiedContent);

    // Delete the file (uncomment if needed)
    // deleteFile("Index.html");
}

int Web::CreateWebServer() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        OutputDebugStringW(L"Failed to init Winsock");
        return 1;
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        OutputDebugStringW(L"Failed to create server socket");
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(31310);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        OutputDebugStringW(L"Failed to bind to an adress");
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == -1) {
        OutputDebugStringW(L"Failed to connect");
        return 1;
    }


    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize);
        if (clientSocket == -1) {
            OutputDebugStringW(L"Failed to accept socket");
            continue;
        }

        std::string fileContent = readFile("Index.html");

        std::string httpResponse = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string(fileContent.size()) + "\r\n"
            "Connection: close\r\n\r\n" + fileContent;

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);

        rewriteIndexHtml(clientSocket);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
}