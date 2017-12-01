//traceroute
//given a source and destination, find the minimum hop
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

	
	/*-------------------------------------------------------*/
	printf("\n\n\t\t\t TRACEROUTE CLIENT \n\t\t\t ---------- ------");
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
	connect(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	printf("\n\n\t Enter source and destination: ");
	gets(buffer);
	write(sockFd, buffer, sizeof(buffer));
	while(1)
	{
		read(sockFd, buffer, sizeof(buffer));
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t Server terminated the connection!");
			break;
		}
		printf("%s", buffer);
		printf("\n\n\t Enter source and destination: ");
		gets(buffer);
		if(strcmp(buffer, "Goodbye") == 0)
		{
			write(sockFd, buffer, sizeof(buffer));
			printf("\n\n\t You terminated the connection!");
			break;
		}
		write(sockFd, buffer, sizeof(buffer));		
	}
	close(sockFd);
	return 0;
}
