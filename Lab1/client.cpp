#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<WS2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA wsaData;
	WORD Version = MAKEWORD(2, 2);
	SOCKET CSocket;
	sockaddr_in ServerInfo;
	
	int result = WSAStartup(Version, &wsaData);
    //check if the requested version is returned or not
    if (result != 0)
    {
        std::cout << "WSAStartup failed with error: " << result << ".\n";
        return 1;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        std::cout << "Could not find a usable version of Winsock.dll\n";
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "The Winsock 2.2 dll was found okay\n";
    }

    //creating socket to connect with server
    CSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    

    //setting server info to connect to server
    ServerInfo.sin_family = AF_INET;
    ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServerInfo.sin_port = htons(8080);

    result = connect(CSocket, (SOCKADDR*)&ServerInfo, sizeof(ServerInfo));

    //Checking if Connection is established Successfully or not
    if (result == SOCKET_ERROR)
    {
        std::cout << "Connecting Failed with Error: " << WSAGetLastError() << ".\n";
        closesocket(CSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Connected Successfully...\n";
    }


    char msg[2048];
    int msglen;

    //process after connection is made
    while (true)
    {
        //sending msg
        ZeroMemory(msg, 2048);
        std::cout << "me: ";
        std::cin.getline(msg, 2048);
        if (strcmp(msg, "exit") == 0)
        {
            std::cout << "You Left!!!\n";
            break;
        }
        else
            send(CSocket, msg, strlen(msg), 0);
        //receiving msg
        ZeroMemory(msg, 2048);
        msglen = recv(CSocket, msg, 2048, 0);
        if (strcmp(msg, "exit") == 0)
        {
            std::cout << "Server Closed\n";
            break;
        }
        if (msglen != 0)
            std::cout << "Server: " << msg << "\n";
    }


    result = closesocket(CSocket);
    if (result == SOCKET_ERROR)
    {
        std::cout << "Failed to Close the Socket with Error: " << WSAGetLastError() << ".\n";
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Socket Closed Successfully...\n";
    }
    //done using the Winsock.dll
    WSACleanup();
    
    return 0;
}