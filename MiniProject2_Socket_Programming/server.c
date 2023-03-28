// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char* str, int start){
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}

int get_int(char* str, int start){
    int i, res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char copy[1024] = {0};
	char *hello = "Hello\n";
	char ans[1024] = {0};
	int n;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

    while(1){
		recv(new_socket, buffer, 1024, 0);			//recieve command from client
		strcpy(copy, buffer);						//copy is a char array same as buffer to be the input of strtok
		int a, b;
		char* command = strtok(copy, " ");			//extract the command part and 
		if(strcmp(command, "add") == 0){			//ADD : scan the string to extract two variable and add them to ans
			sscanf(buffer, "add %d %d", &a, &b);			
			n = sprintf(ans, "%d\n", a + b);
		}
		else if(strcmp(command, "abs") == 0){		//ABS : scan the string to extract variable
			sscanf(buffer, "abs %d\n", &a);
			if(a < 0)								//if a is negative number then turn into positive 
				a  = -a;
			n = sprintf(ans, "%d\n", a);
		}
		else if(strcmp(command, "mul") == 0){		//MUL : scan the string to extract two variable and multiply them to ans
			sscanf(buffer, "mul %d %d", &a, &b);
			n = sprintf(ans, "%d\n", a * b);		
		}
		else if(strcmp(command, "kill\n") == 0){	//KILL : send kill message to client and break the loop to end the code
			n = sprintf(ans, "kill\n");	
			send(new_socket, ans , n , 0 );
			break;
		}
		else{										//Not Support Command : answer "Hello"
			n = sprintf(ans, "Hello\n");
		}
		send(new_socket , ans , sizeof(ans) , 0 );	//send the answer as string to client
    }

	return 0;
}
