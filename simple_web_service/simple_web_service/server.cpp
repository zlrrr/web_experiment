#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")	
#define DEFAULT_PORT "80"
#define DEFAULT_BUFFER_LEN 1024

int _cdecl main() {
	WSADATA wsadata;
	int iResult, iSendResult, recvbuflen = DEFAULT_BUFFER_LEN;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	SOCKET ListenSocket = INVALID_SOCKET;
	char recvbuf[DEFAULT_BUFFER_LEN];
	char sendbuf[DEFAULT_BUFFER_LEN];

	//sprintf(sendbuf,
	//	"<p>I am not really sure whether your answer is right.</p>\n"
	//	"<p>You should probably try again.</p>\n");

	//int sendbuflen = strlen(sendbuf);
	//printf("send size :%d\n %s", sendbuflen,sendbuf);

	iResult = WSAStartup(MAKEWORD(2,2),&wsadata);
	if (iResult != 0) {
		printf("WSAstartup failed: %d\n", iResult);
		return 1;
	}else {
		printf("WSAstartup OK\n");
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	else {
		printf("getaddrinfo OK\n");
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if(ListenSocket == INVALID_SOCKET){
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	else {
		printf("socket create OK\n");
	}

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

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else {
		printf("starting listening\n");
	}

	printf("this is web service,hello!\n");
	hostent* localHost;
	char* localIP;
	localHost = gethostbyname("");
	localIP = inet_ntoa(*(struct in_addr *)*localHost->h_addr_list);
	printf("the ip address is: %s\n\n\n", localIP);

	while(1) {
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

		int iRecvResult = 0;
		memset(recvbuf, 0, sizeof(recvbuf));
		iRecvResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iRecvResult > 0) {
			printf("Received a new message, message length: %d\n", iRecvResult);
			recvbuf[iRecvResult] = '\0';

			int index1 = 0,index2 = 0;
			char method[DEFAULT_BUFFER_LEN];
			char file_addr[DEFAULT_BUFFER_LEN];
			char html_addr[DEFAULT_BUFFER_LEN];
			char *ptr;
			printf("Message:\n %s\n", recvbuf);

			memset(method, 0, sizeof(method));
			memset(file_addr, 0, sizeof(file_addr));
			memset(html_addr, 0, sizeof(html_addr));
			ptr = strtok(recvbuf," ");
			for (index1 = 0;*(ptr+index1)!='\0';index1++) {
				method[index1] = *(ptr+index1);
			}
			method[index1] = '\0';
			printf("method: %s\n",method);
			
			ptr = strtok(NULL," ");
			for (index2 = 0; *(ptr + index2) != '\0'; index2++) {
				file_addr[index2] = *(ptr + index2);
			}
			file_addr[index2] = '\0';
			if (strcmp(file_addr, "/") == 0) {
				sprintf(html_addr, "./html_page/index.php");
			}
			else {
				sprintf(html_addr, "./html_page%s", file_addr);
			}
			printf("file address: %s\n", html_addr);

			FILE *request_page = fopen(html_addr, "rb");

			if (request_page == NULL) {
				memset(sendbuf, 0, sizeof(sendbuf));
				sprintf(sendbuf, "<HTML><TITLE>404 Not Found</TITLE>\r\n"
				"<BODY><h1 align='center'>404</h1><br/><h1 align='center'>Page Not Found.</h1>\r\n"
				"</BODY></HTML>\r\n");
				iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
				if (iSendResult == SOCKET_ERROR) {
					printf("send failed: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					system("pause");
					return 1;
				}
			}
			else {
				int flag = 0;
				while (flag == 0)
				{
					memset(sendbuf, 0, sizeof(sendbuf));
					fgets(sendbuf, sizeof(sendbuf), request_page);
					iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
					if (iSendResult == SOCKET_ERROR) {
						printf("send failed: %d\n", WSAGetLastError());
						closesocket(ClientSocket);
						WSACleanup();
						system("pause");
						return 1;
					}
					if (feof(request_page)) {
						flag = 1;
					}
				}
			}
			if (request_page != NULL) {
				fclose(request_page);
				request_page == NULL;
			}
		} else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			system("pause");
			return 1;
		}
	
		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			system("pause");
			return 1;
		}
		else {
			printf("client disconnected\n\n\n");
		}
	}

	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}