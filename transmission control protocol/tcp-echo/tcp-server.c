//TCP echo server
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

	printf("\n\n\t\t\t TCP Echo Server\n\t\t\t --- ---- ------");
	/*-------------------------------------------------------*/

	sockFd = socket(AF_INET, SOCK_STREAM, 0);

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

	listen(sockFd, 0);

	len = sizeof(clientAddress);
	connectionFd = accept(sockFd, (struct sockaddr *)&clientAddress, &len);

	n = read(connectionFd, buffer, sizeof(buffer));

	printf("\n\n\t\t Received Message: %s\n", buffer);

	write(connectionFd, buffer, sizeof(buffer));

	close(connectionFd);
	close(sockFd);
	return 0;
}