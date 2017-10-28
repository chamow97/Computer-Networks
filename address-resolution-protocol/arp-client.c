//ARP Client

/*----------------------------------------------------------*/

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*----------------------------------------------------------*/

int main(int argc, char **argv)
{
	int socketFd;
	struct sockaddr_in serverAddress;
	char buffer[1000];
	int i;
	/*----------------------------------------------------------*/
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	printf("\n\n\t\t ARP Client\n\t\t --- -----");
	if(socketFd < 0)
	{
		perror("\n\n\t\t Unable to create socket!");
		return 0;
	}
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);
	connect(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	printf("\n\n\t\t Enter IP to be searched for: ");
	scanf("%s", &buffer);
	write(socketFd, buffer, sizeof(buffer));
	while(1)
	{
		read(socketFd, buffer, sizeof(buffer));
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t\t Server terminated the connection!");
			break;
		}
		printf("\n\n\t\t Corresponding MAC is: %s", buffer);
		printf("\n\n\t\t Enter IP to be searched for: ");
		scanf("%s", &buffer);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			write(socketFd, buffer, sizeof(buffer));
			printf("\n\n\t\t You terminated the connection!");
			break;
		}
		write(socketFd, buffer, sizeof(buffer));
	}
	close(socketFd);
}