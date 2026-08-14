#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

struct Student {
    char name[100];
    char prn[30];
    float marks[5];
};

int main() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    struct Student student;
    float total = 0;
    float percentage;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    printf("UDP Server is waiting for client...\n");

    recvfrom(server_fd, &student, sizeof(student), 0,
             (struct sockaddr *)&client_addr, &addr_len);

    printf("\nStudent Details Received:\n");
    printf("Name: %s\n", student.name);
    printf("PRN: %s\n", student.prn);

    for (int i = 0; i < 5; i++) {
        printf("Subject %d Marks: %.2f\n",
               i + 1, student.marks[i]);

        total += student.marks[i];
    }

    percentage = total / 5.0;

    printf("\nTotal Marks = %.2f\n", total);
    printf("Percentage = %.2f%%\n", percentage);

    sendto(server_fd, &percentage, sizeof(percentage), 0,
           (struct sockaddr *)&client_addr, addr_len);

    printf("Percentage sent to client.\n");

    close(server_fd);

    return 0;
}
