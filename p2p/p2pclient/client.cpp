#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<windows.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<stdio.h>
#include<iphlpapi.h>

#pragma comment(lib,"Ws2_32.lib")

#define DEFAULT_PORT "2333"
#define DEFAULT_BUFFER_LEN 1024

int _cdecl main(int argc, char **argv) {
	WSADATA wsadata;
	int iResult, recvbuflen = DEFAULT_BUFFER_LEN;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	SOCKET ConnectSocket = INVALID_SOCKET;

	char sendbuf[DEFAULT_BUFFER_LEN];
	char recvbuf[DEFAULT_BUFFER_LEN];

	//判断参数
	if (argc != 2) {
		printf("usage: %s server-ip\n",argv[0]);
		return 1;
	}

	//初始化winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//解析服务器地址和端口
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	
	ptr = result;

	//尝试连接到服务器，创建SOCKET
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	//连接到服务器
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR){
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	//连接完毕，释放指针
	freeaddrinfo(result);

	if(ConnectSocket == INVALID_SOCKET){
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	int iRecvResult,iSendResult;
	//循环接收屏幕输入
	while(1){
		printf("input 'exit' to quit, input other word to send message to server and get data.\n");
		memset(sendbuf, 0, sizeof(sendbuf));
		scanf("%s",sendbuf);

		//将文本发送给服务器
		iSendResult = send(ConnectSocket, sendbuf, strlen(sendbuf), 0);
		if (iSendResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		//如果输入文本为exit，则跳出循环，关闭连接
		if (!strcmp(sendbuf, "exit")) {
			break;
		}

		printf("Byte Sent: %ld\n", iSendResult);

		memset(recvbuf, 0, sizeof(recvbuf));
		//接收服务器传来的消息
		iRecvResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		recvbuf[iRecvResult] = '\0';
		if (iRecvResult > 0)
				printf("Data received: %s\n", recvbuf);
		else if (iRecvResult < 0) {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
	}

	//关闭监听端口，清理winsock
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}