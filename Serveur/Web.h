#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>


class Web
{
public:
	Web();
	virtual ~Web();
	static Web* GetInstance();

	int CreateWebServer();
	std::string readFile(const std::string& filename);

	void writeFile(const std::string& filename, const std::string& content);

	void updateFile(const std::string& filename, const std::string& newContent);

	void deleteFile(const std::string& filename);

	void rewriteIndexHtml(int clientSocket);

private:

};
