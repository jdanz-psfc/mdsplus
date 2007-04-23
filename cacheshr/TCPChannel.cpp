

#include "TCPChannel.h"
bool TCPChannel::initialized;




static int readFromSocket(int sock, int numBytes, char *buf)
{
	int numReadBytes = 0;
	int currBytes;

	while(numReadBytes < numBytes)
	{
		if((currBytes = recv(sock, &buf[numReadBytes], numBytes - numReadBytes,0)) < 0)
		{
			printf("Error in recv: socket closed\n");
			return -1;
		}
		numReadBytes += currBytes;
	}
	return 0;
}


void TCPHandler::run(void *arg)
{
//TCP Message protocol: type (1 byte), length (4 bytes), message (length bytes) 

	IPAddress addr;
	addr.socket = socket;
	char senderIdx;
	while(true)
	{
		char type;
		int len;
		if(readFromSocket(socket, 1, &type) == -1)
		{
			printf("Socket communication terminated\n");
			return;
		}
		if(readFromSocket(socket, 1, &senderIdx) == -1)
		{
			printf("Socket communication terminated\n");
			return;
		}
		unsigned int readLen;
		if(readFromSocket(socket, 4, (char *)&readLen) == -1)
		{
			printf("Socket communication terminated\n");
			return;
		}
		len = ntohl(readLen);
		char *buf = new char[len];
		if(readFromSocket(socket, len, buf) == -1)
		{
			printf("Socket communication terminated\n");
			return;
		}
		channel->messageReceived(&addr, (int)senderIdx, type, buf, len);
	}
}




void TCPServer::run(void *arg)
{
	while(true)
	{
		int newSocket = accept(socket, NULL, NULL);
#ifdef HAVE_WINDOWS_H
		if(socket == INVALID_SOCKET)
#else
		if(newSocket == -1)
#endif
		{   
			printf("Cannot accept socket \n");
			return;
		}
		TCPHandler *tcpHandler = new TCPHandler(channel, newSocket);
		thread.start((Runnable *)tcpHandler, 0);
	}
}



TCPChannel::TCPChannel(int idx):CommunicationChannel(idx)
{
#ifdef HAVE_WINDOWS_H

    WSADATA wsaData;
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(1,1);

	if(!initialized)
	{
		initialized = true;
		WSAStartup(wVersionRequested,&wsaData);
	}

#endif
}

bool TCPChannel::connectSender(ChannelAddress *addr)
{
	IPAddress *tcpAddr = (IPAddress *)addr;
	tcpAddr->socket= socket(AF_INET, SOCK_STREAM, 0);
#ifdef HAVE_WINDOWS_H
	if (tcpAddr->socket == INVALID_SOCKET) return false;
#else
	if (tcpAddr->socket == -1) return false;
#endif
	printf("CONNETING TO %s port %d\n", tcpAddr->ipAddress, tcpAddr->port);
	if(connect(tcpAddr->socket, (struct sockaddr *)&tcpAddr->sin, sizeof(tcpAddr->sin)))
	{
#ifdef HAVE_WINDOWS_H
		int error = WSAGetLastError();
		switch(error)
		{
			case WSANOTINITIALISED: printf("WSAENETDOWN\n"); break;
			case WSAENETDOWN: printf("WSAENETDOWN\n"); break; 
			case WSAEADDRINUSE: printf("WSAEADDRINUSE\n"); break;
			case WSAEINTR : printf("WSAEINTR\n"); break;
			case WSAEINPROGRESS: printf("WSAEINPROGRESS\n"); break;
			case WSAEALREADY: printf("WSAEALREADY\n"); break;
			case WSAEADDRNOTAVAIL: printf("WSAEADDRNOTAVAIL\n"); break;
			case WSAEAFNOSUPPORT: printf("WSAEAFNOSUPPORT\n"); break;
			case WSAECONNREFUSED : printf("WSAECONNREFUSED\n"); break;
			case WSAEFAULT : printf("WSAEFAULT\n"); break;
			default: printf("BOH\n");
		}
#endif
		return false;
	}
	printf("CONNECTED\n");
	return true;






}

bool TCPChannel::connectReceiver(ChannelAddress *address)
{
	char *ipAddress = ((IPAddress *)address)->ipAddress;
	int port = ((IPAddress *)address)->port;


	int addrSize = sizeof(struct sockaddr_in), retAddrSize = 0;
	struct sockaddr_in inAddress, retAddress;
	if((tcpSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		printf("Error creating socket\n");
		return false;
	}
	memset((char *)&inAddress, 0, addrSize);
	memset((char *)&retAddress, 0, addrSize);
	inAddress.sin_family = AF_INET;
	inAddress.sin_port = htons(port);
#ifdef HAVE_WINDOWS_H
	inAddress.sin_addr.s_addr = INADDR_ANY;
	if(bind(tcpSocket, (SOCKADDR *)&inAddress, addrSize) != 0)
#else
	inAddress.sin_addr.s_addr = INADDR_ANY;
	if(bind(tcpSocket, (struct sockaddr *)&inAddress, addrSize) != 0)
#endif
	{   
		printf("Cannot bind socket at port %d\n", port);
		return false;
	}

	if(listen(tcpSocket, 5) != 0)
	{   
		printf("Cannot listen socket at port %d\n", port);
		return false;
	}

	TCPServer *tcpServer = new TCPServer(this, tcpSocket);
	thread.start(tcpServer, 0);
	return true;
}


bool TCPChannel::sendMessage(ChannelAddress *addr, char *buf, int bufLen, char type)
{
	int socket = ((IPAddress *)addr)->socket;

	if(socket == -1) //Not connected yet
	{
		if(!connectSender(addr))
			return false; //Still unsuccesful
		socket = ((IPAddress *)addr)->socket;
	}
	int convLen = fromNative(bufLen);
	send(socket, &type, 1, 0);
	send(socket, &thisIdx, 1, 0);
	send(socket, (char *)&convLen, sizeof(int), 0); 
	send(socket, buf, bufLen, 0);
	return true;
}


unsigned int TCPChannel::fromNative(int n)
{
	return htonl(n);
}

int TCPChannel::toNative(unsigned int n)
{
	return ntohl(n);
}


