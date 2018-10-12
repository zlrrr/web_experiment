//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//
//#include<windows.h>
//#include<winsock2.h>
//#include<ws2tcpip.h>
//#include<stdio.h>
//#include<iphlpapi.h>
//
//#pragma comment(lib,"Ws2_32.lib")
//
//#define DEFAULT_PORT "80"
//#define DEFAULT_BUFFER_LEN 1024
//
//int _cdecl main(int argc, char **argv) {
//	WSADATA wsadata;
//	int iResult;
//	struct addrinfo *result = NULL,
//		*ptr = NULL,
//		hints;
//	SOCKET ConnectSocket = INVALID_SOCKET;
//	int recvbuflen = DEFAULT_BUFFER_LEN;
//
//	char *sendbuf = "hello,this is client!";
//	char recvbuf[DEFAULT_BUFFER_LEN];
//
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
//	if (iResult != 0) {
//		printf("WSAStartup failed: %d\n", iResult);
//		return 1;
//	}
//
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//
//	ptr = result;
//
//	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//	if (ConnectSocket == INVALID_SOCKET) {
//		printf("Error at socket(): %ld\n", WSAGetLastError());
//		freeaddrinfo(result);
//		WSACleanup();
//		return 1;
//	}
//
//	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//	if (iResult == SOCKET_ERROR){
//		closesocket(ConnectSocket);
//		ConnectSocket = INVALID_SOCKET;
//	}
//
//	freeaddrinfo(result);
//
//	if(ConnectSocket == INVALID_SOCKET){
//		printf("Unable to connect to server!\n");
//		WSACleanup();
//		return 1;
//	}
//
//	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
//	if (iResult == SOCKET_ERROR) {
//		printf("send failed: %d\n",WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	printf("Byte Sent: %ld\n", iResult);
//	iResult = shutdown(ConnectSocket, SD_SEND);
//	if (iResult == SOCKET_ERROR) {
//		printf("shutdown failed: %d\n", WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	do{
//		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//		if (iResult > 0)
//			printf("Bytes received: %d\n", iResult);
//		else if (iResult == 0)
//			printf("Connection closed\n");
//		else
//			printf("recv failed: %d\n", WSAGetLastError());
//	} while (iResult > 0);
//
//	closesocket(ConnectSocket);
//	WSACleanup();
//
//	return 0;
//}