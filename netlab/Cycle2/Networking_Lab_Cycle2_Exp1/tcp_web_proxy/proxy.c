/*
   C socket server example
*/

#include <arpa/inet.h> //inet_addr
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h> //write
#include <string.h> //strlen
#include <sys/socket.h>
#include <unistd.h> //write

char ip[256];
char buffer[10000];
char m_hostname[100];

void get_html(char *url, char *hostname);
int resolve_ip(char *hostname);
int get_hostname(char *hostname);

int main(int argc, char *argv[]) {
  int socket_desc, client_sock, c, read_size;
  struct sockaddr_in server, client;
  char client_message[2000];

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("[main] Could not create socket");
  }
  // puts("Socket created");

  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.76");
  server.sin_port = htons(8890);

  // Bind
  if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
    // print the error message
    perror("bind failed. Error");
    return 1;
  }
  puts("bind done");

  // Listen
  listen(socket_desc, 3);

  // Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);

  // accept connection from an incoming client
  client_sock =
      accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
  if (client_sock < 0) {
    perror("accept failed");
    return 1;
  }
  puts("Connection accepted");

  // Receive a message from client
  while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
    printf("%s", client_message);
    // Send the message back to client
    char method[100];
    char hostname[500];
    char rest[1000];

    sscanf(client_message, "%s %s %s", method, hostname, rest);

    printf("---- CLIENT -----\n");

    printf("[main] method : %s\n", method);
    printf("[main] hostname : %s\n", hostname);
    printf("[main] rest : %s\n", rest);

    get_hostname(hostname);
    get_html(hostname, m_hostname);

    write(client_sock, buffer, strlen(buffer));
  }

  if (read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  } else if (read_size == -1) {
    perror("recv failed");
  }

  return 0;
}

void get_html(char *url, char *hostname) {

  resolve_ip(hostname);

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  int n;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("[-]Socket error");
    exit(1);
  }

  printf("[main] TCP Socket Created \n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(80);
  addr.sin_addr.s_addr = inet_addr(ip);

  int null = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  printf("[main] Connected to the server.\n");

  /*

              GET http://example.com/ HTTP/1.1
              Host: example.com
              User-Agent: curl/7.58.0

  */

  sprintf(buffer,
          "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: curl/7.58.0\r\n\r\n", url,
          hostname);
  // sprintf(buffer, "GET http://example.com/ HTTP/1.1\r\nHost:
  // example.com\r\nUser-Agent: curl/7.58.0\r\n\r\n");

  printf("[get_html] Buffer to send is : %s\n", buffer);
  send(sock, buffer, sizeof(buffer), 0);

  bzero(buffer, 10000);
  recv(sock, buffer, sizeof(buffer), 0);

  printf("[get_html] Got the html :)\n");
}

int resolve_ip(char *hostname) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;

  struct addrinfo *res;

  int ret = getaddrinfo(hostname, NULL, &hints, &res);
  if (ret != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
    return -1;
  }
  getnameinfo(res->ai_addr, res->ai_addrlen, ip, sizeof(ip), NULL, 0,
              NI_NUMERICHOST);
  printf("[resolve_ip] Resolved ip address is : %s\n", ip);
  return 0;
}

int get_hostname(char *hostname) {
  // const char text[] = "http://192.168.0.2:8888/servlet/rece";
  // char ip[100];
  int port = 80;
  char page[100];
  sscanf(hostname, "http://%99[^/]/%99[^\n]", m_hostname, page);
  printf("[get_hostname] hostname : %s\n", m_hostname);
  // printf("ip = \"%s\"\n", ip);
  // printf("port = \"%d\"\n", port);
  // printf("page = \"%s\"\n", page);
  return 0;
}
