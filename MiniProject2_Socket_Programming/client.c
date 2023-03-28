// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	char ans[1024] = {0};

    usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

 	while(1){
		fgets(buffer, 1024, stdin);					//get the command
		if(buffer == "\n")
			break;
		send(sock, buffer, sizeof(buffer), 0 );		//send to the server
		int n = recv(sock, ans, sizeof(ans), 0);	//recieve the answer string
		if(strncmp(ans, "kill\n", 5) == 0){			//if answer is kill then break the loop 
			printf("\n");
			break;						
		}											//else print the answer
		else{
			printf("%s", ans);
		}
			
    }
	return 0;
}
