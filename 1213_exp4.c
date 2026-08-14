#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 1213
int main()
{
int server_socket;
char buffer[1024];
struct sockaddr_in server_addr, client_addr;
socklen_t client_len = sizeof(client_addr);
// Create UDP socket
server_socket = socket(AF_INET, SOCK_DGRAM, 0);
if (server_socket < 0)
{
perror("Socket creation failed");
return 1;
}
// Configure server address
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
// Anaya Shende
//24070521213
if (bind(server_socket, (struct sockaddr *)&server_addr,
sizeof(server_addr)) < 0)
{
perror("Bind failed");
close(server_socket);
return 1;
}
printf("UDP Server is running on port %d...\n", PORT);
// Receive message from client
int n = recvfrom(server_socket, buffer, sizeof(buffer) - 1, 0,
(struct sockaddr *)&client_addr, &client_len);
if (n < 0)
{
perror("Receive failed");
close(server_socket);
return 1;
}
buffer[n] = '\0';
printf("Message from Client: %s\n", buffer);
// Send response to client
char *response = "Hello from UDP Server";
sendto(server_socket, response, strlen(response), 0,
(struct sockaddr *)&client_addr, client_len);
return 0;
}
