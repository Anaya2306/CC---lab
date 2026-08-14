#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

struct Student {
    char name[100];
    char prn[30];
    float marks[5];
};

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    struct Student student;
    char buffer[BUFFER_SIZE];

    struct timeval start, end;
    double processing_time;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter Student Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("Enter PRN/Roll No: ");
    fgets(student.prn, sizeof(student.prn), stdin);
    student.prn[strcspn(student.prn, "\n")] = '\0';

    printf("\nEnter marks of 5 subjects:\n");

    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &student.marks[i]);
    }

    
    gettimeofday(&start, NULL);

    if (connect(client_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        return 1;
    }

    send(client_fd, &student, sizeof(student), 0);

    recv(client_fd, buffer, BUFFER_SIZE, 0);

    
    gettimeofday(&end, NULL);

    processing_time =
        (end.tv_sec - start.tv_sec) +
        (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("\n----- Student Result -----\n");
    printf("Name        : %s\n", student.name);
    printf("PRN/Roll No : %s\n", student.prn);
    printf("Percentage  : %s%%\n", buffer);

    printf("\nProcessing Time = %.6f seconds\n",
           processing_time);

    close(client_fd);

    return 0;
}
