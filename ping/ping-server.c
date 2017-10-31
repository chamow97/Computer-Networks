//ping
//time between message
/*-------------------------------------------------------*/

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*-------------------------------------------------------*/
int main(int argc, char **argv)
{
	socklen_t len;
	struct sockaddr_in serverAddress, clientAddress;
	int length, sockFd, connFd;
	char buffer[1000]; 
	int ptr = 0;
	
	/*-------------------------------------------------------*/
	printf("\n\n\t\t\t PING - SERVER\n\t\t\t ----   ------");
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFd < 0)
	{
		perror("\n\n\t\t Socket Error!");
		return 0;
	}
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);
	bind(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(sockFd, 0);
	len = sizeof(clientAddress);
	connFd = accept(sockFd, (struct sockaddr *)&clientAddress, &len);
	if(connFd<0)
	{
		perror("connection error\n");
		return 0;
	}
	while(ptr < 10)
	{
		ptr++;
		read(connFd, buffer, sizeof(buffer));
		printf("\n\t\t Client Pings - %d", ptr);
		write(connFd, buffer, sizeof(buffer));
		
	}

	close(connFd);
	close(sockFd);
	return 0;
}
	