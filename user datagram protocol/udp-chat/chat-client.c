//UDP chat Client

/*-------------------------------------------------------*/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

/*-------------------------------------------------------*/

int main(int agrc, char **argv)
{
	int sockFd;
	struct sockaddr_in serverAddress;
	char buffer[1000];
	sockFd = socket(AF_INET, SOCK_DGRAM, 0);
	socklen_t len;
	//if socket is not created
	printf("\n\n\t\t\t UDP CHAT - Client\n\t\t\t --- ----   -----");

	if(sockFd < 0)
	{
		perror("\n\n\t Socket not created!");
	}

	//clear
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);
	len = sizeof(serverAddress);
	//create a connection
	printf("\n\n\t\t Enter a message: ");
	gets(buffer);
	sendto(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, len);
	//chat is prolonged echo
	while(1)
	{
		recvfrom(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, &len);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t\t Server terminated the connection!");
			break;
		}
		printf("\n\n\t\t Server: %s", buffer);
		printf("\n\n\t\t Enter a message: ");
		gets(buffer);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			sendto(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, len);
			printf("\n\n\t\t You terminated the connection!\n");
			break;
		}
		sendto(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, len);
	}
	//close the socket
	close(sockFd);
	
	return 0;
}