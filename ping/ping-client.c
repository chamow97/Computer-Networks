//ping
//given a source and destination, find the minimum hop
/*-------------------------------------------------------*/

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*-------------------------------------------------------*/

int main(int argc, char **argv)
{

	socklen_t len;
	struct sockaddr_in serverAddress, clientAddress;
	int length, sockFd, connFd;
	char buffer[1000]; 
	char string[1000];
	int ptr = 0;
	long double averageTime = 0.0;
	long double currentTime = 0.0;
	
	/*-------------------------------------------------------*/
	printf("\n\n\n\t\t\t PING - CLIENT\n\t\t\t ----   -----");
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
	struct timespec ts;
	strcpy(buffer, "\n\n\t\t Ping Messages! - ");
	while(ptr < 10)
	{
		ptr++;
		timespec_get(&ts, TIME_UTC);
		strftime(string, sizeof(string), "%D %T", gmtime(&ts.tv_sec));
		currentTime = (ts.tv_nsec + ts.tv_sec * 1e9);
		write(sockFd, buffer, sizeof(buffer));
		read(sockFd, buffer, sizeof(buffer));
		timespec_get(&ts, TIME_UTC);
		strftime(string, sizeof(string), "%D %T", gmtime(&ts.tv_sec));
		currentTime = -currentTime + ts.tv_nsec + ts.tv_sec * 1e9;
		averageTime = (averageTime + currentTime);
		printf("\n\t\t RTT for Packet: %d is: %.12Lf", ptr, currentTime);
	}
	averageTime /= 10;
	printf("\n\n\t\t Average RTT is: %.12Lf", averageTime);
	printf("\n\n");
	close(sockFd);
	return 0;
}
	