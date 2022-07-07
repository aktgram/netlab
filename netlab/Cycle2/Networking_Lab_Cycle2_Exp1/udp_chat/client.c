#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 6969;

    int sock_handler;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char msg[1024];
    int n;

    sock_handler = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_handler < 0){
        perror("Socket error!\n");
        exit(1);
    }
    printf("UDP server socket created\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    memset(&client_addr, '\0', sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

        int len = sizeof(server_addr);
    // while(1){

        char* hello = "Hello from client!";
        sendto(sock_handler, (char *)hello, strlen(hello), MSG_CONFIRM, (struct sockaddr*)&server_addr, len);
        printf("Client: %s\n", hello);

        n = recvfrom(sock_handler, (char *)msg, 1024, MSG_WAITALL, (struct sockaddr*)&server_addr, &len);
        msg[n] = '\0';
        printf("Server: %s\n", msg);

        close(sock_handler);


    // }

    return 0;
}