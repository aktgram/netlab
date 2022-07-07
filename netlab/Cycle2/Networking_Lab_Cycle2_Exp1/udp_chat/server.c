#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

void revstr(char *str1)  
{  
    // declare variable  
    int i, len, temp;  
    len = strlen(str1); // use strlen() to get the length of str string  
      
    // use for loop to iterate the string   
    for (i = 0; i < len/2; i++)  
    {  
        // temp variable use to temporary hold the string  
        temp = str1[i];  
        str1[i] = str1[len - i - 1];  
        str1[len - i - 1] = temp;  
    }  
}

void string_upper(char* str){
    for (int i=0; i<strlen(str); i++)
        str[i] = toupper(str[i]);
}

int main(){
    char *ip = "127.0.0.1";
    int port = 6969;

    int server_sock_handler, client_sock_handler;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char msg[1024];
    int n;

    server_sock_handler = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sock_handler < 0){
        perror("Socket error!\n");
        exit(1);
    }
    printf("UDP server socket created\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    memset(&client_addr, '\0', sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock_handler, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0){
        perror("Binding failed!\n");
        exit(1);
    }
    printf("Bind to port number: %d\n", port);

    int len = sizeof(client_addr);

    // while(1){
        n = recvfrom(server_sock_handler, (char *)msg, 1024, MSG_WAITALL, (struct sockaddr*)&client_addr, &len);
        msg[n] = '\0';
        printf("Client: %s\n", msg);

        // Server reply
        // char* hello = "Hello from server!";
        char *rev_msg;
        strcpy(rev_msg, msg);
        revstr(rev_msg);

        for (int i=0; i<strlen(msg); i++)
            msg[i] = toupper(msg[i]);
        
        sendto(server_sock_handler, msg, strlen(msg), MSG_CONFIRM, (struct sockaddr*)&client_addr, len);
        printf("Server: %s\n", msg);

    // }

    return 0;
}