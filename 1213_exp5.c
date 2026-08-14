#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
int sockfd;
char message[100], buffer[100];
struct sockaddr_in serverAddr;
socklen_t addr_size;
// Create UDP socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0)
{
printf("Socket creation failed\n");
return 1;
}
// Configure server address
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(1213);
serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
printf("Enter message: ");
fgets(message, sizeof(message), stdin);
// Send message to server
sendto(sockfd, message, strlen(message), 0,
(struct sockaddr *)&serverAddr, sizeof(serverAddr));
// Receive response from server
addr_size = sizeof(serverAddr);
int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
(struct sockaddr *)&serverAddr, &addr_size);
buffer[n] = '\0';
printf("Server Response: %s\n", buffer);
// Close socket
close(sockfd);
return 0;
}
