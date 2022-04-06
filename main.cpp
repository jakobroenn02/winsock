#include <iostream>
#include <windows.h>
#include <string>
//server application using winsock

int main(){
    //initialize winsock
    WSADATA wsaData;
    int wsaerr; //error code
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaerr != 0) {
        std::cout << "WSAStartup failed with error: " << wsaerr << std::endl;
        return 1;
    }
    else {
        std::cout << "WSAStartup succeeded" << std::endl;
        cout << "The status code is: " << wVersionRequested << std::endl;
        cout << "The status:" << wsaData.szSystemStatus << std::endl;
    }
    //create socket
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket == INVALID_SOCKET){
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    else{
        std::cout << "Socket successfully created" << std::endl;
    }

    //bind socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    inet_pton(AF_INET, T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if(bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
        std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else{
        std::cout << "Bind done" << std::endl;
    }
    //listen
    if(listen(serverSocket, 1)== SOCKET_ERROR){
        std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else{
        std::cout << "Listening..." << std::endl;
    }
    //accept socket
    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if(acceptSocket == INVALID_SOCKET){
        std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else{
        std::cout << "Accepted" << std::endl;
    }
    //close socket
    closesocket(serverSocket);
}
