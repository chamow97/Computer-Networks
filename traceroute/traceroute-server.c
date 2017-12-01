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
//assume
#define maximumNodes 50
int adjMatrix[maximumNodes][maximumNodes];
int parent[maximumNodes];
int depth[maximumNodes];
int nodeCount, edgeCount;
int i, j; //loop var

/*-------------------------------------------------------*/

void clearValues()
{
	for(i = 0; i < maximumNodes; i++)
	{
		parent[i] = 0;
		depth[i] = 0;
	}
}

/*-------------------------------------------------------*/

void getInput()
{
	printf("\n\n\t\t Enter number of Nodes and Edges: ");
	scanf("%d %d", &nodeCount, &edgeCount);
	printf("\n\n\t\t Enter the edges: ");
	for(i = 0; i < edgeCount; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		adjMatrix[u][v] = 1;
		adjMatrix[v][u] = 1;
	}
}

/*-------------------------------------------------------*/

void depthFirstSearch(int source)
{
	printf("%d ", source);
	for(i = 0; i < maximumNodes; i++)
	{
		if(adjMatrix[source][i] == 1 && parent[i] == 0)
		{
			parent[i] = source;
			depth[i] = 1 + depth[source];
			depthFirstSearch(i);
		}
	}
}

/*-------------------------------------------------------*/

int main(int argc, char **argv)
{
	socklen_t len;
	struct sockaddr_in serverAddress, clientAddress;
	int length, sockFd, connFd;
	char buffer[1000]; 
	int u = 0, v = 0, pointer = 0, counter = 0;
	
	/*-------------------------------------------------------*/

	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockFd < 0)
	{
		perror("\n\n\t\t Socket Error!");
		return 0;
	}
	printf("\n\n\t\t\t TRACEROUTE SERVER \n\t\t\t ---------- ------\n");
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(5000);
	bind(sockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	getInput();
	listen(sockFd, 0);
	len = sizeof(clientAddress);
	connFd = accept(sockFd, (struct sockaddr *)&clientAddress, &len);
	while(1)
	{
		read(connFd, buffer, sizeof(buffer));
		if(strcmp(buffer, "Goodbye") == 0)
		{
			printf("\n\n\t Client Terminated the connection!");
			break;
		}
		for(i = 0; buffer[i] != ' '; i++)
		{
			u = (u * 10) + (buffer[i] - '0');
		}
		i++;
		for(; buffer[i] != '\0'; i++)
		{
			v = (v * 10) + (buffer[i] - '0');
		}
		printf("\n\n\t Client asked for a path bewtween %d and %d .", u, v);
		clearValues();
		for(i = 0; i < 50; i++)
		{
			buffer[i] = ' ';
		}
		depthFirstSearch(v);
		if(parent[u] == 0)
		{
			strcpy(buffer, "\n\n\t No such path!");
		}
		else
		{
			pointer = u;
			counter = 0;
			int ptr = 0;
			buffer[0] = '\0';
			while(pointer != v)
			{
				strcat(buffer, pointer + '0');
				strcat(buffer, "-");
				pointer = parent[pointer];
			}
			strcat(buffer, v + '0');
			strcat(buffer, "-");			
			//strrev(string);
		}
		write(connFd, buffer, sizeof(buffer));
	}
	//close socket
	close(connFd);
	close(sockFd);
	return 0;
}
