#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<time.h>

#pragma comment(lib,"ws2_32.lib")	
#define DEFAULT_PORT "2333"
#define DEFAULT_BUFFER_LEN 1024

int _cdecl main() {
	WSADATA wsadata;
	int iResult, iSendResult, recvbuflen = DEFAULT_BUFFER_LEN;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	SOCKET ListenSocket = INVALID_SOCKET;
	char recvbuf[DEFAULT_BUFFER_LEN];
	char sendbuf[DEFAULT_BUFFER_LEN];
	int tp[200], hm[200], lg[200];
	int len_hm = 0,len_tp = 0, len_lg = 0;
	FILE *fp_tp, *fp_hm, *fp_lg;

	//初始化winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (iResult != 0) {
		printf("WSAstartup failed: %d\n", iResult);
		return 1;
	}
	else {
		printf("WSAstartup OK\n");
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	//解析服务器地址和端口
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	else {
		printf("getaddrinfo OK\n");
	}

	//创建socket用于监听
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	else {
		printf("socket create OK\n");
	}

	//绑定端口和地址
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else {
		printf("bind OK\n");
	}
	freeaddrinfo(result);

	//开始监听
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else {
		printf("starting listening\n");
	}

	//输出ip地址等信息
	printf("this is service,hello!\n");
	hostent* localHost;
	char* localIP;
	localHost = gethostbyname("");
	localIP = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	printf("the ip address is: %s\n", localIP);

	//打开数据文件
	fp_hm = fopen("./data/proprammingProject1 humidity.dat","r");
	fp_lg = fopen("./data/proprammingProject1 light.dat","r");
	fp_tp = fopen("./data/proprammingProject1 temperature.dat","r");

	if((fp_hm == NULL) || (fp_lg == NULL) || (fp_tp == NULL)){
		printf("failed to open data file.\n");
		return 2;
	}
	memset(hm, 0, sizeof(hm));
	memset(lg, 0, sizeof(lg));
	memset(tp, 0, sizeof(tp));

	//将数据依次读取到int型数组中
	while (fscanf(fp_hm,"%d",&hm[len_hm]) != EOF)
	{
		len_hm++;
	}
	fclose(fp_hm);
	
	while (fscanf(fp_tp, "%d", &tp[len_tp]) != EOF)
	{
		len_tp++;
	}
	fclose(fp_tp);

	while (fscanf(fp_lg, "%d", &lg[len_lg]) != EOF)
	{
		len_lg++;
	}
	fclose(fp_lg);

	while (1)
	{
		//创建socket用于连接客户端
		SOCKET ClientSocket = INVALID_SOCKET;

		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("Accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		else {
			printf("got new client request\n");
		}

		int iRecvResult;
		int exit_flag = 0;
		//循环接收客户端请求
		while (1) {
			//接收从客户端发来的信息
			iRecvResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
			if (iRecvResult > 0) {
				recvbuf[iRecvResult] = '\0';
				if (!strcmp(recvbuf, "exit")) {
					break;
				}
				printf("Received a message: %d\n%s\n", iRecvResult, recvbuf);

				//随机从数组中读取数据
				srand(time(NULL));
				sprintf(sendbuf, "TEMPERATURE = %d  HUMIDITY = %d  LIGHT = %d\n",
					tp[rand() % len_tp], hm[rand() % len_hm], lg[rand() % len_lg]);

				//将数据发送给客户端
				iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				printf("Bytes sent: %d\n", iSendResult);
			}
			else if (iRecvResult < 0) {
				printf("recv failed: %d\n", WSAGetLastError());
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}
		}
		
		//关闭客户端口
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		else {
			printf("client disconnected\n\n\n");
		}

	}
	
	//关闭监听端口，清理winsock
	closesocket(ListenSocket);
	WSACleanup();

	system("pause");
	return 0;
}