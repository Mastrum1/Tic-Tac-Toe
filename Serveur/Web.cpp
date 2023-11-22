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
        std::cerr << "Error deleting file: " << filename << std::endl;
    }
}

void Web::rewriteIndexHtml(int clientSocket) {
    // Read the content of the index.html file
    std::string fileContent = readFile("Index.html");
    int oui = 10;
    int neuf = 5;
    int gh = 15;
    int numberOfGames;
    std::string buttonString;
    Server* serv = Server::GetInstance();

    std::string ouiStr = std::to_string(oui);
    std::string ghStr = std::to_string(gh);
    std::string neufStr = std::to_string(neuf);

    // Send the modified response
    for (int i = 1; i < 7; i++)
    {
        std::string pageName = std::to_string(i);
        buttonString += "<li><button onclick=\"window.open('blank" + pageName + ".html', '_blank');\">Button " + std::to_string(i) + "</button></li>\n";
    }

    std::string modifiedContent = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Modified HTML Page</title>
        </head>
        <body>
            <header>
                <h1>This is a Modified HTML Page</h1>
            </header>

            <section>
                <p>This is a modified paragraph of text.</p>

                <p>Feel free to modify and customize this page further!</p>
            </section>)" +
        buttonString +
        R"(<footer>
                <p>&copy; 2023 Modified HTML Page. All rights reserved.</p>
            </footer>
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
    //deleteFile("Index.html");
}

int Web::CreateWebServer() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock" << std::endl;
        return 1;
    }

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to an address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(31310);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket to address" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen for connections" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << 31310 << std::endl;

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