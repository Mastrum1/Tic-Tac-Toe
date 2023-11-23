#include "Web.h"

Web::Web() {
    // Constructor implementation
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
    // Read existing content
    std::string existingContent = readFile(filename);

    // Update content
    existingContent = newContent;

    // Write back to the file
    writeFile(filename, existingContent);
}

void Web::deleteFile(const std::string& filename) {
    // Use remove function to delete the file
    if (remove(filename.c_str()) != 0) {
        OutputDebugStringW(L"Failed Destroying");
    }
}

void Web::rewriteIndexHtml(int clientSocket) {
    // Read the content of the index.html file
    std::string fileContent = readFile("Index.html");

    int numberOfGames;
    std::string buttonString;
    std::string omegaString;
    Server* serv = Server::GetInstance();

    for (int i = 0; i <= serv->getDataListLenght(); i++) {
        std::string pageName = std::to_string(i);
        std::string gameId = "game" + std::to_string(i);
        buttonString += "<li><button onclick=\"window.open('tictactoe.html?gameId=" + gameId + "', '_blank');\">Game number " + std::to_string(i) + "</button></li>\n";
        omegaString += "\n";
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
               
                 <p>Hope we end this project ASAP</p>
             </section>)" +
        buttonString +
        R"(<div id="grid-container"></div>

             <footer>
                 <p>Help me, this page has a trash aesthetic</p>
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
                         if(cell.dataset.row == 1  && cell.dataset.col == 1)
                         {cell.textContent = 'X'; }
                         

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

    // Update the file with new content
    updateFile("Index.html", modifiedContent);

    // Delete the file (uncomment if needed)
    deleteFile("Index.html");
}

int Web::CreateWebServer() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        return 1;
    }

    // Bind the socket to an address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(31310);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == -1) {
        return 1;
    }


    while (true) {
        // Accept a connection
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize);
        if (clientSocket == -1) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        // Read the content of the index.html file
        std::string fileContent = readFile("Index.html");

        // Send the regular response
        std::string httpResponse = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string(fileContent.size()) + "\r\n"
            "Connection: close\r\n\r\n" + fileContent;

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);

        // Rewrite and update the file
        rewriteIndexHtml(clientSocket);

        // Close the client socket
        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
}