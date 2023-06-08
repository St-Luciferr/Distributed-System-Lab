// Chat Server

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
int main()
{
    WSADATA wsaData;
    WORD requiredVersion = MAKEWORD(2, 2);
    SOCKET LSocket;
    sockaddr_in Server;

    //localHost=gethostbyname("");

    //requesting a desired version of winsock dll
    int result = WSAStartup(requiredVersion, &wsaData);

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

    //Creating the listening Socket
    LSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Checking if the Socket was created Successfully or not
    if (LSocket == INVALID_SOCKET)
    {
        std::cout << "Failed to Create a Scocket, with error: "
        << WSAGetLastError() << ".\n";
        WSACleanup();
        return 1;
    }

    //Configure the Local adress and port
    Server.sin_family = AF_INET;
    Server.sin_addr.s_addr = inet_addr("127.0.0.1");
    Server.sin_port = htons(8080);

    //Bind the socket with Local Address
    result = bind(LSocket, (SOCKADDR*)&Server, sizeof(Server));

    //Checking if Binding was Successful or not
    if (result == SOCKET_ERROR)
    {
        std::cout << "Binding Failed with Error: " << 
        WSAGetLastError() << ".\n";
        closesocket(LSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Binding Successful\n";
    }
    //Listen for incoming Connection
    result = listen(LSocket, SOMAXCONN);
    if (result == SOCKET_ERROR)
    {
        std::cout << "Failed to Listen on Socket with Error: " <<
        WSAGetLastError() << ".\n";
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Listening on Socket...\n";
    }


    sockaddr_in ClientAddr;
    int ClientSize = sizeof(ClientAddr);
    SOCKET ClientSock;

    //Accepting Connection
    std::cout << "Waiting for Client to Connect...\n";
    ClientSock= accept(LSocket, (sockaddr*)&ClientAddr, &ClientSize);
    char ClientName[NI_MAXHOST];
    char ClientPort[NI_MAXSERV];
    if (ClientSock == INVALID_SOCKET)
    {
        std::cout << "Accept Failed with error: " << 
        WSAGetLastError() << ".\n";
        closesocket(LSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Client Connected...\n";
    }

    char msg[2048];
    int msglen;

    //process after connection is made
    while (true)
    {
        ZeroMemory(msg,2048);
        msglen = recv(ClientSock, msg, 2048, 0);
        if (strcmp(msg, "exit") == 0)
        {
            std::cout << "user left\n";
            break;
        }
        if(msglen!=0)
            std::cout<< "user: " << msg << "\n";
        
        std::cout << "me: "; 
        std::cin.getline(msg, 2048);
      
        if (strcmp(msg,"exit")==0)
        {
            break;
        }
        else
            send(ClientSock, msg, 2048, 0);
      
    }
    //Close the socket
    result = closesocket(LSocket);
    if (result == SOCKET_ERROR)
    {
        std::cout << "Failed to Close the Socket with Error: " << 
        WSAGetLastError() << ".\n";
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Socket Closed Successfully...\n";
    }
    //done using the Winsock.dll
    WSACleanup();
}