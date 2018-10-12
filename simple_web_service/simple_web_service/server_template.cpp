//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//
//#include<windows.h>
//#include<stdio.h>
//#include<stdlib.h>
//#include<winsock2.h>
//#include<ws2tcpip.h>
//
//#pragma comment(lib,"ws2_32.lib")	
//#define DEFAULT_PORT "80"
//#define DEFAULT_BUFFER_LEN 1024
//
//int _cdecl main() {
//	WSADATA wsadata;
//	int iResult, iSendResult, recvbuflen = DEFAULT_BUFFER_LEN;
//	struct addrinfo *result = NULL, *ptr = NULL, hints;
//	SOCKET ListenSocket = INVALID_SOCKET;
//	char recvbuf[DEFAULT_BUFFER_LEN];
//
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
//	if (iResult != 0) {
//		printf("WSAstartup failed: %d\n", iResult);
//		return 1;
//	}
//	else {
//		printf("WSAstartup OK\n");
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//	hints.ai_flags = AI_PASSIVE;
//
//	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//	else {
//		printf("getaddrinfo OK\n");
//	}
//
//	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//
//	if (ListenSocket == INVALID_SOCKET) {
//		printf("Error at socket(): %ld\n", WSAGetLastError());
//		freeaddrinfo(result);
//		WSACleanup();
//		return 1;
//	}
//	else {
//		printf("socket create OK\n");
//	}
//
//	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//	if (iResult == SOCKET_ERROR) {
//		printf("bind failed with error: %d\n", WSAGetLastError());
//		freeaddrinfo(result);
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//	else {
//		printf("bind OK\n");
//	}
//	freeaddrinfo(result);
//
//	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
//		printf("Listen failed with error: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//	else {
//		printf("starting listening\n");
//	}
//
//	printf("this is web service,hello!\n");
//	hostent* localHost;
//	char* localIP;
//	localHost = gethostbyname("");
//	localIP = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
//	printf("the ip address is: %s\n", localIP);
//
//	SOCKET ClientSocket = INVALID_SOCKET;
//
//	ClientSocket = accept(ListenSocket, NULL, NULL);
//	if (ClientSocket == INVALID_SOCKET) {
//		printf("Accept failed with error: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//	else {
//		printf("got new client request\n");
//	}
//
//	do {
//		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//		if (iResult > 0) {
//			printf("Received a message: %d\n", iResult);
//			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
//			if (iSendResult == SOCKET_ERROR) {
//				printf("send failed: %d\n", WSAGetLastError());
//				closesocket(ClientSocket);
//				WSACleanup();
//				return 1;
//			}
//			printf("Bytes sent: %d\n", iSendResult);
//		}
//		else if (iResult == 0) {
//			printf("connection closing......\n");
//		}
//		else {
//			printf("recv failed: %d\n", WSAGetLastError());
//			closesocket(ListenSocket);
//			WSACleanup();
//			return 1;
//		}
//	} while (iResult > 0);
//
//	iResult = shutdown(ClientSocket, SD_SEND);
//	if (iResult == SOCKET_ERROR) {
//		printf("shutdown failed: %d\n", WSAGetLastError());
//		closesocket(ListenSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	closesocket(ListenSocket);
//	WSACleanup();
//
//	system("pause");
//	return 0;
////}