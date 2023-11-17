#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Window.h"

#pragma comment (lib, "Ws2_32.lib")

#define PORT = 31350;
#define LOCALHOST = 127.0.0.1;
#define WM_SOCKET (WM_USER + 1)

class Server
{
public:
	Server();
	static Server* GetInstance();

	int Init(HINSTANCE hInstance);
	void AcceptConnexion(WPARAM wParam, HWND hwnd);
	void CloseConnexion(SOCKET sock);
	void Read();
	void LogClient(WPARAM wParam);

	sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);


private:
	static Server* _instance;

	SOCKET hClient;

	int _server_fd, _new_socket;
	char _opt = 1;
	size_t _valread;
	char _buffer[1024] = { 0 };
	bool _isListening = false;
};
