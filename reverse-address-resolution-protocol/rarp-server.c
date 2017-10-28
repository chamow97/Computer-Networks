//RARP Server

/*----------------------------------------------------------*/

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*----------------------------------------------------------*/

int main(int argc, char **argv)
{
	char ipAddress[100][1000], macAddress[100][1000];
	socklen_t len;
	struct sockaddr_in serverAddress, clientAddress;
	char buffer[1000];
	int sockFd, connectionFd, length;
	int i;
	int found = 0;
	/*----------------------------------------------------------*/
	printf("\n\n\t\t\t RARP SERVER\n\t\t\t ---- ------");
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFd < 0)
	{
		perror("\n\n\t\t Socket Not Created!");
		return 0;
	}
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);
	bind(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	listen(sockFd, 0);
	len = sizeof(clientAddress);
	printf("\n\n\t\t Enter number of entries: ");
	scanf("%d", &length);
	for(i = 1; i <= length; i++)
	{
		printf("\n\t Enter IP and MAC of Entry %d: ", i);
		scanf("%s %s", &ipAddress[i], &macAddress[i]);
	}
	connectionFd = accept(sockFd, (struct sockaddr *)&clientAddress, &len);
	while(1)
	{
		read(connectionFd, buffer, sizeof(buffer));
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t\t Client Terminated!");
			break;
		}
		printf("\n\n\t\t Client Requested IP for MAC: %s", buffer);
		for(i = 1; i <= length; i++)
		{
			if(strcmp(buffer, macAddress[i]) == 0)
			{
				found = 1;
				strcpy(buffer, ipAddress[i]);
				break;
			}
		}
		if(found != 1)
		{
			strcpy(buffer, "\n\n\t\t No Such MAC found!");
		}
		write(connectionFd, buffer, sizeof(buffer));
		found = 0;
		
	}
	//close the socket
	close(connectionFd);
	close(sockFd);
}