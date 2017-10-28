//TCP chat Client

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
	char string[1000], buffer[1000];
	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	//if socket is not created
	printf("\n\n\t\t\t TCP CHAT - Client\n\t\t\t --- ----   -----");

	if(sockFd < 0)
	{
		perror("\n\n\t Socket not created!");
	}

	//clear
	bzero(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);

	//create a connection
	connect(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	printf("\n\n\t\t Enter a message: ");
	gets(string);
	write(sockFd, string, sizeof(string));
	//chat is prolonged echo
	while(1)
	{
		read(sockFd, buffer, sizeof(buffer));
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
			write(sockFd, buffer, sizeof(buffer));
			printf("\n\n\t\t You terminated the connection!\n");
			break;
		}
		write(sockFd, buffer, sizeof(buffer));
	}
	//close the socket
	close(sockFd);
	
	return 0;
}