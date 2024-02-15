#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/sendfile.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server = {
		AF_INET,
		htons(8080),
		INADDR_ANY
	};
	
	bind(sockfd, &server, sizeof(server));	
	
	listen(sockfd, 10);

	int client_fd = accept(sockfd, 0, 0);

	char buffer[1024] = {0};

	recv(client_fd, buffer, sizeof(buffer), 0);

	// GET /file.html
	
	char* f = buffer + 5;
	*strchr(f, ' ') = 0;
	int openned_fd = open(f, O_RDONLY);
	sendfile(client_fd, openned_fd, 0, 1024);
	close(openned_fd);
	close(client_fd);
	close(sockfd);

	return 0;
}
