#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "2000"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_BUFLEN 512

int ConnectTo(SOCKET& ConnectSocket, PCSTR ServerAddress, PCSTR ServerPort) {
    ;

    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL,
                *ptr = NULL,
                hints;

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ServerAddress, ServerPort, &hints, &result);
    
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr=result;

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
        ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    return 0;
}

int SendUsing(SOCKET ConnectSocket, std::string sendbuf) {
    int iResult;

    // Send an initial buffer
    iResult = send(ConnectSocket, sendbuf.c_str(), sendbuf.length(), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);
    return 0;
}

int RecvUsing(SOCKET &ConnectSocket, char* recvbuf, int recvbuflen) {
    int iResult;
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
        return 0;
    }
    else if (iResult == 0) {
        printf("Connection closed\n");
        return 1;
    }
    else {
        printf("recv failed: %d\n", WSAGetLastError());
        return 1;
    }
}

int Shutdown(SOCKET &ConnectSocket) {
    // shutdown the connection for sending since no more data will be sent
    // the client can still use the ConnectSocket for receiving data
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    return 0;
}

int main() {
    SOCKET Socket = INVALID_SOCKET;
    
    while (ConnectTo(Socket, "127.0.0.1", "2000") == 1) {
        std::cout << "Retrying connection." << std::endl;
        Sleep(1000);
    }

    char msg[4];
    int SendiResult = 0;
    int RecviResult = 0;

    while (SendiResult == 0 || SendiResult == 0)
    {
        std::cout << "Receiving." << std::endl;
        RecviResult = RecvUsing(Socket, msg, 4);

        std::cout << "Sending: " << std::string(msg) << std::endl;
        SendiResult = SendUsing(Socket, msg);
    }

    Shutdown(Socket);
}