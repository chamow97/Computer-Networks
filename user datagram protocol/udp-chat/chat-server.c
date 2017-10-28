//UDP chat server
/*-------------------------------------------------------*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

/*-------------------------------------------------------*/

int main(int argc, char **argv)
{
	socklen_t len;
	int sockFd, connectionFd, n;

	struct sockaddr_in serverAddress, clientAddress;

	char buffer[1000];

	printf("\n\n\t\t\t UDP CHAT Server\n\t\t\t --- ---- ------");
	/*-------------------------------------------------------*/

	sockFd = socket(AF_INET, SOCK_DGRAM, 0);

	//if not created
	if(sockFd < 0)
	{
		perror("\n\t\t Cannot create socket!");
		return 0;
	}
	//initialisation
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);

	//binding the socket
	bind(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

	
	len = sizeof(clientAddress);

	//chat is infinite echo
	while(1)
	{
		recvfrom(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, &len);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t\t Client Terminated the connection!\n");
			break;
		}

		printf("\n\n\t\t Client: %s\n", buffer);
		printf("\n\n\t\t Enter message: ");
		gets(buffer);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			sendto(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, len);
			printf("\n\n\t\t You terminated the connection!\n");
			break;
		}
		sendto(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, len);

	}

	close(sockFd);
	
	return 0;
}